/*
 * WorkingAgent.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef WORKINGAGENT_H_
#define WORKINGAGENT_H_

#include <model/agents/Agent.h>
#include <model/agents/MainAgent.h>
#include <cstring>
using namespace std;

class WorkingAgent : public Agent {
   public:
      WorkingAgent(MainAgent*, Map*);
      ~WorkingAgent();

      void setPosition (Point p) { m_position = p; }
      Package* readFIPAPackage (Package*);

      void followRoute(std::string);
      Direction translateRoute (std::string);

      vector<Direction>& getRoutes();
      void setRoutes(vector<Direction>& routes);

   private:
      const MainAgent* refMainAgent_;

      vector<Direction> m_routes;
};

#endif /* WORKINGAGENT_H_ */
