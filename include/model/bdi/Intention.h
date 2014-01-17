/*
 * Intention.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef INTENTION_H_
#define INTENTION_H_

#include <string>
#include <vector>

class BeliefSet;
class Desire;

//TODO: Falta la función que realiza acciones dependiendo de la creencia y el objetivo
class Intention {
private:
	BeliefSet* m_beliefSet;
	std::vector<Desire>* m_desireVector;
public:
	Intention(BeliefSet&, std::vector<Desire>&);
	~Intention();
};

#endif /* INTENTION_H_ */
