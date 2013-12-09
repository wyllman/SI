/*
 * main.cpp
 *
 *  Created on: 09/11/2013
 *      Author: manwe
 */

#include "map/Map.h"
#include "map/MapConsoleInterface.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
	Map mapa;
	MapConsoleInterface mapci(mapa);

	for (uint i = 0; i < mapa.size(); i++) {
		for (uint j = 0; j < mapa.size(); j++)
			std::cout << mapci(i, j);
		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}
