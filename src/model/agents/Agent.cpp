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
   const float MOV_DIFF = 0.01;
   bool result = false;

   switch(theMovement) {
      case NORTH:
         m_position.second -= MOV_DIFF;
         break;
      case SOUTH:
         m_position.second += MOV_DIFF;
         break;
      case EAST:
         m_position.first += MOV_DIFF;
         break;
      case WEST:
         m_position.first -= MOV_DIFF;
         break;
      case NEAST:
         m_position.second -= MOV_DIFF;
         m_position.first += MOV_DIFF;
         break;
      case NWEST:
         m_position.second -= MOV_DIFF;
         m_position.first -= MOV_DIFF;
         break;
      case SEAST:
         m_position.second += MOV_DIFF;
         m_position.first += MOV_DIFF;
         break;
      case SWEST:
         m_position.second += MOV_DIFF;
         m_position.first -= MOV_DIFF;
         break;
	}
	return result;
}

Point Agent::getPosition () {
	return m_position;
}
