/*
 * Agent.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/agents/Agent.h>
#include <model/bdi/BeliefSet.h>
#include <model/bdi/Goals.h>
#include <model/bdi/Intentions.h>

Agent::Agent() {
	// TODO Auto-generated constructor stub

}

Agent::~Agent() {
	// TODO Auto-generated destructor stub
}

bool Agent::move(Movement theMovement) {
	bool result = false;
	switch(theMovement) {
	case NORTH:
		--m_position.second;
		break;
	case SOUTH:
		++m_position.second;
		break;
	case EAST:
		++m_position.first;
		break;
	case WEST:
		--m_position.first;
		break;
	}
	return result;
}
