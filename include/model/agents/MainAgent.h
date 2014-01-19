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

#include <cmath>
#include <vector>
#include <model/simulator/Simulator.h>
#include <model/agents/tools/Node.h>
#include <model/agents/tools/PathFindingTree.h>

class Simulator;
class BeliefSet;
class Desire;
class Intention;

/**
 * \class MainAgent
 * \brief Agente principal de la simulación.
 *
 * El agente MainAgent (único) implementa el agente mediador de la arquitectura.
 *
 */
class MainAgent: public Agent {
   public:
      MainAgent(Simulator*, Map*);
      ~MainAgent();

      void initAgents ();
      bool update ();
      bool updateMiniAgents ();

      void logAction(int);
      void createRndInitialPos (Map*);
      std::vector<Agent*>& getVAgents ();
      std::vector<Agent*>& getWorVecAgents();
      std::vector<Package*>& getPackagesFipa();
      const Map* getMap() const;
      void setKnownMapPosition(int, int, bool);
      bool** getKnownMap ();
      bool knownMapPosition(int, int);
      void checkedCells(int);
      void updatedKnownMap ();


      Package* readFIPAPackage (Package*);
      Package* createFIPAPackage ();

      void sendToRoute (Point, Point);

   private:
      Simulator* refSimulator_;

      BeliefSet* m_beliefSet;
      Desire* m_desires;
      Intention* m_intentions;

      std::vector<Agent*> m_Vagents;
      std::vector<Agent*> m_WorVecAgents;

      std::vector<Package*> m_packagesFIPA;

      void createInitialBelieves();
      void createDesires();
};

#endif /* MAINAGENT_H_ */
