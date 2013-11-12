/*
 * Map.h
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#ifndef MAP_H_
#define MAP_H_

#include <stdint.h>

class MapBuilder;

/**
 * \class Map
 * \brief Clase contenedora el mapa.
 *
 * La clase Map contiene el mapa sobre el que operan los agentes en la
 * simulación y que es renderizado en pantalla.
 *
 */
class Map {
private:
	uint32_t m_size;
	MapBuilder* m_builder;
	const char* const* m_map;
public:
	Map(uint32_t size);
	~Map();
	const char* const* map() { return m_map; }
};

#endif /* MAP_H_ */
