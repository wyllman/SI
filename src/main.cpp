/*
 * main.cpp
 *
 *  Created on: 09/11/2013
 *      Author: manwe
 */

#include "Map.h"
#include <cstdlib>
#include <cstdio>

int main(int argc, char* argv[]) {
	Map map(8);

	for(int i = 0; i < 8; i++) {
		printf("%s\n", map.map()[i]);
	}

	return EXIT_SUCCESS;
}
