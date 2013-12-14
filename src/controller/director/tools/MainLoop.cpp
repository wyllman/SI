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

#include <controller/director/tools/MainLoop.h>
#include <controller/director/tools/FileLog.h>
#include <controller/director/Director.h>
#include <Tools.h>

#include <iostream>

// ___________________________________________________________________________________
// Constructores y Destructor:
MainLoop::MainLoop(const Director& director) {
	refDirector_ = &director;
	logAction(LOG_INIT);
	continue_ = false;
	pause_ = false;
	requireReset_ = false;
	requireUpdate_ = false;
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
	if (BASIC_LOG) {
		switch (index) {
		case LOG_INIT:
			std::cout << "------Generado la herramienta MainLoop para el Director " << std::endl;
			break;
		case LOG_END:
			std::cout << "------Destruyendo la herramienta MainLoop para el Director " << std::endl;
			break;
		default:
			break;
		}
	}
	if (ADVAN_LOG) {
		FileLog* regist = const_cast<FileLog*>(refDirector_->getRegAccErr());
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

