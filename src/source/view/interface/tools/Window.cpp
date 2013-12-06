/*
 *      Nombre: Window.cpp
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de inicializar y gestionar al ventana en la que se mostrará
 *              el simulador (SDL).
 *
 */

#include "../../../../headers/view/interface/tools/Window.h"
#include "../../../../headers/Tools.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Window::Window(const Interface* interface) {
	if (BASIC_LOG) {
		cout << "------Generado la herramienta Window para la vista Interfaz " << endl;
	}
	refInterface_ = interface;
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
				->log("------Generado la herramienta Window para la vista Interfaz ");
	}
}

Window::~Window() {
	if (BASIC_LOG) {
		cout << "------Destruyendo la herramienta Window para la vista Interfaz " << endl;
	}
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
				->log("------Destruyendo la herramienta Window para la vista Interfaz ");
	}
	delete(displayRendererInfo_);
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
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
				->log("------Inicializando la ventana SDL. ");
	}
	displayRendererInfo_ = new SDL_RendererInfo;
	SDL_CreateWindowAndRenderer( width, height, SDL_WINDOW_OPENGL, &windowSDL_, &rendererScene_);
	SDL_GetRendererInfo(rendererScene_, displayRendererInfo_);

	if ((displayRendererInfo_->flags & SDL_RENDERER_ACCELERATED) == 0 ) {
		if (ADVAN_LOG) {
			((Interface*)refInterface_)
					->log("------ERROR!! SDL RendererInfo (Sin aceleración gráfica) ");
		}
		((Interface*)refInterface_)->stop();
	}
	if ((displayRendererInfo_->flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
		if (ADVAN_LOG) {
			((Interface*)refInterface_)
					->log("------ERROR!! SDL RendererInfo (Sin ... textura?...) ");
		}
		((Interface*)refInterface_)->stop();
	}

	SDL_SetWindowTitle(windowSDL_, "Simulador PreColonia");
}
void Window::update() {
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

// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

