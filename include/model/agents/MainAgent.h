/*
 * MainAgent.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef MAINAGENT_H_
#define MAINAGENT_H_

#include "Agent.h"

/**
 * \class MainAgent
 * \brief Agente principal de la simulación.
 *
 * El agente MainAgent (único) implementa el agente mediador de la arquitectura.
 *
 */
class MainAgent: public Agent {
public:
	MainAgent();
	~MainAgent();
};

#endif /* MAINAGENT_H_ */