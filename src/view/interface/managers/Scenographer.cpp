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
   initObjects();
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
// ---Inicializar:
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
void Scenographer::initObjects() {
   updateObjects();
}

// ---Actualizar:
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
                           ->getVertexFloor(MAP_WIDTH * MAP_HEIGHT * NUM_VER_POINT);
   float* vertexFloorColor = const_cast<Scene*>(refScene_)
                                ->getVertexFloorColor(MAP_WIDTH * MAP_HEIGHT
                                		* NUM_VER_POINT);
   float* color = new float[3];
   color[0] = 0;
   color[1] = 0;
   color[2] = 0;
   BYTE slot;

   const_cast<Scene*> (refScene_)->setNumberVertex(0);
   const_cast<Scene*> (refScene_)->setNumberQuadsFloor(0);

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
               color[2] = 0.0;

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
               color[2] = 0.0;

               createSideUpFloor(i, j, 0.5, color, vertexFloor, vertexFloorColor);
               createSideFloor(i, j, 0.5, color, vertexFloor, vertexFloorColor, 1);
               createSideFloor(i, j, 0.5, color, vertexFloor, vertexFloorColor, 2);
               createSideFloor(i, j, 0.5, color, vertexFloor, vertexFloorColor, 3);
               createSideFloor(i, j, 0.5, color, vertexFloor, vertexFloorColor, 4);
               break;
            case TERRAIN_WATER:
               color[0] = 0.0;
               color[1] = 0.0;
               color[2] = 1.0;

               createSideUpFloor(i, j, - 0.2, color, vertexFloor, vertexFloorColor);
               createSideFloor(i, j, - 0.2, color, vertexFloor, vertexFloorColor, 1);
               createSideFloor(i, j, - 0.2, color, vertexFloor, vertexFloorColor, 2);
               createSideFloor(i, j, - 0.2, color, vertexFloor, vertexFloorColor, 3);
               createSideFloor(i, j, - 0.2, color, vertexFloor, vertexFloorColor, 4);
               break;
            default:
               color[0] = 0.0;
               color[1] = 1.0;
               color[2] = 0.0;

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
void Scenographer::updateObjects() {
   float* vertexPos = const_cast<float*>(const_cast<Scene*>(refScene_)->getVertexFloor());
   float* vertexColor = const_cast<float*>(const_cast<Scene*>(refScene_)
                           ->getVertexFloorColor());
   createMainAgent(50, 50, 0.1, vertexPos, vertexColor);
   createSearchAgent(51, 51, 0.01, vertexPos, vertexColor);
   createWorkingAgent(49, 49, 0.01, vertexPos, vertexColor);
}

// ---Crear:
void Scenographer::createSideUpFloor(int row, int col, float height, float color[3], float* vertexFloor, float* vertexFloorColor) {
   const int NUM_VER = (const_cast<Scene*> (refScene_)->getNumberVertex()) * 3;
   const int NUM_QUADS = const_cast<Scene*> (refScene_)->getNumberQuadsFloor();

   // Eje X
   vertexFloor[NUM_VER] = (row - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
   vertexFloor[NUM_VER + 3] = ((row + 1) - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
   vertexFloor[NUM_VER + 6] = ((row + 1) - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
   vertexFloor[NUM_VER + 9] = (row - (MAP_HEIGHT / 2.0)) * MAP_SCALE;

   // Eje Y
   vertexFloor[NUM_VER + 1] = height * MAP_UP_SCALE;
   vertexFloor[NUM_VER + 4] = height * MAP_UP_SCALE;
   vertexFloor[NUM_VER + 7] = height * MAP_UP_SCALE;
   vertexFloor[NUM_VER + 10] = height * MAP_UP_SCALE;

	// Eje Z
   vertexFloor[NUM_VER + 2] = (col - (MAP_WIDTH / 2.0)) * MAP_SCALE;
   vertexFloor[NUM_VER + 5] = (col - (MAP_WIDTH / 2.0)) * MAP_SCALE;
   vertexFloor[NUM_VER + 8] = ((col + 1) - (MAP_WIDTH / 2.0)) * MAP_SCALE;
   vertexFloor[NUM_VER + 11] = ((col + 1) - (MAP_WIDTH / 2.0)) * MAP_SCALE;

   vertexFloorColor[NUM_VER] = color[0];
   vertexFloorColor[NUM_VER + 1] = color[1];
   vertexFloorColor[NUM_VER + 2] = color[2];

   vertexFloorColor[NUM_VER + 3] = color[0];
   vertexFloorColor[NUM_VER + 4] = color[1];
   vertexFloorColor[NUM_VER + 5] = color[2];

   vertexFloorColor[NUM_VER + 6] = color[0];
   vertexFloorColor[NUM_VER + 7] = color[1];
   vertexFloorColor[NUM_VER + 8] = color[2];

   vertexFloorColor[NUM_VER + 9] = color[0];
   vertexFloorColor[NUM_VER + 10] = color[1];
   vertexFloorColor[NUM_VER + 11] = color[2];

   const_cast<Scene*> (refScene_)->setNumberVertex((NUM_VER / 3) + 4);
   const_cast<Scene*> (refScene_)->setNumberQuadsFloor(NUM_QUADS + 1);
}
void Scenographer::createSideFloor(int row, int col, float height, float color[3], float* vertexFloor, float* vertexFloorColor, int side) {
   const int NUM_VER = (const_cast<Scene*> (refScene_)->getNumberVertex()) * 3;
   const int NUM_QUADS = const_cast<Scene*> (refScene_)->getNumberQuadsFloor();
   bool paintQuad = false;
   float heightDown = -1;

   switch (side) {
      case 1:
         if (row == 0) {
            paintQuad = true;
         } else if (checkHeightNorth(row, col)) {
            paintQuad = true;
            heightDown = getHeight(row - 1, col);
         }
         break;
      case 2:
         if (col == 0) {
            paintQuad = true;
         } else if (checkHeightWest(row, col)) {
            paintQuad = true;
            heightDown = getHeight(row, col - 1);
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
      case 4:
         if (col == (MAP_WIDTH - 1)) {
            paintQuad = true;
         } else if (checkHeightEast(row, col)) {
            paintQuad = true;
            heightDown = getHeight(row, col + 1);
         }
         break;
      default:
         break;
   }

   if (paintQuad) {
      // Eje X
      if (side == 2 || side == 4) {
         vertexFloor[NUM_VER] = (row - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 3] = ((row + 1) - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 6] = ((row + 1) - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 9] = (row - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
      } else if (side == 1) {
         vertexFloor[NUM_VER] = (row - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 3] = (row - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 6] = (row - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 9] = (row - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
      } else if (side == 3) {
         vertexFloor[NUM_VER] = ((row + 1) - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 3] = ((row + 1) - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 6] = ((row + 1) - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 9] = ((row + 1) - (MAP_HEIGHT / 2.0)) * MAP_SCALE;
      }

      // Eje Y
      if (side == 1 || side == 3) {
         vertexFloor[NUM_VER + 1] = height * MAP_UP_SCALE;
         vertexFloor[NUM_VER + 4] = heightDown * MAP_UP_SCALE;
         vertexFloor[NUM_VER + 7] = heightDown * MAP_UP_SCALE;
         vertexFloor[NUM_VER + 10] = height * MAP_UP_SCALE;
      } else if (side == 2) {
         vertexFloor[NUM_VER + 1] = heightDown * MAP_UP_SCALE;
         vertexFloor[NUM_VER + 4] = heightDown * MAP_UP_SCALE;
         vertexFloor[NUM_VER + 7] = height * MAP_UP_SCALE;
         vertexFloor[NUM_VER + 10] = height * MAP_UP_SCALE;
      } else if (side == 4) {
         vertexFloor[NUM_VER + 1] = height * MAP_UP_SCALE;
         vertexFloor[NUM_VER + 4] = height * MAP_UP_SCALE;
         vertexFloor[NUM_VER + 7] = heightDown * MAP_UP_SCALE;
         vertexFloor[NUM_VER + 10] = heightDown * MAP_UP_SCALE;
      }

      // Eje Z
      if (side == 3) {
         vertexFloor[NUM_VER + 2] = (col - (MAP_WIDTH / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 5] = (col - (MAP_WIDTH / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 8] = ((col + 1) - (MAP_WIDTH / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 11] = ((col + 1) - (MAP_WIDTH / 2.0)) * MAP_SCALE;
      }  else if (side == 1) {
         vertexFloor[NUM_VER + 2] = ((col + 1) - (MAP_WIDTH / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 5] = ((col + 1) - (MAP_WIDTH / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 8] = (col - (MAP_WIDTH / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 11] = (col - (MAP_WIDTH / 2.0)) * MAP_SCALE;
      } else if (side == 2) {
         vertexFloor[NUM_VER + 2] = (col - (MAP_WIDTH / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 5] = (col - (MAP_WIDTH / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 8] = (col - (MAP_WIDTH / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 11] = (col - (MAP_WIDTH / 2.0)) * MAP_SCALE;
      } else if (side == 4) {
         vertexFloor[NUM_VER + 2] = ((col + 1) - (MAP_WIDTH / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 5] = ((col + 1) - (MAP_WIDTH / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 8] = ((col + 1) - (MAP_WIDTH / 2.0)) * MAP_SCALE;
         vertexFloor[NUM_VER + 11] = ((col + 1) - (MAP_WIDTH / 2.0)) * MAP_SCALE;
      }

      vertexFloorColor[NUM_VER] = color[0] / 2;
      vertexFloorColor[NUM_VER + 1] = color[1] / 2;
      vertexFloorColor[NUM_VER + 2] = color[2] / 2;

      vertexFloorColor[NUM_VER + 3] = color[0] / 2;
      vertexFloorColor[NUM_VER + 4] = color[1] / 2;
      vertexFloorColor[NUM_VER + 5] = color[2] / 2;

      vertexFloorColor[NUM_VER + 6] = color[0] / 2;
      vertexFloorColor[NUM_VER + 7] = color[1] / 2;
      vertexFloorColor[NUM_VER + 8] = color[2] / 2;

      vertexFloorColor[NUM_VER + 9] = color[0] / 2;
      vertexFloorColor[NUM_VER + 10] = color[1] / 2;
      vertexFloorColor[NUM_VER + 11] = color[2] / 2;

      const_cast<Scene*> (refScene_)->setNumberVertex((NUM_VER / 3) + 4);
      const_cast<Scene*> (refScene_)->setNumberQuadsFloor(NUM_QUADS + 1);
   }
}
void Scenographer::createMainAgent(int row, int col, float height, float* vertexPos,
      float* vertexColor) {
   const int NUM_VER = (const_cast<Scene*> (refScene_)->getNumberVertex());
   const int NUM_QUADS = const_cast<Scene*> (refScene_)->getNumberQuadsFloor();
   float centralPosX = ((row - (MAP_HEIGHT / 2.0)) * MAP_SCALE) + (MAP_SCALE / 2.0);
   float centralPosY = height * MAP_UP_SCALE;
   float centralPosZ = ((col - (MAP_WIDTH / 2.0)) * MAP_SCALE) + (MAP_SCALE / 2.0);
   // Triangulo 1 (Inf.)
   // ---Eje X
   vertexPos[(NUM_QUADS * 4 * 3)] = centralPosX;
   vertexPos[(NUM_QUADS * 4 * 3) + 3] = centralPosX + (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 6] = centralPosX - (1 * MAIN_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS * 4 * 3) + 1] = centralPosY;
   vertexPos[(NUM_QUADS * 4 * 3) + 4] = centralPosY + (3 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 7] = centralPosY + (3 * MAIN_AGENT_SCALE);
   // ---Eje Z
   vertexPos[(NUM_QUADS * 4 * 3) + 2] = centralPosZ;
   vertexPos[(NUM_QUADS * 4 * 3) + 5] = centralPosZ - (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 8] = centralPosZ - (1 * MAIN_AGENT_SCALE);

   // Triangulo 2
   // ---Eje X
   vertexPos[(NUM_QUADS * 4 * 3) + 9] = centralPosX;
   vertexPos[(NUM_QUADS * 4 * 3) + 12] = centralPosX + (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 15] = centralPosX + (1 * MAIN_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS * 4 * 3) + 10] = centralPosY;
   vertexPos[(NUM_QUADS * 4 * 3) + 13] = centralPosY + (3 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 16] = centralPosY + (3 * MAIN_AGENT_SCALE);
   // ---Eje Z
   vertexPos[(NUM_QUADS * 4 * 3) + 11] = centralPosZ;
   vertexPos[(NUM_QUADS * 4 * 3) + 14] = centralPosZ + (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 17] = centralPosZ - (1 * MAIN_AGENT_SCALE);

   // Triangulo 3
   // ---Eje X
   vertexPos[(NUM_QUADS * 4 * 3) + 18] = centralPosX;
   vertexPos[(NUM_QUADS * 4 * 3) + 21] = centralPosX - (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 24] = centralPosX + (1 * MAIN_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS * 4 * 3) + 19] = centralPosY;
   vertexPos[(NUM_QUADS * 4 * 3) + 22] = centralPosY + (3 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 25] = centralPosY + (3 * MAIN_AGENT_SCALE);
   // ---Eje Z
   vertexPos[(NUM_QUADS * 4 * 3) + 20] = centralPosZ;
   vertexPos[(NUM_QUADS * 4 * 3) + 23] = centralPosZ + (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 26] = centralPosZ + (1 * MAIN_AGENT_SCALE);

   // Triangulo 4
   // ---Eje X
   vertexPos[(NUM_QUADS * 4 * 3) + 27] = centralPosX;
   vertexPos[(NUM_QUADS * 4 * 3) + 30] = centralPosX - (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 33] = centralPosX - (1 * MAIN_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS * 4 * 3) + 28] = centralPosY;
   vertexPos[(NUM_QUADS * 4 * 3) + 31] = centralPosY + (3 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 34] = centralPosY + (3 * MAIN_AGENT_SCALE);
   // ---Eje Z
   vertexPos[(NUM_QUADS * 4 * 3) + 29] = centralPosZ;
   vertexPos[(NUM_QUADS * 4 * 3) + 32] = centralPosZ - (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 35] = centralPosZ + (1 * MAIN_AGENT_SCALE);

   //-----------------
   // Triangulo 1 (Sup.)
   // ---Eje X
   vertexPos[(NUM_QUADS * 4 * 3) + 36] = centralPosX;
   vertexPos[(NUM_QUADS * 4 * 3) + 3 + 36] = centralPosX - (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 6 + 36] = centralPosX + (1 * MAIN_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS * 4 * 3) + 1 + 36] = centralPosY + (6 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 4 + 36] = centralPosY + (3 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 7 + 36] = centralPosY + (3 * MAIN_AGENT_SCALE);
   // ---Eje Z
   vertexPos[(NUM_QUADS * 4 * 3) + 2 + 36] = centralPosZ;
   vertexPos[(NUM_QUADS * 4 * 3) + 5 + 36] = centralPosZ - (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 8 + 36] = centralPosZ - (1 * MAIN_AGENT_SCALE);

   // Triangulo 2 (Sup.)
   // ---Eje X
   vertexPos[(NUM_QUADS * 4 * 3) + 9 + 36] = centralPosX;
   vertexPos[(NUM_QUADS * 4 * 3) + 12 + 36] = centralPosX + (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 15 + 36] = centralPosX + (1 * MAIN_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS * 4 * 3) + 10 + 36] = centralPosY + (6 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 13 + 36] = centralPosY + (3 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 16 + 36] = centralPosY + (3 * MAIN_AGENT_SCALE);
   // ---Eje Z
   vertexPos[(NUM_QUADS * 4 * 3) + 11 + 36] = centralPosZ;
   vertexPos[(NUM_QUADS * 4 * 3) + 14 + 36] = centralPosZ - (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 17 + 36] = centralPosZ + (1 * MAIN_AGENT_SCALE);

   // Triangulo 3 (Sup.)
   // ---Eje X
   vertexPos[(NUM_QUADS * 4 * 3) + 18 + 36] = centralPosX;
   vertexPos[(NUM_QUADS * 4 * 3) + 21 + 36] = centralPosX + (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 24 + 36] = centralPosX - (1 * MAIN_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS * 4 * 3) + 19 + 36] = centralPosY + (6 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 22 + 36] = centralPosY + (3 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 25 + 36] = centralPosY + (3 * MAIN_AGENT_SCALE);
   // ---Eje Z
   vertexPos[(NUM_QUADS * 4 * 3) + 20 + 36] = centralPosZ;
   vertexPos[(NUM_QUADS * 4 * 3) + 23 + 36] = centralPosZ + (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 26 + 36] = centralPosZ + (1 * MAIN_AGENT_SCALE);

   // Triangulo 4 (Sup.)
   // ---Eje X
   vertexPos[(NUM_QUADS * 4 * 3) + 27 + 36] = centralPosX;
   vertexPos[(NUM_QUADS * 4 * 3) + 30 + 36] = centralPosX - (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 33 + 36] = centralPosX - (1 * MAIN_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS * 4 * 3) + 28 + 36] = centralPosY + (6 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 31 + 36] = centralPosY + (3 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 34 + 36] = centralPosY + (3 * MAIN_AGENT_SCALE);
   // ---Eje Z
   vertexPos[(NUM_QUADS * 4 * 3) + 29 + 36] = centralPosZ;
   vertexPos[(NUM_QUADS * 4 * 3) + 32 + 36] = centralPosZ + (1 * MAIN_AGENT_SCALE);
   vertexPos[(NUM_QUADS * 4 * 3) + 35 + 36] = centralPosZ - (1 * MAIN_AGENT_SCALE);


   // Colores de los vértices RGB (Inf.)
   vertexColor[(NUM_QUADS * 4 * 3)] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 1] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 2] = 1;

   vertexColor[(NUM_QUADS * 4 * 3) + 3] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 4] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 5] = 0;

   vertexColor[(NUM_QUADS * 4 * 3) + 6] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 7] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 8] = 0;

   vertexColor[(NUM_QUADS * 4 * 3) + 9] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 10] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 11] = 1;

   vertexColor[(NUM_QUADS * 4 * 3) + 12] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 13] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 14] = 0;

   vertexColor[(NUM_QUADS * 4 * 3) + 15] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 16] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 17] = 0;

   vertexColor[(NUM_QUADS * 4 * 3) + 18] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 19] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 20] = 1;

   vertexColor[(NUM_QUADS * 4 * 3) + 21] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 22] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 23] = 0;

   vertexColor[(NUM_QUADS * 4 * 3) + 24] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 25] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 26] = 0;

   vertexColor[(NUM_QUADS * 4 * 3) + 27] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 28] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 29] = 1;

   vertexColor[(NUM_QUADS * 4 * 3) + 30] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 31] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 32] = 0;

   vertexColor[(NUM_QUADS * 4 * 3) + 33] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 34] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 35] = 0;

   //----
   // Colores de los vértices RGB (Inf.)
   vertexColor[(NUM_QUADS * 4 * 3) + 36] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 1 + 36] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 2 + 36] = 1;

   vertexColor[(NUM_QUADS * 4 * 3) + 3 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 4 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 5 + 36] = 0;

   vertexColor[(NUM_QUADS * 4 * 3) + 6 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 7 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 8 + 36] = 0;

   vertexColor[(NUM_QUADS * 4 * 3) + 9 + 36] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 10 + 36] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 11 + 36] = 1;

   vertexColor[(NUM_QUADS * 4 * 3) + 12 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 13 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 14 + 36] = 0;

   vertexColor[(NUM_QUADS * 4 * 3) + 15 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 16 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 17 + 36] = 0;

   vertexColor[(NUM_QUADS * 4 * 3) + 18 + 36] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 19 + 36] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 20 + 36] = 1;

   vertexColor[(NUM_QUADS * 4 * 3) + 21 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 22 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 23 + 36] = 0;

   vertexColor[(NUM_QUADS * 4 * 3) + 24 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 25 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 26 + 36] = 0;

   vertexColor[(NUM_QUADS * 4 * 3) + 27 + 36] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 28 + 36] = 1;
   vertexColor[(NUM_QUADS * 4 * 3) + 29 + 36] = 1;

   vertexColor[(NUM_QUADS * 4 * 3) + 30 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 31 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 32 + 36] = 0;

   vertexColor[(NUM_QUADS * 4 * 3) + 33 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 34 + 36] = 0;
   vertexColor[(NUM_QUADS * 4 * 3) + 35 + 36] = 0;

   const_cast<Scene*> (refScene_)->setNumberVertex(NUM_VER + (12 * 2));
}
void Scenographer::createSearchAgent(int row, int col, float height,
      float* vertexPos, float* vertexColor) {
   const int NUM_VER = (const_cast<Scene*> (refScene_)->getNumberVertex());
   const int NUM_QUADS = (const_cast<Scene*> (refScene_)->getNumberQuadsFloor()) * 4 * 3;
   const int NUM_VER_MAIN = 24 *  3;
   float centralPosX = ((row - (MAP_HEIGHT / 2.0)) * MAP_SCALE) + (MAP_SCALE / 2.0);
   float centralPosY = height * MAP_UP_SCALE;
   float centralPosZ = ((col - (MAP_WIDTH / 2.0)) * MAP_SCALE) + (MAP_SCALE / 2.0);

   //-----------------
   // Triangulo 1 (Sup.)
   // ---Eje X
   vertexPos[(NUM_QUADS + NUM_VER_MAIN)] = centralPosX;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 3] = centralPosX - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 6] = centralPosX + (1 * SECOND_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 1] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 4] = centralPosY;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 7] = centralPosY;
   // ---Eje Z
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 2] = centralPosZ;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 5] = centralPosZ - (1  * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 8] = centralPosZ - (1 * SECOND_AGENT_SCALE);

   // Triangulo 2 (Sup.)
   // ---Eje X
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 9] = centralPosX;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 12] = centralPosX + (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 15] = centralPosX + (1 * SECOND_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 10] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 13] = centralPosY;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 16] = centralPosY;
   // ---Eje Z
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 11] = centralPosZ;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 14] = centralPosZ - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 17] = centralPosZ + (1 * SECOND_AGENT_SCALE);

   // Triangulo 3 (Sup.)
   // ---Eje X
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 18] = centralPosX;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 21] = centralPosX + (1  * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 24] = centralPosX - (1  * SECOND_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 19] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 22] = centralPosY;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 25] = centralPosY;
   // ---Eje Z
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 20] = centralPosZ;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 23] = centralPosZ + (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 26] = centralPosZ + (1 * SECOND_AGENT_SCALE);

   // Triangulo 4 (Sup.)
   // ---Eje X
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 27] = centralPosX;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 30] = centralPosX - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 33] = centralPosX - (1 * SECOND_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 28] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 31] = centralPosY;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 34] = centralPosY;
   // ---Eje Z
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 29] = centralPosZ;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 32] = centralPosZ + (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN) + 35] = centralPosZ - (1 * SECOND_AGENT_SCALE);

   // Colores de los vértices RGB (Inf.)
   vertexColor[(NUM_QUADS + NUM_VER_MAIN)] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 1] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 2] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 3] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 4] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 5] = 0;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 6] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 7] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 8] = 0;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 9] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 10] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 11] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 12] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 13] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 14] = 0;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 15] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 16] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 17] = 0;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 18] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 19] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 20] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 21] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 22] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 23] = 0;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 24] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 25] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 26] = 0;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 27] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 28] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 29] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 30] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 31] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 32] = 0;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 33] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 34] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN) + 35] = 0;

   const_cast<Scene*> (refScene_)->setNumberVertex(NUM_VER + 12);

}
void Scenographer::createWorkingAgent(int row, int col, float height,
      float* vertexPos, float* vertexColor) {
   const int NUM_VER = (const_cast<Scene*> (refScene_)->getNumberVertex());
   const int NUM_QUADS = (const_cast<Scene*> (refScene_)->getNumberQuadsFloor()) * 4 * 3;
   const int NUM_VER_MAIN_SEARCH = (24 * 3) + (12 * 3);
   float centralPosX = ((row - (MAP_HEIGHT / 2.0)) * MAP_SCALE) + (MAP_SCALE / 2.0);
   float centralPosY = height * MAP_UP_SCALE;
   float centralPosZ = ((col - (MAP_WIDTH / 2.0)) * MAP_SCALE) + (MAP_SCALE / 2.0);

   //-----------------
   // Cuadrado 0 (Sup.)
   // ---Eje X
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH)] = centralPosX + (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 3] = centralPosX - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 6] = centralPosX - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 9] = centralPosX + (1 * SECOND_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 1] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 4] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 7] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 10] = centralPosY + (2 * SECOND_AGENT_SCALE);
   // ---Eje Z
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 2] = centralPosZ + (1  * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 5] = centralPosZ + (1  * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 8] = centralPosZ - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 11] = centralPosZ - (1  * SECOND_AGENT_SCALE);


   // Cuadrado 1 (Oeste)
   // ---Eje X
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 12] = centralPosX - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 15] = centralPosX - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 18] = centralPosX - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 21] = centralPosX - (1 * SECOND_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 13] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 16] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 19] = centralPosY;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 22] = centralPosY;
   // ---Eje Z
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 14] = centralPosZ - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 17] = centralPosZ + (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 20] = centralPosZ + (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 23] = centralPosZ - (1 * SECOND_AGENT_SCALE);

   // Cuadrado 2 (Norte)
   // ---Eje X
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 24] = centralPosX + (1  * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 27] = centralPosX - (1  * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 30] = centralPosX - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 33] = centralPosX + (1 * SECOND_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 25] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 28] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 31] = centralPosY;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 34] = centralPosY;
   // ---Eje Z
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 26] = centralPosZ - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 29] = centralPosZ - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 32] = centralPosZ - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 35] = centralPosZ - (1 * SECOND_AGENT_SCALE);

   // Cuadrado 3 (Este)
   // ---Eje X
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 36] = centralPosX + (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 39] = centralPosX + (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 42] = centralPosX + (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 45] = centralPosX + (1 * SECOND_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 37] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 40] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 43] = centralPosY;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 46] = centralPosY;
   // ---Eje Z
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 38] = centralPosZ + (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 41] = centralPosZ - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 44] = centralPosZ - (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 47] = centralPosZ + (1 * SECOND_AGENT_SCALE);

   // Cuadrado 4 (Sur)
   // ---Eje X
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 48] = centralPosX - (1  * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 51] = centralPosX + (1  * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 54] = centralPosX + (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 57] = centralPosX - (1 * SECOND_AGENT_SCALE);
   // ---Eje Y
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 49] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 52] = centralPosY + (2 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 55] = centralPosY;
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 58] = centralPosY;
   // ---Eje Z
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 50] = centralPosZ + (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 53] = centralPosZ + (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 56] = centralPosZ + (1 * SECOND_AGENT_SCALE);
   vertexPos[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 59] = centralPosZ + (1 * SECOND_AGENT_SCALE);

   // Colores de los vértices RGB
   // Cuadrado 0 (Sup.)
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH)] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 1] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 2] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 3] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 4] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 5] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 6] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 7] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 8] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 9] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 10] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 11] = 1;

   // Cuadrado 1 (Oeste)
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 12] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 13] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 14] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 15] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 16] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 17] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 18] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 19] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 20] = 0;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 21] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 22] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 23] = 0;

   // Cuadrado 2 (Norte)
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 24] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 25] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 26] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 27] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 28] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 29] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 30] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 31] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 32] = 0;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 33] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 34] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 35] = 0;

   // Cuadrado 3 (Este)
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 36] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 37] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 38] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 39] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 40] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 41] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 42] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 43] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 44] = 0;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 45] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 46] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 47] = 0;

   // Cuadrado 4 (Sur)
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 48] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 49] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 50] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 51] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 52] = 1;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 53] = 1;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 54] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 55] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 56] = 0;

   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 57] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 58] = 0;
   vertexColor[(NUM_QUADS + NUM_VER_MAIN_SEARCH) + 59] = 0;

   const_cast<Scene*> (refScene_)->setNumberVertex(NUM_VER + (4 * 5));
}
// ---Comprobar:
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

// ---Auxiliar:
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

// ---LOG:
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

