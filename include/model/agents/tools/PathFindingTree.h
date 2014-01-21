/*
 * PathFindingTree.h
 *
 *  Created on: 19/01/2014
 *      Author: maikel
 */

#ifndef PATHFINDINGTREE_H_
#define PATHFINDINGTREE_H_

#include <model/agents/tools/Node.h>
#include <model/agents/MainAgent.h>
#include <cmath>
#include <queue>

class PathFindingTree {
public:
	PathFindingTree(MainAgent*, Point, Point);
	virtual ~PathFindingTree();

	// A*
	void calculateHeuristicRoute (); 	// Crea la mejor ruta del "Root" a "Goal"
	void expandir (); 					// Expande el nodo actual --> añadiendo sus hijos al vector de hijos del Nodo
	void calculateBetterNode (); 		// Pone como nodo actual el mejor de sus hijos
	bool isInRoute (Node*); 			// Indica si el nodo a buscar está en la ruta heurística
	float heuristicValue (Node*);		// Devuelve la distancia de manhattan del nodo parámetro al GOAL

	// Manejadores de atributos públicos
	std::string& getRoute();

private:
	std::vector<Node*> elPutoVector;
	Node* m_Root;
	Node* m_Goal;
	Node* m_actual;

	std::string m_route;
	MainAgent* m_refMainAgent;

	// Manejadores de atributos PRIVADOS

	Map* getMap ();

	Node* getActual();
	void setActual(Node* actual);
	Node* getGoal();
	void setGoal(Node* goal);
	MainAgent* getRefMainAgent();
	void setRefMainAgent(MainAgent* refMainAgent);
	Node* getRoot();
	void setRoot(Node* root);
	void setRoute(std::string& route);

};

#endif /* PATHFINDINGTREE_H_ */
