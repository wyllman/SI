/*
 *      Nombre: Scenographer.h
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

#ifndef SCENOGRAPHER_H_
#define SCENOGRAPHER_H_

#include <Tools.h>
#include <vector.h>

class Interface;
class Scene;
class Map;

class Scenographer {
   public:
      Scenographer(const Interface&, const Scene&, const Map&);
      virtual ~Scenographer();

      void init ();
      void update ();
      void projZoom (float);
      void camPosX (float);
      void camRotationPos (float);
      void setMainAgentPos (float*);
      void clearAgents ();
      void addSearchAgent (float*);
      void addWorkingAgent (float*);

   private:
      const Interface* refInterface_;
      const Scene* refScene_;
      const Map* refMap_;

      float projAng_;
      float projRatio_;
      int projNear_;
      int projFar_;

      float camRotAngle_;
      float camPos_[3];
      float camViewPoint_[3];
      float camVectorUp_[3];

      float mainAgentPos_[3];
      vector<float*> searchAgentVector_;
      vector<float*> workingAgentVector_;

      void initProy (float, float, int, int);
      void initCam (float [3], float [3], float [3]);
      void initFloor ();
      void initObjects ();

      void updateProy ();
      void updateCam ();
      void updateFloor (int, int);
      void updateObjects ();

      // Funciones para la creación de cada uno de las casillas del terreno.
      void createSlotFloor (int, int, float, float [3]);
      void createSlotFloor (int, int, float, float [3], float [3]);

      // Funciones para la creación de los lados de cada uno de los objetos de la
      // escena
      void createMainAgent (int row, int col, float height);
      void createSearchAgent (int row, int col, float height);
      void createWorkingAgent (int row, int col, float height);

      // Funciones para las comprobaciones de alturas, de terreno, en la eliminación
      // de quads internos.
      bool checkHeightNorth (int, int);
      bool checkHeightEast (int, int);
      bool checkHeightSouth (int, int);
      bool checkHeightWest (int, int);

      // Funciones auxiliares para la creación del terreno.
      float getHeight(int, int);
      float getHeight(BYTE);
      float* getcolor(BYTE);

      void logAction(int);
};

#endif /* SCENOGRAPHER_H_ */
