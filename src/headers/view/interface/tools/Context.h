/*
 *      Nombre: Context.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de gestionar e inicializar la libreria de openGL.
 *
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <iostream>

#include "../Interface.h"

using namespace std;

class Context {
public:
	Context(const Interface*);
	virtual ~Context();

private:
	const Interface* refInterface_;

};

#endif /* CONTEXT_H_ */
