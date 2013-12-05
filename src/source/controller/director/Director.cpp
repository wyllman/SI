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

// ___________________________________________________________________________________
// Constructores y Destructor:
Director::Director() {
	cout << "---Generado el coordinador Director " << endl;
	regAccErr_ = 0;
	mainLoop_ = 0;
}

Director::~Director() {
	cout << "---Destruyendo el coordinador Director " << endl;
	stop ();
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Director::init() {
	cout << "---Llamando a la funcion init del Director" << endl;
	regAccErr_ = new FileLog;
	mainLoop_ = new MainLoop;
}
void Director::stop() {
	cout << "---Llamando a la funcion stop del Director" << endl;
	if (regAccErr_ != 0) {
		delete (regAccErr_);
		regAccErr_ = 0;
	}
	if (mainLoop_ != 0) {
		delete (mainLoop_);
		mainLoop_ = 0;
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Manejadores públicos:

// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos privados:

// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

