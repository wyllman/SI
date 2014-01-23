/*
 * Node.cpp
 *
 *  Created on: 16/01/2014
 *      Author: maikel
 */

#include <model/agents/tools/Node.h>

Node::Node(const Point& position, const std::string& movement, const Node& parent) :
	m_position(position),
	m_movement(movement),
	m_nodeParent(&parent),
	m_distanceFromStart(0),
	m_heuristicDistance(0.0) {
	m_childrenNodes = new std::vector<Node*>;
	m_objectiveDistance = static_cast<float>(m_distanceFromStart) + m_heuristicDistance;
}

Node::Node(const Node& node) :
	m_position(node.m_position),
	m_nodeParent(node.m_nodeParent),
	m_childrenNodes(node.m_childrenNodes),
	m_distanceFromStart(node.m_distanceFromStart),
	m_heuristicDistance(node.m_heuristicDistance),
	m_objectiveDistance(node.m_objectiveDistance) {
}


Node::~Node() {
	if (!m_childrenNodes->empty()) {
		for (uint32_t i = 0; i < m_childrenNodes->size(); ++i) {
			if ((*m_childrenNodes)[i] != NULL) {
				delete (*m_childrenNodes)[i];
				(*m_childrenNodes)[i] = NULL;
			}
		}
	}
}

void Node::setDistanceFromStart(uint32_t dist) {
	m_distanceFromStart = dist;
	m_objectiveDistance = static_cast<float>(m_distanceFromStart) + m_heuristicDistance;
}

void Node::setHeuristicDistance(float dist) {
	m_heuristicDistance = dist;
	m_objectiveDistance = static_cast<float>(m_distanceFromStart) + m_heuristicDistance;
}

void Node::insertChildren(const Node& node) {
	m_childrenNodes->push_back(&const_cast<Node&>(node));
}
// kate: indent-mode cstyle; indent-width 8; replace-tabs off; tab-width 8; 
