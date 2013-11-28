/*
 * MapBuilder.cpp
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#include "MapBuilder.h"
#include "include/simplexnoise.h"
#include "../assets/map3.c"
#include <string>
#include <boost/unordered_map.hpp>
#include <cstdlib>
#include <cstring>
#include <cstdio>
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
	m_map = new BYTE*[m_mapSize];

	for (uint32_t i = 0; i < m_mapSize; i++) {
		m_map[i] = new BYTE[m_mapSize];
	}

	generateMap();
	generateElevation();
	generateResources();
}

/*
 * FIXME: el metodo parece estar recorriendo mal el array de map.c
 * no recorre los caracteres secuencialmente
 */
MapBuilder::MapBuilder() {
	uint32_t lowerBound;
	uint32_t upperBound;
	uint32_t caca;

	m_mapSize = gimp.width;

	m_map = new BYTE*[m_mapSize];

	// reserva de memoria
	for (uint32_t i = 0; i < m_mapSize; i++) {
		m_map[i] = new BYTE[m_mapSize];
	}

	// bucle para hallar el rango de colores
	uint32_t max;
	uint32_t min;
	max = min = gimp.pixel_data[0];
	for (uint32_t i = 0; i < m_mapSize; i++) {
		for (uint32_t j = 0; j < m_mapSize; j++) {
			if (gimp.pixel_data[i * m_mapSize + j] > max) {
				max = gimp.pixel_data[i * m_mapSize + j];
			}
			if (gimp.pixel_data[i * m_mapSize + j] < min) {
				min = gimp.pixel_data[i * m_mapSize + j];
			}
		}
	}
	lowerBound = min + (max - min) * 0.1;
	upperBound = max - (max - min) * 0.1;

	//bucle de relleno del array
	int j = 0;
	for (uint32_t i = 0; i < (m_mapSize * m_mapSize - 1); i++) {
		caca = gimp.pixel_data[i];
//		std::cout << " "<< i << " ";
//		std::cout << std::hex << static_cast<int>(gimp.pixel_data[i]);
//		std::cin.get();
//		m_map[j][i % m_mapSize] = static_cast<char>(caca);
//			std::cout << "lowerBound = " << std::hex << lowerBound << std::endl;
//			std::cout << "upperBound = " << std::hex << upperBound << std::endl;
//			std::cout << "caca = " << std::hex << caca << std::endl;
//			std::cin.get();
		if (caca <= lowerBound) {
			m_map[i % m_mapSize][j] = 'w';
		} else if (caca > upperBound) {
			m_map[i % m_mapSize][j] = 'A';
		} else {
			m_map[i % m_mapSize][j] = '_';
		}
		if (i != 0 && i % m_mapSize == (m_mapSize - 1)) {
			j++;
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
	unsigned char* tmpString;
	tmpString = new BYTE[m_mapSize];

	memset(tmpString, '_', m_mapSize * sizeof(BYTE));
	for (uint32_t i = 0; i < m_mapSize; i++) {
		memcpy(m_map[i], tmpString, (m_mapSize) * sizeof(BYTE));
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
			tmp[index] =
					atoi(
							const_cast<char*>(str.substr(initPos, i - initPos).c_str()));
			index++;
			initPos = i;
		}
	}
	return tmp;
}
