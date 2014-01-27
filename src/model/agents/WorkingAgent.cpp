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

WorkingAgent::WorkingAgent(MainAgent* mainAgent, Map* theMap): Agent(theMap), refMainAgent_(mainAgent) {
	setNameAgent(const_cast<char*>("WORK_AGENT"));
	setRecolectTime(0);
	activeRecolecting_ = true;
}

WorkingAgent::~WorkingAgent() {
}

Package* WorkingAgent::readFIPAPackage(Package* p) {
	Package* answer;

	// Comprobamos que el paquete es de la conversación actual
	if (p -> getIdComm() == getIdComm()) {
		// Comprobamos que el paquete va destinado al agente correcto
		if (p -> getReceiver() == getNameAgent()) {
			switch (p -> getType()) {
			case NOT_UNDERSTOOD:
				cout << "Working Agent: --- NOT_UNDERSTOOD: recibido paquete cuyo contenido no es entendible. ---" << endl;
				return NULL;
				break;

			case CONFIRM:
				cout << "Working Agent: --- CONFIRM: Confirmada la operación. ---" << endl;
				return NULL;
				break;

			case GO_RESOURCE_LOCATION:
				//Realizar búsqueda dada esta dirección
				followRoute(p -> getContent().at(0));
				m_ret_routes.clear();
				for (int i = 0; i < m_routes.size(); ++i) {
					m_ret_routes.push_back(calculateInverseDirection(m_routes[m_routes.size() - (i + 1)]));
				}
				answer = new Package(getNameAgent(), p -> getSender(), CONFIRM);
				setState(FOLLOWING_RES_ROUTE);
				break;

			case COME_BACK:
				followRoute(p -> getContent().at(0));
				answer = new Package(getNameAgent(), p -> getSender(), CONFIRM);
				setState(FOLLOWING_RET_ROUTE);
				break;

			case GO_LOCATION:
				followRoute(p -> getContent().at(0));
				answer = new Package(getNameAgent(), p -> getSender(), CONFIRM);
				setState(FOLLOWING_ROUTE);
				break;

			default:
				cout << "Working Agent: --- ERROR! No se entiende el tipo del paquete recibido. ---" << endl;
			}
		}
	}

	return answer;
}


void WorkingAgent::actDependingOfState() {
	switch (getState()) {
	case RECOLECTING:
		if (getRecolectTime() < 250)
			setRecolectTime(getRecolectTime() + 1);
		else {
			m_routes.clear();
			for (int i = 0; i < m_ret_routes.size(); ++i) {
				m_routes.push_back(m_ret_routes[i]);
			}
			setState(FOLLOWING_RET_ROUTE);
		}
		break;
	case FOLLOWING_ROUTE:
		if (!routedMove()) {
			setState(AVAILABLE);
			getRefMainAgent() -> readFIPAPackage(new Package(getNameAgent(), getRefMainAgent() -> getNameAgent(), CONFIRM));
		}
		break;
	case PUTTING_RESOURCE:
		if (getRecolectTime() > 0) {
			setRecolectTime(getRecolectTime() - 1);
		} else {
			setState(AVAILABLE);
			m_ret_routes.clear();
			getRefMainAgent() -> readFIPAPackage(new Package(getNameAgent(), getRefMainAgent() -> getNameAgent(), CONFIRM));
		}
		break;
	case FOLLOWING_RES_ROUTE:
		if (!routedMove()) {
			setState(RECOLECTING);
			getRefMainAgent() -> readFIPAPackage(new Package(getNameAgent(), getRefMainAgent() -> getNameAgent(), CONFIRM));
		}
		break;
	case FOLLOWING_RET_ROUTE:
		if (!routedMove()) {
			setState(PUTTING_RESOURCE);
			getRefMainAgent() -> readFIPAPackage(new Package(getNameAgent(), getRefMainAgent() -> getNameAgent(), CONFIRM));
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
