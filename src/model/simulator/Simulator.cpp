/*
 *      Nombre: Simulator.cpp
 *
 *   Creado en: 05/12/2013
 *     Versión: v0.003
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Modelo específico para la ejecución del sistema inteligente. La generación del
 *              terreno y la gestión de los agentes que intervienen en la simulación.
 *
 */

#include <controller/director/Director.h>
#include <controller/director/tools/FileLog.h>
#include <model/abstracts/Model.h>
#include <model/simulator/Simulator.h>
#include <model/map/Map.h>
#include <model/map/MapConsoleInterface.h>
#include <model/agents/MainAgent.h>
#include <model/agents/SearchAgent.h>
#include <Tools.h>

#include <iostream>

// ___________________________________________________________________________________
// Constructores y Destructor:
Simulator::Simulator(const Controller& controller) :
      Model(controller) {
   logAction(LOG_INIT);
   m_MainAgent = new MainAgent ();

}
Simulator::~Simulator() {
   logAction(LOG_END);
   stop();
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Simulator::init() {
   logAction(LOG_F_INIT);
   map_ = new Map();

   MapConsoleInterface mapci(*map_);

   for (uint32_t i = 0; i < map_->size(); i++) {
      for (uint32_t j = 0; j < map_->size(); j++) {
         std::cout << mapci(i, j);
      }
      std::cout << std::endl;
   }

   m_MainAgent -> createRndInitialPos(map_); // Da una posición inicial al agente principal
   std::cout << "Simbolo en la posición generada: " << mapci(m_MainAgent -> getPosition().first, m_MainAgent -> getPosition().second) << std::endl;

   // Prueba 1 de agente instanciado al lado de la nave
   SearchAgent* searchg1 = new SearchAgent ();
   searchg1 -> setPosition (Point (m_MainAgent -> getPosition().first + 1, m_MainAgent -> getPosition().second));
   m_MainAgent -> getVAgents().push_back(searchg1);

   std::cout << " - Posición del Ag. Trabajador:  x = " <<
   		   m_MainAgent -> getVAgents().at(0) -> getPosition ().first << " , y = " <<
   		   m_MainAgent -> getVAgents().at(0) -> getPosition ().second << std::endl;


   // Prueba de movimiento hacia el sur de un agente
   while (m_MainAgent -> getVAgents().at(0) -> getPosition().second < 100) {
	   m_MainAgent -> getVAgents().at(0) -> move (SOUTH);
	   std::cout << "Pos:  x = " << m_MainAgent -> getVAgents().at(0) -> getPosition().first <<
			   " , y = " << m_MainAgent -> getVAgents().at(0) -> getPosition().second << std::endl;
	   //std::cout << "Simbolo = " << mapci(searchg1 -> getPosition().first, searchg1 -> getPosition().second) << std::endl;
   }
}

void Simulator::stop() {
   logAction(LOG_F_STOP);
   if (map_ != NULL) {
      delete (map_);
      map_ = NULL;
   }
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Manejadores públicos:
const Map* Simulator::getMap() const {
   return map_;
}
const MainAgent* Simulator::getMainAgent () const {
	return m_MainAgent;
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos privados:
void Simulator::logAction(int index) {
   if (BASIC_LOG) {
      switch (index) {
         case LOG_INIT:
            std::cout << "---Generado el modelo Simulator " << std::endl;
            break;
         case LOG_END:
            std::cout << "---Destruyendo el modelo Simulator " << std::endl;
            break;
         case LOG_F_INIT:
            std::cout << "---Llamando a la función init de la clase Simulator " << std::endl;
            break;
         case LOG_F_STOP:
            std::cout << "---Llamando a la función stop de la clase Simulator " << std::endl;
            break;
         default:
            break;
      }
   }
   if (ADVAN_LOG) {
      FileLog* fileLogTmp = const_cast<FileLog*>(
                               dynamic_cast<Director*>(
                               const_cast<Controller*>(refController_))->getRegAccErr());
      switch (index) {
         case LOG_INIT:
            fileLogTmp->insertLine("---Generando el modelo Simulator ");
            break;
         case LOG_END:
            fileLogTmp->insertLine("---Destruyendo el modelo Simulator ");
            break;
         case LOG_F_INIT:
            fileLogTmp->insertLine("---Llamando a la función init de la clase Simulator.");
            break;
         case LOG_F_STOP:
            fileLogTmp->insertLine("---Llamando a la función stop de la clase Simulator.");
            break;
         default:
            break;
      }
   }
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
