/*
 * SearchAgent.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/agents/SearchAgent.h>

SearchAgent::SearchAgent(MainAgent* mainAgent): refMainAgent_ (mainAgent) {
   setNameAgent(const_cast<char*>("SEARCH_AGENT"));
}

SearchAgent::~SearchAgent() {
}

Package* SearchAgent::readFIPAPackage (Package* p) {
	Package* answer = new Package (getNameAgent(), p -> getSender(), NOT_UNDERSTOOD);
	// Comprobamos que el paquete es de la conversación actual
	if (p -> getIdComm() == getIdComm()) {
		// Comprobamos que el paquete va destinado al agente correcto
		if (p -> getReceiver() == getNameAgent()) {
			switch (p -> getType()) {
			case NOT_UNDERSTOOD:
				std::cout << "NOT_UNDERSTOOD: recibido paquete cuyo contenido no es entendible" << std::endl;
				return NULL;
				break;
			case CONFIRM:
				std::cout << "CONFIRM: Confirmada la operación." << std::endl;
				return NULL;
				break;
			case DIRECTION_SEARCH:
				//Realizar búsqueda dada esta dirección
				localDireccionalSearch(p -> getContent().at(0));
				break;
			default:
				std::cout << "No se entiende el tipo del paquete recibido." << std::endl;
			}
		}
	}
	return answer;
}

void SearchAgent::localDireccionalSearch (std::string  d) {
	switch (atoi(d.c_str())) {
		case NORTH:
			std::cout << "Emprender búsqueda hacial el norte" << std::endl;
			break;
		case SOUTH:
			std::cout << "Emprender búsqueda hacial el sur" << std::endl;
			break;
		case EAST:
			std::cout << "Emprender búsqueda hacial el este" << std::endl;
			break;
		case WEST:
			std::cout << "Emprender búsqueda hacial el oeste" << std::endl;
			break;
		case NEAST:
			std::cout << "Emprender búsqueda hacial el noreste" << std::endl;
			break;
		case NWEST:
			std::cout << "Emprender búsqueda hacial el noroeste" << std::endl;
			break;
		case SEAST:
			std::cout << "Emprender búsqueda hacial el sureste" << std::endl;
			break;
		case SWEST:
			std::cout << "Emprender búsqueda hacial el suroeste" << std::endl;
			break;
	}

}

bool SearchAgent::controledMove(Direction theMovement) {
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

bool SearchAgent::checkTerrain (Direction theMovement) {
   const float MOV_DIFF = 1;
   bool result = false;
   Map* refMap = const_cast<Map*>(refMainAgent_->getMap());
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
   slot = (*refMap)(posX, posZ);
   if ((slot & MASK_TERRAIN) == TERRAIN_GROUND) {
      result = true;
   }
   return result;
}
