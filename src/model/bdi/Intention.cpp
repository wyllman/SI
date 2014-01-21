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


Intention::Intention(const Agent& agent, BeliefSet& beliefSet, Desire& desire) :
m_beliefSet(&beliefSet), m_desire(&desire), m_agent(
		&dynamic_cast<MainAgent&>(const_cast<Agent&>(agent))) {
	m_currentDesire = "Initial_Exploration";
}

Intention::~Intention() {
}

void Intention::update() {
	std::cout << "Current Desire: " << m_currentDesire << std::endl;
	if (!(*m_desire)["50_Percent_Explored"]) {
		exploreMap();
	} else {
		if (!(*m_desire)["100_Percent_Explored"]) {
			std::cout << "Mapa explorado" << std::endl;
			exploreMap();
		}
		std::cout << "Explora" << std::endl;
		if ((*m_desire)["Settlement_Place_Found"]) {
			std::cout << "Busca asentamiento" << std::endl;
			findOptimalLocation();
			gotoOptimalLocation ();
			if (!(*m_desire)["Resources_Gathered"]) {
				std::cout << "Busca recursos" << std::endl;
				gatherResources();
			} else {
				std::cout << "Construye asentamiento" << std::endl;
				buildSettlement();
			}
		}
	}
}

void Intention::exploreMap() {
	//TODO: Comprobar el mapa y enviar a los agentes
	Package* pack;
	if (m_currentDesire == "Initial_Exploration") {
		for (uint32_t i = 0; i < m_agent->getVAgents().size(); ++i) {
			if (m_agent->getVAgents()[i]->getState() == AVAILABLE) {
				pack = new Package(m_agent->getNameAgent(),
						m_agent->getVAgents()[i]->getNameAgent(),
						DIRECTION_SEARCH);
				std::vector<std::string> packContent;
				// Dirección a la que se envía el agente (i * 2). Ver Tools.h
				std::cout << "Enviando agente "
						<< directionEnumToString(static_cast<Direction>(i * 2))
						<< std::endl;
				packContent.push_back(
						directionEnumToString(static_cast<Direction>(i * 2)));
				pack->setContent(packContent);
				m_agent->getVAgents()[i]->readFIPAPackage(pack);
			}
			m_currentDesire = "Awaiting_Exploration_End";
		}
	}

	if (m_currentDesire == "Start_Sector_Exploration") {
		sectorExploration();
	}

	if (m_currentDesire == "Awaiting_Exploration_End") {
		if (m_beliefSet->exists("NORTH") && m_beliefSet->exists("SOUTH")
				&& m_beliefSet->exists("EAST") && m_beliefSet->exists("WEST")) {
			m_currentDesire = "Start_Sector_Exploration";
		}
	}

	if (m_beliefSet->exploredPercentage() >= 0.5) {
		if (!(*m_desire)["50_Percent_Explored"]) {
			m_desire->set("50_Percent_Explored", true);
		}
		checkSectors();
	}
	if (m_beliefSet->exploredPercentage() >= 0.9) {
		m_desire->set("100_Percent_Explored", true);
	}
	std::cout << "Porcentaje explorado: " << m_beliefSet->exploredPercentage()
									<< std::endl;
}

void Intention::findOptimalLocation() {
	//TODO: Calcular la localizacion optima
	/*Valor agua 4, comida 2, otros 1
	 * div d^2
	 */
	const uint32_t SECTORS = 100;
	const uint32_t SECTOR_SIZE = 10;
	const float EXPLORATED_RATIO = 0.9;
	bool water = false, food = false, metal = false, mineral = false;
	bool elevation = false;
	BYTE terrainValue;
	BYTE resourceValue;
	float sectorValue = 0.0;

	for (uint32_t i = 0; i < SECTORS; ++i) {
		if (m_beliefSet->getSectorExploredRatio(i) >= EXPLORATED_RATIO) {
			uint32_t limitJ = (i / SECTOR_SIZE) * SECTOR_SIZE + SECTOR_SIZE;
			uint32_t limitK = (i % SECTOR_SIZE) * SECTOR_SIZE + SECTOR_SIZE;
			for (uint32_t j = (i / SECTOR_SIZE) * SECTOR_SIZE; j < limitJ && !elevation; ++j) {
				for (uint32_t k = (i % SECTOR_SIZE) * SECTOR_SIZE; k < limitK && !elevation; ++k) {
					if (m_beliefSet->getKnownMap()[j][k]) {
						terrainValue = (*m_beliefSet->map())(j, k) & MASK_TERRAIN;
						resourceValue = (*m_beliefSet->map())(j, k) & MASK_RESOURCE;
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

			sectorValue /= euclideanDistance(m_agent->getPosition(), Point (limitJ - 5, limitK - 5));
			m_beliefSet->setSectorSettlementFactor(i, sectorValue);
		}
	}
}

void Intention::gatherResources() {
	//TODO: Recolectar recursos
}

void Intention::buildSettlement() {
	//TODO: Mostrar algo y fin del programa
}

void Intention::checkSectors() {
	const int32_t SECTOR_SIZE = 10;
	const float CELL_VALUE = 1 / pow((float)SECTOR_SIZE, 2);
	int32_t cell;
	cell = 0;

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
	std::cout << "MANDANDO A EXPLORAR ANTERIOR " << std::endl;
	const int32_t SECTORS = 100;
	const float EXPLORED_RATIO = 0.9;
	int row;
	int col;
	for(int32_t i = 0; i < m_agent->getVAgents().size(); ++i) {

		if (m_agent->getVAgents()[i]->getState() == AVAILABLE) {
			for (uint32_t j = 0; j < SECTORS; ++j) {
				if (m_beliefSet->getSectorExploredRatio(j) >= EXPLORED_RATIO) {
					// TODO Enviar al puto cabrón y que haga el movimiento
					std::cout << "MANDANDO A EXPLORAR " << std::endl;
					row = j / 10;
					col = j % 10;
					row *= 10;
					col *= 10;

					if (((*(m_agent->getMap()))(row, col) & MASK_TERRAIN) == TERRAIN_GROUND
							&& (m_agent->getKnownMap())[row][col]) {

						m_agent->sendToRoute(m_agent->getVAgents()[i]->getPosition()
							            , Point(row, col), const_cast<Agent*>(m_agent->getVAgents()[i])
							            , GO_SEARCHING_LOCATION);

					}

				}
			}
		}
	}
}

void Intention::gotoOptimalLocation () {
	const int SECTORS = 100;
	float maxValue = 0.0;
	uint32_t bestSector = 0;
	stringstream ss;

	for(int32_t i = 0; i < SECTORS; ++i) {
		if (m_beliefSet->getSectorSettlementFactor(i) > maxValue) {
			maxValue = m_beliefSet->getSectorSettlementFactor(i);
			bestSector = i;
		}
	}
	ss << bestSector;
	Belief* belief = new Belief (ss.str());
	m_beliefSet->add(std::string ("Optimal_Location"), belief);
}
