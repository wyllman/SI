/*
 * Map.cpp
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#include "Map.h"
#include "MapBuilder.h"
#include <cstdlib>

Map::Map(uint32_t size) : m_size(size){
	m_builder = new MapBuilder(m_size);

	m_map = m_builder->generatedMap();

	if(m_builder != NULL) {
		delete m_builder;
		m_builder = NULL;
	}
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

