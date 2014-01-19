/*
 * MainAgent.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/agents/MainAgent.h>
#include <model/agents/SearchAgent.h>
#include <model/agents/WorkingAgent.h>

#include <model/bdi/BeliefSet.h>
#include <model/bdi/Desire.h>
#include <model/bdi/Intention.h>

#include <controller/director/tools/FileLog.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/binomial_distribution.hpp>
#include <boost/random/negative_binomial_distribution.hpp>
#include <boost/random/random_device.hpp>

MainAgent::MainAgent(Simulator* refModel, Map* theMap): Agent(theMap), refSimulator_(refModel) {
	logAction(LOG_INIT);
	m_beliefSet = new BeliefSet();
    m_desires = new Desire();
    createInitialBelieves();
    createDesires();
    m_intentions = new Intention(*dynamic_cast<Agent*>(this), *m_beliefSet, *m_desires);
	setNameAgent(const_cast<char*>("MAIN_AGENT"));
	createRndInitialPos (const_cast<Map*>(refSimulator_->getMap()));
	initAgents ();
}

MainAgent::~MainAgent() {
	logAction(LOG_END);
    if (m_beliefSet != NULL) {
        delete m_beliefSet;
        m_beliefSet = NULL;
    }
    if(m_desires != NULL) {
        delete m_desires;
        m_desires = NULL;
    }
}
void MainAgent::initAgents() {
	// Creación inicial de los agentes exploradores
	// --- Primer agente (Norte)
	SearchAgent* searchg1 = new SearchAgent (this, refMap_);
	searchg1 -> setPosition (Point (getPosition().first - 1, getPosition().second));
	m_Vagents.push_back(searchg1);
	// --- Segundo agente (Sur)
	SearchAgent* searchg2 = new SearchAgent (this, refMap_);
	searchg2 -> setPosition (Point (getPosition().first + 1, getPosition().second));
	m_Vagents.push_back(searchg2);
	// --- Tercer agente (Este)
	SearchAgent* searchg3 = new SearchAgent (this, refMap_);
	searchg3 -> setPosition (Point (getPosition().first, getPosition().second + 1));
	m_Vagents.push_back(searchg3);
	// --- Cuarto agente (Oeste)
	SearchAgent* searchg4 = new SearchAgent (this, refMap_);
	searchg4 -> setPosition (Point (getPosition().first, getPosition().second - 1));
	m_Vagents.push_back(searchg4);

	// Creación inicial de los agentes trabajadores
	// --- Primer agente (NOeste)
	WorkingAgent* working1 = new WorkingAgent (this, refMap_);
	working1 -> setPosition (Point (getPosition().first - 1, getPosition().second - 1));
	m_WorVecAgents.push_back(working1);
	// --- Segundo agente (NEste)
	WorkingAgent* working2 = new WorkingAgent (this, refMap_);
	working2 -> setPosition (Point (getPosition().first - 1, getPosition().second + 1));
	m_WorVecAgents.push_back(working2);
	// --- Tercer agente (SEste)
	WorkingAgent* working3 = new WorkingAgent (this, refMap_);
	working3 -> setPosition (Point (getPosition().first + 1, getPosition().second + 1));
	m_WorVecAgents.push_back(working3);
	// --- Cuarto agente (SOeste)
	WorkingAgent* working4 = new WorkingAgent (this, refMap_);
	working4 -> setPosition (Point (getPosition().first + 1, getPosition().second - 1));
	m_WorVecAgents.push_back(working4);

	dynamic_cast<SearchAgent*>(m_Vagents[0]) -> initExplorationMove(m_Vagents[0]->getPosition().first
			                                                       ,m_Vagents[0]->getPosition().second
	                                                               , NORTH);
	m_Vagents[0] -> setState(SEARCHING);
}
bool temp = false;
bool MainAgent::update () {
	bool result = false;

	// TODO: crear una ruta y enviar un agente a ella!!
	/*if (!temp) {
		sendToRoute(getWorVecAgents().at(0) -> getPosition(), Point (getWorVecAgents().at(0) -> getPosition().first, getWorVecAgents().at(0) -> getPosition().second - 5));
		temp = true;
	}*/

	/*
   if (m_WorVecAgents[0]->checkRouteMoves()) {
      if (m_WorVecAgents[0]->routedMove()) {
//         cout << "MOVIENDO AGENTE TRABAJADOR EN RUTA"  << endl;
         result = true;
      }
   } else if (m_WorVecAgents[0]->controledMove(NWEST)) {
      result = true;
   }
   if (m_WorVecAgents[1]->controledMove(NEAST)) {
      result = true;
   }
   if (m_WorVecAgents[2]->controledMove(SEAST)) {
      result = true;
   }
   if (m_WorVecAgents[3]->controledMove(SWEST)) {
      result = true;
   }*/

		//Prueba de seguimiento de rutas !!
//	  if (m_Vagents[0] -> getState() == AVAILABLE) {
//		Package* p = new Package (getNameAgent(), m_Vagents[0] -> getNameAgent(), GO_LOCATION);
//		vector<string> dirTemp;
//		dirTemp.push_back("[NORTH,NORTH,NORTH,NORTH,NORTH,NORTH,NORTH,NORTH]");
//		p -> setContent(dirTemp);
//		m_Vagents[0] -> readFIPAPackage(p);
//	}

//	if (m_WorVecAgents[0] -> getState() == AVAILABLE) {
//		Package* q = new Package (getNameAgent(), m_WorVecAgents[0] -> getNameAgent(), GO_RESOURCE_LOCATION);
//		vector<string> dirTemp2;
//		dirTemp2.push_back("[EAST,EAST,EAST,EAST,EAST,EAST,EAST]");
//		q -> setContent(dirTemp2);
//		m_WorVecAgents[0] -> readFIPAPackage(q);
//	}

	return updateMiniAgents();
}

bool MainAgent::updateMiniAgents () {
	bool result = false;
	for (unsigned int i = 0; i < getVAgents().size(); i++) {
		if (getVAgents().at(i) -> getState() != AVAILABLE) {
			getVAgents().at(i) -> actDependingOfState();
			result = true;
		}
	}

	for (unsigned int i = 0; i < getWorVecAgents().size(); i++) {
		if (getWorVecAgents().at(i) -> getState() != AVAILABLE) {
			getWorVecAgents().at(i) -> actDependingOfState();
			result = true;
		}
	}

	return result;
}

void MainAgent::createRndInitialPos (Map* mainMap) {
	logAction(LOG_F_INIT);
	boost::random::random_device rndDev;
	boost::random::mt11213b probabilityRNG;
	boost::random::mt11213b layoutRNG;
	boost::random::mt11213b positionRNG;
	boost::random::mt11213b typeRNG;
	boost::random::negative_binomial_distribution<> probabilityDistrib(3, 0.5);
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
		BYTE tempCentro = ((*mainMap)(m_position.first, m_position.second) & MASK_TERRAIN);
		BYTE tempArrIzq = ((*mainMap)(m_position.first - 1, m_position.second - 1) & MASK_TERRAIN);
		BYTE tempArr = ((*mainMap)(m_position.first, m_position.second - 1) & MASK_TERRAIN);
		BYTE tempArrDer = ((*mainMap)(m_position.first + 1, m_position.second - 1) & MASK_TERRAIN);
		BYTE tempIzq = ((*mainMap)(m_position.first - 1, m_position.second) & MASK_TERRAIN);
		BYTE tempDer = ((*mainMap)(m_position.first + 1, m_position.second) & MASK_TERRAIN);
		BYTE tempAbjIzq = ((*mainMap)(m_position.first - 1, m_position.second + 1) & MASK_TERRAIN);
		BYTE tempAbj = ((*mainMap)(m_position.first, m_position.second + 1) & MASK_TERRAIN);
		BYTE tempAbjDer = ((*mainMap)(m_position.first + 1, m_position.second + 1) & MASK_TERRAIN);

		if (tempCentro == TERRAIN_GROUND && tempArrIzq == TERRAIN_GROUND && tempArr == TERRAIN_GROUND
				&& tempArrDer == TERRAIN_GROUND && tempIzq == TERRAIN_GROUND && tempDer == TERRAIN_GROUND &&
				tempAbjIzq == TERRAIN_GROUND && tempAbj == TERRAIN_GROUND && tempAbjDer == TERRAIN_GROUND){
			condition = true;
		}

	} while (!condition);

	std::cout << "Position generated on: x = " << m_position.first << " , y = " << m_position.second << std::endl;
}

void MainAgent::logAction(int index) {
	if (BASIC_LOG) {
		switch (index) {
		case LOG_INIT:
			std::cout << "---Generando el Agente principal " << std::endl;
			break;
		case LOG_END:
			std::cout << "---Destruyendo el Agente principal " << std::endl;
			break;
		case LOG_F_INIT:
			std::cout << "---Llamando a la función createRndInitialPos () del agente principal." << std::endl;
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
			refSimulator_->log("---Llamando a la función createRndInitialPos () del agente principal.");
			break;
		default:
			break;
		}
	}
}

Package* MainAgent::readFIPAPackage (Package* p) {
	Package* answer = new Package (getNameAgent(), p -> getSender(), NOT_UNDERSTOOD);

	// Comprobamos que el paquete es de la conversación actual
	if (p -> getIdComm() == getIdComm()) {
		// Comprobamos que el paquete va destinado al agente correcto
		if (p -> getReceiver() == getNameAgent()) {
			switch (p -> getType()) {
			case NOT_UNDERSTOOD:
				std::cout << "NOT_UNDERSTOOD: recibido paquete cuyo contenido no es entendible" << std::endl;
				break;
			case CONFIRM:
				std::cout << "CONFIRM: Confirmada la operación." << std::endl;
				break;
			case ARRIVED_GOAL:
				std::cout << "Se ha confirmado la finalización de la ruta." << std::endl;
				break;
			case MAP_UPDATE:
				break;
			case LOCATED_OBSTACLE:
				break;
			case END_LIMITS:
				break;
			default:
				std::cout << "No se entiende el tipo del paquete recibido." << std::endl;
			}
		}

	}
	return answer;
}

Package* MainAgent::createFIPAPackage() {
	/*Package* p = new Package (getNameAgent(), getVAgents().at(0) -> getNameAgent(), CONFIRM);
	std::cout << "Creado paquete CONFIRM por la nave principal: " << p -> getSender() << p -> getReceiver() << p -> getType() << std::endl;*/

	/*Package* p = new Package (getNameAgent(), getWorVecAgents().at(0) -> getNameAgent(), GO_RESOURCE_LOCATION);
	std::vector<std::string> temp;
	temp.push_back();
	p -> setContent(temp);
	std::cout << "Creado paquete GO_RESOURCE_LOCATION por la nave principal: " << p -> getSender() << p -> getReceiver() << p -> getType() << std::endl;
	return p;*/
}

void MainAgent::sendToRoute(Point s, Point e) {
	PathFindingTree* tree = new PathFindingTree (this, s, e);
	std::string route = "";

	tree -> calculateHeuristicRoute();
	route += tree -> getRoute();
	std::cout << "Ruta mínima = " << route << std::endl;
	std::vector<std::string> vect;
	//bool doIt = false;
	//for (unsigned int i = 0; i < getWorVecAgents().size(); ++i) {
		//if (!doIt) {
			//if (getWorVecAgents().at(0)->getState() == AVAILABLE) {
				Package* p = new Package (this->getNameAgent(), getWorVecAgents().at(0)->getNameAgent(), GO_RESOURCE_LOCATION);
				vect.push_back(route);
				p ->setContent(vect);
				getWorVecAgents().at(0) -> readFIPAPackage(p);
				//doIt = true;
			//}
		//}
	//}
	//delete tree;
}

// Manejadores de atributos
std::vector<Agent*>& MainAgent::getVAgents () {
	return m_Vagents;
}
std::vector<Agent*>& MainAgent::getWorVecAgents() {
	return m_WorVecAgents;
}
std::vector<Package*>& MainAgent::getPackagesFipa() {
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
    m_beliefSet->setExploredCells(i);
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

