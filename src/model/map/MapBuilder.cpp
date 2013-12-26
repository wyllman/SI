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

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <map>

#include <map2.c>

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
	boost::random::mt11213b mersenneGenerator;
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
	enum {
		DEPOSIT = 0,
		VEIN = 1
	} ResourceDistribution;
	boost::random::mt11213b resourceLayoutRNG;
	boost::random::mt11213b resourceProbabilityRNG;
	boost::random::mt11213b resourcePositionRNG;
	boost::random::mt11213b resourceTypeRNG;
	boost::random::negative_binomial_distribution<> resourceDistrib(3, 0.5);
	boost::random::uniform_int_distribution<> layoutDistrib(0, 1);
	boost::random::uniform_int_distribution<> positionDistrib(0, m_mapSize);
	boost::random::uniform_int_distribution<> typeDistrib(5, 5);
	Point point;
	
	resourceProbabilityRNG.seed(time(NULL));
	resourceLayoutRNG.seed(time(NULL));
	resourcePositionRNG.seed(time(NULL));
	resourceTypeRNG.seed(time(NULL));
	// probabilidad de generar un recurso
	do {
		// posicion del recurso
		resourcePositionRNG();
		point.first = positionDistrib(resourcePositionRNG);
		resourcePositionRNG();
		point.second = positionDistrib(resourcePositionRNG);
		// tipo del recurso
		resourceTypeRNG();
		// disposicion del recurso
		resourceLayoutRNG();
		switch(layoutDistrib(resourceLayoutRNG)) {
		case DEPOSIT:
			generateDeposit(pow(2, typeDistrib(resourceTypeRNG)), point);
			break;
		case VEIN:
			generateVein(pow(2, typeDistrib(resourceTypeRNG)), point);
			break;
		}
		
	} while(resourceDistrib(resourceProbabilityRNG) < 6);
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
			tmp[index] = atoi(const_cast<char*>(str.substr(initPos, i - initPos).c_str()));
			index++;
			initPos = i;
		}
	}
	return tmp;
}

void MapBuilder::generateDeposit(BYTE type, Point loc) {
	std::cout << "creando deposito del tipo 0x" << std::hex << static_cast<int>(type) << " en la posicion (" << std::dec <<loc.first << "," << loc.second << ")" << std::endl;
	
	uint32_t size;
	uint32_t width;
	uint32_t i;
	i = 0;
	
	boost::random::mt11213b sizeRNG;
	boost::random::mt11213b directionRNG;
	boost::random::mt11213b widthRNG;
	boost::random::uniform_int_distribution<> sizeDistrib(4, 8);
	boost::random::uniform_int_distribution<> directionDistrib(0, 3);
	boost::random::uniform_int_distribution<> widthDistrib(5, 10);
	
	sizeRNG.seed(std::time(NULL));
	directionRNG.seed(std::time(NULL));
	widthRNG.seed(std::time(NULL));
	size = sizeDistrib(sizeRNG);
	
	do {
		widthRNG();
		width = widthDistrib(widthRNG);
		
		for(uint32_t j = loc.first - width; j < loc.first + width; ++j) {
			for (uint32_t k = loc.second - width; k < loc.second + width; ++k) {
				if(j >= 0 && j < m_mapSize && k >= 0 && k < m_mapSize) {
					if(abs(sqrt(pow(j, 2) + pow(k, 2))
						- sqrt(pow(loc.first, 2)
						+ pow(loc.second, 2))) <= width) {
						m_map[j][k] |= type;
						//std::cout << m_map[j][k] << std::endl;
						//std::cin.get();
					}
				}
			}
		}
		
		directionRNG();
		switch(directionDistrib(directionRNG)) {
			case NORTH:
				--loc.first;
				break;
			case SOUTH:
				++loc.first;
				break;
			case EAST:
				++loc.second;
				break;
			case WEST:
				--loc.second;
				break;
		}
	} while (i++ < size);

}

void MapBuilder::generateVein(BYTE type, Point loc) {
	std::cout << "creando veta del tipo 0x" << std::hex << static_cast<int>(type) << " en la posicion (" << std::dec << loc.first << "," << loc.second << ")" << std::endl;
}
