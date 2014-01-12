/*
 * Agent.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef AGENT_H_
#define AGENT_H_

#include <Tools.h>
#include <model/fipa/Package.h>

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
	BeliefSet* m_beliefSet;
	Goals* m_goals;
	Intentions* m_intentions;

	// FIXME: dejo aquí que un agente conoce en qué comunicación está embebido
	unsigned int m_idComm;
	char* m_nameAgent;

protected:
	Point m_position;
public:
	Agent();
	virtual ~Agent() = 0;

	bool move(Direction);
	Point getPosition ();
	unsigned int getIdComm() const;
	void setIdComm(unsigned int idComm);
	char* getNameAgent() const;
	void setNameAgent(char* nameAgent);

	virtual Package* readFIPAPackage (Package*) { return NULL; };
};

#endif /* AGENT_H_ */
