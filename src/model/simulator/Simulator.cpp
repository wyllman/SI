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
#include <model/agents/WorkingAgent.h>
#include <Tools.h>

#include <iostream>

using namespace std;

// ___________________________________________________________________________________
// Constructores y Destructor:
Simulator::Simulator(const Controller& controller) :
      Model (controller), map_ (NULL), m_MainAgent (NULL) {
   logAction (LOG_INIT);
   updatedKnonwMap_ = false;
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
         cout << mapci(i, j);
      }
      cout << endl;
   }
   reset ();
}

bool Simulator::update() {
   updatedKnonwMap_ = false;
   return m_MainAgent -> update();
}
void Simulator::reset() {
   if (m_MainAgent != NULL) {
      delete (m_MainAgent);
   }
   m_MainAgent = new MainAgent (this, map_);
}
void Simulator::stop() {
   logAction(LOG_F_STOP);
   if (map_ != NULL) {
      delete (map_);
      map_ = NULL;
   }
   if (m_MainAgent != NULL) {
      delete (m_MainAgent);
      m_MainAgent = NULL;
   }
}
void Simulator::log(const char* line) {
   if (ADVAN_LOG) {
      FileLog* fileLogTmp = dynamic_cast<Director*>(
                               const_cast<Controller*>(refController_))->getRegAccErr();
      fileLogTmp->insertLine(line);
   }
}
bool Simulator::isUpdatedKnownMap() {
   return updatedKnonwMap_;
}
void Simulator::updatedKnownMap() {
   updatedKnonwMap_ = true;
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
Point Simulator::getPosMainAgent() {
   return (m_MainAgent->getPosition());
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
            cout << "---Generado el modelo Simulator " << endl;
            break;
         case LOG_END:
            cout << "---Destruyendo el modelo Simulator " << endl;
            break;
         case LOG_F_INIT:
            cout << "---Llamando a la función init de la clase Simulator " << endl;
            break;
         case LOG_F_STOP:
            cout << "---Llamando a la función stop de la clase Simulator " << endl;
            break;
         default:
            break;
      }
   }
   if (ADVAN_LOG) {
      FileLog* fileLogTmp = dynamic_cast<Director*>(
                               const_cast<Controller*>(refController_))->getRegAccErr();
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


