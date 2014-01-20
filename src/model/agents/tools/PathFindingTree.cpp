/*
 * PathFindingTree.cpp
 *
 *  Created on: 19/01/2014
 *      Author: maikel
 */

#include <model/agents/tools/PathFindingTree.h>
#include <Tools.h>

PathFindingTree::PathFindingTree(MainAgent* refMAg, Point s, Point e) {
	setRoot(new Node (s, "RAIZ", NULL)); // Raíz no tiene padre!
	setGoal(new Node (e, " ", getRoot()));
	setRefMainAgent(refMAg);

	setActual(getRoot());
}

PathFindingTree::~PathFindingTree() {
	delete getRoot();
	delete getGoal();
	delete getActual();
}

// A*
void PathFindingTree::calculateHeuristicRoute () {
	std::string routeMin = "]";
	if (getActual()->getP().first > 0 && getActual()->getP().first < MAP_WIDTH &&
			getActual()->getP().second > 0 && getActual()->getP().second < MAP_HEIGHT &&
			((*getMap())(getActual()->getP().first, getActual()->getP().second) & MASK_TERRAIN) == TERRAIN_GROUND) {
		while (!getActual() -> areEquals(getGoal())) {
			expandir();
			calculateBetterNode();
		}

		while (getActual() -> getPadre() -> getPadre() != NULL) {
			routeMin = "," + getActual() -> getMov() + routeMin;
			setActual(getActual() -> getPadre());
		}
		routeMin = "[" + getActual() -> getMov() + routeMin;
		setRoute(routeMin); // Asignamos como ruta mínima definitiva la calculada por el algoritmo
	} else {
		throw "AVISOOO!! No se puede calcular la ruta hacia el destino indicado!!";
	}
}

void PathFindingTree::expandir () {
	// 1º Creamos nodos auxiliares para cada movimiento posible.
	Node* nodeNorth = new Node (Point (getActual() -> getP().first - 1, getActual() -> getP().second), "NORTH", getActual());
	Node* nodeEast = new Node (Point (getActual() -> getP().first, getActual() -> getP().second + 1), "EAST", getActual());
	Node* nodeSouth = new Node (Point (getActual() -> getP().first + 1, getActual() -> getP().second), "SOUTH", getActual());
	Node* nodeWest = new Node (Point (getActual() -> getP().first, getActual() -> getP().second - 1), "WEST", getActual());

	// 2º Comprobamos qué hijo se sale de los límites del tablero
	// 3º Comprobamos que no son obtáculos.
	// 4º Comprobamos que no están en la ruta mínima.
	if (nodeNorth -> isPointIntoLimitsMap(MAP_WIDTH, MAP_HEIGHT) &&
		(((*getMap())(nodeNorth -> getP().first, nodeNorth -> getP().second) & MASK_TERRAIN) == TERRAIN_GROUND) &&
		!isInRoute(nodeNorth)) {
		nodeNorth->setDistFromStart(nodeNorth->getDistFromStart() + 1);
		getActual() -> getNodosHijos().push_back(nodeNorth);
	}

	if (nodeEast -> isPointIntoLimitsMap(MAP_WIDTH, MAP_HEIGHT) &&
		(((*getMap())(nodeEast -> getP().first, nodeEast -> getP().second) & MASK_TERRAIN) == TERRAIN_GROUND) &&
		!isInRoute(nodeEast)) {
		nodeEast->setDistFromStart(nodeEast->getDistFromStart() + 1);
		getActual() -> getNodosHijos().push_back(nodeEast);
	}

	if (nodeSouth -> isPointIntoLimitsMap(MAP_WIDTH, MAP_HEIGHT) &&
		(((*getMap())(nodeSouth -> getP().first, nodeSouth -> getP().second) & MASK_TERRAIN) == TERRAIN_GROUND) &&
		!isInRoute(nodeSouth)) {
		nodeSouth->setDistFromStart(nodeSouth->getDistFromStart() + 1);
		getActual() -> getNodosHijos().push_back(nodeSouth);
	}

	if (nodeWest -> isPointIntoLimitsMap(MAP_WIDTH, MAP_HEIGHT) &&
		(((*getMap())(nodeWest -> getP().first, nodeWest -> getP().second) & MASK_TERRAIN) == TERRAIN_GROUND) &&
		!isInRoute(nodeWest)) {
		nodeWest->setDistFromStart(nodeWest->getDistFromStart() + 1);
		getActual() -> getNodosHijos().push_back(nodeWest);
	}

}

void PathFindingTree::calculateBetterNode () {
	//INFO: Cola de Nodos -> push_back (), pop_front ()
	std::queue<Node*> colaNodos;
	Node* start = new Node ((*getRoot()));
	int distance = 99999;

	colaNodos.push(start);
	while (!colaNodos.empty()) {
		for (unsigned int i = 0; i < colaNodos.front() -> getNodosHijos().size(); ++i) {
			if (colaNodos.front() -> getNodosHijos().at(i) -> getNodosHijos().size() > 0) { // No son nodos HOJA!!
				colaNodos.push(colaNodos.front() -> getNodosHijos().at(i));
			} else if (!colaNodos.front() -> getNodosHijos().at(i) -> isVisitado()){ // Son nodos HOJA
				int val = heuristicValue(colaNodos.front() -> getNodosHijos().at(i));
				if (val < distance) {
					distance = val;
					setActual(colaNodos.front() -> getNodosHijos().at(i));
				}
			}
		}
		colaNodos.pop();
	}
}

bool PathFindingTree::isInRoute (Node* nodeCheck) {
	Node* temp = new Node (*(getActual()));
	bool result = false;
	std::cout << "Antes del While de isInRoute ()" <<std::endl;
	while (temp -> getPadre() != NULL) {
		std::cout << "Buscando en ruta.... Padre = "<< temp->getPadre()<<std::endl;
		if (temp -> areEquals(nodeCheck))
			result = true;
		temp = temp -> getPadre();
	}
	return result;
}

int PathFindingTree::heuristicValue (Node* start) {
	return ( 	std::abs (start->getP().first - getGoal()->getP().first) +
			std::abs (start->getP().second - getGoal()->getP().second) +
			start -> getDistFromStart() );
}

Map* PathFindingTree::getMap () {
	return const_cast<Map*> (m_refMainAgent -> getMap());
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