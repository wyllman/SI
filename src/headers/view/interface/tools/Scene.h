/*
 *      Nombre: Scene.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de gestionar y contener los objetos a mostrar en la escena.
 *
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <iostream>

#include "../Interface.h"

using namespace std;

class Interface;

class Scene {
public:
	Scene(const Interface*);
	virtual ~Scene();

private:
	const Interface* refInterface_;

	void logAction(int);

};

#endif /* SCENE_H_ */
