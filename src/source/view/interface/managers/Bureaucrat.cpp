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
#include "../../../../headers/Tools.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Bureaucrat::Bureaucrat(const Interface* interface) {
	if (BASIC_LOG) {
		cout << "------Generado el gestor Bureaucrat para la vista Interfaz " << endl;
	}
	refInterface_ = interface;
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
				->log("------Generado el gestor Bureaucrat para la vista Interfaz ");
	}
}

Bureaucrat::~Bureaucrat() {
	if (BASIC_LOG) {
		cout << "------Destruyendo el gestor Bureaucrat para la vista Interfaz " << endl;
	}
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
			->log("------Destruyendo el gestor Bureaucrat para la vista Interfaz ");
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Bureaucrat::initSDL() {
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
			->log("------Inicializando SDL en la clase Bureaucrat. ");
	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		if (BASIC_LOG) {
			cout << "------ERROR!! No se pudo iniciar SDL: " << SDL_GetError() << endl;
		}
		if (ADVAN_LOG) {
			((Interface*)refInterface_)
				->log("------ERROR!! No se pudo iniciar SDL ");
		}
		((Interface*)refInterface_)->stop();
	}
}
void Bureaucrat::initOGL() {
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
			->log("------Inicializando OGL en la clase Bureaucrat. ");
	}
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

// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

