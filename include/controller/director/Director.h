/*
 *      Nombre: Director.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.003
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Controlador específico para la ejecución del simulador. Lleva el control del
 *              tiempo, del bucle principal y el registro de las acciones y errores internos.
 *
 */

#ifndef DIRECTOR_H_
#define DIRECTOR_H_

#include <controller/abstracts/Controller.h>

#ifdef __linux
   #include <SDL2/SDL.h>
#else
   #include <SDL.h>
#endif

class MainLoop;
class FileLog;
class Map;

class Director: public Controller {
   public:
      Director();
      virtual ~Director();

      void init ();
      void start ();
      void stop ();

      FileLog* getRegAccErr();
      const Map* getMap() const;

   private:
      FileLog* regAccErr_;
      MainLoop* mainLoop_;
      int simulatorVel_;

      void getAgentsPos ();
      void mainLoop ();
      void mainFunction ();
      void iddleFunction ();
      void keyEvents (SDL_Event& eventSDL);
      double getSimulatorVel ();

      void logAction (int);

};

#endif /* DIRECTOR_H_ */
