/*
 * Agent.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef AGENT_H_
#define AGENT_H_

#include <Tools.h>
#include <model/map/Map.h>
#include <model/fipa/Package.h>

/**
 * \class Agent (abstract)
 * \brief Clase base para los agentes.
 *
 * La clase Agent implementa el modelo BDI general a todos los agentes y el
 * protocolo de comunicación.
 *
 */

class Package;

class Agent {
   private:
      State m_state;

      unsigned int m_idComm;
      char* m_nameAgent;

   protected:
      Point m_position;
      Map* refMap_;
      std::vector<Direction> m_routes;
   public:
      Agent(Map*);
      virtual ~Agent() = 0;

      void move(Direction);
      bool controledMove (Direction);
      bool checkTerrain (Direction);
      bool routedMove ();
      bool checkRouteMoves ();

      void setRoutes(std::vector<Direction>& routes);

      Point getPosition ();
      unsigned int getIdComm() const;
      void setIdComm(unsigned int idComm);
      char* getNameAgent() const;
      void setNameAgent(char* nameAgent);
      State getState() const;
     void setState(State state);
     std::vector<Direction>& getRoutes();

      virtual Package* readFIPAPackage (Package*) { return NULL; };
      virtual void actDependingOfState () { };
};

#endif /* AGENT_H_ */
