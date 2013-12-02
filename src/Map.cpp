/*
 * Map.cpp
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#include "Map.h"
#include "MapBuilder.h"
#include <cstdlib>
#include <cstring>

Map::Map(uint32_t size) :
		m_size(size), m_mapArray(NULL) {
	m_builder = new MapBuilder(m_size);

	m_mapArray = const_cast<BYTE**>(m_builder->generatedMap());
	if (m_mapArray == NULL) {
		std::cout << "something went horribly wrong" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (m_builder != NULL) {
		delete m_builder;
		m_builder = NULL;
	}
}

Map::Map() {
	m_builder = new MapBuilder();
	m_size = m_builder->mapSize();
	m_mapArray = const_cast<BYTE**>(m_builder->generatedMap());

	if (m_mapArray == NULL) {
		std::cout << "something went horribly wrong" << std::endl;
		exit(EXIT_FAILURE);
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

	for(uint32_t i = 0; i < m_size; i++) {
		memcpy(m_mapArray[i], map.map()[i], m_size * sizeof(BYTE));
	}
}

Map::~Map() {
	//FIXME
	if (m_mapArray != NULL) {
		delete[] m_mapArray;
		m_mapArray = NULL;
	}
}

