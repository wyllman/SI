/*
 * BeliefSet.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/bdi/BeliefSet.h>
#include <model/bdi/Belief.h>

BeliefSet::BeliefSet() {
}

BeliefSet::~BeliefSet() {
}

void BeliefSet::add(std::string str, const Belief* belief) {
    m_beliefSet.insert(std::pair<std::string, const Belief*>(str, belief));
}

void BeliefSet::remove(std::string str) {
    if (m_beliefSet.count("str") == 1) {
        delete m_beliefSet["str"];
        m_beliefSet["str"] = NULL;
        m_beliefSet.erase(str);
    }
}

void BeliefSet::setMap(Map* map) {
	if (map != NULL) {
		m_map = map;
	}
}

void BeliefSet::setPosition(Point p) {
	if (p.first >= 0 && p.first <= MAP_WIDTH
		&& p.second >= 0 && p.second <= MAP_WIDTH) {
		m_position = p;
	}
}