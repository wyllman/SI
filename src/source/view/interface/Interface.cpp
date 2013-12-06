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
#include "../../../headers/Tools.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Interface::Interface(const Controller* controller):View(controller) {
	if (BASIC_LOG) {
		cout << "---Generado la vista Interfaz " << endl;
	}

	bureaucrat_ = 0;
	scenographer_ = 0;

	window_ = 0;
	context_ = 0;
	scene_ = 0;
}
Interface::~Interface() {
	if (BASIC_LOG) {
		cout << "---Destruyendo la vista Interfaz " << endl;
	}
	if (ADVAN_LOG) {
		FileLog* fileLogTmp = (FileLog*)(((Director*)refController_)->getRegAccErr());
		fileLogTmp->insertLine("---Destruyendo la vista Interfaz ");
	}
	stop ();
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Interface::init() {
	if (BASIC_LOG) {
		cout << "---Llamano a la función init de la clase Interface." << endl;
	}
	if (ADVAN_LOG) {
		FileLog* fileLogTmp = (FileLog*)(((Director*)refController_)->getRegAccErr());
		fileLogTmp->insertLine("---Llamano a la función init de la clase Interface.");
	}
	bureaucrat_ = new Bureaucrat (this);
	scenographer_ = new Scenographer (this);

	window_ = new Window (this);
	context_ = new Context (this);
	scene_ = new Scene (this);

	bureaucrat_->initSDL();
	bureaucrat_->initOGL();

	window_->init(500, 500);
}
void Interface::stop() {
	if (BASIC_LOG) {
		cout << "---Llamano a la función stop de la clase Interface." << endl;
	}
	if (ADVAN_LOG) {
		FileLog* fileLogTmp = (FileLog*)(((Director*)refController_)->getRegAccErr());
		fileLogTmp->insertLine("---Llamano a la función stop de la clase Interface.");
	}
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
void Interface::log(const char* line) {
	if (ADVAN_LOG) {
		FileLog* fileLogTmp = (FileLog*)(((Director*)refController_)->getRegAccErr());
		fileLogTmp->insertLine(line);
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


