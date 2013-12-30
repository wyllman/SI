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

/**
 * @class MapBuilder
 * @brief Constructor de mapas
 *
 */

class MapBuilder {
private:
	uint32_t m_mapSize;
	BYTE** m_map;

	void generateMap();
	void generateElevation();
	void generateResources();
	/**
	 * @fn generateResourceType(BYTE, Point)
	 * @brief Genera recursos del tipo deposit
	 * 
	 * @param byte El tipo de recurso segun el enum bla.
	 * @param point El punto desde donde se empieza a generar el recurso.
	 * 
	 * Genera un recurso del typo @byte distribuido aleatoriamente a partir
	 * del punto @point.
	 * Se recorren  los puntos en la distancia manhattan alrededor de @point
	 * y se comprueban con \f$|\sqrt{(x_0+d)^{2}+(y_0+d)^{2}}-\sqrt{x_0^{2}+y_0^{2}}|<=d\f$
	 */
	void generateResourceType(BYTE, Point);
	const int* splitArray(const char*);
public:
	/**
	 *  @fn MapBuilder()
	 *  @brief Constructor por defecto del mapa.
	 *
	 *	El constructor por defecto genera el terreno usando una imagen de
	 *	ruido perlin compilada.
	 */
	MapBuilder();
	/**
	 *	@fn ~MapBuilder()
	 *	@brief Destructor
	 */
	~MapBuilder();

	/**
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
