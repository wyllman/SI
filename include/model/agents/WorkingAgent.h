/*
 * WorkingAgent.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef WORKINGAGENT_H_
#define WORKINGAGENT_H_

#include <model/agents/Agent.h>

class WorkingAgent : public Agent {
public:
	WorkingAgent();
	~WorkingAgent();

	void setPosition (Point p) { m_position = p; }
};

#endif /* WORKINGAGENT_H_ */
