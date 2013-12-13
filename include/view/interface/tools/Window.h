/*
 *      Nombre: Window.h
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

#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL.h>

class Interface;

class Window {
public:
	Window(const Interface&);
	virtual ~Window();

	void init (int, int);
	void update ();
	void reshape ();

private:
	const Interface* refInterface_;

	SDL_Window* windowSDL_;
	SDL_Renderer* rendererScene_;
	SDL_RendererInfo* displayRendererInfo_;

	void logAction(int);

};

#endif /* WINDOW_H_ */
