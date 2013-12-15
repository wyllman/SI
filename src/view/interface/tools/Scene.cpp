/*
 *      Nombre: Scene.cpp
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

#include <view/interface/tools/Scene.h>
#include <view/interface/Interface.h>
#include <Tools.h>

#include <string.h>
#include <iostream>

// ___________________________________________________________________________________
// Constructores y Destructor:
Scene::Scene(const Interface& interface) {
	refInterface_ = &interface;
	logAction(LOG_INIT);
	vertexFloor_ = NULL;
	vertexFloorColor_ = NULL;
}

Scene::~Scene() {
	logAction(LOG_END);
	if (vertexFloor_ != NULL) {
		delete [] vertexFloor_;
		vertexFloor_ = NULL;
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:

// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Manejadores públicos:
void Scene::updateProy(GLfloat projectionMatrix[]) {
	memcpy(projectionMatrix_, projectionMatrix, sizeof(float) * 16);
}
void Scene::updateCam(GLfloat modelviewMatrix[]) {
	memcpy(modelviewMatrix_, modelviewMatrix, sizeof(float) * 16);
}
void Scene::updateFloor(float vertexFloor[], int size) {
	if (vertexFloor_ != NULL) {
		memcpy(vertexFloor_, vertexFloor, sizeof(float) * size);
	}
}
GLfloat* Scene::getModelviewMatrix() {
	return modelviewMatrix_;
}
GLfloat* Scene::getProjectionMatrix() {
	return projectionMatrix_;
}
const float* Scene::getVertexFloor() const {
	return vertexFloor_;
}
float* Scene::getVertexFloor(int size) {
	if (vertexFloor_ != NULL) {
		delete [] vertexFloor_;
	}
	vertexFloor_ = new float[size];
	return vertexFloor_;
}
const float* Scene::getVertexFloorColor() const {
	return vertexFloorColor_;
}
float* Scene::getVertexFloorColor(int size) {
	if (vertexFloorColor_ != NULL) {
		delete [] vertexFloorColor_;
	}
	vertexFloorColor_ = new float[size];
	return vertexFloorColor_;
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos privados:
void Scene::logAction(int index) {
	if (BASIC_LOG) {
		switch (index) {
		case LOG_INIT:
			std::cout
					<< "------Generado la herramienta Scene para la vista Interfaz "
					<< std::endl;
			break;
		case LOG_END:
			std::cout
					<< "------Destruyendo la herramienta Scene para la vista Interfaz "
					<< std::endl;
			break;
		default:
			break;
		}
	}
	if (ADVAN_LOG) {
		switch (index) {
		case LOG_INIT:
			((Interface*) refInterface_)->log(
					"------Generado la herramienta Scene para la vista Interfaz ");
			break;
		case LOG_END:
			((Interface*) refInterface_)->log(
					"------Destruyendo la herramienta Scene para la vista Interfaz ");
			break;
		default:
			break;
		}
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

