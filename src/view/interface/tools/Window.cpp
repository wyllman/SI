/*
 *      Nombre: Window.cpp
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.003
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de inicializar y gestionar al ventana en la que se mostrará
 *              el simulador (SDL).
 *
 */

#include <view/interface/tools/Window.h>

#include <view/interface/Interface.h>
#include <Tools.h>

#include <iostream>

using namespace std;

// ___________________________________________________________________________________
// Constructores y Destructor:
Window::Window(const Interface& interface) {
   refInterface_ = &interface;
   logAction(LOG_INIT);
}

Window::~Window() {
   logAction(LOG_END);
   delete (displayRendererInfo_);
   SDL_DestroyRenderer(rendererScene_);
   SDL_DestroyWindow(windowSDL_);
   SDL_Quit();
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Window::init(int width, int height) {
   logAction(LOG_F_INIT);
   displayRendererInfo_ = new SDL_RendererInfo;
   SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &windowSDL_,
                               &rendererScene_);
   SDL_GetRendererInfo(rendererScene_, displayRendererInfo_);

   if ((displayRendererInfo_->flags & SDL_RENDERER_ACCELERATED) == 0) {
      logAction(LOG_ERROR);
      const_cast<Interface*> (refInterface_)->stop();
    }
   if ((displayRendererInfo_->flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
      logAction(LOG_ERROR_1);
      const_cast<Interface*> (refInterface_)->stop();
   }

   SDL_SetWindowTitle(windowSDL_, "Simulador PreColonia");
}
void Window::update() {
   SDL_RenderPresent(rendererScene_);
}
void Window::reshape() {
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
void Window::logAction(int index) {
   if (BASIC_LOG) {
      switch (index) {
         case LOG_INIT:
			cout
					<< "------Generado la herramienta Window para la vista Interfaz "
					<< endl;
			break;
		case LOG_END:
			cout
					<< "------Destruyendo la herramienta Window para la vista Interfaz "
					<< endl;
			break;
		case LOG_F_INIT:
			cout << "------Inicializando la ventana SDL. " << endl;
			break;
		case LOG_ERROR:
			cout << "------ERROR!! SDL RendererInfo (Sin aceleración gráfica) "
					<< endl;
			break;
		case LOG_ERROR_1:
			cout << "------ERROR!! SDL RendererInfo (Sin ... textura?...) "
					<< endl;
			break;
		default:
			break;
		}
	}
	if (ADVAN_LOG) {
		switch (index) {
		case LOG_INIT:
			const_cast<Interface*> (refInterface_)->log(
					"------Generado la herramienta Window para la vista Interfaz ");
			break;
		case LOG_END:
			const_cast<Interface*> (refInterface_)->log(
					"------Destruyendo la herramienta Window para la vista Interfaz ");
			break;
		case LOG_F_INIT:
			const_cast<Interface*> (refInterface_)->log(
					"------Inicializando la ventana SDL");
			break;
		case LOG_ERROR:
			const_cast<Interface*> (refInterface_)->log(
					"------ERROR!! SDL RendererInfo (Sin aceleración gráfica) ");
			break;
		case LOG_ERROR_1:
			const_cast<Interface*> (refInterface_)->log(
					"------ERROR!! SDL RendererInfo (Sin ... textura?...) ");
			break;
		default:
			break;
		}
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

