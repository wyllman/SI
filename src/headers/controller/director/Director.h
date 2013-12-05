/*
 *      Nombre: Director.h
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

#ifndef DIRECTOR_H_
#define DIRECTOR_H_

#include <iostream>

#include "../abstracts/controller.h"
#include "tools/FileLog.h"
#include "tools/MainLoop.h"

using namespace std;

class Director: public Controller {
public:
	Director();
	virtual ~Director();

	void init ();
	void stop ();

private:
	FileLog* regAccErr_;
	MainLoop* mainLoop_;

};

#endif /* DIRECTOR_H_ */
