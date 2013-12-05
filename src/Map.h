/*
 * Map.h
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#ifndef MAP_H_
#define MAP_H_

#include "../include/typedefs.h"
#include <stdint.h>

class MapBuilder;

/**
 *	@class Map
 *	@brief Clase contenedora el mapa.
 *
 *	La clase Map contiene el mapa sobre el que operan los agentes en la
 *	simulación y que es renderizado en pantalla.
 *
 */
class Map {
private:
	uint32_t m_size;
	MapBuilder* m_builder;
	BYTE** m_mapArray;
public:
	Map(uint32_t size);
	Map();
	Map(const Map& map);
	~Map();
	inline BYTE const* const* map() const { return m_mapArray; }
	inline uint32_t size() const { return m_size; }
};

#endif /* MAP_H_ */
