/*
 * MapConsoleInterface.h
 *
 *  Created on: 01/12/2013
 *      Author: manwe
 */

#ifndef MAPCONSOLEINTERFACE_H_
#define MAPCONSOLEINTERFACE_H_

#include <typedefs.h>
#include <map>

class Map;

class MapConsoleInterface {
private:
	const Map* m_map;
	std::map<BYTE, BYTE> m_consoleMapping;
public:
	MapConsoleInterface(const Map& map);
	~MapConsoleInterface();

	BYTE const * const * map();
	BYTE operator()(int, int);
};

#endif /* MAPCONSOLEINTERFACE_H_ */
