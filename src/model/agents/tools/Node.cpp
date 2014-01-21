/*
 * Node.cpp
 *
 *  Created on: 16/01/2014
 *      Author: maikel
 */

#include <model/agents/tools/Node.h>

Node::Node(Point p, std::string mov, Node* padre) {
	m_p.first = p.first;
	m_p.second = p.second;
	m_mov = mov;
	m_padre = padre;

	m_visitado = false;
	distFromStart = 0;
}

Node::Node (const Node& p) {
	m_p.first = p.m_p.first;
	m_p.second = p.m_p.second;
	m_padre = p.m_padre;
	m_visitado = p.m_visitado;
	m_nodosHijos = p.m_nodosHijos;
	distFromStart = p.distFromStart;
}


Node::~Node() {
	//delete m_padre;
}

bool Node::areEquals (Node* q) {
	bool result = false;
	if (this->getP().first == q->getP().first &&
			this->getP().second == q->getP().second)
		result = true;
	return result;
}

bool Node::isPointIntoMapLimits (int widthMap, int heightMap) {
	bool intoMap = false;
	if (this -> getP().first >= 0 && this -> getP().first < widthMap &&
			this -> getP().second >= 0 && this -> getP().second < heightMap)
		intoMap = true;
	return intoMap;
}

void Node::setAttr (Point p, std::string s, Node* n) {
	m_p = p;
	m_mov = s;
	m_padre = n;
}

const std::string& Node::getMov() const {
	return m_mov;
}

Point Node::getP() const {
	return m_p;
}

bool Node::isVisitado() const {
	return m_visitado;
}

void Node::setVisitado(bool visitado) {
	m_visitado = visitado;
}

const Node* Node::getPadre() {
	return m_padre;
}

std::vector<Node*>& Node::getNodosHijos() {
	return m_nodosHijos;
}

void Node::setNodosHijos(std::vector<Node*>& nodosHijos) {
	m_nodosHijos = nodosHijos;
}

int Node::getDistFromStart() {
	return distFromStart;
}

int Node::getHeurVal() const {
	return heurVal_;
}

void Node::setHeurVal(int heurVal) {
	heurVal_ = heurVal;
}

void Node::setDistFromStart(int distFromStart) {
	this->distFromStart = distFromStart;
}

