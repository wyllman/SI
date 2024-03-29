/*
 *      Nombre: Bureaucrat.cpp
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.003
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de las gestiones y cargas de librerías y los recursos
 *              necesarios del sistema operativo.
 *
 */

#include <view/interface/managers/Bureaucrat.h>

#include <view/interface/Interface.h>
#include <Tools.h>

#include <iostream>
#include <SDL.h>
#ifdef __linux
   #include <GL/glew.h>
#else
   #include <GL.h>
   #include <GLU.h>
#endif

using namespace std;

// ___________________________________________________________________________________
// Constructores y Destructor:
Bureaucrat::Bureaucrat(const Interface& interface) {
   refInterface_ = &interface;
   logAction(LOG_F_INIT);
}
Bureaucrat::~Bureaucrat() {
   logAction(LOG_END);
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Bureaucrat::initSDL() {
   logAction(LOG_F_INIT);
   // Inicializar SDL y comprobar que no hubo ningún error básico.
   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      logAction(LOG_ERROR);
      const_cast<Interface*>(refInterface_)->stop();
   }
}
void Bureaucrat::initOGL() {
   logAction(LOG_F_INIT_1);
   // En caso de compilar en linux, inicializar las librerías GLEW
   // y comprobar que no hubo ningún error básico.
   #ifdef __linux
      GLenum err = glewInit();
      if (GLEW_OK != err) {
         const_cast<Interface*>(refInterface_)->stop();
      }
   #endif
   // Configurar la máquina de estados de OpenGL para su correcta
   // ejecución.
   glShadeModel( GL_SMOOTH );

   glEnable( GL_DEPTH_TEST );
   glDepthMask(GL_TRUE);
   glDepthFunc( GL_LEQUAL );
   glDepthRange(0.0f, 1.0f);
   glClearDepth( 1.0f );

   glEnable( GL_BLEND );
   //glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);

   glEnable(GL_CULL_FACE);
   glCullFace(GL_FRONT);

   glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
   // loadShader();
}
void Bureaucrat::loadShader() {
   if (ADVAN_LOG) {
      const_cast<Interface*>(refInterface_)->log("------Cargando Shaders en la clase Bureaucrat. ");
   }
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
void Bureaucrat::logAction(int index) {
   if (BASIC_LOG) {
      switch (index) {
         case LOG_INIT:
            cout << "------Generado el gestor Bureaucrat para la vista Interfaz " << endl;
            break;
         case LOG_END:
            cout << "------Destruyendo el gestor Bureaucrat para la vista Interfaz" << endl;
            break;
         case LOG_F_INIT:
            cout << "------Inicializando SDL en la clase Bureaucrat." << endl;
            break;
         case LOG_F_INIT_1:
            cout << "------Inicializando OGL en la clase Bureaucrat." << endl;
            break;
         case LOG_ERROR:
            cout << "------ERROR!! No se pudo iniciar SDL: " << SDL_GetError() << endl;
            break;
         default:
            break;
      }
   }
   if (ADVAN_LOG) {
      switch (index) {
         case LOG_INIT:
            const_cast<Interface*>(refInterface_)->log("------Generado el gestor Bureaucrat para la vista Interfaz ");
            break;
         case LOG_END:
            const_cast<Interface*>(refInterface_)->log("------Destruyendo el gestor Bureaucrat para la vista Interfaz ");
            break;
         case LOG_F_INIT:
            const_cast<Interface*>(refInterface_)->log("------Inicializando SDL en la clase Bureaucrat. ");
            break;
         case LOG_F_INIT_1:
            const_cast<Interface*>(refInterface_)->log("------Inicializando OGL en la clase Bureaucrat. ");
            break;
         case LOG_ERROR:
            const_cast<Interface*>(refInterface_)->log("------ERROR!! No se pudo iniciar SDL ");
            break;
         default:
            break;
      }
   }
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
