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

#include "../../../headers/controller/director/Director.h"
#include "../../../headers/Tools.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Director::Director() {
	if (BASIC_LOG) {
		cout << "---Generado el coordinador Director " << endl;
	}
	regAccErr_ = 0;
	mainLoop_ = 0;
}

Director::~Director() {
	//if (BASIC_LOG) {
		cout << "---Destruyendo el coordinador Director " << endl;
	//}
	stop ();
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Director::init() {
	if (BASIC_LOG) {
		cout << "---Llamando a la funcion init del Director" << endl;
	}
	regAccErr_ = new FileLog;
	regAccErr_->init();
	if(ADVAN_LOG) {
		regAccErr_->insertLine("---Llamando a la funcion init del Director");
	}
	mainLoop_ = new MainLoop (this);
}
void Director::stop() {
	if (BASIC_LOG) {
		cout << "---Llamando a la funcion stop del Director" << endl;
	}
	if (mainLoop_ != 0) {
		delete (mainLoop_);
		mainLoop_ = 0;
	}

	if (regAccErr_ != 0) {
		if(ADVAN_LOG) {
			regAccErr_->insertLine("---Llamando a la funcion stop del Director");
			regAccErr_->insertLine("******************************************");
			regAccErr_->showConsole();
			regAccErr_->save();
		}
		delete (regAccErr_);
		regAccErr_ = 0;
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Manejadores públicos:
const FileLog* Director::getRegAccErr() const{
	return regAccErr_;
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos privados:

// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


