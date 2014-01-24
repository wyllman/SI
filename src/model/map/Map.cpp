/*
 * Map.cpp
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#include <model/map/Map.h>
#include <model/map/MapBuilder.h>

#include <cstring>

Map::Map() {
	m_builder = new MapBuilder();
	m_size = m_builder->mapSize();
	m_mapArray = new BYTE*[m_size];

	for (uint32_t i = 0; i < m_size; i++) {
		m_mapArray[i] = new BYTE[m_size];
		memcpy(m_mapArray[i], m_builder->generatedMap()[i], sizeof(BYTE) * m_size);
	}

	if (m_builder != NULL) {
		delete m_builder;
		m_builder = NULL;
	}
}

Map::Map(const Map& map) :
	m_size(map.size()), m_builder(NULL) {
	this->m_mapArray = new BYTE*[m_size];

	for (uint32_t i = 0; i < m_size; i++) {
		this->m_mapArray[i] = new BYTE[m_size];
	}

	for (uint32_t i = 0; i < m_size; i++) {
		memcpy(m_mapArray[i], map.map()[i], m_size * sizeof(BYTE));
	}
}

Map::~Map() {
	if (m_mapArray != NULL) {
		for (uint32_t i = 0; i < m_size; i++) {
			delete [] m_mapArray[i];
			m_mapArray[i] = NULL;
		}

		delete [] m_mapArray;
		m_mapArray = NULL;
	}
}

BYTE Map::operator()(int x, int y) const {
	if (x >= 0 && x < m_size && y >= 0 && y < m_size) {
		return m_mapArray[x][y];
	}
	return 0x0;
}

BYTE Map::operator() ( Point p ) const {
	if(p.first >= 0 && p.first < m_size && p.second >= 0 && p.second < m_size) {
		return m_mapArray[p.first][p.second];
	}
	return 0x0;
}