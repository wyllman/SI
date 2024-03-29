/*
 *      Nombre: Interface.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.003
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Vista específica para la ejecución del simulador. Lleva el control de la
 *              ejecución y creación de la ventana y el contexto (SDL y OGL). Renderizar
 *              la escena, animar los objetos, etc...
 *
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <view/abstracts/View.h>

class Bureaucrat;
class Scenographer;
class Window;
class Context;
class Scene;

class Interface: public View {
   public:
      Interface(const Controller&);
      virtual ~Interface();

      void init();
      void update();
      void stop();
      void render();

      void log(const char*);
      const Scene* getScene() const;
      const Scenographer* getScenographer() const;

   private:
      Bureaucrat* bureaucrat_;
      Scenographer* scenographer_;

      Window* window_;
      Context* context_;
      Scene* scene_;

      void createFloor(int, int);
      void logAction(int);
};

#endif /* INTERFACE_H_ */
