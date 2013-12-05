/*
 * MapBuilder.cpp
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#include "MapBuilder.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <map>

#include "../assets/map2.c"

#ifdef __linux
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
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

MapBuilder::MapBuilder() {
	boost::random::mt11213b mersenneGenerator;
	uint32_t lowerBound;
	uint32_t upperBound;
	uint32_t bytesPerPixel;
	uint32_t pixelGrayscaleValue;
	std::map<uint32_t, uint32_t> terrainBounds;

	m_mapSize = gimp.width;
	bytesPerPixel = gimp.bytes_per_pixel;

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
	// generacion de rangos aleatorios para los tipos de terreno
	mersenneGenerator.seed(time(NULL));
	boost::random::uniform_int_distribution<> minimumElevation(min, max - 12);
	boost::random::uniform_int_distribution<> maximumElevation(8, 12);
	for (int i = 0; i < 5; i++) {
		mersenneGenerator();
		Point p;
		p.first = minimumElevation(mersenneGenerator);
		p.second = p.first + maximumElevation(mersenneGenerator);
		terrainBounds.insert(p);
	}

	lowerBound = min + (max - min) * 0.05;
	upperBound = max - (max - min) * 0.4;

//bucle de relleno del array
	for (uint32_t i = 0; i < m_mapSize; i++) {
		for (uint32_t j = 0; j < m_mapSize; j++) {
			pixelGrayscaleValue = gimp.pixel_data[((i * m_mapSize) + j)
					* bytesPerPixel];
			if (pixelGrayscaleValue < lowerBound) {
				m_map[i][j] = TERRAIN_WATER;
			} else if (pixelGrayscaleValue > upperBound) {
				m_map[i][j] = TERRAIN_ELEVATION;
			} else {
				m_map[i][j] = TERRAIN_GROUND;
			}
			// creamos agua en los bordes del mapa para simplificar la deteccion de colisiones
			if (i == 0 || i == m_mapSize - 1 || j == 0 || j == m_mapSize - 1) {
				m_map[i][j] = TERRAIN_WATER;
			}
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
	boost::random::mt11213b mersenneGenerator;
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

const int* MapBuilder::splitArray(const char* cstr) {
	std::string str(cstr);
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
