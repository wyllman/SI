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
	Point m_p; //!< Punto en el mapa
	std::string m_mov; //!< indica la dirección que llevó hacia este nodo
	Node* m_padre; //!< Nodo que alcanza al nodo actual (su padre en el árbol)
	bool m_visitado; //!< Indica si el nodo ha sido expandido -> si se han generado hijos
	int distFromStart; //!< Distancia desde el origen
	std::vector<Node*> m_nodosHijos; //!<Vector de nodos hijos en el árbol de búsqueda
public:

	Node(Point, std::string, Node*);
	Node (const Node&);
	virtual ~Node();

	bool areEquals (Node*);
	bool isPointIntoLimitsMap (int widthMap, int heightMap);

	void setAttr (Point, std::string, Node*);
	const std::string& getMov() const;
	Point getP() const;
	Node* getPadre();
	bool isVisitado() const;
	void setVisitado(bool visitado);
	std::vector<Node*>& getNodosHijos();
	void setNodosHijos(std::vector<Node*>& nodosHijos);
	int getDistFromStart();
	void setDistFromStart(int distFromStart);
};

#endif /* NODE_H_ */
