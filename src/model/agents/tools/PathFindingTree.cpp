/*
 * PathFindingTree.cpp
 *
 *  Created on: 19/01/2014
 *      Author: maikel
 */

#include <Tools.h>
#include <model/agents/tools/Node.h>
#include <model/agents/tools/PathFindingTree.h>
#include <model/agents/MainAgent.h>

#include <cstring>
#include <iostream>
#include <typeinfo>
#include <list>
#include <stdio.h>

using namespace std;

PathFindingTree::PathFindingTree(const MainAgent& agent, const Point& start, const Point& end) :
	m_rootNode(new Node(start, std::string("RAIZ"), *static_cast<Node*>(NULL))),
	m_goalNode(new Node(end, " ", *m_rootNode)),
	m_agent(const_cast<MainAgent*>(&agent)) {
	m_rootNode->setHeuristicDistance(heuristicValue(*m_rootNode));
}

PathFindingTree::~PathFindingTree() {
	if (m_rootNode != NULL) {
		delete m_rootNode;
		m_rootNode = NULL;
	}

	if (m_goalNode != NULL) {
		delete m_goalNode;
		m_goalNode = NULL;
	}

	if (!m_leafNodes.empty()) {
		for (uint32_t i = 0; i < m_leafNodes.size(); ++i) {
			if (m_leafNodes [i] != NULL) {
				delete m_leafNodes[i];
				m_leafNodes[i] = NULL;
			}
		}

		m_leafNodes.clear();
	}
}

// A*
// FIXME Hay que comprobar que el terreno sea pasable
// FIXME Hay alguna comprobacion o asignacion mal, el bucle no termina nunca
void PathFindingTree::calculateHeuristicRoute() {
	vector<Node*> closedSet;
	vector<Node*> openSet;
	vector<Node*>::iterator setIterator;
	vector<Node*>::iterator successorIterator;
	vector<Node*>::iterator bestIterator;
	Node* bestNode;
	bool success;
	bool existsInOpenSet;
	bool existsInClosedSet;
	uint32_t bestDistance;
	float currentDistance;
	bestNode = m_rootNode;

	cout << "Insertando root (" << m_rootNode->position().first << "," <<
	     m_rootNode->position().second << ")" << endl;
	cout << "Objetivo (" << m_goalNode->position().first << "," <<
	     m_goalNode->position().second << ")" << endl;
	openSet.push_back(m_rootNode);

	while (!openSet.empty() && !success) {
		bestDistance = 9999;

		// se busca el mejor nodo candidato en la lista
		for (setIterator = openSet.begin(); setIterator != openSet.end(); ++setIterator) {
			cout << "Comprobando nodo " << *setIterator << endl;
			currentDistance = (*setIterator)->objectiveDistance();

			if (currentDistance <= bestDistance) {
				bestDistance = currentDistance;
				bestNode = *setIterator;
				bestIterator = setIterator;
			}
		}

		cout << "Elegido nodo " << bestNode << " con distancia " <<
		     bestDistance << endl;
		expandNode(*bestNode);
		openSet.erase(bestIterator);

		for (successorIterator = bestNode->children()->begin(); successorIterator != bestNode->children()->end(); ++successorIterator) {
			cout << "Comprobando nodo hijo " << & (*successorIterator) << " (" << (*successorIterator)->position().first << "," <<
			     (*successorIterator)->position().second << ")" << endl;

			if ((*successorIterator)->position() == m_goalNode->position()) {
				success = true;
				break;
			} else {
				(*successorIterator)->setDistanceFromStart(bestNode->distanceFromStart() + 1);
				(*successorIterator)->setHeuristicDistance(heuristicValue(*(*successorIterator)));
			}

			existsInClosedSet = false;
			existsInOpenSet = false;

			for (std::vector<Node*>::iterator i = openSet.begin(); i != openSet.end(); ++i) {
				if ((*successorIterator)->position() == (*i)->position()) {
					if ((*successorIterator)->objectiveDistance() >= (*i)->objectiveDistance()) {
						existsInOpenSet = true;
						break;
					}
				}
			}

			if (!existsInOpenSet) {
				for (std::vector<Node*>::iterator i = closedSet.begin(); i != closedSet.end(); ++i) {
					if ((*successorIterator)->position() == (*i)->position()) {
						if ((*successorIterator)->objectiveDistance() >= (*i)->objectiveDistance()) {
							existsInClosedSet = true;
							break;
						}
					}
				}
			}

			if (!existsInOpenSet && !existsInClosedSet) {
				cout << "Insertando nodo " << (*successorIterator) << " (" << (*successorIterator)->position().first << "," <<
				     (*successorIterator)->position().second << ")" << endl;
				openSet.push_back((*successorIterator));
			}
		}

		cout << "Añadiendo nodo " << bestNode << " a closedSet" << endl;
		closedSet.push_back(bestNode);
		cin.get();
	}

	if (success) {
		reversePath(*(*successorIterator));
	}
}

void PathFindingTree::expandNode(Node& node) {
	cout << "Expandiendo nodo " << &node << endl;
	Node* north;
	Node* east;
	Node* south;
	Node* west;
	Point northPoint(const_cast<Node&>(node).position().first, const_cast<Node&>(node).position().second - 1);
	Point eastPoint(const_cast<Node&>(node).position().first + 1, const_cast<Node&>(node).position().second);
	Point southPoint(const_cast<Node&>(node).position().first, const_cast<Node&>(node).position().second + 1);
	Point westPoint(const_cast<Node&>(node).position().first - 1, const_cast<Node&>(node).position().second);

	north = new Node(northPoint, "NORTH", node);
	north->setDistanceFromStart(node.distanceFromStart() + 1);
	north->setHeuristicDistance(heuristicValue(*north));
	node.insertChildren(*north);

	east = new Node(eastPoint, "EAST", node);
	east->setDistanceFromStart(node.distanceFromStart() + 1);
	east->setHeuristicDistance(heuristicValue(*east));
	node.insertChildren(*east);

	south = new Node(southPoint, "SOUTH", node);
	south->setDistanceFromStart(node.distanceFromStart() + 1);
	south->setHeuristicDistance(heuristicValue(*south));
	node.insertChildren(*south);

	west = new Node(westPoint, "WEST", node);
	west->setDistanceFromStart(node.distanceFromStart() + 1);
	west->setHeuristicDistance(heuristicValue(*west));
	node.insertChildren(*west);

	for (vector<Node*>::iterator i = node.children()->begin(); i != node.children()->end(); i += 1) {
		cout << "Nodo " << &(*i) << " (" << (*i)->direction() << ") distancia inicio " << (*i)->distanceFromStart() << " distancia heuristica " <<
		     (*i)->heuristicDistance() << " total " << (*i)->objectiveDistance() << endl;
	}

	cout << "Nodo expandido: regresando" << endl;
}

uint32_t PathFindingTree::calculateBestCandidate() {

}

bool PathFindingTree::isInRoute(const Node& nodeCheck) {
	// Comprobar que el nodo no se encuentra en la rama actual.
}

float PathFindingTree::heuristicValue(const Node& start) {
	return euclideanDistance(const_cast<Node&>(start).position(), m_goalNode->position());
}

void PathFindingTree::reversePath(const Node& node) {
	Node* tmp;
	tmp = &const_cast<Node&>(node);

	while (tmp != NULL) {
		// TODO Codigo para rellenar el camino
		tmp = const_cast<Node*>(tmp->parent());
	}
}
