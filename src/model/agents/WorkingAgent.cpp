/*
 * WorkingAgent.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/agents/WorkingAgent.h>

WorkingAgent::WorkingAgent() {
	setNameAgent("WORK_AGENT");
}

WorkingAgent::~WorkingAgent() {
}

Package* WorkingAgent::readFIPAPackage (Package* p) {
	Package* answer = new Package (getNameAgent(), p -> getSender(), NOT_UNDERSTOOD);
	// Comprobamos que el paquete es de la conversación actual
	if (p -> getIdComm() == getIdComm()) {
		// Comprobamos que el paquete va destinado al agente correcto
		if (p -> getReceiver() == getNameAgent()) {
			switch (p -> getType()) {
			case NOT_UNDERSTOOD:
				cout << "NOT_UNDERSTOOD: recibido paquete cuyo contenido no es entendible" << endl;
				return NULL;
				break;
			case CONFIRM:
				cout << "CONFIRM: Confirmada la operación." << endl;
				return NULL;
				break;
			case GO_RESOURCE_LOCATION:
				//Realizar búsqueda dada esta dirección
				followRoute(p -> getContent().at(0));
				break;
			default:
				cout << "No se entiende el tipo del paquete recibido." << endl;
			}
		}
	}
}

void WorkingAgent::followRoute(std::string route) {
	cout << "SEGUIR LA RUTA: " << route << endl;
	vector<Direction> camino;
	// [NORTH, NORTH, ...]
	int posIni = route.find("[");
	int posCorchFin = route.find("]");
	cout << "Pos ini:" << posIni << " posFin: " << posCorchFin << endl;
	route = route.substr(1, route.length());
	int posComa = 0, i = 0;
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
		cout << translateRoute(dirTemp) << endl;
		move(camino.at(i));
		cout << "POS AGeNTE: " << m_position.first << ", "<< m_position.second << endl;
		i++;
	}
}

Direction WorkingAgent::translateRoute (std::string dir) {
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

vector<Direction>& WorkingAgent::getRoutes() {
	return m_routes;
}

void WorkingAgent::setRoutes(vector<Direction>& routes) {
	m_routes = routes;
}
