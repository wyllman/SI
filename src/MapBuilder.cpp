/*
 * MapBuilder.cpp
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#include "MapBuilder.h"
#include "include/simplexnoise.h"
#include "../assets/map.c"
#include <string>
#include <boost/unordered_map.hpp>
#include <cstdlib>
#include <cstring>
#include <ctime>
#ifdef __linux
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#elif __APPLE__
#ifdef TARGET_OS_MAC
/* includes */
#endif
#endif

MapBuilder::MapBuilder(uint32_t size) :
		m_mapSize(size) {
	m_map = new WORD*[m_mapSize];

	for (uint32_t i = 0; i < m_mapSize; i++) {
		m_map[i] = new WORD[m_mapSize];
	}

	generateMap();
	generateElevation();
	generateResources();
}

MapBuilder::MapBuilder() {
	uint32_t depth;
	uint32_t lowerBound;
	uint32_t upperBound;

	m_mapSize = gimp_image.width;
	depth = gimp_image.bytes_per_pixel;
	lowerBound = pow(2, depth) * 0.1;
	upperBound = pow(2, depth) * 0.9;

	m_map = new WORD*[m_mapSize];

	for (uint32_t i = 0; i < m_mapSize; i++) {
		m_map[i] = new WORD[m_mapSize];
	}

	for (uint32_t i = 0; i < m_mapSize; i++) {
		for (uint32_t j = 0; j < m_mapSize; j++) {
			gimp_image.pixel_data[(i * 3) + (j * 3)];
			std::cout;
		}
	}

}

MapBuilder::~MapBuilder() {
//	if (m_map != NULL) {
//		for (uint32_t i = 0; i < m_mapSize; i++) {
//			delete[] m_map[i];
//			m_map[i] = NULL;
//		}
//		delete[] m_map;
//		m_map = NULL;
//	}
}

void MapBuilder::generateMap() {
	WORD* tmpString;
	tmpString = new WORD[m_mapSize];

	memset(tmpString, '_', m_mapSize * sizeof(WORD));
	for (uint32_t i = 0; i < m_mapSize; i++) {
		memcpy(m_map[i], tmpString, (m_mapSize) * sizeof(WORD));
	}
	if (tmpString != NULL) {
		delete[] tmpString;
		tmpString = NULL;
	}
}

void MapBuilder::generateElevation() {
	uint32_t elevations;
	Point point;
	int32_t min;
	int32_t radius;

	min = sqrt(m_mapSize) / 2;
	elevations = sqrt(m_mapSize);
	mersenneGenerator.seed(time(NULL));
	boost::random::uniform_int_distribution<> elevationDist(0, m_mapSize);

	for (uint32_t i = 0; i < elevations; i++) {
		mersenneGenerator();
		point.first = elevationDist(mersenneGenerator);
		point.second = elevationDist(mersenneGenerator);
		boost::random::uniform_int_distribution<> radiusDist(min,
				sqrt(m_mapSize));
		radius = radiusDist(mersenneGenerator);

		for (int32_t i = 0; static_cast<uint32_t>(i) < m_mapSize; i++) {
			for (int32_t j = 0; static_cast<uint32_t>(j) < m_mapSize; j++) {
				if ((sqrt(pow(i - point.first, 2) + pow(j - point.second, 2))
						<= radius)) {
					m_map[i][j] = 'A';
				}
			}
		}
	}
	for (uint32_t i = 0; i < elevations; i++) {
		mersenneGenerator();
		point.first = elevationDist(mersenneGenerator);
		point.second = elevationDist(mersenneGenerator);
		boost::random::uniform_int_distribution<> radiusDist(min,
				sqrt(m_mapSize));
		radius = radiusDist(mersenneGenerator);

		for (int32_t i = 0; static_cast<uint32_t>(i) < m_mapSize; i++) {
			for (int32_t j = 0; static_cast<uint32_t>(j) < m_mapSize; j++) {
				if ((sqrt(pow(i - point.first, 2) + pow(j - point.second, 2))
						<= radius)) {
					m_map[i][j] = 'w';
				}
			}
		}
	}
}

void MapBuilder::generateResources() {

}

const int* MapBuilder::splitArray(const std::string str) {
	int tmp[4];
	int initPos;
	int index;
	initPos = 0;
	index = 0;

	for (uint32_t i = 0; i <= str.length(); i++) {
		if (str[i] == ' ' || str[i] == '\0') {
			tmp[index] = atoi(const_cast<char*>(str.substr(initPos, i - initPos).c_str()));
			index++;
			initPos = i;
		}
	}
	return tmp;
}
