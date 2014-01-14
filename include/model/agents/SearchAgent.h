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
      SearchAgent(MainAgent*);
      ~SearchAgent();

      void setPosition (Point p) { m_position = p; }
      Package* readFIPAPackage (Package*);

      void localDireccionalSearch (std::string);
      bool controledMove (Direction);
      bool checkTerrain (Direction);
   private:
      const MainAgent* refMainAgent_;
};

#endif /* SEARCHAGENT_H_ */
