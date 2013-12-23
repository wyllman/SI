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
		boost::random::uniform_int_distribution<> radiusDist(min, sqrt(m_mapSize));
		radius = radiusDist(mersenneGenerator);

		for (int32_t i = 0; static_cast<uint32_t>(i) < m_mapSize; i++) {
			for (int32_t j = 0; static_cast<uint32_t>(j) < m_mapSize; j++) {
				if ((sqrt(pow(i - point.first, 2) + pow(j - point.second, 2)) <= radius)) {
					m_map[i][j] = TERRAIN_ELEVATION;
				}
			}
		}
	}
	for (uint32_t i = 0; i < elevations; i++) {
		mersenneGenerator();
		point.first = elevationDist(mersenneGenerator);
		point.second = elevationDist(mersenneGenerator);
		boost::random::uniform_int_distribution<> radiusDist(min, sqrt(m_mapSize));
		radius = radiusDist(mersenneGenerator);

		for (int32_t i = 0; static_cast<uint32_t>(i) < m_mapSize; i++) {
			for (int32_t j = 0; static_cast<uint32_t>(j) < m_mapSize; j++) {
				if ((sqrt(pow(i - point.first, 2) + pow(j - point.second, 2)) <= radius)) {
					m_map[i][j] = TERRAIN_WATER;
				}
			}
		}
	}
}

void MapBuilder::generateResources() {
	enum {
		DEPOSIT = 0,
		VEIN
	} ResourceDistribution;
	boost::random::mt11213b resourceLayoutRNG;
	boost::random::mt11213b resourceProbabilityRNG;
	boost::random::mt11213b resourcePositionRNG;
	boost::random::mt11213b resourceTypeRNG;
	boost::random::negative_binomial_distribution<> resourceDistrib(3, 0.5);
	boost::random::uniform_int_distribution<> layoutDistrib(0, 1);
	boost::random::uniform_int_distribution<> positionDistrib(0, m_mapSize);
	boost::random::uniform_int_distribution<> typeDistrib(3, 5);
	Point p;
	
	resourceProbabilityRNG.seed(time(NULL));
	resourceLayoutRNG.seed(time(NULL));
	resourcePositionRNG.seed(time(NULL));
	resourceTypeRNG.seed(time(NULL));
	// probabilidad de generar un recurso
	do {
		// posicion del recurso
		resourcePositionRNG();
		p.first = positionDistrib(resourcePositionRNG);
		resourcePositionRNG();
		p.second = positionDistrib(resourcePositionRNG);
		// tipo del recurso
		resourceTypeRNG();
		// disposicion del recurso
		resourceLayoutRNG();
		switch(layoutDistrib(resourceLayoutRNG)) {
		case DEPOSIT:
			generateDeposit(pow(2, typeDistrib(resourceTypeRNG)), p);
			break;
		case VEIN:
			generateVein(pow(2, typeDistrib(resourceTypeRNG)), p);
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
	for(int32_t i = 0; i < size; ++i) {
		widthRNG();
		width = widthDistrib(widthRNG);
		
		directionRNG();
		switch(directionDistrib(directionRNG)) {
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
		}
	}
}

void MapBuilder::generateVein(BYTE type, Point loc) {
	std::cout << "creando veta del tipo 0x" << std::hex << static_cast<int>(type) << " en la posicion (" << std::dec << loc.first << "," << loc.second << ")" << std::endl;
}