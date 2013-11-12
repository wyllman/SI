/*
 * BeliefSet.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef BELIEFSET_H_
#define BELIEFSET_H_

#include <vector>
class Belief;

class BeliefSet {
private:
	std::vector<Belief*> m_beliefSet;
public:
	BeliefSet();
	~BeliefSet();
};

#endif /* BELIEFSET_H_ */
