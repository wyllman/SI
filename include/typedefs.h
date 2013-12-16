/*
 * typedefs.h
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include <map>
#include <bits/stl_pair.h>

typedef unsigned char BYTE;
typedef std::pair<int, int> Point;

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

#endif /* TYPEDEFS_H_ */
