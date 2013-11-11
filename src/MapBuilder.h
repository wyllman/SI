/*
 * MapBuilder.h
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#ifndef MAPBUILDER_H_
#define MAPBUILDER_H_

#include <stdint.h>

class MapBuilder {
private:
	uint32_t m_mapSize;
	char** m_initialMap;
	char** m_resultingMap;

	void generateMap();
	void generateElevation();
	void generateResources();
public:
	MapBuilder(uint32_t);
	~MapBuilder();

	char const* const* generatedMap();
};

#endif /* MAPBUILDER_H_ */
