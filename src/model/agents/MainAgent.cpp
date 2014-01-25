/*
 * MainAgent.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/agents/MainAgent.h>
#include <model/agents/SearchAgent.h>
#include <model/agents/WorkingAgent.h>
#include <model/agents/tools/PathFindingTree.h>

#include <model/bdi/Belief.h>
#include <model/bdi/BeliefSet.h>
#include <model/bdi/Desire.h>
#include <model/bdi/Intention.h>

#include <controller/director/tools/FileLog.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/binomial_distribution.hpp>
#include <boost/random/negative_binomial_distribution.hpp>
#include <boost/random/random_device.hpp>

using namespace std;
using namespace boost;

MainAgent::MainAgent(Simulator* refModel, Map* theMap) :
	Agent(theMap), refSimulator_(refModel) {
	logAction(LOG_INIT);
	m_beliefSet = new BeliefSet(*theMap);
	m_desires = new Desire();
	createInitialBelieves();
	createDesires();
	m_intentions = new Intention(*dynamic_cast<Agent*>(this), *m_beliefSet,
	                             *m_desires);
	setNameAgent(const_cast<char*>("MAIN_AGENT"));
	createRndInitialPos(const_cast<Map*>(refSimulator_->getMap()));
	initAgents();
}

MainAgent::~MainAgent() {
	logAction(LOG_END);

	if (m_beliefSet != NULL) {
		delete m_beliefSet;
		m_beliefSet = NULL;
	}

	if (m_desires != NULL) {
		delete m_desires;
		m_desires = NULL;
	}
}
void MainAgent::initAgents() {
	// Creación inicial de los agentes exploradores
	// --- Primer agente (Norte)
	SearchAgent* searchg1 = new SearchAgent(this, refMap_);
	searchg1->setPosition(Point(getPosition().first - 1, getPosition().second));
	m_Vagents.push_back(searchg1);
	// --- Tercer agente (Este)
	SearchAgent* searchg3 = new SearchAgent(this, refMap_);
	searchg3->setPosition(Point(getPosition().first, getPosition().second + 1));
	m_Vagents.push_back(searchg3);
	// --- Segundo agente (Sur)
	SearchAgent* searchg2 = new SearchAgent(this, refMap_);
	searchg2->setPosition(Point(getPosition().first + 1, getPosition().second));
	m_Vagents.push_back(searchg2);
	// --- Cuarto agente (Oeste)
	SearchAgent* searchg4 = new SearchAgent(this, refMap_);
	searchg4->setPosition(Point(getPosition().first, getPosition().second - 1));
	m_Vagents.push_back(searchg4);

	// Creación inicial de los agentes trabajadores
	// --- Primer agente (NOeste)
	WorkingAgent* working1 = new WorkingAgent(this, refMap_);
	working1->setPosition(
	        Point(getPosition().first - 1, getPosition().second - 1));
	m_WorVecAgents.push_back(working1);
	// --- Segundo agente (NEste)
	WorkingAgent* working2 = new WorkingAgent(this, refMap_);
	working2->setPosition(
	        Point(getPosition().first - 1, getPosition().second + 1));
	m_WorVecAgents.push_back(working2);
	// --- Tercer agente (SEste)
	WorkingAgent* working3 = new WorkingAgent(this, refMap_);
	working3->setPosition(
	        Point(getPosition().first + 1, getPosition().second + 1));
	m_WorVecAgents.push_back(working3);
	// --- Cuarto agente (SOeste)
	WorkingAgent* working4 = new WorkingAgent(this, refMap_);
	working4->setPosition(
	        Point(getPosition().first + 1, getPosition().second - 1));
	m_WorVecAgents.push_back(working4);

}

bool MainAgent::update() {
	m_intentions->update();
	return updateMiniAgents();
}

bool MainAgent::updateMiniAgents() {
	bool result = false;

	for (unsigned int i = 0; i < getVAgents().size(); i++) {
		if (getVAgents().at(i)->getState() != AVAILABLE) {
			getVAgents().at(i)->actDependingOfState();
			result = true;
		}
	}

	for (unsigned int i = 0; i < getWorVecAgents().size(); i++) {
		if (getWorVecAgents().at(i)->getState() != AVAILABLE) {
			getWorVecAgents().at(i)->actDependingOfState();
			result = true;
		}
	}

	return result;
}

void MainAgent::createRndInitialPos(Map* mainMap) {
	logAction(LOG_F_INIT);
	boost::random::random_device rndDev;
	boost::random::mt11213b probabilityRNG;
	boost::random::mt11213b layoutRNG;
	boost::random::mt11213b positionRNG;
	boost::random::mt11213b typeRNG;
	boost::random::binomial_distribution<> probabilityDistrib(3, 0.5);
	boost::random::uniform_int_distribution<> positionDistrib(2, MAP_WIDTH - 2); // Porque WIDTH = HEIGHT
	boost::random::uniform_int_distribution<> typeDistrib(3, 5);

	bool condition = false; // Indica si está en una posición CORRECTA

	do {
		// posición x del agente principal
		positionRNG.seed(rndDev());
		positionRNG();
		positionDistrib.reset();
		m_position.first = positionDistrib(positionRNG);
		// posicion y del agente principal
		positionRNG.seed(rndDev());
		positionRNG();
		positionDistrib.reset();
		m_position.second = positionDistrib(positionRNG);

		// Comprobación de vecindad de la nave -> para la colocación de agentes
		BYTE tempCentro = ((*mainMap)(m_position.first, m_position.second)
		                   & MASK_TERRAIN);
		BYTE tempArrIzq = ((*mainMap)(m_position.first - 1,
		                              m_position.second - 1) & MASK_TERRAIN);
		BYTE tempArr = ((*mainMap)(m_position.first, m_position.second - 1)
		                & MASK_TERRAIN);
		BYTE tempArrDer = ((*mainMap)(m_position.first + 1,
		                              m_position.second - 1) & MASK_TERRAIN);
		BYTE tempIzq = ((*mainMap)(m_position.first - 1, m_position.second)
		                & MASK_TERRAIN);
		BYTE tempDer = ((*mainMap)(m_position.first + 1, m_position.second)
		                & MASK_TERRAIN);
		BYTE tempAbjIzq = ((*mainMap)(m_position.first - 1,
		                              m_position.second + 1) & MASK_TERRAIN);
		BYTE tempAbj = ((*mainMap)(m_position.first, m_position.second + 1)
		                & MASK_TERRAIN);
		BYTE tempAbjDer = ((*mainMap)(m_position.first + 1,
		                              m_position.second + 1) & MASK_TERRAIN);

		if (tempCentro == TERRAIN_GROUND && tempArrIzq == TERRAIN_GROUND
		                && tempArr == TERRAIN_GROUND && tempArrDer == TERRAIN_GROUND
		                && tempIzq == TERRAIN_GROUND && tempDer == TERRAIN_GROUND
		                && tempAbjIzq == TERRAIN_GROUND && tempAbj == TERRAIN_GROUND
		                && tempAbjDer == TERRAIN_GROUND) {
			condition = true;
		}

	} while (!condition);

	cout << "Position generated on: x = " << m_position.first << " , y = "
	          << m_position.second << endl;
}

void MainAgent::logAction(int index) {
	if (BASIC_LOG) {
		switch (index) {
		case LOG_INIT:
			cout << "---Generando el Agente principal " << endl;
			break;

		case LOG_END:
			cout << "---Destruyendo el Agente principal " << endl;
			break;

		case LOG_F_INIT:
			cout << "---Llamando a la función createRndInitialPos () del agente principal." << endl;
			break;

		default:
			break;
		}
	}

	if (ADVAN_LOG) {
		switch (index) {
		case LOG_INIT:
			refSimulator_->log("---Generando el Agente principal ");
			break;

		case LOG_END:
			refSimulator_->log("---Destruyendo el Agente principal ");
			break;

		case LOG_F_INIT:
			refSimulator_->log(
			        "---Llamando a la función createRndInitialPos () del agente principal.");
			break;

		default:
			break;
		}
	}
}

Package* MainAgent::readFIPAPackage(Package* p) {
	Package* answer = new Package(getNameAgent(), p->getSender(),
	                              NOT_UNDERSTOOD);

	// Comprobamos que el paquete es de la conversación actual
	if (p->getIdComm() == getIdComm()) {
		// Comprobamos que el paquete va destinado al agente correcto
		if (p->getReceiver() == getNameAgent()) {
			switch (p->getType()) {
			case NOT_UNDERSTOOD:
				cout << "NOT_UNDERSTOOD: recibido paquete cuyo contenido no es entendible" << endl;
				break;

			case CONFIRM:
				cout << "CONFIRM: Recibido paquete que indica -> Confirmada la operación." << endl;
				break;

			case ARRIVED_GOAL:
				cout << "Se ha confirmado la finalización de la ruta." << endl;
				Belief* belief;
				belief = new Belief("AGENT_ARRIVED");
				m_beliefSet->add(p->getSender(), belief);
				break;

			case MAP_UPDATE:
				break;

			case LOCATED_OBSTACLE:
				break;

			case END_LIMITS:
				break;

			case COME_BACK:
				sendToRoute(p->getRefSenderAgent()->getPosition(),
				            getPosition(), p->getRefSenderAgent(), COME_BACK);
				break;

			case DIRECTION_SEARCH:

				break;

			default:
				cout << "No se entiende el tipo del paquete recibido." << endl;

			}
		}

	}

	return answer;
}

void MainAgent::sendToRoute(Point s, Point e, Agent* theAgent, Type theType) {
	if (s != e) {
		PathFindingTree* tree = new PathFindingTree(*this, s, e);
		std::string route = "";

		tree->calculateHeuristicRoute();
		route += tree->getRoute();
		std::cout << "Ruta mínima = " << route << std::endl;
		std::vector<std::string> vect;

		Package* p = new Package(this->getNameAgent(), theAgent->getNameAgent(),
				theType);
		vect.push_back(route);
		p->setContent(vect);
		readFIPAPackage(theAgent->readFIPAPackage(p));

		delete (tree);
	}
}

// Manejadores de atributos
vector<Agent*>& MainAgent::getVAgents() {
	return m_Vagents;
}
vector<Agent*>& MainAgent::getWorVecAgents() {
	return m_WorVecAgents;
}
vector<Package*>& MainAgent::getPackagesFipa() {
	return m_packagesFIPA;
}
const Map* MainAgent::getMap() const {
	return (refSimulator_->getMap());
}

void MainAgent::setKnownMapPosition(int i, int j, bool value) {
	m_beliefSet->setKnownMapCell(i, j, value);
}

bool MainAgent::knownMapPosition(int i, int j) {
	return m_beliefSet->knownMapCell(i, j);
}

void MainAgent::checkedCells(int i) {
	m_beliefSet->sumExploredCells(i);
}

bool** MainAgent::getKnownMap() {
	return (m_beliefSet->getKnownMap());
}

/********************************************************************
 *                  FUNCIONES BDI                                   *
 ********************************************************************/

void MainAgent::createInitialBelieves() {
	m_beliefSet->setPosition(m_position);
}

void MainAgent::updatedKnownMap() {
	refSimulator_->updatedKnownMap();
}

void MainAgent::createDesires() {
	m_desires->add("Settlement_Built", false);
	m_desires->add("Settlement_Placement_Found", false);
	m_desires->add("Resources_Gathered", false);
	m_desires->add("50_Percent_Explored", false);
	m_desires->add("100_Percent_Explored", false);
}

