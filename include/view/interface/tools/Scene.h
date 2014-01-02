/*
 *      Nombre: Scene.h
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

#ifndef SCENE_H_
#define SCENE_H_

#ifdef __linux
   #include <GL/glew.h>
#else
   #include <GL.h>
   #include <GLU.h>
#endif

class Interface;

class Scene {
   public:
      Scene(const Interface&);
      virtual ~Scene();

      void updateProy (GLfloat []);
      void updateCam (GLfloat []);
      void updateFloor (float [], int);
      GLfloat* getModelviewMatrix();
      GLfloat* getProjectionMatrix();
      const float* getVertexFloor() const;
      float* getVertexFloor(int);
      const float* getVertexFloorColor() const;
      float* getVertexFloorColor(int);
      int getNumberVertex() const;
      void setNumberVertex(int numberVertex);
      int getNumberQuadsFloor() const;
      void setNumberQuadsFloor(int numberQuadsFloor);


      void createUpQuads (float* position, float* color1, float scale, int memPos);
      void createSideQuads (float* position, float height2, float* color1, float scale
            , int memPos, int side);
      void createSideQuads (float* position, float height2, float* color1, float* color2
            , float scale, int memPos, int side);
      void createSideTriangle (float* position, float height2, float* color1, float* color2
            , float scale, int memPos, int side);
      void createSideTriangleInf (float* position, float height2, float* color1, float* color2
            , float scale, int memPos, int side);

   private:
      const Interface* refInterface_;
      GLfloat modelviewMatrix_[16];
      GLfloat projectionMatrix_[16];

      int numberVertex_;  // Número de vertices a pintar.

      int numberQuadsFloor_; // Número de Quads creados al construir el terreno.
      int numberTriangMainA_;
      int numberTriangSearchA_;
      int numberQuadsWorkingA_;

      float* vertexFloor_;
      float* vertexFloorColor_;



      void logAction(int);
};

#endif /* SCENE_H_ */
