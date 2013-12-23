/*
 *      Nombre: Tools.h
 *
 *   Creado en: 05/12/2013
 *     Versión: v0.003
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Archivo de cabecera con el conjunto de constantes útiles
 *              en la mqyoría de las clases del simulador.
 *
 *
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <bits/stl_pair.h>

typedef unsigned char BYTE;
typedef std::pair<int, int> Point;

const bool BASIC_LOG = true;
const bool ADVAN_LOG = true;

enum {
   LOG_ERROR = -1,
   LOG_INIT = 1,
   LOG_END = 2,
   LOG_F_INIT = 3,
   LOG_F_STOP = 4,
   LOG_F_START = 5,
   LOG_F_LOOP = 6
};

const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;

const int WIN_WIDTH = 1000;
const int WIN_HEIGHT = 500;

enum {
   LOG_ERROR_1 = -101,
   LOG_INIT_1 = 101,
   LOG_END_1 = 102,
   LOG_F_INIT_1 = 103,
   LOG_F_STOP_1 = 104,
   LOG_F_START_1 = 105,
   LOG_F_LOOP_1 = 106,
   LOG_ERROR_2 = -201
};

enum {
	TERRAIN_GROUND = 0x1,
	TERRAIN_ELEVATION = 0x2,
	TERRAIN_WATER = 0x4,
	RESOURCE_METAL = 0x8,
	RESOURCE_FOOD = 0xF,
	RESOURCE_MINERAL = 0x20
};

enum {
	MASK_TERRAIN = 0x7,	// bits 1-3 (0x1-0x4)
	MASK_RESOURCE = 0x37	// bits 4-6 (0x8-0x20)
};

#endif /* TOOLS_H_ */
