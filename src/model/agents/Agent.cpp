/*
 * Agent.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/agents/Agent.h>

#include <cmath>

using namespace std;

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
bool Agent::routedMove() {
   bool result = false;
   if (!(m_routes.empty())) {
      result = controledMove (m_routes.back());
      m_routes.pop_back();
   }
   return result;
}

unsigned int Agent::getIdComm() const {
	return m_idComm;
}

char* Agent::getNameAgent() const {
	return m_nameAgent;
}

bool Agent::checkRouteMoves() {
   bool result = false;
   if (m_routes.size() > 0) {
      result = true;
   }
   return (result);
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

vector<Direction>& Agent::getRoutes() {
	return m_routes;
}

void Agent::setRoutes(vector<Direction>& routes) {
	m_routes = routes;
}

void Agent::followRoute(string route) {
	//cout << "SEGUIR LA RUTA: " << route << endl;
	vector<Direction> camino;
	int posIni = route.find("[");
	int posCorchFin = route.find("]");
	if (!route.empty() && route.size() > 4) {
		route = route.substr(1, route.size() - 1);// FIXME: da problemas principalmente en map4.c
	}
	int posComa = 0;
	bool stop = false;
	string dirTemp;

	while (!stop) {
		posComa = route.find(",");
		if (posComa == -1) {
			stop = true;
			dirTemp = route.substr(0, route.length() - 1);
		} else {
			dirTemp = route.substr(0, posComa);
			route = route.substr(posComa + 1, route.length());
		}
		camino.push_back(strToDirectionEnum(dirTemp));
	}

	for (unsigned int i = 0; i < camino.size(); i++) {
		m_routes.push_back(camino[camino.size() - i]);
	}
}
