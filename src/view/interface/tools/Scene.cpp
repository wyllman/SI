/*
 *      Nombre: Scene.cpp
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.003
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
#include <view/interface/managers/Scenographer.h>
#include <Tools.h>

#include <string.h>
#include <iostream>

using namespace std;

// ___________________________________________________________________________________
// Constructores y Destructor:
Scene::Scene(const Interface& interface) {
	const int NUM_VER_POINT = 3 * 4 * 5;
	const int NUM_VER = MAP_WIDTH * MAP_HEIGHT * NUM_VER_POINT;
	refInterface_ = &interface;
	logAction(LOG_INIT);
	numberVertex_ = 0;
	numberQuadsFloor_ = 0;
	vertexFloor_ = new float[NUM_VER];
	vertexFloorColor_ = new float[NUM_VER];
	resetFloor();
}

Scene::~Scene() {
	logAction(LOG_END);

	if (vertexFloor_ != NULL) {
		delete [] vertexFloor_;
		vertexFloor_ = NULL;
	}

	if (vertexFloorColor_ != NULL) {
		delete [] vertexFloorColor_;
		vertexFloorColor_ = NULL;
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Scene::updateColor(bool mask, bool** knownMask) {
	int vecSize = indicesFloorSlots_.size();
	int firstInd;
	int lastInd;
	float color1[3] = {0, 0, 0};
	float* origColor;
	int row;
	int col;
	int vecPos;
	float alpha = 1;

	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			vecPos = (i * MAP_WIDTH) + j;
			firstInd = indicesFloorSlots_[vecPos];

			if (vecPos < (vecSize - 1)) {
				lastInd = (indicesFloorSlots_[vecPos + 1]);
			} else {
				lastInd = ((numberQuadsFloor_ * 4) * 3) - (3 * 36);
			}

			origColor = const_cast<Scenographer*>
			            (const_cast<Interface*>(refInterface_)
			             ->getScenographer())->getcolor(i, j);

			for (int k = firstInd; k < lastInd; k += 3) {
				if (mask && !knownMask[i][j]) {
					vertexFloorColor_[k] = color1[0];
					vertexFloorColor_[k + 1] = color1[1];
					vertexFloorColor_[k + 2] = color1[2];
				} else {
					if ((k - firstInd) < (4 * 3)) {
						alpha = 1;
					} else {
						alpha = 0.5;
					}

					vertexFloorColor_[k] = origColor[0] * alpha;
					vertexFloorColor_[k + 1] = origColor[1] * alpha;
					vertexFloorColor_[k + 2] = origColor[2] * alpha;

				}
			}
		}
	}
}
void Scene::resetFloor() {
	indicesFloorSlots_.clear();
}
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
const float* Scene::getVertexFloorColor() const {
	return vertexFloorColor_;
}
int Scene::getNumberVertex() const {
	return numberVertex_;
}
void Scene::setNumberVertex(int numberVertex) {
	numberVertex_ = numberVertex;
}
int Scene::getNumberQuadsFloor() const {
	return numberQuadsFloor_;
}
void Scene::setNumberQuadsFloor(int numberQuadsFloor) {
	numberQuadsFloor_ = numberQuadsFloor;
}
int Scene::getNumberQuadsWorkingA() const {
	return numberQuadsWorkingA_;
}
void Scene::setNumberQuadsWorkingA(int numberQuadsWorkingA) {
	numberQuadsWorkingA_ = numberQuadsWorkingA;
}
int Scene::getNumberTriangMainA() const {
	return numberTriangMainA_;
}
void Scene::setNumberTriangMainA(int numberTriangMainA) {
	numberTriangMainA_ = numberTriangMainA;
}
int Scene::getNumberTriangSearchA() const {
	return numberTriangSearchA_;
}
void Scene::setNumberTriangSearchA(int numberTriangSearchA) {
	numberTriangSearchA_ = numberTriangSearchA;
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos privados:
void Scene::createUpQuads(float* position, float* color1, float scale,
                          int memPos) {
	const float DIFF = (0.5 * scale);
	float centralPosX = ((position[0] - (MAP_HEIGHT / 2.0)) * MAP_SCALE) + (MAP_SCALE / 2.0);
	float centralPosY = position[1] * MAP_UP_SCALE;
	float centralPosZ = ((position[2] - (MAP_WIDTH / 2.0)) * MAP_SCALE) + (MAP_SCALE / 2.0);

	indicesFloorSlots_.push_back(memPos);

	// Posiciones de los vértices
	// ---Eje X
	vertexFloor_[(memPos)] = centralPosX + (DIFF);
	vertexFloor_[(memPos) + 3] = centralPosX - (DIFF);
	vertexFloor_[(memPos) + 6] = centralPosX - (DIFF);
	vertexFloor_[(memPos) + 9] = centralPosX + (DIFF);
	// ---Eje Y
	vertexFloor_[(memPos) + 1] = centralPosY;
	vertexFloor_[(memPos) + 4] = centralPosY;
	vertexFloor_[(memPos) + 7] = centralPosY;
	vertexFloor_[(memPos) + 10] = centralPosY;
	// ---Eje Z
	vertexFloor_[(memPos) + 2] = centralPosZ + (DIFF);
	vertexFloor_[(memPos) + 5] = centralPosZ + (DIFF);
	vertexFloor_[(memPos) + 8] = centralPosZ - (DIFF);
	vertexFloor_[(memPos) + 11] = centralPosZ - (DIFF);

	// Colores de los vértices RGB
	vertexFloorColor_[(memPos)] = color1[0];
	vertexFloorColor_[(memPos) + 1] = color1[1];
	vertexFloorColor_[(memPos) + 2] = color1[2];

	vertexFloorColor_[(memPos) + 3] = color1[0];
	vertexFloorColor_[(memPos) + 4] = color1[1];
	vertexFloorColor_[(memPos) + 5] = color1[2];

	vertexFloorColor_[(memPos) + 6] = color1[0];
	vertexFloorColor_[(memPos) + 7] = color1[1];
	vertexFloorColor_[(memPos) + 8] = color1[2];

	vertexFloorColor_[(memPos) + 9] = color1[0];
	vertexFloorColor_[(memPos) + 10] = color1[1];
	vertexFloorColor_[(memPos) + 11] = color1[2];
}
void Scene::createSideQuads(float* position, float height2, float* color1,
                            float scale, int memPos, int side) {
	createSideQuads(position, height2, color1, color1, scale, memPos, side);
}
void Scene::createSideQuads(float* position, float height2, float* color1,
                            float* color2, float scale, int memPos, int side) {
	const float DIFF = (0.5 * scale);
	float centralPosX = ((position[0] - (MAP_HEIGHT / 2.0)) * MAP_SCALE) + (MAP_SCALE / 2.0);
	float centralPosY = position[1] * MAP_UP_SCALE;
	float centralPosZ = ((position[2] - (MAP_WIDTH / 2.0)) * MAP_SCALE) + (MAP_SCALE / 2.0);
	float heightDown = height2 * scale;

	if (heightDown > position[1]) {
		centralPosY = heightDown;
		heightDown = position[1] * MAP_UP_SCALE;
	}

	// Posiciones de los vértices
	if (side == 1) { // Oeste
		// Eje X
		vertexFloor_[memPos] = centralPosX - (DIFF);
		vertexFloor_[memPos + 3] = centralPosX - (DIFF);
		vertexFloor_[memPos + 6] = centralPosX - (DIFF);
		vertexFloor_[memPos + 9] = centralPosX - (DIFF);
		// Eje Z
		vertexFloor_[memPos + 2] = centralPosZ - (DIFF);
		vertexFloor_[memPos + 5] = centralPosZ + (DIFF);
		vertexFloor_[memPos + 8] = centralPosZ + (DIFF);
		vertexFloor_[memPos + 11] = centralPosZ - (DIFF);
	} else if (side == 2) { // Norte
		// Eje X
		vertexFloor_[memPos] = centralPosX + (DIFF);
		vertexFloor_[memPos + 3] = centralPosX - (DIFF);
		vertexFloor_[memPos + 6] = centralPosX - (DIFF);
		vertexFloor_[memPos + 9] = centralPosX + (DIFF);
		// Eje Z
		vertexFloor_[memPos + 2] = centralPosZ - (DIFF);
		vertexFloor_[memPos + 5] = centralPosZ - (DIFF);
		vertexFloor_[memPos + 8] = centralPosZ - (DIFF);
		vertexFloor_[memPos + 11] = centralPosZ - (DIFF);
	} else if (side == 3) { // Este
		// Eje X
		vertexFloor_[memPos] = centralPosX + (DIFF);
		vertexFloor_[memPos + 3] = centralPosX + (DIFF);
		vertexFloor_[memPos + 6] = centralPosX + (DIFF);
		vertexFloor_[memPos + 9] = centralPosX + (DIFF);
		// Eje Z
		vertexFloor_[memPos + 2] = centralPosZ + (DIFF);
		vertexFloor_[memPos + 5] = centralPosZ - (DIFF);
		vertexFloor_[memPos + 8] = centralPosZ - (DIFF);
		vertexFloor_[memPos + 11] = centralPosZ + (DIFF);
	} else if (side == 4) { // Sur
		// Eje X
		vertexFloor_[memPos] = centralPosX - (DIFF);
		vertexFloor_[memPos + 3] = centralPosX + (DIFF);
		vertexFloor_[memPos + 6] = centralPosX + (DIFF);
		vertexFloor_[memPos + 9] = centralPosX - (DIFF);
		// Eje Z
		vertexFloor_[memPos + 2] = centralPosZ + (DIFF);
		vertexFloor_[memPos + 5] = centralPosZ + (DIFF);
		vertexFloor_[memPos + 8] = centralPosZ + (DIFF);
		vertexFloor_[memPos + 11] = centralPosZ + (DIFF);
	}

	// Eje Y
	vertexFloor_[memPos + 1] = centralPosY;
	vertexFloor_[memPos + 4] = centralPosY;
	vertexFloor_[memPos + 7] = heightDown;
	vertexFloor_[memPos + 10] = heightDown;

	// Colores de los vértices RGB
	// ---Vertices superiores:
	vertexFloorColor_[memPos] = color1[0];
	vertexFloorColor_[memPos + 1] = color1[1];
	vertexFloorColor_[memPos + 2] = color1[2];

	vertexFloorColor_[memPos + 3] = color1[0];
	vertexFloorColor_[memPos + 4] = color1[1];
	vertexFloorColor_[memPos + 5] = color1[2];

	// ---Vertices inferiores:
	vertexFloorColor_[memPos + 6] = color2[0];
	vertexFloorColor_[memPos + 7] = color2[1];
	vertexFloorColor_[memPos + 8] = color2[2];

	vertexFloorColor_[memPos + 9] = color2[0];
	vertexFloorColor_[memPos + 10] = color2[1];
	vertexFloorColor_[memPos + 11] = color2[2];
}
void Scene::createSideTriangle(float* position, float height2, float* color1,
                               float* color2, float scale, int memPos, int side) {
	const float DIFF = (0.5 * scale);
	float centralPosX = ((position[0] - (MAP_HEIGHT / 2.0)) * MAP_SCALE) + (MAP_SCALE / 2.0);
	float centralPosY = position[1] * MAP_UP_SCALE;
	float centralPosZ = ((position[2] - (MAP_WIDTH / 2.0)) * MAP_SCALE) + (MAP_SCALE / 2.0);
	float heightUp = height2 * scale;

	// Posiciones de los vértices
	if (side == 1) { // Norte
		// Eje X
		vertexFloor_[memPos] = centralPosX;
		vertexFloor_[memPos + 3] = centralPosX - (DIFF);
		vertexFloor_[memPos + 6] = centralPosX + (DIFF);

		// Eje Z
		vertexFloor_[memPos + 2] = centralPosZ;
		vertexFloor_[memPos + 5] = centralPosZ - (DIFF);
		vertexFloor_[memPos + 8] = centralPosZ - (DIFF);
	} else if (side == 2) { // Este
		// ---Eje X
		vertexFloor_[memPos] = centralPosX;
		vertexFloor_[memPos + 3] = centralPosX + (DIFF);
		vertexFloor_[memPos + 6] = centralPosX + (DIFF);

		// ---Eje Z
		vertexFloor_[memPos + 2] = centralPosZ;
		vertexFloor_[memPos + 5] = centralPosZ - (DIFF);
		vertexFloor_[memPos + 8] = centralPosZ + (DIFF);
	} else if (side == 3) { // Sur
		// ---Eje X
		vertexFloor_[memPos] = centralPosX;
		vertexFloor_[memPos + 3] = centralPosX + (DIFF);
		vertexFloor_[memPos + 6] = centralPosX - (DIFF);

		// ---Eje Z
		vertexFloor_[memPos + 2] = centralPosZ;
		vertexFloor_[memPos + 5] = centralPosZ + (DIFF);
		vertexFloor_[memPos + 8] = centralPosZ + (DIFF);
	} else if (side == 4) { // Oeste
		// ---Eje X
		vertexFloor_[memPos] = centralPosX;
		vertexFloor_[memPos + 3] = centralPosX - (DIFF);
		vertexFloor_[memPos + 6] = centralPosX - (DIFF);

		// ---Eje Z
		vertexFloor_[memPos + 2] = centralPosZ;
		vertexFloor_[memPos + 5] = centralPosZ + (DIFF);
		vertexFloor_[memPos + 8] = centralPosZ - (DIFF);
	}

	// ---Eje Y
	vertexFloor_[memPos + 1] = centralPosY + (heightUp);
	vertexFloor_[memPos + 4] = centralPosY;
	vertexFloor_[memPos + 7] = centralPosY;


	// Colores de los vértices RGB
	vertexFloorColor_[memPos] = color1[0];
	vertexFloorColor_[memPos + 1] = color1[1];
	vertexFloorColor_[memPos + 2] = color1[2];

	vertexFloorColor_[memPos + 3] = color2[0];
	vertexFloorColor_[memPos + 4] = color2[1];
	vertexFloorColor_[memPos + 5] = color2[2];

	vertexFloorColor_[memPos + 6] = color2[0];
	vertexFloorColor_[memPos + 7] = color2[1];
	vertexFloorColor_[memPos + 8] = color2[2];
}

void Scene::createSideTriangleInf(float* position, float height2, float* color1,
                                  float* color2, float scale, int memPos, int side) {
	const float DIFF = (0.5 * scale);
	float centralPosX = ((position[0] - (MAP_HEIGHT / 2.0)) * MAP_SCALE) + (MAP_SCALE / 2.0);
	float centralPosY = position[1] * MAP_UP_SCALE;
	float centralPosZ = ((position[2] - (MAP_WIDTH / 2.0)) * MAP_SCALE) + (MAP_SCALE / 2.0);
	float heightDown = height2 * scale;

	// Posiciones de los vértices
	if (side == 1) { // Norte
		// Eje X
		vertexFloor_[memPos] = centralPosX;
		vertexFloor_[memPos + 3] = centralPosX + (DIFF);
		vertexFloor_[memPos + 6] = centralPosX - (DIFF);

		// Eje Z
		vertexFloor_[memPos + 2] = centralPosZ;
		vertexFloor_[memPos + 5] = centralPosZ - (DIFF);
		vertexFloor_[memPos + 8] = centralPosZ - (DIFF);
	} else if (side == 2) { // Este
		// ---Eje X
		vertexFloor_[memPos] = centralPosX;
		vertexFloor_[memPos + 3] = centralPosX + (DIFF);
		vertexFloor_[memPos + 6] = centralPosX + (DIFF);

		// ---Eje Z
		vertexFloor_[memPos + 2] = centralPosZ;
		vertexFloor_[memPos + 5] = centralPosZ + (DIFF);
		vertexFloor_[memPos + 8] = centralPosZ - (DIFF);
	} else if (side == 3) { // Sur
		// ---Eje X
		vertexFloor_[memPos] = centralPosX;
		vertexFloor_[memPos + 3] = centralPosX - (DIFF);
		vertexFloor_[memPos + 6] = centralPosX + (DIFF);

		// ---Eje Z
		vertexFloor_[memPos + 2] = centralPosZ;
		vertexFloor_[memPos + 5] = centralPosZ + (DIFF);
		vertexFloor_[memPos + 8] = centralPosZ + (DIFF);
	} else if (side == 4) { // Oeste
		// ---Eje X
		vertexFloor_[memPos] = centralPosX;
		vertexFloor_[memPos + 3] = centralPosX - (DIFF);
		vertexFloor_[memPos + 6] = centralPosX - (DIFF);

		// ---Eje Z
		vertexFloor_[memPos + 2] = centralPosZ;
		vertexFloor_[memPos + 5] = centralPosZ - (DIFF);
		vertexFloor_[memPos + 8] = centralPosZ + (DIFF);
	}

	// ---Eje Y
	vertexFloor_[memPos + 1] = centralPosY - (heightDown);
	vertexFloor_[memPos + 4] = centralPosY;
	vertexFloor_[memPos + 7] = centralPosY;


	// Colores de los vértices RGB
	vertexFloorColor_[memPos] = color1[0];
	vertexFloorColor_[memPos + 1] = color1[1];
	vertexFloorColor_[memPos + 2] = color1[2];

	vertexFloorColor_[memPos + 3] = color2[0];
	vertexFloorColor_[memPos + 4] = color2[1];
	vertexFloorColor_[memPos + 5] = color2[2];

	vertexFloorColor_[memPos + 6] = color2[0];
	vertexFloorColor_[memPos + 7] = color2[1];
	vertexFloorColor_[memPos + 8] = color2[2];
}

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

