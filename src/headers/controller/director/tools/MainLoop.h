/*
 *      Nombre: MainLoop.h
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

#ifndef MAINLOOP_H_
#define MAINLOOP_H_

#include <iostream>

#include "../Director.h"
#include "FileLog.h"

using namespace std;
class Director;

class MainLoop {
public:
	MainLoop(const Director*);
	virtual ~MainLoop();

private:
	const Director* refDirector_;
};

#endif /* MAINLOOP_H_ */
