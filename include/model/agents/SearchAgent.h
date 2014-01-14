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

      void setPosition (Point p) { m_position = p; }
      vector<Direction>& getRoutes();
      void setRoutes(const vector<Direction>& routes);

      Package* readFIPAPackage (Package*);

      void localDireccionalSearch (std::string);

      void actDependingOfState ();

   private:
      const MainAgent* refMainAgent_;
      vector<Direction> m_routes;
};

#endif /* SEARCHAGENT_H_ */
