/*
 * typedefs.h
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

//#include <bits/stl_pair.h>

typedef unsigned char BYTE;
//typedef std::pair<int, int> Point;

enum {
	TERRAIN_GROUND = 0x0,
	TERRAIN_ELEVATION = 0x1,
	TERRAIN_WATER = 0x2,
	RESOURCE_WATER = 0x4,
	RESOURCE_FOOD = 0x8,
	RESOURCE_MINERAL = 0x12
};

enum {
	MASK_TERRAIN = 0x2,		// bits 1-2 (0x1-0x2)
	MASK_RESOURCE = 0x12	// bits 3-4 (0x4-0xC)
};

#endif /* TYPEDEFS_H_ */
