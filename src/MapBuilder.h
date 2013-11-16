/*
 * MapBuilder.h
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#ifndef MAPBUILDER_H_
#define MAPBUILDER_H_

#include "include/typedefs.h"
#include <stdint.h>
#include <boost/random/mersenne_twister.hpp>

/**
 * \class MapBuilder
 * \brief Constructor de mapas
 *
 * La clase MapBuilder recibe como único parámetro en su constructor el tamaño
 * deseado del lado del mapa y lo genera.
 *
 */
class MapBuilder {
private:
	uint32_t m_mapSize;
	WORD** m_map;
	boost::random::mt11213b mersenneGenerator;

	void generateMap();
	void generateElevation();
	void generateResources();
	const int* getArray(const std::string str);
public:
	MapBuilder(uint32_t);
	MapBuilder();
	~MapBuilder();

	WORD const* const* generatedMap() {
		return m_map;
	}
};

#endif /* MAPBUILDER_H_ */
