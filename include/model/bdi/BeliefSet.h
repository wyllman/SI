/*
 * BeliefSet.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef BELIEFSET_H_
#define BELIEFSET_H_

#include <model/map/Map.h>

#include <vector>
class Belief;

class BeliefSet {
private:
	std::vector<Belief*> m_beliefSet;
	Map* m_map; // Mapa del Sistema de Agentes
public:
	BeliefSet();
	~BeliefSet();
};

#endif /* BELIEFSET_H_ */
