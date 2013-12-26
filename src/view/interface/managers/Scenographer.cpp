/*
 *      Nombre: Scenographer.cpp
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.003
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de gestionar y renderizar la escena a mostrar en el simulador.
 *
 */

#include <model/map/Map.h>
#include <view/interface/managers/Scenographer.h>
#include <view/interface/Interface.h>
#include <view/interface/tools/Scene.h>
#include <Tools.h>
//#include <typedefs.h>

#include <iostream>
#ifdef __linux
   #include <GL/gl.h>
   #include <GL/glu.h>
#else
   #include <GL.h>
   #include <GLU.h>
#endif

#include <math.h>


// ___________________________________________________________________________________
// Constructores y Destructor:
Scenographer::Scenographer(const Interface& interface, const Scene& scene, const Map& map) {
   refInterface_ = &interface;
   refScene_ = &scene;
   refMap_ = &map;
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
   float camPos[3] = {0.0, 20.0, -100.0};
   float viewPoint[3] = {0.0, 0.0, 0.0};
   float vectorUp[3] = {0.0, 1.0, 0.0};

   initProy(45.0, WIN_WIDTH / WIN_HEIGHT, 1, 1000);
   initCam(camPos, viewPoint, vectorUp);
   initFloor();
}
void Scenographer::update() {
}
void Scenographer::projZoom(float value) {
   projAng_ += value;
   updateProy();
}
void Scenographer::camPosX(float value) {
   camPos_[0] += value;
   updateCam();
}
void Scenographer::camRotationPos(float value) {
   camRotAngle_ += value;
   updateCam();
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
void Scenographer::initProy(float ang, float ratio, int near, int far) {
   projAng_ = ang;
   projRatio_ = ratio;
   projNear_ = near;
   projFar_ = far;
   updateProy();
}
void Scenographer::initCam(float camPos[3], float viewPoint[3], float vectorUp[3]) {
   camRotAngle_ = 0;

   camPos_[0] = camPos[0];
   camPos_[1] = camPos[1];
   camPos_[2] = camPos[2];

   camViewPoint_[0] = viewPoint[0];
   camViewPoint_[1] = viewPoint[1];
   camViewPoint_[2] = viewPoint[2];

   camVectorUp_[0] = vectorUp[0];
   camVectorUp_[1] = vectorUp[1];
   camVectorUp_[2] = vectorUp[2];
   updateCam();
}
void Scenographer::initFloor() {
   updateFloor(MAP_WIDTH, MAP_HEIGHT);
}
void Scenographer::updateProy() {
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(projAng_, projRatio_, projNear_, projFar_);

   glGetFloatv(GL_PROJECTION_MATRIX, const_cast<Scene*>(refScene_)->getProjectionMatrix());
   glMatrixMode(0);
}
void Scenographer::updateCam() {
   float camDistance = powf(camPos_[0] - camViewPoint_[0], 2);
   camDistance += powf(camPos_[2] - camViewPoint_[2], 2);
   camDistance = sqrtf(camDistance);

   camPos_[0] = sinf(camRotAngle_ * (3.1416 / 180)) * (camDistance);
   camPos_[2] = cosf(camRotAngle_ * (3.1416 / 180)) * (camDistance);

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(camPos_[0], camPos_[1], camPos_[2]
            , camViewPoint_[0], camViewPoint_[1], camViewPoint_[2]
            , camVectorUp_[0], camVectorUp_[1], camVectorUp_[2]);

   glGetFloatv(GL_MODELVIEW_MATRIX, const_cast<Scene*>(refScene_)->getModelviewMatrix());
   glMatrixMode(0);
}
void Scenographer::updateFloor(int width, int height) {
   const int NUM_VER_POINT = 3 * 4 * 5;
   float* vertexFloor = const_cast<Scene*>(refScene_)
                           ->getVertexFloor(100 * 100 * NUM_VER_POINT);
   float* vertexFloorColor = const_cast<Scene*>(refScene_)
                                ->getVertexFloorColor(100 * 100 * NUM_VER_POINT);
   float* color = new float[3];
   color[0] = 0;
   color[1] = 0;
   color[2] = 0;
   BYTE slot;

   for (int i = 0; i < MAP_WIDTH; i++) {
      for (int j = 0; j < MAP_HEIGHT; j++) {
         slot = (*refMap_)(i, j);
         switch (slot & MASK_TERRAIN) {
            case TERRAIN_GROUND:
               if (slot != TERRAIN_GROUND) {
                  delete [] (color);
                  color = getcolor(slot & MASK_RESOURCE);
                  createSideUpFloor(i, j, 0.0, color, vertexFloor, vertexFloorColor);
               }

               color[0] = 0.0;
               color[1] = 1.0;
               color [2] = 0.0;

               if (slot == TERRAIN_GROUND) {
                  createSideUpFloor(i, j, 0.0, color, vertexFloor, vertexFloorColor);
               }

               createSideFloor(i, j, 0.0, color, vertexFloor, vertexFloorColor, 1);
               createSideFloor(i, j, 0.0, color, vertexFloor, vertexFloorColor, 2);
               createSideFloor(i, j, 0.0, color, vertexFloor, vertexFloorColor, 3);
               createSideFloor(i, j, 0.0, color, vertexFloor, vertexFloorColor, 4);
               break;
            case TERRAIN_ELEVATION:
               color[0] = 0.0;
               color[1] = 0.5;
               color [2] = 0.0;

               createSideUpFloor(i, j, 0.5, color, vertexFloor, vertexFloorColor);
               createSideFloor(i, j, 0.5, color, vertexFloor, vertexFloorColor, 1);
               createSideFloor(i, j, 0.5, color, vertexFloor, vertexFloorColor, 2);
               createSideFloor(i, j, 0.5, color, vertexFloor, vertexFloorColor, 3);
               createSideFloor(i, j, 0.5, color, vertexFloor, vertexFloorColor, 4);
               break;
            case TERRAIN_WATER:
               color[0] = 0.0;
               color[1] = 0.0;
               color [2] = 1.0;

               createSideUpFloor(i, j, - 0.2, color, vertexFloor, vertexFloorColor);
               createSideFloor(i, j, - 0.2, color, vertexFloor, vertexFloorColor, 1);
               createSideFloor(i, j, - 0.2, color, vertexFloor, vertexFloorColor, 2);
               createSideFloor(i, j, - 0.2, color, vertexFloor, vertexFloorColor, 3);
               createSideFloor(i, j, - 0.2, color, vertexFloor, vertexFloorColor, 4);
               break;
            default:
               color[0] = 0.0;
               color[1] = 1.0;
               color [2] = 0.0;

               createSideUpFloor(i, j, - 0.01, color, vertexFloor, vertexFloorColor);
               createSideFloor(i, j, - 0.01, color, vertexFloor, vertexFloorColor, 1);
               createSideFloor(i, j, - 0.01, color, vertexFloor, vertexFloorColor, 2);
               createSideFloor(i, j, - 0.01, color, vertexFloor, vertexFloorColor, 3);
               createSideFloor(i, j, - 0.01, color, vertexFloor, vertexFloorColor, 4);
               break;
         }
      }
   }
   delete [] (color);
}
void Scenographer::createSideUpFloor(int row, int col, float height, float color[3], float* vertexFloor, float* vertexFloorColor) {
	const int NUM_VER_POINT = 3 * 4 * 5;

	// Eje X
	vertexFloor[((row * 100) + col) * NUM_VER_POINT] = (row - (100.0 / 2.0)) / 1.0;
	vertexFloor[((row * 100) + col) * NUM_VER_POINT + 3] = ((row + 1) - (100.0 / 2.0)) / 1.0;
	vertexFloor[((row * 100) + col) * NUM_VER_POINT + 6] = ((row + 1) - (100.0 / 2.0)) / 1.0;
	vertexFloor[((row * 100) + col) * NUM_VER_POINT + 9] = (row - (100.0 / 2.0)) / 1.0;

	// Eje Y
	vertexFloor[((row * 100) + col) * NUM_VER_POINT + 1] = height;
	vertexFloor[((row * 100) + col) * NUM_VER_POINT + 4] = height;
	vertexFloor[((row * 100) + col) * NUM_VER_POINT + 7] = height;
	vertexFloor[((row * 100) + col) * NUM_VER_POINT + 10] = height;

	// Eje Z
   vertexFloor[((row * 100) + col) * NUM_VER_POINT + 2] = (col - (100.0 / 2.0)) / 1.0;
   vertexFloor[((row * 100) + col) * NUM_VER_POINT + 5] = (col - (100.0 / 2.0)) / 1.0;
   vertexFloor[((row * 100) + col) * NUM_VER_POINT + 8] = ((col + 1) - (100.0 / 2.0)) / 1.0;
   vertexFloor[((row * 100) + col) * NUM_VER_POINT + 11] = ((col + 1) - (100.0 / 2.0)) / 1.0;


   vertexFloorColor[((row * 100) + col) * NUM_VER_POINT] = color[0];
   vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 1] = color[1];
   vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 2] = color[2];

	vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 3] = color[0];
	vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 4] = color[1];
	vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 5] = color[2];

	vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 6] = color[0];
	vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 7] = color[1];
	vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 8] = color[2];

	vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 9] = color[0];
	vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 10] = color[1];
	vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 11] = color[2];
}
void Scenographer::createSideFloor(int row, int col, float height, float color[3], float* vertexFloor, float* vertexFloorColor, int side) {
   const int NUM_VER_POINT = 3 * 4 * 5;
   bool paintQuad = false;
   float heightDown = -1;

   switch (side) {
      case 2:
         if (col == 0) {
            paintQuad = true;
         } else if (checkHeightWest(row, col)) {
            paintQuad = true;
            heightDown = getHeight(row, col - 1);
         }
         break;
      case 1:
         if (row == 0) {
            paintQuad = true;
         } else if (checkHeightNorth(row, col)) {
            paintQuad = true;
            heightDown = getHeight(row - 1, col);
         }
         break;
      case 4:
         if (col == (MAP_WIDTH - 1)) {
            paintQuad = true;
         } else if (checkHeightEast(row, col)) {
            paintQuad = true;
            heightDown = getHeight(row, col + 1);
         }
         break;
      case 3:
         if (row == (MAP_HEIGHT - 1)) {
            paintQuad = true;
         } else if (checkHeightSouth(row, col)) {
            paintQuad = true;
            heightDown = getHeight(row + 1, col);
         }
         break;
   default:
      break;
   }

   if (paintQuad) {
	   // Eje X
	   if (side == 2 || side == 4) {
		  vertexFloor[((row * 100) + col) * NUM_VER_POINT + (side * 12)] = (row - (100.0 / 2.0)) / 1.0;
		  vertexFloor[((row * 100) + col) * NUM_VER_POINT + 3 + (side * 12)] = ((row + 1) - (100.0 / 2.0)) / 1.0;
		  vertexFloor[((row * 100) + col) * NUM_VER_POINT + 6 + (side * 12)] = ((row + 1) - (100.0 / 2.0)) / 1.0;
		  vertexFloor[((row * 100) + col) * NUM_VER_POINT + 9 + (side * 12)] = (row - (100.0 / 2.0)) / 1.0;
	   } else if (side == 1) {
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + (side * 12)] = (row - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 3 + (side * 12)] = (row - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 6 + (side * 12)] = (row - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 9 + (side * 12)] = (row - (100.0 / 2.0)) / 1.0;
	   } else if (side == 3) {
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + (side * 12)] = ((row + 1) - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 3 + (side * 12)] = ((row + 1) - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 6 + (side * 12)] = ((row + 1) - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 9 + (side * 12)] = ((row + 1) - (100.0 / 2.0)) / 1.0;
	   }

	   // Eje Y
	   if (side == 1 || side == 3) {
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 1 + (side * 12)] = height;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 4 + (side * 12)] = heightDown;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 7 + (side * 12)] = heightDown;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 10 + (side * 12)] = height;
	   } else if (side == 2) {
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 1 + (side * 12)] = heightDown;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 4 + (side * 12)] = heightDown;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 7 + (side * 12)] = height;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 10 + (side * 12)] = height;
	   } else if (side == 4) {
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 1 + (side * 12)] = height;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 4 + (side * 12)] = height;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 7 + (side * 12)] = heightDown;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 10 + (side * 12)] = heightDown;
	   }

	   // Eje Z
	   if (side == 3) {
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 2 + (side * 12)] = (col - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 5 + (side * 12)] = (col - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 8 + (side * 12)] = ((col + 1) - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 11 + (side * 12)] = ((col + 1) - (100.0 / 2.0)) / 1.0;
	   }  else if (side == 1) {
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 2 + (side * 12)] = ((col + 1) - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 5 + (side * 12)] = ((col + 1) - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 8 + (side * 12)] = (col - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 11 + (side * 12)] = (col - (100.0 / 2.0)) / 1.0;
	   } else if (side == 2) {
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 2 + (side * 12)] = (col - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 5 + (side * 12)] = (col - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 8 + (side * 12)] = (col - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 11 + (side * 12)] = (col - (100.0 / 2.0)) / 1.0;
	   } else if (side == 4) {
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 2 + (side * 12)] = ((col + 1) - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 5 + (side * 12)] = ((col + 1) - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 8 + (side * 12)] = ((col + 1) - (100.0 / 2.0)) / 1.0;
			vertexFloor[((row * 100) + col) * NUM_VER_POINT + 11 + (side * 12)] = ((col + 1) - (100.0 / 2.0)) / 1.0;
	   }

		vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + (side * 12)] = color[0] / 2;
		vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 1 + (side * 12)] = color[1] / 2;
		vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 2 + (side * 12)] = color[2] / 2;

		vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 3 + (side * 12)] = color[0] / 2;
		vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 4 + (side * 12)] = color[1] / 2;
		vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 5 + (side * 12)] = color[2] / 2;

		vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 6 + (side * 12)] = color[0] / 2;
		vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 7 + (side * 12)] = color[1] / 2;
		vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 8 + (side * 12)] = color[2] / 2;

		vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 9 + (side * 12)] = color[0] / 2;
		vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 10 + (side * 12)] = color[1] / 2;
		vertexFloorColor[((row * 100) + col) * NUM_VER_POINT + 11 + (side * 12)] = color[2] / 2;


   }
}

bool Scenographer::checkHeightNorth(int row, int col) {
   bool result = false;
   if ( row > 0) {
      if (getHeight(row, col) > getHeight(row - 1, col)) {
         result = true;
      }
   }
   return result;
}

bool Scenographer::checkHeightEast(int row, int col) {
   bool result = false;
   if ( col < MAP_WIDTH - 1) {
      if (getHeight(row, col) > getHeight(row, col + 1)) {
         result = true;
      }
   }
   return result;
}

bool Scenographer::checkHeightSouth(int row, int col) {
   bool result = false;
   if ( row < MAP_HEIGHT - 1) {
      if (getHeight(row, col) > getHeight(row + 1, col)) {
        result = true;
      }
   }
   return result;
}

bool Scenographer::checkHeightWest(int row, int col) {
   bool result = false;
   if ( col > 0) {
      if (getHeight(row, col) > getHeight(row, col - 1)) {
         result = true;
      }
   }
   return result;
}


float Scenographer::getHeight(int row, int col) {
   return getHeight((*refMap_)(row, col));
}

float Scenographer::getHeight(BYTE value) {
   float result = -10;
   switch (value & MASK_TERRAIN) {
      case TERRAIN_GROUND:
         result = 0.0;
         break;
      case TERRAIN_ELEVATION:
         result = 0.5;
         break;
      case TERRAIN_WATER:
         result = - 0.2;
         break;
      default:
         result = 0.0;
         break;
   }
   return result;
}

float* Scenographer::getcolor(BYTE value) {
   float* color = new float[3];
   switch (value) {
      case RESOURCE_METAL:
         color[0] = 0.75;
         color[1] = 0.75;
         color[2] = 0.75;
         break;
      case RESOURCE_FOOD:
         color[0] = 1;
         color[1] = 0;
         color[2] = 0;
         break;
      case RESOURCE_MINERAL:
         color[0] = 0;
         color[1] = 0;
         color[2] = 0;
         break;
      default:
         color[0] = 1;
         color[1] = 0;
         color[2] = 1;
         break;
   }
   return color;
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
			const_cast<Interface*>(refInterface_)
				->log("------Generado el gestor Scenographer para la vista Interfaz ");
			break;
		case LOG_END:
			const_cast<Interface*>(refInterface_)
				->log("------Destruyendo el gestor Scenographer para la vista Interfaz ");
			break;
		default:
			break;
		}
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

