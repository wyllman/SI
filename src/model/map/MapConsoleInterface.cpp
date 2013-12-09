/*
 * MapConsoleInterface.cpp
 *
 *  Created on: 01/12/2013
 *      Author: manwe
 */

#include "../../../include/model/map/MapConsoleInterface.h"
#include "../../../include/model/map/Map.h"

MapConsoleInterface::MapConsoleInterface(const Map& map) :
		m_map(&map) {
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_GROUND, '_'));
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_ELEVATION, 'A'));
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_WATER, 'w'));
}

MapConsoleInterface::~MapConsoleInterface() {

}

BYTE const* const * MapConsoleInterface::map() {
	//return 0;
	return m_map->map();
}

BYTE MapConsoleInterface::operator()(int x, int y) {
	//return 0;
	//std::cout << "Retornar cada pieza de terreno." << std::endl;
	//std::cout << m_map->map()[x][y] << std::endl;
	return m_consoleMapping[m_map->map()[x][y]];
}
