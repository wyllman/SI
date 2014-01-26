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

#include <model/agents/tools/Node.h>
#include <cstring>

class WorkingAgent : public Agent {
   public:
      WorkingAgent(MainAgent*, Map*);
      ~WorkingAgent();

      void setPosition (Point p) { m_position = p; }
      Package* readFIPAPackage (Package*);


      unsigned int getRecolectTime() const;
      void setRecolectTime(unsigned int recolectTime);

      MainAgent* getRefMainAgent();

      void actDependingOfState ();

   private:
      MainAgent* refMainAgent_;
      unsigned int m_recolectTime;

      std::vector<Direction> m_ret_routes;
};

#endif /* WORKINGAGENT_H_ */
