/*
 * main.cpp
 *
 *  Created on: 09/11/2013
 *      Author: manwe
 */

#include "Map.h"
#include "MapConsoleInterface.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
	if(argc != 2) {
		std::cout << "Usage: SI <size>" << std::endl;
		return EXIT_SUCCESS;
	}

	int size;
	size = atoi(argv[1]);
	Map mapa;
	MapConsoleInterface mapci(mapa);

	for(uint i = 0; i < mapa.size(); i++) {
		for(uint j = 0; j < mapa.size(); j++)
			std::cout << mapci(i, j);
		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}
