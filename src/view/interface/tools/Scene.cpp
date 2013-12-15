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

#include "../../../../include/view/interface/tools/Scene.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Scene::Scene(const Interface* interface) {
	refInterface_ = interface;
	logAction(LOG_INIT);
	vertexFloor_ = 0;
	vertexFloorColor_ = 0;
}

Scene::~Scene() {
	logAction(LOG_END);
	if (vertexFloor_ != 0) {
		delete[] (vertexFloor_);
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
	for (int i = 0; i < 16; i++) {
		projectionMatrix_[i] = projectionMatrix[i];
	}
}
void Scene::updateCam(GLfloat modelviewMatrix[]) {
	for (int i = 0; i < 16; i++) {
		modelviewMatrix_[i] = modelviewMatrix[i];
	}
}
void Scene::updateFloor(float vertexFloor[], int size) {
	if (vertexFloor_ != 0) {
		delete[] (vertexFloor_);
	}
	vertexFloor_ = new float[size];
	for (int i = 0; i < size; i++) {
		vertexFloor_[i] = vertexFloor[i];
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
	if (vertexFloor_ != 0) {
		delete[] (vertexFloor_);
	}
	vertexFloor_ = new float[size];
	return vertexFloor_;
}
const float* Scene::getVertexFloorColor() const {
	return vertexFloorColor_;
}
float* Scene::getVertexFloorColor(int size) {
	if (vertexFloorColor_ != 0) {
		delete[] (vertexFloorColor_);
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
			cout
					<< "------Generado la herramienta Scene para la vista Interfaz "
					<< endl;
			break;
		case LOG_END:
			cout
					<< "------Destruyendo la herramienta Scene para la vista Interfaz "
					<< endl;
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

