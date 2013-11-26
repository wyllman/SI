/*
 * Intentions.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef INTENTIONS_H_
#define INTENTIONS_H_

#include <vector>

class Plan;

class Intentions {
private:
	std::vector<Plan*> m_intentions;
public:
	Intentions();
	~Intentions();
};

#endif /* INTENTIONS_H_ */
