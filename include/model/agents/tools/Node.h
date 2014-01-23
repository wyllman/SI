/*
 * Node.h
 *
 *  Created on: 16/01/2014
 *      Author: maikel
 */

#ifndef NODE_H_
#define NODE_H_

#include <Tools.h>

#include <string>
#include <vector>

class Node {
private:
	Point m_position; //!< \var m_position Punto en el mapa
	std::string m_movement; //!< \var m_movement indica la dirección que llevó hacia este nodo
	const Node* m_nodeParent; //!< \var m_nodeParent Nodo que alcanza al nodo actual (su padre en el árbol)
	uint32_t m_distanceFromStart; //!< \var m_distanceFromStart Distancia desde el origen
	float m_heuristicDistance; //!< \var m_heuristicDistance heurística hasta el objetivo.
	float m_objectiveDistance;

	std::vector<Node*>* m_childrenNodes; //!<Vector de nodos hijos en el árbol de búsqueda

public:
	Node(const Point&, const std::string&, const Node&);
	Node(const Node&);
	~Node();

	inline Point position() {
		return m_position;
	}
	inline uint32_t distanceFromStart() {
		return m_distanceFromStart;
	}
	inline float heuristicDistance() {
		return m_heuristicDistance;
	}
	
	inline float objectiveDistance() {
		return m_objectiveDistance;
	}

	inline std::vector<Node*>* children() {
		return m_childrenNodes;
	}
	
	const char* direction() {
		return m_movement.c_str();
	}
	
	std::string getMov () {
		return m_movement;
	}

	const Node* parent() {
		return m_nodeParent;
	}

	void setDistanceFromStart(uint32_t);
	void setHeuristicDistance(float);

	void insertChildren(const Node&);
};

#endif /* NODE_H_ */


