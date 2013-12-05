/*
 *      Nombre: Interface.cpp
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Vista específica para la ejecución del simulador. Lleva el control de la
 *              ejecución y creación de la ventana y el contexto (SDL y OGL). Renderizar
 *              la escena, animar los objetos, etc...
 *
 */

#include "../../../headers/view/interface/Interface.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Interface::Interface(const Controller* controller):View(controller) {
	cout << "---Generado la vista Interfaz " << endl;
	bureaucrat_ = 0;
	scenographer_ = 0;

	window_ = 0;
	context_ = 0;
	scene_ = 0;
}
Interface::~Interface() {
	cout << "---Destruyendo la vista Interfaz " << endl;
	stop ();
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Interface::init() {
	cout << "---Llamano a la función init de la clase Interface." << endl;
	bureaucrat_ = new Bureaucrat;
	scenographer_ = new Scenographer;

	window_ = new Window;
	context_ = new Context;
	scene_ = new Scene;
}
void Interface::stop() {
	cout << "---Llamano a la función stop de la clase Interface." << endl;
	if (bureaucrat_ != 0) {
		delete (bureaucrat_);
		bureaucrat_ = 0;
	}
	if (scenographer_ != 0) {
		delete (scenographer_);
		scenographer_ = 0;
	}
	if (window_ != 0) {
		delete (window_);
		window_ = 0;
	}
	if (context_ != 0) {
		delete (context_);
		context_ = 0;
	}
	if (scene_ != 0) {
		delete (scene_);
		scene_ = 0;
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


