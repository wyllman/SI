/*
 * SDL2App.h
 *
 *  Created on: 09/11/2013
 *      Author: manwe
 */

#ifndef SDL2APP_H_
#define SDL2APP_H_

#include <SDL.h>
#include <SDL_events.h>

/**
 * \class SDL2App
 * \brief Interfaz con SDL2
 *
 * La clase SDL2App implementa los métodos necesarios para crear el bucle del
 * programa de la simulación.
 */
class SDL2App {
public:
	SDL2App();
	~SDL2App();
	bool onInit();
	int onExecute();
private:
	bool m_running;
	void onDie(const char* msg);
	void onEvent(SDL_Event *evt);
	void onLoop();
	void onExit();
	void onRender();
	void onCleanUp();
};

#endif /* SDL2APP_H_ */
