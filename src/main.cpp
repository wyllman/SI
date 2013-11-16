/*
 * main.cpp
 *
 *  Created on: 09/11/2013
 *      Author: manwe
 */

#include "Map.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
	if(argc != 2) {
		std::cout << "Usage: SI <size>" << std::endl;
		return EXIT_SUCCESS;
	}

	int size;
	size = atoi(argv[1]);

	Map map(size);

	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			std::cout << (map.map()[i][j]);
		}
		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}
