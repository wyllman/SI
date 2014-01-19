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
   refKnownMap_ = NULL;
   showVisibleMask_ = false;
   updateColor_ = false;
   logAction(LOG_INIT);
}
Scenographer::~Scenographer() {
   logAction(LOG_END);
   clearAgents();
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

   needUpdateObjects_ = true;
   needUpdateFloor_ = true;

   initProy(45.0, WIN_WIDTH / WIN_HEIGHT, 1, 1000);
   initCam(camPos, viewPoint, vectorUp);
   initFloor();
   initObjects();
}
void Scenographer::update() {
   if (needUpdateFloor_) {
      updateFloor();
      if (updateColor_) {
         updateColorFloor();
      }
      updateObjects();
   } else if (needUpdateObjects_) {
      if (updateColor_) {
         updateColorFloor();
      }
      updateObjects();
   }

}
// --- Métedos específicos para el control de la cámara desde el controlador
void Scenographer::projZoom(float value) {
   projAng_ += value;
   updateProy();
}
void Scenographer::camPosX(float value) {
   camPos_[0] += value;
   camViewPoint_[0] += value;
   updateCam();
}
void Scenographer::camPosZ(float value) {
   camPos_[2] += value;
   camViewPoint_[2] += value;
   updateCam();
}
void Scenographer::camRotationPos(float value) {
   camRotAngle_ += value;
   updateCam();
}

void Scenographer::showHideMask() {
   if (showVisibleMask_) {
      showVisibleMask_ = false;
   } else {
      showVisibleMask_ = true;
   }
}
void Scenographer::updatedColor() {
   updateColor_ = true;
}

// --- Métodos específicos para el control de la representación de
//     los agentes y el terreno desde el controlador.
void Scenographer::setMainAgentPos(float* pos) {
   mainAgentPos_[0] = pos[0];
   mainAgentPos_[1] = pos[1];
   mainAgentPos_[2] = pos[2];

   needUpdateObjects_ = true;
}
void Scenographer::clearAgents() {
   if (!searchAgentVector_.empty()) {
      for (int i = 0; i < searchAgentVector_.size(); i++) {
         delete [] (searchAgentVector_[i]);
      }
      searchAgentVector_.clear();
   }
   if (!workingAgentVector_.empty()) {
      for (int i = 0; i < workingAgentVector_.size(); i++) {
         delete [] (workingAgentVector_[i]);
      }
      workingAgentVector_.clear();
   }
   needUpdateObjects_ = true;
}
void Scenographer::addSearchAgent(float* pos) {
   float* posAgent = new float[3];

   posAgent[0] = pos[0];
   posAgent[1] = pos[1];
   posAgent[2] = pos[2];

   searchAgentVector_.push_back(posAgent);
   needUpdateObjects_ = true;
}
void Scenographer::addWorkingAgent(float* pos) {
   float* posAgent = new float[3];

   posAgent[0] = pos[0];
   posAgent[1] = pos[1];
   posAgent[2] = pos[2];

   workingAgentVector_.push_back(posAgent);
   needUpdateObjects_ = true;
}
void Scenographer::requireUpdateFloor() {
   needUpdateFloor_ = true;
   needUpdateObjects_ = true;
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Manejadores públicos:
float* Scenographer::getcolor(int row, int col) {
   // TODO:
   return getcolor((*refMap_)(row, col));
}
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
   updateFloor();
}
void Scenographer::initObjects() {
   mainAgentPos_ [0] = 50.0;
   mainAgentPos_ [1] = 0.1;
   mainAgentPos_ [2] = 50.0;
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

   camPos_[0] += camViewPoint_[0];
   camPos_[2] += camViewPoint_[2];

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(camPos_[0], camPos_[1], camPos_[2]
            , camViewPoint_[0], camViewPoint_[1], camViewPoint_[2]
            , camVectorUp_[0], camVectorUp_[1], camVectorUp_[2]);

   glGetFloatv(GL_MODELVIEW_MATRIX, const_cast<Scene*>(refScene_)->getModelviewMatrix());
   glMatrixMode(0);
}
void Scenographer::updateFloor() {
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
               color[0] = 0.0;
               color[1] = 1.0;
               color[2] = 0.0;

               if (slot == TERRAIN_GROUND) {
                  createSlotFloor(i, j, 0.0, color);
               } else {
                  float* colorRes = getcolor(slot & MASK_RESOURCE);
                  createSlotFloor(i, j, 0.0, color, colorRes);
                  delete [] (colorRes);
               }
               break;
            case TERRAIN_ELEVATION:
               color[0] = 0.0;
               color[1] = 0.5;
               color[2] = 0.0;

               createSlotFloor(i, j, 0.5, color);
               break;
            case TERRAIN_WATER:
               color[0] = 0.0;
               color[1] = 0.0;
               color[2] = 1.0;

               createSlotFloor(i, j, - 0.2, color);
               break;
            default:
               color[0] = 0.0;
               color[1] = 1.0;
               color[2] = 0.0;

               createSlotFloor(i, j, - 0.01, color);
               break;
         }
      }
   }
   delete [] (color);
   needUpdateFloor_ = false;
}
void Scenographer::updateColorFloor() {
   const_cast<Scene*> (refScene_)->updateColor(showVisibleMask_, refKnownMap_);
   updateColor_ = false;
}
void Scenographer::setMask(bool** mask) {
   refKnownMap_ = mask;
}
void Scenographer::updateObjects() {
   const int NUM_QUADS = const_cast<Scene*> (refScene_)->getNumberQuadsFloor();
   const_cast<Scene*> (refScene_)->setNumberVertex (NUM_QUADS * 4);
   const_cast<Scene*> (refScene_)->setNumberTriangMainA (0);
   const_cast<Scene*> (refScene_)->setNumberTriangSearchA (0);
   const_cast<Scene*> (refScene_)->setNumberQuadsWorkingA (0);

   createMainAgent(mainAgentPos_[2], mainAgentPos_[0], mainAgentPos_[1]);
   if (!searchAgentVector_.empty()) {
      for (int i = 0; i < searchAgentVector_.size(); i++) {
         createSearchAgent(searchAgentVector_[i][2] , searchAgentVector_[i][0], searchAgentVector_[i][1]);
      }
   } else {
      createSearchAgent(51, 51, 0.01);
   }
   if (!workingAgentVector_.empty()) {
      for (int i = 0; i < workingAgentVector_.size(); i++) {
         createWorkingAgent(workingAgentVector_[i][2] , workingAgentVector_[i][0], workingAgentVector_[i][1]);
      }
   } else {
      createWorkingAgent(49, 49, 0.01);
   }
   needUpdateObjects_ = false;
}

// ---Crear:
void Scenographer::createSlotFloor(int row, int col, float height, float color[3]) {
   createSlotFloor(row, col, height, color, color);
}
void Scenographer::createSlotFloor(int row, int col, float height, float color[3], float colorRes[3]) {
   int numVer = (const_cast<Scene*> (refScene_)->getNumberVertex()) * 3;
   int numQuads = const_cast<Scene*> (refScene_)->getNumberQuadsFloor();
   float pos[3] = {col, height, row};
   bool paintQuad;
   float heightDown;

   const_cast<Scene*>(refScene_)->createUpQuads(pos, colorRes, MAP_SCALE, numVer);
   numVer += 4 * 3;
   ++numQuads;
   color[0] = color[0] / 2;
   color[1] = color[1] / 2;
   color[2] = color[2] / 2;

   for (int side = 1; side < 5; side++) {
      paintQuad = false;
      heightDown = -1;
      switch (side) {
         case 1:
            if (col == 0) {
               paintQuad = true;
            } else if (checkHeightWest(row, col)) {
               paintQuad = true;
               heightDown = getHeight(row, col - 1);
            }
            break;
         case 2:
            if (row == 0) {
               paintQuad = true;
            } else if (checkHeightNorth(row, col)) {
               paintQuad = true;
               heightDown = getHeight(row - 1, col);
            }
            break;
         case 3:
            if (col == (MAP_WIDTH - 1)) {
               paintQuad = true;
            } else if (checkHeightEast(row, col)) {
               paintQuad = true;
            heightDown = getHeight(row, col + 1);
            }
            break;
         case 4:
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
      if(paintQuad){
         const_cast<Scene*>(refScene_)->createSideQuads(pos, heightDown * MAP_UP_SCALE, color, MAP_SCALE, numVer, side);
         numVer += 4 * 3;
         ++numQuads;
      }
   }
   const_cast<Scene*> (refScene_)->setNumberVertex(numVer / 3);
   const_cast<Scene*> (refScene_)->setNumberQuadsFloor(numQuads);
}
void Scenographer::createMainAgent(int row, int col, float height) {
   const int NUM_VER = (const_cast<Scene*> (refScene_)->getNumberVertex());
   const int NUM_QUADS = const_cast<Scene*> (refScene_)->getNumberQuadsFloor();
   int numVer = NUM_QUADS * 4 * 3;
   float pos[3] = {col, ((height * MAP_UP_SCALE) + (1.0 * MAIN_AGENT_SCALE)) / MAP_UP_SCALE, row};
   float color[3] = {0.25, 0.12, 0.0};
   float color2[3] = {1.0, 1.0, 1.0};

   const_cast<Scene*>(refScene_)->createSideTriangle(pos, 0.75, color2, color, MAIN_AGENT_SCALE, numVer, 1);
   const_cast<Scene*>(refScene_)->createSideTriangle(pos, 0.75, color2, color, MAIN_AGENT_SCALE, numVer + (3 * 3), 2);
   const_cast<Scene*>(refScene_)->createSideTriangle(pos, 0.75, color2, color, MAIN_AGENT_SCALE, numVer + (6 * 3), 3);
   const_cast<Scene*>(refScene_)->createSideTriangle(pos, 0.75, color2, color, MAIN_AGENT_SCALE, numVer + (9 * 3), 4);

   const_cast<Scene*>(refScene_)->createSideTriangleInf(pos, 1.25, color2, color, MAIN_AGENT_SCALE, numVer + (12 * 3), 1);
   const_cast<Scene*>(refScene_)->createSideTriangleInf(pos, 1.25, color2, color, MAIN_AGENT_SCALE, numVer + (15 * 3), 2);
   const_cast<Scene*>(refScene_)->createSideTriangleInf(pos, 1.25, color2, color, MAIN_AGENT_SCALE, numVer + (18 * 3), 3);
   const_cast<Scene*>(refScene_)->createSideTriangleInf(pos, 1.25, color2, color, MAIN_AGENT_SCALE, numVer + (21 * 3), 4);

   const_cast<Scene*> (refScene_)->setNumberVertex (NUM_VER + (12 * 2));
   const_cast<Scene*> (refScene_)->setNumberTriangMainA (8);
}
void Scenographer::createSearchAgent(int row, int col, float height) {
   const int NUM_VER = (const_cast<Scene*> (refScene_)->getNumberVertex());
   const int NUM_QUADS = (const_cast<Scene*> (refScene_)->getNumberQuadsFloor()) * 4 * 3;
   const int NUM_VER_MAIN = (const_cast<Scene*> (refScene_)->getNumberTriangMainA()) * 3 * 3;
   const int NUM_VER_SA = (const_cast<Scene*> (refScene_)->getNumberTriangSearchA());
   int numVer = NUM_QUADS + NUM_VER_MAIN + (NUM_VER_SA * 3 * 3);
   float pos[3] = {col, height, row};
   float color[3] = {0.25, 0.12, 0.0};
   float color2[3] = {1.0, 1.0, 1.0};

   const_cast<Scene*>(refScene_)->createSideTriangle(pos, 1.0, color2, color, SECOND_AGENT_SCALE, numVer, 1);
   const_cast<Scene*>(refScene_)->createSideTriangle(pos, 1.0, color2, color, SECOND_AGENT_SCALE, numVer + (3 * 3), 2);
   const_cast<Scene*>(refScene_)->createSideTriangle(pos, 1.0, color2, color, SECOND_AGENT_SCALE, numVer + (6 * 3), 3);
   const_cast<Scene*>(refScene_)->createSideTriangle(pos, 1.0, color2, color, SECOND_AGENT_SCALE, numVer + (9 * 3), 4);

   const_cast<Scene*> (refScene_)->setNumberVertex(NUM_VER + 12);
   const_cast<Scene*> (refScene_)->setNumberTriangSearchA(NUM_VER_SA + 4);
}
void Scenographer::createWorkingAgent(int row, int col, float height) {
   const int NUM_VER = (const_cast<Scene*> (refScene_)->getNumberVertex());
   const int NUM_QUADS = (const_cast<Scene*> (refScene_)->getNumberQuadsFloor()) * 4 * 3;
   const int NUM_VER_MAIN = (const_cast<Scene*> (refScene_)->getNumberTriangMainA()) * 3 * 3;
   const int NUM_VER_SA = (const_cast<Scene*> (refScene_)->getNumberTriangSearchA()) * 3 * 3;
   const int NUM_VER_WA = (const_cast<Scene*> (refScene_)->getNumberQuadsWorkingA());
   const int NUM_VER_MAIN_SEARCH = NUM_VER_MAIN + NUM_VER_SA;
   int numVer = NUM_QUADS + NUM_VER_MAIN_SEARCH + (NUM_VER_WA * 4 * 3);
   float pos[3] = {col, ((height * MAP_UP_SCALE) + (1.0 * SECOND_AGENT_SCALE)) / MAP_UP_SCALE, row};
   float col1[3] = {1.0, 1.0, 1.0};
   float col2[3] = {0.25, 0.12, 0.0};
   float heightTmp = (height * MAP_UP_SCALE) / SECOND_AGENT_SCALE;

   const_cast<Scene*>(refScene_)->createUpQuads(pos, col1, SECOND_AGENT_SCALE, numVer);
   const_cast<Scene*>(refScene_)->createSideQuads(pos, heightTmp, col1, col2, SECOND_AGENT_SCALE, numVer + (4 * 3), 1);
   const_cast<Scene*>(refScene_)->createSideQuads(pos, heightTmp, col1, col2, SECOND_AGENT_SCALE, numVer + (8 * 3), 2);
   const_cast<Scene*>(refScene_)->createSideQuads(pos, heightTmp, col1, col2, SECOND_AGENT_SCALE, numVer + (12 * 3), 3);
   const_cast<Scene*>(refScene_)->createSideQuads(pos, heightTmp, col1, col2, SECOND_AGENT_SCALE, numVer + (16 * 3), 4);

   const_cast<Scene*> (refScene_)->setNumberVertex(NUM_VER + (4 * 5));
   const_cast<Scene*> (refScene_)->setNumberQuadsWorkingA(NUM_VER_WA + 5);
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
         switch (value & MASK_TERRAIN) {
            case TERRAIN_GROUND:
               color[0] = 0.0;
               color[1] = 1.0;
               color[2] = 0.0;
               switch (value & MASK_RESOURCE) {
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
                     break;
               }
               break;
            case TERRAIN_ELEVATION:
               color[0] = 0.0;
               color[1] = 0.5;
               color[2] = 0.0;
               break;
            case TERRAIN_WATER:
               color[0] = 0.0;
               color[1] = 0.0;
               color[2] = 1.0;
               break;
            default:
               color[0] = 1;
               color[1] = 0;
               color[2] = 1;
               break;
         }
         //color[0] = 1;
         //color[1] = 0;
         //color[2] = 1;
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


