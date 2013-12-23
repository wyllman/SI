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

      void initProy (float, float, int, int);
      void initCam (float [3], float [3], float [3]);
      void initFloor ();

      void updateProy ();
      void updateCam ();
      void updateFloor (int, int);
      void createSideUpFloor (int, int, float, float [3], float*, float*);
      void createSideFloor (int, int, float, float [3], float*, float*, int);

      bool checkHeightNorth (int, int);
      bool checkHeightEast (int, int);
      bool checkHeightSouth (int, int);
      bool checkHeightWest (int, int);

      float getHeight(int, int);
      float getHeight(BYTE);

      void logAction(int);
};

#endif /* SCENOGRAPHER_H_ */
