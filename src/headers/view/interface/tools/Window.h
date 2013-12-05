/*
 *      Nombre: Window.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de inicializar y gestionar al ventana en la que se mostrará
 *              el simulador (SDL).
 *
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>

#include "../Interface.h"

using namespace std;

class Interface;

class Window {
public:
	Window(const Interface*);
	virtual ~Window();

private:
	const Interface* refInterface_;

};

#endif /* WINDOW_H_ */
