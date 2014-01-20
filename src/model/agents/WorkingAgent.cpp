/*
 * WorkingAgent.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <Tools.h>
#include <model/agents/WorkingAgent.h>
#include <cstring>

using namespace std;

WorkingAgent::WorkingAgent(MainAgent* mainAgent, Map* theMap): Agent (theMap), refMainAgent_ (mainAgent) {
	setNameAgent(const_cast<char*>("WORK_AGENT"));
	setRecolectTime(0);
}

WorkingAgent::~WorkingAgent() {
}

Package* WorkingAgent::readFIPAPackage (Package* p) {
	Package* answer;
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
			case GO_RESOURCE_LOCATION:
				//Realizar búsqueda dada esta dirección
				followRoute(p -> getContent().at(0));
				answer = new Package (getNameAgent(), p -> getSender(), CONFIRM);
				setState(FOLLOWING_RES_ROUTE);
				break;
			case COME_BACK:
				followRoute(p -> getContent().at(0));
				answer = new Package (getNameAgent(), p -> getSender(), CONFIRM);
				setState(FOLLOWING_RET_ROUTE);
				break;
			default:
                std::cout << "No se entiende el tipo del paquete recibido." << std::endl;
			}
		}
	}
	return answer;
}

void WorkingAgent::followRoute(std::string route) {
	cout << "SEGUIR LA RUTA: " << route << endl;
	vector<Direction> camino;
	int posIni = route.find("[");
	int posCorchFin = route.find("]");
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
		camino.push_back(strToDirectionEnum(dirTemp));
	}


	for (unsigned int i = 0; i < camino.size(); ++i) {
		m_routes.push_back(camino[camino.size() - i]);
	}
	cout << "RUTA que SEGUIRA el AGENTE!! " << endl;
	for (unsigned int i = 0; i < m_routes.size(); ++i)
		cout << m_routes.at(i) <<  " ";
	cout << endl;
}

void WorkingAgent::actDependingOfState () {
	switch (getState()) {
	case RECOLECTING:
		if (getRecolectTime() < 10)
			setRecolectTime(getRecolectTime() + 1);
		else {
			setState(FULL_OF_RESOURCES);
			getRefMainAgent() -> readFIPAPackage(new Package(getNameAgent(), getRefMainAgent() -> getNameAgent(), COME_BACK));
		}
		break;
	case FOLLOWING_ROUTE:
		if (!routedMove()) {
			setState(AVAILABLE);
			getRefMainAgent() -> readFIPAPackage(new Package(getNameAgent(), getRefMainAgent() -> getNameAgent(), ARRIVED_GOAL));
		}
		break;
	case PUTTING_RESOURCE:
		if (getRecolectTime() > 0) {
			setRecolectTime(getRecolectTime() - 1);
		} else {
			setState(AVAILABLE);
			getRefMainAgent() -> readFIPAPackage(new Package(getNameAgent(), getRefMainAgent() -> getNameAgent(), CONFIRM));
		}
		break;
	case FOLLOWING_RES_ROUTE:
		if (!routedMove()) {
			setState(RECOLECTING);
			getRefMainAgent() -> readFIPAPackage(new Package(getNameAgent(), getRefMainAgent() -> getNameAgent(), ARRIVED_GOAL));
		}
		break;
	case FOLLOWING_RET_ROUTE:
		if (!routedMove()) {
			setState(PUTTING_RESOURCE);
			getRefMainAgent() -> readFIPAPackage(new Package(getNameAgent(), getRefMainAgent() -> getNameAgent(), ARRIVED_GOAL));
		}
		break;
	}

}

unsigned int WorkingAgent::getRecolectTime() const {
	return m_recolectTime;
}

void WorkingAgent::setRecolectTime(unsigned int recolectTime) {
	m_recolectTime = recolectTime;
}

MainAgent* WorkingAgent::getRefMainAgent() {
	return refMainAgent_;
}

