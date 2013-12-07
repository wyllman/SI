/*
 *      Nombre: Bureaucrat.cpp
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de las gestiones y cargas de librerías y los recursos
 *              necesarios del sistema operativo.
 *
 */

#include "../../../../headers/view/interface/managers/Bureaucrat.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Bureaucrat::Bureaucrat(const Interface* interface) {
	refInterface_ = interface;
	logAction(LOG_F_INIT);
}

Bureaucrat::~Bureaucrat() {
	logAction(LOG_END);
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Bureaucrat::initSDL() {
	logAction(LOG_F_INIT);
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		logAction(LOG_ERROR);
		((Interface*)refInterface_)->stop();
	}
}
void Bureaucrat::initOGL() {
	logAction(LOG_F_INIT_1);
	//glShadeModel( GL_SMOOTH );
	//glClearDepth( 1.0f );
	//glEnable( GL_DEPTH_TEST );
	//glDepthFunc( GL_LEQUAL );
	//glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	//loadShader ();
}
void Bureaucrat::loadShader() {
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
			->log("------Cargando Shaders en la clase Bureaucrat. ");
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
void Bureaucrat::logAction(int index) {
	if (BASIC_LOG) {
		switch (index) {
			case LOG_INIT:
				cout << "------Generado el gestor Bureaucrat para la vista Interfaz " << endl;
				break;
			case LOG_END:
				cout << "------Destruyendo el gestor Bureaucrat para la vista Interfaz"
					<< endl;
				break;
			case LOG_F_INIT:
				cout << "------Inicializando SDL en la clase Bureaucrat." << endl;
				break;
			case LOG_F_INIT_1:
				cout << "------Inicializando OGL en la clase Bureaucrat." << endl;
				break;
			case LOG_ERROR:
				cout << "------ERROR!! No se pudo iniciar SDL: " << SDL_GetError() << endl;
				break;
			default:
				break;
		}
	}
	if(ADVAN_LOG) {
		switch (index) {
			case LOG_INIT:
				((Interface*)refInterface_)
					->log("------Generado el gestor Bureaucrat para la vista Interfaz ");
				break;
			case LOG_END:
				((Interface*)refInterface_)
					->log("------Destruyendo el gestor Bureaucrat para la vista Interfaz ");
				break;
			case LOG_F_INIT:
				((Interface*)refInterface_)
					->log("------Inicializando SDL en la clase Bureaucrat. ");
				break;
			case LOG_F_INIT_1:
				((Interface*)refInterface_)
					->log("------Inicializando OGL en la clase Bureaucrat. ");
				break;
			case LOG_ERROR:
				((Interface*)refInterface_)
					->log("------ERROR!! No se pudo iniciar SDL ");
				break;
			default:
				break;
		}
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


