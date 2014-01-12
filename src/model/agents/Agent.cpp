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
}

Agent::~Agent() {
}

bool Agent::move(Direction theMovement) {
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

unsigned int Agent::getIdComm() const {
	return m_idComm;
}

char* Agent::getNameAgent() const {
	return m_nameAgent;
}

void Agent::setNameAgent(char* nameAgent) {
	m_nameAgent = nameAgent;
}

void Agent::setIdComm(unsigned int idComm) {
	m_idComm = idComm;
}

Point Agent::getPosition () {
	return m_position;
}
