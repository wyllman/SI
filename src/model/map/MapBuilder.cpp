/*
 * MapBuilder.cpp
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#include <model/map/MapBuilder.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/binomial_distribution.hpp>
#include <boost/random/negative_binomial_distribution.hpp>
#include <boost/random/random_device.hpp>

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <map>

//#include <map2.c>
#include <map3.c>
//#include <map4.c>

using namespace boost;

MapBuilder::MapBuilder() {
	m_mapSize = gimp.width;
	m_map = new BYTE*[m_mapSize];

	for (uint32_t i = 0; i < m_mapSize; i++) {
		m_map[i] = new BYTE[m_mapSize];
	}
	
	generateElevation();
	generateResources();
}

MapBuilder::~MapBuilder() {
	if (m_map != NULL) {
		for (uint32_t i = 0; i < m_mapSize; i++) {
			delete [] m_map[i];
			m_map[i] = NULL;
		}
		delete [] m_map;
		m_map = NULL;
	}
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
	random::mt11213b mersenneGenerator;
	uint32_t lowerBound;
	uint32_t upperBound;
	uint32_t bytesPerPixel;
	uint32_t pixelGrayscaleValue;

	bytesPerPixel = gimp.bytes_per_pixel;
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

	lowerBound = min + (max - min) * 0.05;
	upperBound = max - (max - min) * 0.4;

	//bucle de relleno del array
	for (uint32_t i = 0; i < m_mapSize; i++) {
		for (uint32_t j = 0; j < m_mapSize; j++) {
			pixelGrayscaleValue = gimp.pixel_data[((i * m_mapSize) + j) * bytesPerPixel];
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

void MapBuilder::generateResources() {
	random::random_device rndDev;
	random::mt11213b probabilityRNG;
	random::mt11213b layoutRNG;
	random::mt11213b positionRNG;
	random::mt11213b typeRNG;
	random::negative_binomial_distribution<> probabilityDistrib(3, 0.5);
	random::uniform_int_distribution<> positionDistrib(0, m_mapSize);
	random::uniform_int_distribution<> typeDistrib(3, 5);
	Point point;
	
	probabilityRNG.seed(rndDev());
	// probabilidad de generar un recurso
	do {
		// posicion x del recurso
		positionRNG.seed(rndDev());
		positionRNG();
		positionDistrib.reset();
		point.first = positionDistrib(positionRNG);
		// posicion y del recurso
		positionRNG.seed(rndDev());
		positionRNG();
		positionDistrib.reset();
		point.second = positionDistrib(positionRNG);
		// tipo del recurso
		typeRNG.seed(rndDev());
		typeRNG();

		generateResourceType(pow(2, typeDistrib(typeRNG)), point);
		
	} while(probabilityDistrib(probabilityRNG) < 6);
}

void MapBuilder::generateResourceType(BYTE type, Point loc) {
	uint32_t size;
	uint32_t width;
	uint32_t i;
	i = 0;

	random_device rndDev;
	random::mt11213b sizeRNG;
	random::mt11213b directionRNG;
	random::mt11213b widthRNG;
	random::uniform_int_distribution<> sizeDistrib(10, 15);
	random::uniform_int_distribution<> directionDistrib(0, 7);
	random::uniform_int_distribution<> widthDistrib(3, 5);

	sizeRNG.seed(rndDev());
	sizeRNG();
	size = sizeDistrib(sizeRNG);
	
	do {
		widthRNG.seed(rndDev());
		widthRNG();
		widthDistrib.reset();
		width = widthDistrib(widthRNG);
		
		for(uint32_t j = loc.first - width; j < loc.first + width; ++j) {
			for (uint32_t k = loc.second - width; k < loc.second + width; ++k) {
				if (j >= 0 && j < m_mapSize && k >= 0 && k < m_mapSize) {
					if ((m_map[j][k] & MASK_RESOURCE) == 0x0) {
						if (abs(sqrt(pow(j, 2) + pow(k, 2))
							- sqrt(pow(loc.first, 2)
							+ pow(loc.second, 2))) <= width) {
							m_map[j][k] |= type;
						}
					}
				}
			}
		}
		
		directionRNG.seed(rndDev());
		directionRNG();
		directionDistrib.reset();
		switch(directionDistrib(directionRNG)) {
			case NORTH:
				loc.first -= width;
				break;
			case SOUTH:
				loc.first += width;
				break;
			case EAST:
				loc.second += width;
				break;
			case WEST:
				loc.second -= width;
				break;
			case NEAST:
				loc.first += width;
				loc.second += width;
				break;
			case NWEST:
				loc.first += width;
				loc.second -= width;
				break;
			case SEAST:
				loc.first -= width;
				loc.second += width;
				break;
			case SWEST:
				loc.first -= width;
				loc.second -= width;
				break;
		}
	} while (i++ < size);
}
