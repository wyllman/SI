/*
 * PathFindingTree.cpp
 *
 *  Created on: 19/01/2014
 *      Author: maikel
 */

#include <model/agents/tools/PathFindingTree.h>
#include <Tools.h>

PathFindingTree::PathFindingTree(MainAgent* refMAg, Point s, Point e) {
	setRoot(new Node(s, "RAIZ", NULL)); // Raíz no tiene padre!
	setGoal(new Node(e, " ", getRoot()));
	setRefMainAgent(refMAg);

	setActual(getRoot());
}

PathFindingTree::~PathFindingTree() {
	delete getRoot();
	delete getGoal();
	delete getActual();
}

// A*

void PathFindingTree::calculateHeuristicRoute() {
	elPutoVector.clear();
	std::string routeMin = "]";
	if (getActual()->getP().first > 0 && getActual()->getP().first < MAP_WIDTH
			&& getActual()->getP().second > 0
			&& getActual()->getP().second < MAP_HEIGHT
			&& ((*getMap())(getGoal()->getP().first,
					getGoal()->getP().second) & MASK_TERRAIN)
					== TERRAIN_GROUND) {
		while (!getActual()->areEquals(getGoal())) {
			expandir();
			//std::cout<< "Expandiendo Nodo actual"<<std::endl;
			calculateBetterNode();
			//std::cout<< "Calculando Mejor Nodo"<<std::endl;
			//std::cin.get();
		}


		while (const_cast<Node*>(getActual()->getPadre()) != NULL) {
			routeMin = "," + getActual()->getMov() + routeMin;
			setActual(const_cast<Node*> (getActual()->getPadre()));
		}
		routeMin = "[" + getActual()->getMov() + routeMin;
		setRoute(routeMin); // Asignamos como ruta mínima definitiva la calculada por el algoritmo
	} else {
		throw "AVISOOO!! No se puede calcular la ruta hacia el destino indicado!!";
	}
}

void PathFindingTree::expandir() {
	int firstTmp = getActual()->getP().first + 1;
	int secondTmp = getActual()->getP().second;

	if ((firstTmp >= 0)
		&& (firstTmp < MAP_WIDTH)
		&& (secondTmp >= 0)
		&& (secondTmp < MAP_WIDTH)
		&& m_refMainAgent->getKnownMap()[firstTmp][secondTmp]
		&& (((*getMap())(firstTmp, secondTmp)) & MASK_TERRAIN) == TERRAIN_GROUND) {

		Node* nodeNorth = new Node( Point(firstTmp, secondTmp),
			"NORTH", getActual());
		if (!isInRoute(nodeNorth)) {
			nodeNorth->setDistFromStart(getActual()->getDistFromStart() + 1);
			getActual()->getNodosHijos().push_back(nodeNorth);

			//nodeNorth->setHeurVal(heuristicValue(nodeNorth));
			elPutoVector.push_back(nodeNorth);
		}
	}

	firstTmp = getActual()->getP().first;
	secondTmp = getActual()->getP().second + 1;

	if ((firstTmp >= 0)
		&& (firstTmp < MAP_WIDTH)
		&& (secondTmp >= 0)
		&& (secondTmp < MAP_WIDTH)
		&& m_refMainAgent->getKnownMap()[firstTmp][secondTmp]
		&& (((*getMap())(firstTmp, secondTmp)) & MASK_TERRAIN) == TERRAIN_GROUND) {

		Node* nodeEast = new Node( Point(firstTmp, secondTmp),
			"EAST", getActual());
		if (!isInRoute(nodeEast)) {
			nodeEast->setDistFromStart(getActual()->getDistFromStart() + 1);
			getActual()->getNodosHijos().push_back(nodeEast);

			//nodeEast->setHeurVal(heuristicValue(nodeEast));
			elPutoVector.push_back(nodeEast);

		}
	}

	firstTmp = getActual()->getP().first - 1;
	secondTmp = getActual()->getP().second;

	if ((firstTmp >= 0)
		&& (firstTmp < MAP_WIDTH)
		&& (secondTmp >= 0)
		&& (secondTmp < MAP_WIDTH)
		&& m_refMainAgent->getKnownMap()[firstTmp][secondTmp]
		&& (((*getMap())(firstTmp, secondTmp)) & MASK_TERRAIN) == TERRAIN_GROUND) {

		Node* nodeSouth = new Node( Point(firstTmp, secondTmp),
			"SOUTH", getActual());
		if (!isInRoute(nodeSouth)) {
			nodeSouth->setDistFromStart(getActual()->getDistFromStart() + 1);
			getActual()->getNodosHijos().push_back(nodeSouth);

			//nodeSouth->setHeurVal(heuristicValue(nodeSouth));
			elPutoVector.push_back(nodeSouth);

		}
	}

	firstTmp = getActual()->getP().first;
	secondTmp = getActual()->getP().second - 1;

	if ((firstTmp >= 0)
		&& (firstTmp < MAP_WIDTH)
		&& (secondTmp >= 0)
		&& (secondTmp < MAP_WIDTH)
		&& m_refMainAgent->getKnownMap()[firstTmp][secondTmp]
		&& (((*getMap())(firstTmp, secondTmp)) & MASK_TERRAIN) == TERRAIN_GROUND) {

		Node* nodeWest = new Node( Point(firstTmp, secondTmp),
			"WEST", getActual());
		if (!isInRoute(nodeWest)) {
			nodeWest->setDistFromStart(getActual()->getDistFromStart() + 1);
			getActual()->getNodosHijos().push_back(nodeWest);

			//nodeWest->setHeurVal(heuristicValue(nodeWest));
			elPutoVector.push_back(nodeWest);

		}
	}
	getActual()->setVisitado(true);
}

void PathFindingTree::calculateBetterNode() {
	//INFO: Cola de Nodos -> push_back (), pop_front ()
	std::queue<Node*> colaNodos;
	Node* start = new Node(*getRoot());
	int distance = 99999999;


	colaNodos.push(start);
	while (!colaNodos.empty()) {
		for (unsigned int i = 0; i < colaNodos.front()->getNodosHijos().size();
				++i) {
			if (colaNodos.front()->getNodosHijos().at(i)->getNodosHijos().size()
					> 0) { // No son nodos HOJA!!
				//std::cout << "No hoja" << std::endl;

				colaNodos.push(colaNodos.front()->getNodosHijos().at(i));
			} else if (!colaNodos.front()->getNodosHijos().at(i)->isVisitado()) { // Son nodos HOJA
				float val = heuristicValue(
						colaNodos.front()->getNodosHijos().at(i));
				//int val = colaNodos.front()->getHeurVal();
				if (val <= distance) {
					distance = val;
					setActual(colaNodos.front()->getNodosHijos().at(i));
				}
				//std::cout << "Si hoja" << std::endl;
			}
			//std::cout << "TAMPILA = " << colaNodos.size() << std::endl;
		}
		colaNodos.pop();
	}
}

bool PathFindingTree::isInRoute(Node* nodeCheck) {
	Node* temp;
	temp = new Node(*getActual());
	bool result = false;

	//std::cout << "Antes del While de isInRoute ()" << std::endl;
	while (temp->getPadre() != NULL) {
		//std::cout << "Buscando en ruta.... Padre = " << temp->getPadre()
				//<< std::endl;
		if (temp->areEquals(nodeCheck)) {
			result = true;
			break;
		}
		temp = const_cast<Node*> (temp->getPadre());
	}
	if (!result) {
		if (temp -> areEquals(nodeCheck)) {
			result = true;
		}
	}
	return result;
}

float PathFindingTree::heuristicValue(Node* start) {
	return ( 	std::abs (start->getP().first - getGoal()->getP().first) +
			std::abs (start->getP().second - getGoal()->getP().second) +
			start -> getDistFromStart() );
}

Map* PathFindingTree::getMap() {
	return const_cast<Map*>(m_refMainAgent->getMap());
}

Node* PathFindingTree::getActual() {
	return m_actual;
}

void PathFindingTree::setActual(Node* actual) {
	m_actual = actual;
}

Node* PathFindingTree::getGoal() {
	return m_Goal;
}

void PathFindingTree::setGoal(Node* goal) {
	m_Goal = goal;
}

MainAgent* PathFindingTree::getRefMainAgent() {
	return m_refMainAgent;
}

void PathFindingTree::setRefMainAgent(MainAgent* refMainAgent) {
	m_refMainAgent = refMainAgent;
}

Node* PathFindingTree::getRoot() {
	return m_Root;
}

void PathFindingTree::setRoot(Node* root) {
	m_Root = root;
}

std::string& PathFindingTree::getRoute() {
	return m_route;
}

void PathFindingTree::setRoute(std::string& route) {
	m_route = route;
}
