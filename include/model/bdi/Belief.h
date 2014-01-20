/*
 * Belief.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef BELIEF_H_
#define BELIEF_H_

#include <string>

/**
 * \class Belief
 * \brief Clase base de creencias.
 * 
 * La clase Belief almacena las creencias como un string.
 * Se considera un mundo cerrado, así que toda creencia no definida se
 * presupone falsa y las definidas verdaderas.
 * 
 */
class Belief {
private:
	std::string m_belief;
public:
	Belief(std::string);
	Belief(const char*);
	~Belief();
	std::string operator()() const { return m_belief; }
	bool operator==(const Belief&);
};

#endif /* BELIEF_H_ */
