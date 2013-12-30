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
      const float* getVertexObjects() const;
      float* getVertexObjects(int);
      const float* getVertexObjectsColor() const;
      float* getVertexObjectsColor(int);
      int getNumberVertex() const;
      void setNumberVertex(int numberVertex);
      int getNumberQuadsFloor() const;
      void setNumberQuadsFloor(int numberQuadsFloor);

   private:
      const Interface* refInterface_;
      GLfloat modelviewMatrix_[16];
      GLfloat projectionMatrix_[16];
      int numberVertex_;  // Número de vertices a pintar.

      int numberQuadsFloor_; // Número de Quads creados al construir el terreno.
      float* vertexFloor_;
      float* vertexFloorColor_;

      float* vertexObjects_;
      float* vertexObjectsColor_;

      void logAction(int);
};

#endif /* SCENE_H_ */
