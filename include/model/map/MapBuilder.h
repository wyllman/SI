/*
 * MapBuilder.h
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#ifndef MAPBUILDER_H_
#define MAPBUILDER_H_

#include <Tools.h>
#include <stdint.h>

/*
 * @class MapBuilder
 * @brief Constructor de mapas
 *
 * La clase MapBuilder recibe como único parámetro en su constructor el tamaño
 * deseado del lado del mapa y lo genera.
 */

class MapBuilder {
private:
	uint32_t m_mapSize;
	BYTE** m_map;

	void generateMap();
	void generateElevation();
	void generateResources();
	void generateVein(BYTE, Point);
	void generateDeposit(BYTE, Point);
	const int* splitArray(const char*);
public:
	MapBuilder(uint32_t);
	/*
	 *	@fn MapBuilder()
	 *  @brief Constructor por defecto del mapa.
	 *
	 *	El constructor por defecto genera el terreno usando una imagen de
	 *	ruido perlin compilada.
	 */
	MapBuilder();
	/*
	 *	@fn ~MapBuilder()
	 *	@brief Destructor
	 */
	~MapBuilder();

	/*
	 *	@fn generatedMap()
	 *	@brief Devuelve el mapa generado
	 *	@return BYTE**
	 */
	inline BYTE** generatedMap() {
		return m_map;
	}
	inline int32_t mapSize() {
		return m_mapSize;
	}
};

#endif /* MAPBUILDER_H_ */
