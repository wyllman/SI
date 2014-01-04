/*
 * MainAgent.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef MAINAGENT_H_
#define MAINAGENT_H_

#include <model/agents/Agent.h>
#include <model/map/Map.h>

#include <vector>

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

      void logAction(int);
      void createRndInitialPos (Map*);
      std::vector<Agent*>& getVAgents ();
      std::vector<Agent*>& getWorVecAgents();

   private:
      BeliefSet* m_beliefSet;
      std::vector<Agent*> m_Vagents;
      std::vector<Agent*> m_WorVecAgents;

};

#endif /* MAINAGENT_H_ */
