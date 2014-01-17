/*
 * Intention.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/bdi/Intention.h>

Intention::Intention(std::string intention, bool value) :
	m_intention(intention),
	m_value(value)
{

}

Intention::~Intention() {
}

bool operator&&(const Intention& _A, const Intention& _B) {
	return (_A.m_value && _B.m_value);
}
bool operator||(const Intention& _A, const Intention& _B) {
	return (_A.m_value || _B.m_value);
}