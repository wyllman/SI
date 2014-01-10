/*
 *      Nombre: Director.cpp
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.003
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Controlador específico para la ejecución del simulador. Lleva el control del
 *              tiempo, del bucle principal y el registro de las acciones y errores internos.
 *
 */

#include <view/abstracts/View.h>
#include <controller/director/Director.h>
#include <controller/director/tools/FileLog.h>
#include <controller/director/tools/MainLoop.h>
#include <model/abstracts/Model.h>
#include <model/simulator/Simulator.h>

#include <model/agents/MainAgent.h>

#include <view/interface/Interface.h>
#include <view/interface/managers/Scenographer.h>
#include <Tools.h>

#ifdef __linux
   #include <SDL2/SDL.h>
#else
   #include <SDL.h>
#endif

#include <iostream>

// ___________________________________________________________________________________
// Constructores y Destructor:
Director::Director() {
   logAction(LOG_INIT);
   regAccErr_ = new FileLog;
   regAccErr_->init();
   mainLoop_ = NULL;
}

Director::~Director() {
   logAction(LOG_END);
   stop();
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Director::init() {
   mainLoop_ = new MainLoop(*this);
   logAction(LOG_F_INIT);
}
void Director::start() {
   // Incializando el modelo (clase Simulator)
   const_cast<Model*>(refModel_)->init();
   // Inicializando la vista (clase Interface)
   const_cast<View*>(refView_)->init();

   // Enviando a la vista la información necesaria de los
   // agentes.
   getAgentsPos();

   // Iniciando el bucle principal de ejecución del programa
   mainLoop();
}
void Director::stop() {
   if (refModel_ != NULL) {
      const_cast<Model*>(refModel_)->stop();
      delete (const_cast<Model*>(refModel_));
      refModel_ = NULL;
   }
   if (refView_ != NULL) {
      const_cast<View*>(refView_)->stop();
      delete (const_cast<View*>(refView_));
      refView_ = NULL;
   }
   if (mainLoop_ != NULL) {
      delete (mainLoop_);
      mainLoop_ = NULL;
   }

   logAction(LOG_F_STOP);

   if (regAccErr_ != NULL) {
      delete (regAccErr_);
      regAccErr_ = NULL;
   }
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Manejadores públicos:
FileLog* Director::getRegAccErr() {
   return regAccErr_;
}
const Map* Director::getMap() const {
   return (dynamic_cast<Simulator*>(const_cast<Model*>(refModel_))->getMap());
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos privados:
void Director::getAgentsPos() {
    const_cast<Scenographer*> (
    (dynamic_cast<Interface*>(
       const_cast<View*> (refView_))->getScenographer()))->clearAgents();
   // Obteniendo la posición inicial del agente principal, creada en el modelo,
   // y pasarsela a la vista para que pueda mostrala en pantalla.
   Point posTmp = (dynamic_cast<Simulator*> (
                     const_cast<Model*>(refModel_)))->getPosMainAgent();
   float* posTmp3D = new float[3];
   int numAgents;
   posTmp3D[0] = posTmp.second;
   posTmp3D[1] = 0.1;
   posTmp3D[2] = posTmp.first;

   const_cast<Scenographer*> (
   (dynamic_cast<Interface*>(
      const_cast<View*> (refView_))->getScenographer()))->setMainAgentPos((float*)posTmp3D);

   // Obteniendo el número de agentes exploradores y sus posiciones del modelo
   // y pasarle la información a la vista.
   if (!const_cast<MainAgent*> (
      (dynamic_cast<Simulator*> (
         const_cast<Model*>(refModel_)))
            ->getMainAgent())
               ->getVAgents().empty()) {
      numAgents = const_cast<MainAgent*> (
                     (dynamic_cast<Simulator*> (
                        const_cast<Model*>(refModel_)))
                           ->getMainAgent())
                              ->getVAgents().size();
      for (int i = 0; i < numAgents; i++) {
         posTmp = const_cast<MainAgent*> (
                 (dynamic_cast<Simulator*> (
                    const_cast<Model*>(refModel_)))
                       ->getMainAgent())
                          ->getVAgents()[i]->getPosition();
         posTmp3D[0] = posTmp.second;
         posTmp3D[1] = 0.1;
         posTmp3D[2] = posTmp.first;
         const_cast<Scenographer*> (
         (dynamic_cast<Interface*>(
            const_cast<View*> (refView_))->getScenographer()))->addSearchAgent((float*)posTmp3D);
      }
   }


   // Obteniendo el número de agentes trabajadores y sus posiciones del modelo
   // y pasarle la información a la vista.
   if (!const_cast<MainAgent*> (
      (dynamic_cast<Simulator*> (
         const_cast<Model*>(refModel_)))
            ->getMainAgent())
               ->getWorVecAgents().empty()) {
      numAgents = const_cast<MainAgent*> (
                     (dynamic_cast<Simulator*> (
                        const_cast<Model*>(refModel_)))
                           ->getMainAgent())
                              ->getWorVecAgents().size();
      for (int i = 0; i < numAgents; i++) {
         posTmp = const_cast<MainAgent*> (
                 (dynamic_cast<Simulator*> (
                    const_cast<Model*>(refModel_)))
                       ->getMainAgent())
                          ->getWorVecAgents()[i]->getPosition();
         posTmp3D[0] = posTmp.second;
         posTmp3D[1] = 0.1;
         posTmp3D[2] = posTmp.first;
         const_cast<Scenographer*> (
         (dynamic_cast<Interface*>(
            const_cast<View*> (refView_))->getScenographer()))->addWorkingAgent((float*)posTmp3D);
      }
   }
}
void Director::mainLoop() {
   const float ZOOM_DIFF = 0.75;
   const float ROT_DIFF = 2.5;
   SDL_Event eventSDL;
   logAction(LOG_F_LOOP);


   mainLoop_->init();

   while (mainLoop_->isContinue()) {
      while (SDL_PollEvent(&eventSDL)) {
         if (eventSDL.type == SDL_QUIT) {
            mainLoop_->stop();
         } else if (eventSDL.type == SDL_KEYDOWN && eventSDL.key.state == SDL_PRESSED) {
            if (eventSDL.key.keysym.sym == SDLK_UP) {
               const_cast<Scenographer*>(
                  dynamic_cast<Interface*>(
                  const_cast<View*>(refView_))->getScenographer())->projZoom (-ZOOM_DIFF);
               mainLoop_->render();

            } else if (eventSDL.key.keysym.sym == SDLK_DOWN) {
               const_cast<Scenographer*>(
                  dynamic_cast<Interface*>(
                  const_cast<View*>(refView_))->getScenographer())->projZoom (ZOOM_DIFF);
               mainLoop_->render();
            } else if (eventSDL.key.keysym.sym == SDLK_LEFT) {
               const_cast<Scenographer*>(
                  dynamic_cast<Interface*>(
                  const_cast<View*>(refView_))->getScenographer())->camRotationPos (ROT_DIFF);
               mainLoop_->render();
            } else if (eventSDL.key.keysym.sym == SDLK_RIGHT) {
               const_cast<Scenographer*>(
                  dynamic_cast<Interface*>(
                  const_cast<View*>(refView_))->getScenographer())->camRotationPos (-ROT_DIFF);
               mainLoop_->render();
            }
         }
         mainFunction();
      }
   }
}

void Director::mainFunction() {
   if (!(mainLoop_->isPause()))  {
		// Actualizar el simulador y comprobar si se ha movido algún agente para actualizar la inerfaz gráfica.
		if (dynamic_cast<Simulator*>(
				const_cast<Model*>(refModel_))->update()) {
			mainLoop_->update();
		}else {
			mainLoop_->stopUpdate();
		}
		// En caso de requerirse, enviar la información necesaria sobe los agente a la interfaz gráfica.
		if (mainLoop_->isRequireUpdate()) {
			getAgentsPos();
			mainLoop_->render();
		}
		// En caso de requerirse, actualizar los datos internos de la interfaz gráfica y renderizar la escena.
		if (mainLoop_->isRequireRender()) {
			dynamic_cast<Interface*>(const_cast<View*>(refView_))->update();
			dynamic_cast<Interface*>(const_cast<View*>(refView_))->render();
			mainLoop_->stopRender();
		}
   }
}

void Director::logAction(int index) {
   if (BASIC_LOG) {
      switch (index) {
         case LOG_INIT:
            std::cout << "---Generado el coordinador Director " << std::endl;
            break;
         case LOG_END:
            std::cout << "---Destruyendo el coordinador Director " << std::endl;
            break;
         case LOG_F_INIT:
            std::cout << "---Llamando a la funcion init del Director" << std::endl;
            break;
         case LOG_F_STOP:
            std::cout << "---Llamando a la funcion stop del Director" << std::endl;
            break;
         case LOG_F_LOOP:
            std::cout << "---Llamando a la función mainLoop del Director" << std::endl;
            break;
         default:
            break;
      }
   }
   if (ADVAN_LOG) {
      switch (index) {
         case LOG_F_INIT:
            regAccErr_->insertLine("---Llamando a la funcion init del Director");
            break;
         case LOG_F_STOP:
            if (regAccErr_ != NULL) {
               regAccErr_->insertLine("---Llamando a la funcion stop del Director");
               regAccErr_->insertLine("******************************************");
               regAccErr_->showConsole();
               regAccErr_->save();
            }
            break;
         case LOG_F_LOOP:
            regAccErr_->insertLine("---Llamando a la función mainLoop del Director");
            break;
         default:
            break;
      }
   }
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

