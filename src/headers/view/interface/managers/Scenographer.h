/*
 *      Nombre: Scenographer.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de gestionar y renderizar la escena a mostrar en el simulador.
 *
 */

#ifndef SCENOGRAPHER_H_
#define SCENOGRAPHER_H_

#include <iostream>

#include "../Interface.h"
#include "../../../Tools.h"

using namespace std;

class Interface;

class Scenographer {
public:
	Scenographer(const Interface*);
	virtual ~Scenographer();

private:
	const Interface* refInterface_;

	void logAction(int);
};

#endif /* SCENOGRAPHER_H_ */
