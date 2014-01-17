/*
 * Intention.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/bdi/Intention.h>
#include <model/bdi/BeliefSet.h>
#include <model/bdi/Desire.h>

Intention::Intention(BeliefSet& beliefSet, std::vector<Desire>& desireVector) {
	m_beliefSet = &beliefSet;
	m_desireVector = &desireVector;
}

Intention::~Intention() {
}
