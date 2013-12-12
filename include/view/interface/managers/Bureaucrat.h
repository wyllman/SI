/*
 *      Nombre: Bureaucrat.h
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

#ifndef BUREAUCRAT_H_
#define BUREAUCRAT_H_

#include <iostream>

#ifdef __linux
	#include <SDL2/SDL.h>
	#include <GL/glew.h>
#else
	#include <SDL.h>
	#include <GL.h>
	#include <GLU.h>
#endif

class Interface;

class Bureaucrat {
public:
	Bureaucrat(const Interface&);
	virtual ~Bureaucrat();

	void initSDL ();
	void initOGL ();

	void loadShader ();

private:
	const Interface* refInterface_;

	void logAction(int);
};

#endif /* BUREAUCRAT_H_ */
