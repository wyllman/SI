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
		m_initialMap[i] = new char[m_mapSize + 1];
		m_resultingMap[i] = new char[m_mapSize + 1];
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
	for(uint32_t i = 0; i < m_mapSize; i++) {
		memcpy(m_resultingMap[i], m_initialMap[i], (m_mapSize + 1) * sizeof(char));
	}
	return m_resultingMap;
}

void MapBuilder::generateMap() {
	char* tmpString;
	tmpString = new char[m_mapSize + 1];
	memset(tmpString, 'g', m_mapSize * sizeof(char));
	tmpString[m_mapSize] = '\0';
	for(uint32_t i = 0; i < m_mapSize; i++) {
		memcpy(m_initialMap[i], tmpString, (m_mapSize + 1) * sizeof(char));
	}
}

void MapBuilder::generateElevation() {

}

void MapBuilder::generateResources() {

}
