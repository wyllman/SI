/*
 * PathFindingTree.h
 *
 *  Created on: 19/01/2014
 *      Author: maikel
 */

#ifndef PATHFINDINGTREE_H_
#define PATHFINDINGTREE_H_

#include <vector>

class Node;
class MainAgent;

class PathFindingTree {
public:
	PathFindingTree(const MainAgent&, const Point&, const Point&);
	~PathFindingTree();

	// Manejadores de atributos públicos
	void calculateHeuristicRoute (); 	// Crea la mejor ruta del "Root" a "Goal"
	inline std::string& getRoute() { return m_route; }

private:
	std::vector<Node*> m_leafNodes;
	Node* m_rootNode;
	Node* m_goalNode;

	std::string m_route;
	MainAgent* m_agent;
	
	// A*
	void expandNode (Node&); 			// Expande el nodo actual --> añadiendo sus hijos al vector de hijos del Nodo
	uint32_t calculateBestCandidate (); 		// Pone como nodo actual el mejor de sus hijos
	bool isInRoute(const Node&); 			// Indica si el nodo a buscar está en la ruta heurística
	float heuristicValue(const Node&);		// Devuelve la distancia de manhattan del nodo parámetro al GOAL
	void reversePath(const Node&);
};

#endif /* PATHFINDINGTREE_H_ */
