/*
 * Intention.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef INTENTION_H_
#define INTENTION_H_

#include <string>

/**
 * \class Intention
 * \brief Clase para el modelado de intenciones
 * 
 * Sigue la estructura básica de la clase Belief, pero no se presupone
 * cierta.
 */
class Intention {
private:
	std::string m_intention;
	bool m_value;
public:
	Intention(std::string, bool);
	~Intention();
	std::string operator()() { return m_intention; }
	bool isTrue() { return m_value; }
	friend bool operator&&(const Intention&, const Intention&);
	friend bool operator||(const Intention&, const Intention&);
};

#endif /* INTENTION_H_ */
