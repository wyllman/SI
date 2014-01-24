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

#include <iostream>
#include <sstream>

using namespace std;

Intention::Intention(const Agent& agent, BeliefSet& beliefSet, Desire& desire) :
	m_beliefSet(&beliefSet), m_desire(&desire), m_agent(
	        &dynamic_cast<MainAgent&>(const_cast<Agent&>(agent))) {
	m_currentGoal = "Initial_Exploration";
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
			gotoOptimalLocation();
		}

		if (m_beliefSet->exists("Optimal_Location")
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
	bool water = false, food = false, metal = false, mineral = false;
	bool elevation = false;
	BYTE terrainValue;
	BYTE resourceValue;
	float sectorValue = 0.0;

	for (uint32_t i = 0; i < SECTORS; ++i) {
		if (m_beliefSet->getSectorExploredRatio(i) >= EXPLORED_RATIO) {
			uint32_t limitJ = (i / SECTOR_SIZE) * SECTOR_SIZE + SECTOR_SIZE;
			uint32_t limitK = (i % SECTOR_SIZE) * SECTOR_SIZE + SECTOR_SIZE;

			for (uint32_t j = (i / SECTOR_SIZE) * SECTOR_SIZE;
			                j < limitJ && !elevation; ++j) {
				for (uint32_t k = (i % SECTOR_SIZE) * SECTOR_SIZE;
				                k < limitK && !elevation; ++k) {
					if (m_beliefSet->getKnownMap()[j][k]) {
						terrainValue = (*m_beliefSet->map())(j, k)
						               & MASK_TERRAIN;
						resourceValue = (*m_beliefSet->map())(j, k)
						                & MASK_RESOURCE;

						if (terrainValue == TERRAIN_ELEVATION) {
							elevation = true;
						} else {
							if (terrainValue == TERRAIN_WATER)
								water = true;

							switch (resourceValue) {
							case RESOURCE_FOOD:
								food = true;
								break;

							case RESOURCE_METAL:
								metal = true;
								break;

							case RESOURCE_MINERAL:
								mineral = true;
								break;
							}
						}
					}
				}
			}

			water ? sectorValue += 4 : sectorValue += 0;
			food ? sectorValue += 2 : sectorValue += 0;
			metal ? sectorValue += 1 : sectorValue += 0;
			mineral ? sectorValue += 1 : sectorValue += 0;

			sectorValue /= euclideanDistance(m_agent->getPosition(),
			                                 Point(limitJ - 5, limitK - 5));
			m_beliefSet->setSectorSettlementFactor(i, sectorValue);
		}
	}
}

void Intention::gatherResources() {
//TODO: Recolectar recursos
}

void Intention::buildSettlement() {
	m_desire->set("Settlement_Built", false);
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
	int row;
	int col;
	Point p;
	Point bestPoint;
	uint32_t bestDistance;
	uint32_t distance;
	stringstream ss;
	bestDistance = 99999;

	for (uint32_t i = 0; i < m_agent->getVAgents().size() && !sectorFound;
	                ++i) {
		cout << m_agent->getVAgents()[i]->getNameAgent() << endl;

		// cin.get();
		if (m_agent->getVAgents()[i]->getState() == AVAILABLE) {
			for (uint32_t j = 0; j < SECTORS && !sectorFound; ++j) {
				ss << j;
				cout << "Comprobando sector " << j << endl;

				if (!m_beliefSet->exists(ss.str())) {
					p = *checkSectorBoundaries(j);

					if (p != Point(-1, -1)) {
						cout << "Comprobando sector " << j << " desde el punto " << p << endl;
						m_agent->sendToRoute(m_agent->getVAgents()[i]->getPosition(), p,
						                     const_cast<Agent*>(m_agent->getVAgents()[i]),
						                     GO_SEARCHING_LOCATION);
					}
				}

// 				if (m_beliefSet->getSectorExploredRatio(j) <= EXPLORED_RATIO
// 				                && (m_beliefSet->getSectorExploredRatio(j - 1) >= EXPLORED_RATIO
// 				                    || m_beliefSet->getSectorExploredRatio(j + 1) >= EXPLORED_RATIO
// 				                    || m_beliefSet->getSectorExploredRatio(j - SECTOR_OFFSET) >= EXPLORED_RATIO
// 				                    || m_beliefSet->getSectorExploredRatio(j + SECTOR_OFFSET) >= EXPLORED_RATIO)
// 				                && !m_beliefSet->exists(ss.str())) {
// 					cout << "MANDANDO A EXPLORAR " << endl;
//
// 					row = j / SECTOR_SIZE;
// 					col = j % SECTOR_SIZE;
// 					row *= SECTOR_SIZE;
// 					col *= SECTOR_SIZE;
//
// 					p.first = row;
// 					p.second = col;
// 					bestPoint = p;
//
// 					for (int k = 0; k < 2; ++k) {
// 						for (int l = 0; l < 2; ++l) {
// 							p.first += k * SECTOR_SIZE;
// 							p.second += l * SECTOR_SIZE;
// 							distance = euclideanDistance(m_agent->getVAgents()[i]->getPosition(), p);
//
// 							if (distance <= bestDistance) {
// 								if (((*(m_agent->getMap()))(bestPoint.first,
// 								                            bestPoint.second) & MASK_TERRAIN) == TERRAIN_GROUND
// 								                && m_agent->getKnownMap()[bestPoint.first][bestPoint.second]) {
// 									bestDistance = distance;
// 									bestPoint = p;
// 								}
// 							}
// 						}
// 					}
//
// 					if (((*(m_agent->getMap()))(bestPoint.first,
// 					                            bestPoint.second) & MASK_TERRAIN) == TERRAIN_GROUND
// 					                && (m_agent->getKnownMap())[bestPoint.first][bestPoint.second]) {
// 						m_agent->sendToRoute(m_agent->getVAgents()[i]->getPosition(),
// 						                     Point(bestPoint.first, bestPoint.second),
// 						                     const_cast<Agent*>(m_agent->getVAgents()[i]),
// 						                     GO_SEARCHING_LOCATION);
// 						sectorFound = true;
// 						Belief* belief;
// 						belief = new Belief("EXPLORED");
// 						m_beliefSet->add(ss.str(), belief);
// 					}
// 				}
			}
		}
	}
}

void Intention::gotoOptimalLocation() {
	const int SECTORS = ((MAP_WIDTH * MAP_WIDTH) / (SECTOR_SIZE * SECTOR_SIZE));
	float maxValue = 0.0;
	uint32_t bestSector = 0;
	stringstream ss;

	for (int32_t i = 0; i < SECTORS; ++i) {
		if (m_beliefSet->getSectorSettlementFactor(i) > maxValue) {
			maxValue = m_beliefSet->getSectorSettlementFactor(i);
			bestSector = i;
		}
	}

	ss << bestSector;
	Belief* belief = new Belief(ss.str());
	m_beliefSet->add(string("Optimal_Location"), belief);
	// TODO Ir
	m_desire->set("Settlement_Place_Found", true);
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
