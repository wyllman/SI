/*
 * MapConsoleInterface.cpp
 *
 *  Created on: 01/12/2013
 *      Author: manwe
 */

#include "MapConsoleInterface.h"
#include "Map.h"

MapConsoleInterface::MapConsoleInterface(const Map& map) :
		m_map(&map) {
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_GROUND, '_'));
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_ELEVATION, 'A'));
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_WATER, 'w'));
}

MapConsoleInterface::~MapConsoleInterface() {

}

BYTE const* const * MapConsoleInterface::map() {
	return m_map->map();
}

BYTE MapConsoleInterface::operator()(int x, int y) {
	return m_consoleMapping[m_map->map()[x][y]];
}
