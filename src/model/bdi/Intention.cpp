/*
 * Intention.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/bdi/Intention.h>
#include <model/bdi/Belief.h>
#include <model/bdi/BeliefSet.h>
#include <model/bdi/Desire.h>
#include <model/agents/MainAgent.h>
#include <model/agents/Agent.h>
#include <model/agents/SearchAgent.h>
#include <model/agents/WorkingAgent.h>
#include <model/fipa/Package.h>
#include <model/agents/tools/PathFindingTree.h>

#include <iostream>
#include <sstream>

using namespace std;

Intention::Intention(const Agent& agent, BeliefSet& beliefSet, Desire& desire) :
	m_beliefSet(&beliefSet), m_desire(&desire), m_agent(
	        &dynamic_cast<MainAgent&>(const_cast<Agent&>(agent))) {
	m_currentGoal = "Initial_Exploration";
	loopCount_ = 0;
}

Intention::~Intention() {
}

void Intention::update() {
	cout << "Current Desire: " << m_currentGoal << endl;

	if (!(*m_desire)["50_Percent_Explored"]) {
		exploreMap();
	} else {
		if (!(*m_desire)["100_Percent_Explored"]) {

			cout << "Mapa explorado" << endl;

			exploreMap();
		} else if (!(*m_desire)["Settlement_Place_Found"]) {
			cout << "Busca asentamiento" << endl;
			findOptimalLocation();
			if (m_beliefSet->exists("Best_Location")) {
				cout << "Se mueve al asentamiento" << endl;
				gotoOptimalLocation();
			} else {
				cout << "No existe lugar para el asentamiento" << endl;
				exit (1);
			}
		}

		if ((*m_desire)["Settlement_Place_Found"]
		                && !(*m_desire)["Resources_Gathered"]) {
			cout << "Busca recursos" << endl;
			gatherResources();
		}

		if ((*m_desire)["Resources_Gathered"]) {
			cout << "Construye asentamiento" << endl;
			buildSettlement();
		}

		if ((*m_desire)["Settlement_Built"]) {
			//TODO Fin Simulacion
		}
	}
}

void Intention::exploreMap() {
	Package* pack;

	if (m_currentGoal == "Initial_Exploration") {
		for (uint32_t i = 0; i < m_agent->getVAgents().size(); ++i) {
			if (m_agent->getVAgents()[i]->getState() == AVAILABLE) {
				pack = new Package(m_agent->getNameAgent(),
				                   m_agent->getVAgents()[i]->getNameAgent(),
				                   DIRECTION_SEARCH);
				vector<string> packContent;
				// Dirección a la que se envía el agente (i * 2). Ver Tools.h
				cout << "Enviando agente "
				          << directionEnumToString(static_cast<Direction>(i * 2))
				          << endl;
				packContent.push_back(
				        directionEnumToString(static_cast<Direction>(i * 2)));
				pack->setContent(packContent);
				m_agent->getVAgents()[i]->readFIPAPackage(pack);
			}

			m_currentGoal = "Awaiting_Exploration_End";
		}
	}

	if (m_currentGoal == "Start_Sector_Exploration") {
		sectorExploration();
	}

	if (m_currentGoal == "Awaiting_Exploration_End") {
		if (m_beliefSet->exists("NORTH") && m_beliefSet->exists("SOUTH")
		                && m_beliefSet->exists("EAST") && m_beliefSet->exists("WEST")) {
			m_currentGoal = "Start_Sector_Exploration";
			m_beliefSet->remove("NORTH");
			m_beliefSet->remove("SOUTH");
			m_beliefSet->remove("EAST");
			m_beliefSet->remove("WEST");
		}
	}

	if (m_beliefSet->exploredPercentage() >= 0.5) {
		if (!(*m_desire)["50_Percent_Explored"]) {
			m_desire->set("50_Percent_Explored", true);
		}
	}

	if (m_beliefSet->exploredPercentage() >= 0.9) {
		m_desire->set("100_Percent_Explored", true);
	}

	checkSectorsExplorationRatio();
	cout << "Porcentaje explorado: " << m_beliefSet->exploredPercentage()
	          << endl;
}

void Intention::findOptimalLocation() {
	const uint32_t SECTORS = ((MAP_WIDTH * MAP_WIDTH) / (SECTOR_SIZE * SECTOR_SIZE));
	const float EXPLORED_RATIO = 0.9;
	uint32_t water;
	uint32_t food;
	uint32_t metal;
	uint32_t mineral;
	uint32_t ground;
	BYTE terrainValue;
	BYTE resourceValue;
	float sectorValue;

	for (uint32_t i = 0; i < SECTORS; ++i) {
		sectorValue = 0.0;
		water = 0;
		food = 0;
		metal = 0;
		mineral = 0;
		ground = 0;
		cout << m_beliefSet->getSectorExploredRatio(i) << endl;
		if (m_beliefSet->getSectorExploredRatio(i) >= EXPLORED_RATIO) {
			uint32_t limitJ = (i / SECTOR_SIZE) * SECTOR_SIZE + SECTOR_SIZE;
			uint32_t limitK = (i % SECTOR_SIZE) * SECTOR_SIZE + SECTOR_SIZE;

			for (uint32_t j = (i / SECTOR_SIZE) * SECTOR_SIZE; j < limitJ; ++j) {
				for (uint32_t k = (i % SECTOR_SIZE) * SECTOR_SIZE; k < limitK; ++k) {
					if (m_beliefSet->getKnownMapCell(j, k)) {
						terrainValue = m_beliefSet->map()->cellTerrainType(j, k);
						resourceValue = m_beliefSet->map()->cellResourceType(j, k);

						if (terrainValue == TERRAIN_GROUND) {
							switch (resourceValue) {
							case RESOURCE_FOOD:
								++food;
								break;

							case RESOURCE_METAL:
								++metal;
								break;

							case RESOURCE_MINERAL:
								++mineral;
								break;
							}
							++ground;
						} else if (terrainValue == TERRAIN_WATER) {
								++water;
						}
					}
				}
			}

			if (ground >= ((SECTOR_SIZE * SECTOR_SIZE) * 3 / 4)) {
				sectorValue += 4 * water + 2 * food + mineral + metal;
			}

			m_beliefSet->setSectorSettlementFactor(i, sectorValue);
		}
	}
	uint32_t bestSector;
	float bestFactor;

	bestSector = 0;
	bestFactor = -1.0;

	for (uint32_t i = 0; i < SECTORS; ++i) {
		if ( m_beliefSet->getSectorSettlementFactor(i) > bestFactor) {
			bestFactor = m_beliefSet->getSectorSettlementFactor(i);
			bestSector = i;
		}
	}

	stringstream ss;
	ss << bestSector;

	// Se introduce la creencia Best_Location con el sector elegido
	m_beliefSet->add(string("Best_Location"), new Belief(ss.str().c_str()));
}

void Intention::gatherResources() {
//TODO: Recolectar recursos
}

void Intention::buildSettlement() {
	m_desire->set("Settlement_Built", true);
}

void Intention::checkSectorsExplorationRatio() {
	//TODO Media de los sectores
	const float CELL_VALUE = 0.01;
	int32_t cell;
	cell = 0;
	m_beliefSet->resetSectorExploredRatio();

	for (int32_t i = 0; i < MAP_WIDTH; ++i) {
		for (int32_t j = 0; j < MAP_WIDTH; ++j) {
			if (m_beliefSet->getKnownMap()[i][j]) {
				cell = (((i / SECTOR_SIZE) * SECTOR_SIZE) + (j / SECTOR_SIZE));
				m_beliefSet->sumSectorExploredRatio(cell, CELL_VALUE);
			}
		}
	}
}

void Intention::checkSectorsFactor() {

}

void Intention::sectorExploration() {
	const uint32_t SECTORS = ((MAP_WIDTH * MAP_WIDTH) / (SECTOR_SIZE * SECTOR_SIZE));
	const uint32_t SECTOR_OFFSET = MAP_WIDTH / SECTOR_SIZE;
	const float EXPLORED_RATIO = 0.9;
	bool sectorFound = false;
	bool globlalSectorFound = false;
	int row;
	int col;
	Point p;
	Point bestPoint;
	uint32_t bestDistance;
	uint32_t distance;
	stringstream ss;
	bestDistance = 99999;
	float explorationRatioAux;
	std::cout << "ANALIZANDO SECTORES DE TERRENO" << std::endl;
	for (uint32_t i = 0; i < m_agent->getVAgents().size(); ++i) {
		sectorFound = false;
		if (m_agent->getVAgents()[i]->getState() == AVAILABLE) {
			for (uint32_t j = 0; j < SECTORS && !sectorFound; ++j) {
				ss << j;
				explorationRatioAux = m_beliefSet->getSectorExploredRatio(j);
				if (!m_beliefSet->exists(ss.str())
						&& explorationRatioAux <= EXPLORED_RATIO) {
					row = j / SECTOR_SIZE;
					col = j % SECTOR_SIZE;
					row *= SECTOR_SIZE;
					col *= SECTOR_SIZE;

					p.first = row;
					p.second = col;
					bestPoint = p;

					for (int k = 0; k < 2; ++k) {
						for (int l = 0; l < 2; ++l) {
							p.first += k * SECTOR_SIZE;
							p.second += l * SECTOR_SIZE;
							distance = euclideanDistance(m_agent->getVAgents()[i]->getPosition(), p);

							if (distance <= bestDistance) {
								if ((bestPoint.first > 0 && bestPoint.first < MAP_WIDTH - 1)
										&& (bestPoint.second > 0 && bestPoint.second < MAP_WIDTH - 1)) {
									if (((*(m_agent->getMap()))(bestPoint.first,
											bestPoint.second) & MASK_TERRAIN) == TERRAIN_GROUND
											&& m_agent->getKnownMap()[bestPoint.first][bestPoint.second]) {
										bestDistance = distance;
										bestPoint = p;
									}
								}
							}
						}
					}
					if ((bestPoint.first > 0 && bestPoint.first < MAP_WIDTH - 1)
							&& (bestPoint.second > 0 && bestPoint.second < MAP_WIDTH - 1)) {
						if (((*(m_agent->getMap()))(bestPoint.first,
								bestPoint.second) & MASK_TERRAIN) == TERRAIN_GROUND
								&& (m_agent->getKnownMap())[bestPoint.first][bestPoint.second]) {
							m_agent->sendToRoute(m_agent->getVAgents()[i]->getPosition(),
									Point(bestPoint.first, bestPoint.second),
									const_cast<Agent*>(m_agent->getVAgents()[i]),
									GO_SEARCHING_LOCATION);
							sectorFound = true;
							globlalSectorFound = true;
							loopCount_ = 0;
							if (explorationRatioAux >= m_beliefSet->getSectorExploredRatio(j)) {
								Belief* belief;
								belief = new Belief("EXPLORED");
								m_beliefSet->add(ss.str(), belief);
							}
						}
					}
				}
			}
		}
	}
	if (globlalSectorFound) {
		m_currentGoal = "Awaiting_Exploration_End";
	} else {
		++loopCount_;
	}
	if (loopCount_ > 500) {
		loopCount_ = 0;
		m_currentGoal = "END_SECOND_EXPLORATION";
		for (uint32_t i = 0; i < m_agent->getVAgents().size(); ++i) {
			m_agent->sendToRoute(m_agent->getVAgents()[i]->getPosition(),
					m_agent->getPosition(),const_cast<Agent*>(m_agent->getVAgents()[i]),
					GO_LOCATION);
		}
		m_desire->set("50_Percent_Explored", true);
		m_desire->set("100_Percent_Explored", true);
	}
}

void Intention::gotoOptimalLocation() {
	uint32_t sector;
	Point destination;
	PathFindingTree* tree;
	string tempRoute;

	sector = atoi((*(*m_beliefSet)["Best_Location"])().c_str());
	destination = *checkSectorCells(sector);
	tree = new PathFindingTree (*m_agent, m_agent->getPosition(), destination);

	if (tree->calculateHeuristicRoute()) {
		cout << "Moviendo al sector " << sector << " " << destination << endl;
		tempRoute = tree->getRoute();
		m_agent->followRoute(tempRoute);
		cout << tempRoute << endl;
		cin.get();

		if (tree != NULL) {
			delete tree;
			tree = NULL;
		}
		m_desire->set("Settlement_Place_Found", true);
	} else {
		cout << "NO HAY RUTA FINAL" << endl;
	}

//	if (m_beliefSet->map()->cellTerrainType(destination) == TERRAIN_GROUND &&
//			m_beliefSet->knownMapCell(destination.first, destination.second)) {
//		if (tree->calculateHeuristicRoute()) {
//			cout << "Moviendo al sector " << sector << " " << destination << hex <<
//					static_cast<int>(m_beliefSet->map()->cellTerrainType(destination) &
//					m_beliefSet->map()->cellResourceType(destination)) << endl;
//			temp += tree->getRoute();
//			cout << temp << endl;
//			cin.get();
//			m_agent->followRoute(temp);
//
//			if (tree != NULL) {
//				delete tree;
//				tree = NULL;
//			}
//
//			m_desire->set("Settlement_Place_Found", true);
//		} else {
//			cout << "NO HAY RUTA FINAL" << endl;
//		}
//	} else {
//		cout << "NO ES UN TERRENO ACCESIBLE" << endl;
//	}

}

const Point* Intention::checkSectorBoundaries(uint32_t sector) {
	Point upperLeft((sector / SECTOR_SIZE) * SECTOR_SIZE, (sector % SECTOR_SIZE) * SECTOR_SIZE);
	Point lowerRight(upperLeft.first + SECTOR_SIZE, upperLeft.second + SECTOR_SIZE);
	const uint32_t SECTOR_OFFSET = MAP_WIDTH / SECTOR_SIZE;
	const float EXPLORED_RATIO = 0.9;
	int32_t x;
	int32_t y;
	const int32_t TOP_LEFT_X = upperLeft.first - 1;
	const int32_t TOP_LEFT_Y = upperLeft. second - 1;
	const int32_t BOT_RIGHT_X = lowerRight.first + 1;
	const int32_t BOT_RIGHT_Y = lowerRight.second + 1;

	bool accessibleBoundingSectors;
	bool accessibleBoundary;
	accessibleBoundingSectors = false;
	accessibleBoundary = false;
	cout << "Comprobando sector " << sector << endl;

	// se comprueba si alguno de los sectores adyacentes ha sido explorado
	if (m_beliefSet->getSectorExploredRatio(sector - 1) >= EXPLORED_RATIO ||
	                m_beliefSet->getSectorExploredRatio(sector + 1) >= EXPLORED_RATIO ||
	                m_beliefSet->getSectorExploredRatio(sector - SECTOR_OFFSET) >= EXPLORED_RATIO ||
	                m_beliefSet->getSectorExploredRatio(sector + SECTOR_OFFSET) >= EXPLORED_RATIO) {
		accessibleBoundingSectors = true;
		cout << "Tiene un sector adyacente accesible" << endl;
	} else {
		cout << "No tiene sector adyacente accesible, saliendo" << endl;
		return new Point(-1, -1);
	}

	// TODO Añadir comprobación
	// Si los sectores adyacentes son accesibles pero el límite no, marcar como explorado
	if (accessibleBoundingSectors) {

	}

	// Se comprueba desde la esquina NW a la SE, no incluyendo las esquinas.
	for (x = upperLeft.first - 1; x <= lowerRight.first && !accessibleBoundary; ++x) {
		for (y = upperLeft.second - 1; y <= lowerRight.second && !accessibleBoundary; ++y) {
			if (!(x == upperLeft.first - 1 && y == upperLeft.second - 1)
			                || !(x == upperLeft.first - 1 && y == lowerRight.second + 1)
			                || !(x == upperLeft.second + 1 && y == lowerRight.first - 1)
			                || !(x == lowerRight.first + 1 && y == lowerRight.second + 1)) {
				cout << "Comprobando casilla " << Point(x, y) << endl;

				if (m_beliefSet->getKnownMapCell(x, y) && ((*m_agent->getMap())(x, y) & MASK_TERRAIN) == TERRAIN_GROUND) {
					cout << "Es accesible" << endl;
					accessibleBoundary = true;
				}
			}
		}
	}

	if (accessibleBoundary) {
		cout << "Devolviendo éxito " << Point(x, y) << endl;
		cin.get();
		return new Point(x, y);
	}

	cout << "No tiene ningún punto limítrofe accesible. Devolviendo fallo" << endl;
	return new Point(-1, -1);
}


const Point* Intention::checkSectorCells(uint32_t sector) {
	Point destination;
	Point center;
	Point closestToCenter;
	float distanceToCenter;
	float bestDistance;

	bestDistance = 99999.0;
	destination.first = (sector / SECTOR_SIZE) * SECTOR_SIZE;
	destination.second = (sector % SECTOR_SIZE) * SECTOR_SIZE;
	center.first = destination.first + 5;
	center.second = destination.second + 5;
	closestToCenter = destination;

	for (int32_t i = destination.first; i < destination.first + SECTOR_SIZE; ++i) {
		for (int32_t j = destination.second; j < destination.second + SECTOR_SIZE; ++j) {
			if (m_beliefSet->knownMapCell(i, j)) {
				if (m_beliefSet->map()->cellTerrainType(i, j) == TERRAIN_GROUND) {
					distanceToCenter = euclideanDistance(Point(i, j), center);
					if (distanceToCenter < bestDistance) {
						closestToCenter = Point(i, j);
						bestDistance = distanceToCenter;
					}
				}
			}
		}
	}

	return new Point(closestToCenter.first, closestToCenter.second);
}
