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
