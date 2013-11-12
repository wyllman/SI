/*
 * Agent.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef AGENT_H_
#define AGENT_H_

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
	BeliefSet* m_beliefSet;
	Goals* m_goals;
	Intentions* m_intentions;
public:
	Agent();
	virtual ~Agent();
};

#endif /* AGENT_H_ */
