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
#include "../../../Tools.h"

using namespace std;

class Interface;

class Scene {
public:
	Scene(const Interface*);
	virtual ~Scene();

	void updateProy (GLfloat []);
	void updateCam (GLfloat []);
	void updateFloor (float [], int);
	GLfloat* getModelviewMatrix();
	GLfloat* getProjectionMatrix();
	const float* getVertexFloor() const;
	float* getVertexFloor(int);

private:
	const Interface* refInterface_;
	GLfloat modelviewMatrix_[16];
	GLfloat projectionMatrix_[16];
	float* vertexFloor_;

	void logAction(int);
};

#endif /* SCENE_H_ */
