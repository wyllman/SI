/*
 * Belief.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/bdi/Belief.h>

using namespace std;

Belief::Belief(string belief) :
	m_belief(belief) {

}

Belief::Belief(const char* cstr) :
	m_belief(string(cstr)) {

}

Belief::~Belief() {
}

bool Belief::operator==(const Belief& belief) {
	return (this->m_belief == belief.m_belief);
}
