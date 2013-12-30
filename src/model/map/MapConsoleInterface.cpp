/*
 * MapConsoleInterface.cpp
 *
 *  Created on: 01/12/2013
 *      Author: manwe
 */

#include <model/map/MapConsoleInterface.h>
#include <model/map/Map.h>

MapConsoleInterface::MapConsoleInterface(const Map& map) :
		m_map(&map) {
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_GROUND, '_'));
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_GROUND | RESOURCE_FOOD, 'a'));
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_GROUND | RESOURCE_METAL, 'b'));
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_GROUND | RESOURCE_MINERAL, 'c'));
	
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_ELEVATION, '#'));
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_ELEVATION | RESOURCE_FOOD, 'A'));
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_ELEVATION | RESOURCE_METAL, 'B'));
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_ELEVATION | RESOURCE_MINERAL, 'C'));
	
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_WATER, 'w'));
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_WATER | RESOURCE_FOOD, '0'));
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_WATER | RESOURCE_METAL, '1'));
	m_consoleMapping.insert(std::pair<BYTE, BYTE>(TERRAIN_WATER | RESOURCE_MINERAL, '2'));
}

MapConsoleInterface::~MapConsoleInterface() {

}

BYTE const * const * MapConsoleInterface::map() {
	return m_map->map();
}

BYTE MapConsoleInterface::operator()(int x, int y) {
	return m_consoleMapping[m_map->map()[x][y]];
}
