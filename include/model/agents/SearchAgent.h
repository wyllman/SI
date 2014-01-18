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
#include <model/fipa/Package.h>

#include <vector>

class SearchAgent: public Agent {
   public:
      SearchAgent(MainAgent*, Map*);
      ~SearchAgent();

      MainAgent* getRefMainAgent();
      void setPosition (Point p) { m_position = p; }
      std::vector<Direction>& getRoutes();
      void setRoutes(const std::vector<Direction>& routes);

      Package* readFIPAPackage (Package*);

      void localDireccionalSearch (std::string);
      void followRoute(std::string);
      Direction translateRoute (std::string);

      void actDependingOfState ();
      void initExplorationMove (int row, int col, Direction guideDir);

   private:
      MainAgent* refMainAgent_;
       // Atributos para el movimiento exploratorio angular (90º)
      Point initPointEXPL_;
      Direction guideDirectionEXPL_;
      Direction lastDirectionEXPL_;
      Direction lastMoveDirEXPL_;
      int initPointDistanceEXPL_;

      bool explorationMove ();

      // Comprobaciones para el movimiento exploratorio
      // ---Posicionesvde terreno
      bool onLimits ();
      bool onLineLimits ();
      bool onRoute ();

      Direction calculateRouteDir ();
      Direction calculateReturnDir ();
      Direction calculateObstaclDir ();




      Direction calculatePreferedDirection ();
      Direction calculateAngularDirection ();
      Direction calculateRectilinearDirection ();
      Direction calculateFreeDirection (bool);
      Direction calculateClockDirection (Direction, bool);
      Direction calculateInverseDirection (Direction);
      void updateDistance (Direction);
      int sensor();
};

#endif /* SEARCHAGENT_H_ */
