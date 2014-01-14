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

Agent::Agent(Map* theMap): refMap_ (theMap) {
   setIdComm(0);
   m_state = AVAILABLE;
}

Agent::~Agent() {
}

void Agent::move(Direction theMovement) {
   const float MOV_DIFF = 1;
//   bool result = false;

   switch(theMovement) {
      case NORTH:
         m_position.first -= MOV_DIFF;
         break;
      case SOUTH:
         m_position.first += MOV_DIFF;
         break;
      case EAST:
         m_position.second += MOV_DIFF;
         break;
      case WEST:
         m_position.second -= MOV_DIFF;
         break;
      case NEAST:
         m_position.first -= MOV_DIFF;
         m_position.second += MOV_DIFF;
         break;
      case NWEST:
         m_position.first -= MOV_DIFF;
         m_position.second -= MOV_DIFF;
         break;
      case SEAST:
         m_position.first += MOV_DIFF;
         m_position.second += MOV_DIFF;
         break;
      case SWEST:
         m_position.first += MOV_DIFF;
         m_position.second -= MOV_DIFF;
         break;
	}
//	return result;
}
bool Agent::controledMove(Direction theMovement) {
   bool result = false;
   int posX, posZ;

   posX = getPosition().first;
   posZ = getPosition().second;

   if ((posX > 0 && posX < (MAP_WIDTH - 1))
       && (posZ > 0 && posZ < (MAP_HEIGHT - 1))
       && checkTerrain(theMovement)) {
      move(theMovement);
      result = true;
   }
   return result;
}

bool Agent::checkTerrain(Direction theMovement) {
   const float MOV_DIFF = 1;
   bool result = false;
   BYTE slot;
   int posX = getPosition().first;
   int posZ = getPosition().second;

   switch(theMovement) {
      case NORTH:
         posX -= MOV_DIFF;
         break;
      case SOUTH:
         posX += MOV_DIFF;
         break;
      case EAST:
         posZ += MOV_DIFF;
         break;
      case WEST:
         posZ -= MOV_DIFF;
         break;
      case NEAST:
         posX -= MOV_DIFF;
         posZ += MOV_DIFF;
         break;
      case NWEST:
         posX -= MOV_DIFF;
         posZ -= MOV_DIFF;
         break;
      case SEAST:
         posX += MOV_DIFF;
         posZ += MOV_DIFF;
         break;
      case SWEST:
         posX += MOV_DIFF;
         posZ -= MOV_DIFF;
         break;
   }
   slot = (*refMap_)(posX, posZ);
   if ((slot & MASK_TERRAIN) == TERRAIN_GROUND) {
      result = true;
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


State Agent::getState() const {
	return m_state;
}

void Agent::setState(State state) {
	m_state = state;
}
