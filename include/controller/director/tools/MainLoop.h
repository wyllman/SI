/*
 *      Nombre: MainLoop.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.003
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de contener y gestionar el bucle principal de ejecución.
 *
 */

#ifndef MAINLOOP_H_
#define MAINLOOP_H_

#include <sys/time.h>

class Director;

class MainLoop {
   public:
      MainLoop(const Director&);
      virtual ~MainLoop();

      void init();
      void pauseResume();
      void update();
      void stopUpdate();
      void render();
      void stopRender();
      void reset();
      void stopReset();
      void stop();

      void initTime ();
      void endTime ();
      double diffTmie ();
      void init2Time ();
      void end2Time ();
      double diff2Time ();

      bool isContinue() const;
      bool isPause() const;
      bool isRequireReset() const;
      bool isRequireUpdate() const;
      bool isRequireRender() const;

   private:
      const Director* refDirector_;

      bool continue_;
      bool pause_;
      bool requireReset_;
      bool requireUpdate_;
      bool requireRender_;

      struct timeval timeInit_;
      struct timeval timeFinal_;
      struct timeval time2Init_;
      struct timeval time2Final_;

      void logAction (int);
};

#endif /* MAINLOOP_H_ */
