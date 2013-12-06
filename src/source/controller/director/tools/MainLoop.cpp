/*
 *      Nombre: MainLoop.cpp
 *
 *   Creado en: 02/12/2013
  *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de contener y gestionar el bucle principal de ejecución.
 *
 */

#include "../../../../headers/controller/director/tools/MainLoop.h"
#include "../../../../headers/Tools.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
MainLoop::MainLoop(const Director* director) {
	if (BASIC_LOG) {
		cout << "------Generado la herramienta MainLoop para el Director " << endl;
	}
	refDirector_ = director;
	if (ADVAN_LOG) {
		FileLog* regist = (FileLog*) refDirector_->getRegAccErr();
		regist->insertLine("------Generado la herramienta MainLoop para el Director ");
	}
	continue_ = false;
	pause_ = false;
	requireReset_ = false;
	requireUpdate_ = false;
}

MainLoop::~MainLoop() {
	if (BASIC_LOG) {
		cout << "------Destruyendo la herramienta MainLoop para el Director " << endl;
	}
	if (ADVAN_LOG) {
		FileLog* regist = (FileLog*) refDirector_->getRegAccErr();
		regist->insertLine("------Destruyendo la herramienta MainLoop para el Director ");
	}
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
}

void MainLoop::pauseResume() {
	if (pause_) {
		pause_ = false;
	} else {
		pause_ = true;
	}
}

void MainLoop::reset() {
	requireReset_ = true;
}

void MainLoop::stop() {
	continue_ = false;
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
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos privados:
void MainLoop::logAction(int index) {
}

// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

