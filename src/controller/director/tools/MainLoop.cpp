/*
 *      Nombre: MainLoop.cpp
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.003
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de contener y gestionar el bucle principal de ejecución.
 *
 */

#include <controller/director/tools/MainLoop.h>
#include <controller/director/tools/FileLog.h>
#include <controller/director/Director.h>
#include <Tools.h>

#include <iostream>

using namespace std;
// ___________________________________________________________________________________
// Constructores y Destructor:
MainLoop::MainLoop(const Director& director) {
   refDirector_ = &director;
   logAction(LOG_INIT);
   continue_ = false;
   pause_ = false;
   requireReset_ = false;
   requireUpdate_ = false;
   requireRender_ = false;
}
MainLoop::~MainLoop() {
   logAction(LOG_END);
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void MainLoop::init() {
   continue_ = true;
   pause_ = false;
   requireReset_ = false;
   requireUpdate_ = false;
   requireRender_ = true;
   initTime ();
   init2Time ();
}
void MainLoop::pauseResume() {
   if (pause_) {
      pause_ = false;
   } else {
      pause_ = true;
   }
}
void MainLoop::update() {
   requireUpdate_ = true;
}
void MainLoop::stopUpdate() {
   requireUpdate_ = false;
}
void MainLoop::render() {
   requireRender_ = true;
}
void MainLoop::stopRender() {
   requireRender_ = false;
}
void MainLoop::reset() {
   requireReset_ = true;
}
void MainLoop::stopReset() {
   requireReset_ = false;
}
void MainLoop::stop() {
   continue_ = false;
}
void MainLoop::initTime() {
   gettimeofday(&timeInit_, NULL);
}
void MainLoop::endTime() {
	gettimeofday(&timeFinal_, NULL);
}
double MainLoop::diffTmie() {
   double timeInitSeg = timeInit_.tv_sec + (timeInit_.tv_usec / 1000000.0);
   double timeFinalSeg = timeFinal_.tv_sec + (timeFinal_.tv_usec / 1000000.0);
   return (timeFinalSeg - timeInitSeg);
}
void MainLoop::init2Time() {
   gettimeofday(&time2Init_, NULL);
}
void MainLoop::end2Time() {
	gettimeofday(&time2Final_, NULL);
}
double MainLoop::diff2Time() {
   double timeInitSeg = time2Init_.tv_sec + (time2Init_.tv_usec / 1000000.0);
   double timeFinalSeg = time2Final_.tv_sec + (time2Final_.tv_usec / 1000000.0);
   return (timeFinalSeg - timeInitSeg);
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Manejadores públicos:
bool MainLoop::isContinue() const {
   return continue_;
}
bool MainLoop::isPause() const {
   return pause_;
}
bool MainLoop::isRequireReset() const {
   return requireReset_;
}
bool MainLoop::isRequireUpdate() const {
   return requireUpdate_;
}
bool MainLoop::isRequireRender() const {
   return requireRender_;
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos privados:
void MainLoop::logAction(int index) {
   if (BASIC_LOG) {
      switch (index) {
         case LOG_INIT:
            cout << "------Generado la herramienta MainLoop para el Director " << endl;
            break;
         case LOG_END:
            cout << "------Destruyendo la herramienta MainLoop para el Director " << endl;
            break;
         default:
            break;
      }
   }
   if (ADVAN_LOG) {
      FileLog* regist = const_cast<Director*>(refDirector_)->getRegAccErr();
      switch (index) {
         case LOG_INIT:
            regist->insertLine("------Generado la herramienta MainLoop para el Director ");
            break;
         case LOG_END:
            regist->insertLine("------Destruyendo la herramienta MainLoop para el Director ");
            break;
         default:
            break;
      }
   }
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

