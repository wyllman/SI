/*
 *      Nombre: Director.cpp
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Controlador específico para la ejecución del simulador. Lleva el control del
 *              tiempo, del bucle principal y el registro de las acciones y errores internos.
 *
 */

#include <controller/director/Director.h>

#ifdef __linux
	#include <SDL2/SDL.h>
#else
	#include <SDL.h>
#endif

#include <controller/director/tools/FileLog.h>
#include <controller/director/tools/MainLoop.h>
#include <iostream>

// ___________________________________________________________________________________
// Constructores y Destructor:
Director::Director() {
	logAction(LOG_INIT);
	regAccErr_ = new FileLog;
	regAccErr_->init();
	mainLoop_ = 0;
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
	mainLoop_ = new MainLoop(this);
	logAction(LOG_F_INIT);
}
void Director::start() {
	const_cast<View*>(refView_)->init();
	mainLoop();
}
void Director::stop() {
	if (mainLoop_ != 0) {
		delete (mainLoop_);
		mainLoop_ = 0;
	}

	logAction(LOG_F_STOP);

	if (regAccErr_ != 0) {
		delete (regAccErr_);
		regAccErr_ = 0;
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
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos privados:
void Director::mainLoop() {
	SDL_Event eventSDL;
	logAction(LOG_F_LOOP);

	mainLoop_->init();
	while (mainLoop_->isContinue()) {
		while (SDL_PollEvent(&eventSDL)) {
			if (eventSDL.type == SDL_QUIT) {
				mainLoop_->stop();
			}
		}
	}
}
void Director::logAction(int index) {
	if (BASIC_LOG) {
		switch (index) {
		case LOG_INIT:
			cout << "---Generado el coordinador Director " << endl;
			break;
		case LOG_END:
			cout << "---Destruyendo el coordinador Director " << endl;
			break;
		case LOG_F_INIT:
			cout << "---Llamando a la funcion init del Director" << endl;
			break;
		case LOG_F_STOP:
			cout << "---Llamando a la funcion stop del Director" << endl;
			break;
		case LOG_F_LOOP:
			cout << "---Llamando a la función mainLoop del Director" << endl;
			break;
		default:
			break;
		}
	}
	if (ADVAN_LOG) {
		switch (index) {
		case LOG_F_INIT:
			regAccErr_->insertLine(
					"---Llamando a la funcion init del Director");
			break;
		case LOG_F_STOP:
			if (regAccErr_ != 0) {
				regAccErr_->insertLine(
						"---Llamando a la funcion stop del Director");
				regAccErr_->insertLine(
						"******************************************");
				regAccErr_->showConsole();
				regAccErr_->save();
			}
			break;
		case LOG_F_LOOP:
			regAccErr_->insertLine(
					"---Llamando a la función mainLoop del Director");
			break;
		default:
			break;
		}
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

