/*
 * BeliefSet.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/bdi/Belief.h>
#include <model/bdi/BeliefSet.h>

using namespace std;

BeliefSet::BeliefSet(const Map& map) :
	m_map(&map),
	m_exploredCells(0),
	m_exploredPercentage(0.0),
	m_sectorExplorationAverage(0.0) {
	m_knownMap = new bool*[MAP_WIDTH];

	for (uint32_t i = 0; i < MAP_WIDTH; ++i) {
		m_knownMap[i] = new bool[MAP_WIDTH];

		for (uint32_t j = 0; j < MAP_WIDTH; ++j) {
			m_knownMap[i][j] = false;
		}
	}

	m_sectorExploredRatio.resize(100, 0.0);
	m_sectorSettlementFactor.resize(100, 0.0);
}

BeliefSet::~BeliefSet() {
	if (m_knownMap != NULL) {
		for (uint32_t i = 0; i < MAP_WIDTH; ++i) {
			delete [] m_knownMap[i];
			m_knownMap[i] = NULL;
		}

		delete [] m_knownMap;
		m_knownMap = NULL;
	}

	for (std::map<string, const Belief*>::iterator i = m_beliefSet.begin();
	                i != m_beliefSet.end(); ++i) {
		delete (*i).second;
		(*i).second = NULL;
	}
}

void BeliefSet::add(string str, const Belief* belief) {
	m_beliefSet.insert(pair<string, const Belief*>(str, belief));
}

void BeliefSet::remove(string str) {
	if (m_beliefSet.count("str") == 1) {
		delete m_beliefSet["str"];
		m_beliefSet["str"] = NULL;
		m_beliefSet.erase(str);
	}
}

void BeliefSet::setMap(Map* map) {
	if (map == NULL) {
		m_map = map;
	}
}

void BeliefSet::setPosition(Point p) {
	if (p.first >= 0 && p.first <= MAP_WIDTH
	                && p.second >= 0 && p.second <= MAP_WIDTH) {
		m_position = p;
	}
}

void BeliefSet::setKnownMapCell(int i, int j, bool value) {
	m_knownMap[i][j] = value;
}

bool** BeliefSet::getKnownMap() {
	return m_knownMap;
}

bool BeliefSet::getKnownMapCell(uint32_t x, uint32_t y) {
	if (x >= 0 && x < m_map->size() && y >= 0 && y < m_map->size()) {
		return m_knownMap[x][y];
	}
	return false;
}

bool BeliefSet::getKnownMapCell(const Point& p) {
	if (p.first >= 0 && p.first < m_map->size() && p.second >= 0 && p.second < m_map->size()) {
		return m_knownMap[p.first][p.second];
	}
	return false;
}

void BeliefSet::sumExploredCells(int i) {
	m_exploredCells += i;
	m_exploredPercentage = static_cast<float>(m_exploredCells) / (MAP_WIDTH * MAP_WIDTH);
}

void BeliefSet::sumSectorExploredRatio(uint32_t cell, float value) {
	m_sectorExploredRatio[cell] += value;
}

void BeliefSet::setSectorSettlementFactor(uint32_t cell, float value) {
	m_sectorSettlementFactor[cell] = value;
}

bool BeliefSet::exists(string str) {
	if (m_beliefSet.count(str) == 1) {
		return true;
	}

	return false;
}

void BeliefSet::resetSectorExploredRatio() {
	m_sectorExploredRatio.clear();
	m_sectorExploredRatio.resize(100, 0);
}

float BeliefSet::getSectorExploredRatio(int32_t cell) {
	if (cell < 0 || (cell > (MAP_WIDTH * MAP_WIDTH) / (SECTOR_SIZE * SECTOR_SIZE))) {
		return 1.0;
	}

	return m_sectorExploredRatio[cell];
}
