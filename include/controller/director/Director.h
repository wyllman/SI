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
#include <SDL.h>

#include "../abstracts/controller.h"
#include "tools/FileLog.h"
#include "tools/MainLoop.h"
#include "../../view/interface/Interface.h"
#include "../../Tools.h"

using namespace std;
class MainLoop;

class Director: public Controller {
public:
	Director();
	virtual ~Director();

	void init ();
	void start ();
	void stop ();
	const FileLog* getRegAccErr() const;

private:
	FileLog* regAccErr_;
	MainLoop* mainLoop_;

	void mainLoop ();
	void logAction (int);

};

#endif /* DIRECTOR_H_ */
