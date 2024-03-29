/*
 * Map.h
 *
 *  Created on: 10/11/2013
 *      Author: manwe
 */

#ifndef MAP_H_
#define MAP_H_

#include <Tools.h>
#include <stdint.h>

class MapBuilder;

/*
 *	@class Map
 *	@brief Clase contenedora el mapa.
 *
 *	La clase Map contiene el mapa sobre el que operan los agentes en la
 *	simulación y que es renderizado en pantalla.
 */


class Map {
private:
    uint32_t m_size;
    MapBuilder* m_builder;
    BYTE** m_mapArray;
public:
    Map();
    Map ( const Map& map );
    ~Map();

    BYTE operator() ( int, int) const;

    BYTE operator() ( Point p ) const;

    inline BYTE cellTerrainType ( int x, int y ) const {
        return ( m_mapArray[x][y] & MASK_TERRAIN );
    }

    inline BYTE cellTerrainType ( Point p ) const {
        return ( m_mapArray[p.first][p.second] & MASK_TERRAIN );
    }

    inline BYTE cellResourceType ( int x, int y ) const {
        return ( m_mapArray[x][y] & MASK_RESOURCE );
    }

    inline BYTE cellResourceType ( Point p ) const {
        return ( m_mapArray[p.first][p.second] & MASK_RESOURCE );
    }

    inline BYTE const* const* map() const {
        return m_mapArray;
    }
    inline uint32_t size() const {
        return m_size;
    }
};

#endif /* MAP_H_ */
