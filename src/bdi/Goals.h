/*
 * Goals.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef GOALS_H_
#define GOALS_H_

#include <vector>

class Desire;

class Goals {
private:
	std::vector<Desire*> m_goals;
public:
	Goals();
	~Goals();
};

#endif /* GOALS_H_ */
