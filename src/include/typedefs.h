/*
 * typedefs.h
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

typedef char byte;

enum {
	TERRAIN_GROUND = 0x0,
	TERRAIN_ELEVATION = 0x1,
	TERRAIN_WATER = 0x2,
	RESOURCE_WATER = 0x4,
	RESOURCE_FOOD = 0x8,
	RESOURCE_MINERAL = 0x10
};

#endif /* TYPEDEFS_H_ */
