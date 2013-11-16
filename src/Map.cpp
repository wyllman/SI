/*
 * Map.cpp
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#include "Map.h"
#include "MapBuilder.h"
#include <cstdlib>

Map::Map(uint32_t size) :
		m_size(size), m_map(NULL) {
	m_builder = new MapBuilder();

	m_map = m_builder->generatedMap();
	if(m_map == NULL) {
		std::cout << "something went horribly wrong" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (m_builder != NULL) {
		delete m_builder;
		m_builder = NULL;
	}
}

Map::~Map() {
	if (m_map != NULL) {
		delete[] m_map;
		m_map = NULL;
	}
}

