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
   const_cast<Model*>(refModel_)->init();

   const_cast<View*>(refView_)->init();

   Point posTmp = (dynamic_cast<Simulator*> (
                     const_cast<Model*>(refModel_)))->getPosMainAgent();
   float* posTmp3D = new float[3];
//   std::cout << "---------------Punto pos main: " << posTmp.first << std::endl;
   posTmp3D[0] = posTmp.second;
   posTmp3D[1] = 0.1;
   posTmp3D[2] = posTmp.first;

   const_cast<Scenographer*> (
   (dynamic_cast<Interface*>(
      const_cast<View*> (refView_))->getScenographer()))->setMainAgentPos((float*)posTmp3D);

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
const FileLog* Director::getRegAccErr() const {
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
void Director::mainLoop() {
   SDL_Event eventSDL;
   logAction(LOG_F_LOOP);
   bool needRender = false;

   mainLoop_->init();
   while (mainLoop_->isContinue()) {
      while (SDL_PollEvent(&eventSDL)) {
         if (eventSDL.type == SDL_QUIT) {
            mainLoop_->stop();
         } else if (eventSDL.type == SDL_KEYDOWN && eventSDL.key.state == SDL_PRESSED) {
            if (eventSDL.key.keysym.sym == SDLK_UP) {
               const_cast<Scenographer*>(
                  dynamic_cast<Interface*>(
                  const_cast<View*>(refView_))->getScenographer())->projZoom(-0.75);
               needRender = true;
            } else if (eventSDL.key.keysym.sym == SDLK_DOWN) {
               const_cast<Scenographer*>(
                  dynamic_cast<Interface*>(
                  const_cast<View*>(refView_))->getScenographer())->projZoom(0.75);
               needRender = true;
            } else if (eventSDL.key.keysym.sym == SDLK_LEFT) {
               const_cast<Scenographer*>(
                  dynamic_cast<Interface*>(
                  const_cast<View*>(refView_))->getScenographer())->camRotationPos(2.5);
               needRender = true;
            } else if (eventSDL.key.keysym.sym == SDLK_RIGHT) {
               const_cast<Scenographer*>(
                  dynamic_cast<Interface*>(
                  const_cast<View*>(refView_))->getScenographer())->camRotationPos(-2.5);
               needRender = true;
            }
         }
         if (needRender) {
            dynamic_cast<Interface*>(const_cast<View*>(refView_))->update();
            dynamic_cast<Interface*>(const_cast<View*>(refView_))->render();
            needRender = false;
         }
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
