/*
 * SearchAgent.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef SEARCHAGENT_H_
#define SEARCHAGENT_H_

#include <model/agents/WorkingAgent.h>

class SearchAgent: public Agent {
public:
	SearchAgent();
	~SearchAgent();

	void setPosition (Point p) { m_position = p; }
};

#endif /* SEARCHAGENT_H_ */
