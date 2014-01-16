/*
 * SearchAgent.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef SEARCHAGENT_H_
#define SEARCHAGENT_H_

#include <iostream>
#include <cstdlib>

#include <model/agents/MainAgent.h>
#include <model/agents/WorkingAgent.h>
#include <model/fipa/Package.h>

class SearchAgent: public Agent {
   public:
      SearchAgent(MainAgent*, Map*);
      ~SearchAgent();

      MainAgent* getRefMainAgent();
      void setPosition (Point p) { m_position = p; }
      vector<Direction>& getRoutes();
      void setRoutes(const vector<Direction>& routes);

      Package* readFIPAPackage (Package*);

      void localDireccionalSearch (std::string);
      void followRoute(std::string);
      Direction translateRoute (std::string);

      void actDependingOfState ();
      void initExplorationMove (Point initPos, Direction guideDir);

   private:
      MainAgent* refMainAgent_;
       // Atributos para el movimiento exploratorio angular (90º)
      Point initPointEXPL_;
      Direction guideDirectionEXPL_;
      Direction lastDirectionEXPL_;
      int initPointDistanceEXPL_;

      bool explorationMove ();
      void calculateExplorationLimits (int&, int&);
      Direction calculatePreferedDirection ();
      Direction calculateAngularDirection ();
      Direction calculateRectilinearDirection ();
      Direction calculateFreeDirection ();
      Direction calculateClockDirection (Direction, bool);
};

#endif /* SEARCHAGENT_H_ */
