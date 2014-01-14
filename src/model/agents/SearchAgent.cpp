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
			case GO_LOCATION:
				followRoute(p -> getContent().at(0));
				setState(FOLLOWING_ROUTE);
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
		cout << "Tam: " << getRoutes().size() << endl;
		if (!routedMove()) {
			setState(AVAILABLE);
			getRefMainAgent() -> readFIPAPackage(new Package(getNameAgent(), getRefMainAgent() -> getNameAgent(), ARRIVED_GOAL));
		}
		break;
	}
}

void SearchAgent::followRoute(std::string route) {
	cout << "SEGUIR LA RUTA: " << route << endl;
	vector<Direction> camino;
	int posIni = route.find("[");
	int posCorchFin = route.find("]");
	cout << "Pos ini:" << posIni << " posFin: " << posCorchFin << endl;
	route = route.substr(1, route.length());
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

		camino.push_back(translateRoute(dirTemp));

	}
	for (unsigned int i = 0; i < camino.size(); i++) {
		m_routes.push_back(camino[camino.size() - 1]);
	}
}

Direction SearchAgent::translateRoute (std::string dir) {
	if (strcmp(dir.c_str(), "NORTH") == 0) {
		return NORTH;
	} else if (strcmp(dir.c_str(), "SOUTH") == 0) {
		return SOUTH;
	} else if (strcmp(dir.c_str(), "EAST") == 0) {
		return EAST;
	} else if (strcmp(dir.c_str(), "WEST") == 0) {
		return WEST;
	} else if (strcmp(dir.c_str(), "NEAST") == 0) {
		return NEAST;
	} else if (strcmp(dir.c_str(), "NWEST") == 0) {
		return NWEST;
	} else if (strcmp(dir.c_str(), "SEAST") == 0) {
		return SEAST;
	} else if (strcmp(dir.c_str(), "SWEST") == 0) {
		return SWEST;
	}
}

vector<Direction>& SearchAgent::getRoutes() {
	return m_routes;
}

void SearchAgent::setRoutes(const vector<Direction>& routes) {
	m_routes = routes;
}

MainAgent* SearchAgent::getRefMainAgent() {
	return refMainAgent_;
}
