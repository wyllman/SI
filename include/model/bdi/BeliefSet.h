/*
 * BeliefSet.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef BELIEFSET_H_
#define BELIEFSET_H_

#include <model/map/Map.h>

#include <map>
#include <string>

class Belief;

/**
 * \class BeliefSet
 * \brief Clase para almacenar el conjunto de creencias.
 * 
 * La clase BeliefSet almacena el conjunto de creencias en un hashmap.
 * La excepción son el mapa y la localizacón, que por conveniencia
 * son independientes y con sus propios operadores.
 */

class BeliefSet {
private:
	std::map<std::string, const Belief*> m_beliefSet;
	Map* m_map;
	Point m_position;
public:
	BeliefSet();
	~BeliefSet();
	const Belief* operator()(std::string belief) { return m_beliefSet["belief"]; }
	const Map* map() { return m_map; }
	void setMap(Map* map);
	Point position() { return m_position; }
	void setPosition(Point);
	void add(std::string, const Belief*);
	void remove(std::string);
};

#endif /* BELIEFSET_H_ */
