/*
 * SearchAgent.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/agents/SearchAgent.h>

SearchAgent::SearchAgent(MainAgent* mainAgent, Map* theMap): Agent (theMap), refMainAgent_ (mainAgent) {
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


void SearchAgent::actDependingOfState () {
	switch (getState()) {
	case SEARCHING:

		break;

	case FOLLOWING_ROUTE:
		if (!getRoutes().empty()) {
			move(getRoutes().at(0));
			getRoutes().erase(getRoutes().begin()); // FIXME: comprobar que elimina el primero!!
		} else
			setState(AVAILABLE);
		break;
	}
}

vector<Direction>& SearchAgent::getRoutes() {
	return m_routes;
}

void SearchAgent::setRoutes(const vector<Direction>& routes) {
	m_routes = routes;
}
