/*
 * Desires.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef DESIRE_H_
#define DESIRE_H_

#include <string>

/**
 * \class Desire
 * \brief Clase para el modelado de intenciones
 * 
 * Sigue la estructura básica de la clase Belief, pero no se presupone
 * cierta.
 */
class Desire {
private:
	std::string m_desire;
	bool m_value;
public:
	Desire(std::string, bool);
	~Desire();
	std::string operator()() { return m_desire; }
	bool isTrue() { return m_value; }
	void setValue(bool value) { m_value = value; }
	friend bool operator&&(const Desire&, const Desire&);
	friend bool operator||(const Desire&, const Desire&);
};

#endif /* DESIRE_H_ */
