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

#include <view/interface/managers/Bureaucrat.h>

#include <view/interface/Interface.h>
#include <Tools.h>

#include <iostream>
#include <SDL.h>
#ifdef __linux
	#include <GL/glew.h>
#else
	#include <GL.h>
	#include <GLU.h>
#endif

// ___________________________________________________________________________________
// Constructores y Destructor:
Bureaucrat::Bureaucrat(const Interface& interface) {
	refInterface_ = const_cast<Interface*>(&interface);
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
		refInterface_->stop();
	}
}
void Bureaucrat::initOGL() {
	logAction(LOG_F_INIT_1);
	#ifdef __linux
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		exit(-1);
	}
	#else
	glShadeModel( GL_SMOOTH );
	glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	#endif
	loadShader ();
}
void Bureaucrat::loadShader() {
	if (ADVAN_LOG) {
		refInterface_->log("------Cargando Shaders en la clase Bureaucrat. ");
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
			std::cout << "------Generado el gestor Bureaucrat para la vista Interfaz " << std::endl;
			break;
		case LOG_END:
			std::cout << "------Destruyendo el gestor Bureaucrat para la vista Interfaz" << std::endl;
			break;
		case LOG_F_INIT:
			std::cout << "------Inicializando SDL en la clase Bureaucrat." << std::endl;
			break;
		case LOG_F_INIT_1:
			std::cout << "------Inicializando OGL en la clase Bureaucrat." << std::endl;
			break;
		case LOG_ERROR:
			std::cout << "------ERROR!! No se pudo iniciar SDL: " << SDL_GetError() << std::endl;
			break;
		default:
			break;
		}
	}
	if (ADVAN_LOG) {
		switch (index) {
		case LOG_INIT:
			refInterface_->log("------Generado el gestor Bureaucrat para la vista Interfaz ");
			break;
		case LOG_END:
			refInterface_->log("------Destruyendo el gestor Bureaucrat para la vista Interfaz ");
			break;
		case LOG_F_INIT:
			refInterface_->log("------Inicializando SDL en la clase Bureaucrat. ");
			break;
		case LOG_F_INIT_1:
			refInterface_->log("------Inicializando OGL en la clase Bureaucrat. ");
			break;
		case LOG_ERROR:
			refInterface_->log("------ERROR!! No se pudo iniciar SDL ");
			break;
		default:
			break;
		}
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

