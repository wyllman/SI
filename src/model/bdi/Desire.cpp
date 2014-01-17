/*
 * Desires.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/bdi/Desire.h>

Desire::Desire(std::string desire, bool value) :
	m_desire(desire),
	m_value(value)
{

}

Desire::~Desire() {
}

bool operator&&(const Desire& _A, const Desire& _B) {
	return (_A.m_value && _B.m_value);
}
bool operator||(const Desire& _A, const Desire& _B) {
	return (_A.m_value || _B.m_value);
}