/*
 * Tools.cpp
 *
 *  Created on: 20/01/2014
 *      Author: manwe
 */

#include <Tools.h>

#include <cstring>
#include <cmath>

Direction strToDirectionEnum (std::string dir) {
	if (strcmp(dir.c_str(), "NORTH") == 0) {
		return NORTH;
	} else if (strcmp(dir.c_str(), "SOUTH") == 0) {
		return SOUTH;
	} else if (strcmp(dir.c_str(), "EAST") == 0) {
		return EAST;
	} else if (strcmp(dir.c_str(), "WEST") == 0) {
		return WEST;
	} else if (strcmp(dir.c_str(), "NEAST") == 0) {
		return NEAST;
	} else if (strcmp(dir.c_str(), "NWEST") == 0) {
		return NWEST;
	} else if (strcmp(dir.c_str(), "SEAST") == 0) {
		return SEAST;
	} else if (strcmp(dir.c_str(), "SWEST") == 0) {
		return SWEST;
	}
}

std::string directionEnumToString(Direction dir) {
	std::string str;
	switch(dir) {
	case NORTH:
		str = "NORTH";
		break;
	case NEAST:
		str = "NEAST";
			break;
	case EAST:
		str = "EAST";
			break;
	case SEAST:
		str = "SEAST";
			break;
	case SOUTH:
		str = "SOUTH";
			break;
	case SWEST:
		str = "SWEST";
			break;
	case WEST:
		str = "WEST";
			break;
	case NWEST:
		str = "NWEST";
			break;
	default:
		str = "ERROR_DIR";
			break;
	}
	return str;
}

float euclideanDistance (Point p, Point q) {
	return sqrt (pow ((q.first - p.first), 2) + pow ((q.second - q.second), 2));
}
