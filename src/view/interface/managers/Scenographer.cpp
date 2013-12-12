/*
 *      Nombre: Scenographer.cpp
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

#include <view/interface/managers/Scenographer.h>

#include <view/interface/Interface.h>
#include <view/interface/tools/Scene.h>
#include <Tools.h>

#include <iostream>

// ___________________________________________________________________________________
// Constructores y Destructor:
Scenographer::Scenographer(const Interface& interface, const Scene& scene) {
	refInterface_ = &interface;
	refScene_ = &scene;
	logAction(LOG_INIT);
}
Scenographer::~Scenographer() {
	logAction(LOG_END);
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Scenographer::init() {
	initProy();
	initCam();
	initFloor();
}
void Scenographer::update() {
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Manejadores públicos:

// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos privados:
void Scenographer::initProy() {
	updateProy(45.0, 1.0, 1, 1000);
}
void Scenographer::initCam() {
	int pos[3] = { 0, 0, 0 };
	int view[3] = { 0, 0, 1 };
	int upV[3] = { 0, 1, 0 };
	updateCam(pos, view, upV);
}
void Scenographer::initFloor() {
	updateFloor(1000, 1000);
}
void Scenographer::updateProy(float ang, float ratio, int near, int far) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(ang, ratio, near, far);

	glGetFloatv(GL_PROJECTION_MATRIX,
			((Scene*) refScene_)->getProjectionMatrix());
	glMatrixMode(0);
}
void Scenographer::updateCam(int camPos[3], int viewPoint[3], int vectorUp[3]) {
	glMatrixMode (GL_MODELVIEW);
	gluLookAt(camPos[0], camPos[1], camPos[2], viewPoint[0], viewPoint[1],
			viewPoint[2], vectorUp[0], vectorUp[1], vectorUp[2]);

	glGetFloatv(GL_MODELVIEW_MATRIX,
			((Scene*) refScene_)->getModelviewMatrix());
	glMatrixMode(0);
}
void Scenographer::updateFloor(int width, int height) {
	float* vertexFloor = ((Scene*) refScene_)->getVertexFloor(
			width * height * 2);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			vertexFloor[((i * width) + j) * 2] = (i - (width / 2)) / 100.0;
			vertexFloor[((i * width) + j) * 2 + 1] = (j - (width / 2)) / 100.0;
		}
	}

}
void Scenographer::logAction(int index) {
	if (BASIC_LOG) {
		switch (index) {
		case LOG_INIT:
			std::cout
					<< "------Generado el gestor Scenographer para la vista Interfaz "
					<< std::endl;
			break;
		case LOG_END:
			std::cout
					<< "------Destruyendo el gestor Scenographer para la vista Interfaz "
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
					"------Generado el gestor Scenographer para la vista Interfaz ");
			break;
		case LOG_END:
			((Interface*) refInterface_)->log(
					"------Destruyendo el gestor Scenographer para la vista Interfaz ");
			break;
		default:
			break;
		}
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

