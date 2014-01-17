/*
 * Desires.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef DESIRE_H_
#define DESIRE_H_

class BeliefSet;
class Intention;

class Desire {
public:
	Desire(const BeliefSet&, const Intention&);
	~Desire();
};

#endif /* DESIRE_H_ */
