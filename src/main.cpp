/*
 * main.cpp
 *
 *  Created on: 09/11/2013
 *      Author: manwe
 */

#include "MapBuilder.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
	MapBuilder mb(8);

	for(int i = 0; i < 8; i++) {
		std::cout << mb.generatedMap()[i] << std::endl;
	}

	return EXIT_SUCCESS;
}
