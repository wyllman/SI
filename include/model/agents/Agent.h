/*
 * Agent.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef AGENT_H_
#define AGENT_H_

#include <Tools.h>

class BeliefSet;
class Goals;
class Intentions;

/**
 * \class Agent (abstract)
 * \brief Clase base para los agentes.
 *
 * La clase Agent implementa el modelo BDI general a todos los agentes y el
 * protocolo de comunicación.
 *
 */
class Agent {
private:
	// FIXME: la posicion deberia estar incluida en el conjunto de creencias
	Point m_position;
	BeliefSet* m_beliefSet;
	Goals* m_goals;
	Intentions* m_intentions;
protected:
	bool move(Movement);
public:
	Agent();
	virtual ~Agent() = 0;
};

#endif /* AGENT_H_ */
