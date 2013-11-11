/*
 * MapBuilder.cpp
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#include "MapBuilder.h"
#include <cstdlib>
#include <cstring>

MapBuilder::MapBuilder(uint32_t size) : m_mapSize(size) {
	m_initialMap = new char*[m_mapSize];
	m_resultingMap = new char*[m_mapSize];

	for(uint32_t i = 0; i < m_mapSize; i++) {
		m_initialMap[i] = new char[m_mapSize];
		m_resultingMap[i] = new char[m_mapSize];
	}

	generateMap();
	generateElevation();
	generateResources();
}

MapBuilder::~MapBuilder() {
	if(m_initialMap != NULL) {
		for(uint32_t i = 0; i < m_mapSize; i++) {
			delete [] m_initialMap[i];
			m_initialMap[i] = NULL;
		}
		delete [] m_initialMap;
		m_initialMap = NULL;
	}
}

char const* const* MapBuilder::generatedMap() {
	return m_resultingMap;
}

void MapBuilder::generateMap() {
	for(uint32_t i = 0; i < m_mapSize; i++) {
		memset(m_resultingMap[i], 'g', m_mapSize * sizeof(char));
	}
}

void MapBuilder::generateElevation() {

}

void MapBuilder::generateResources() {

}
