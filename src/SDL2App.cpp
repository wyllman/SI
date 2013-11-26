/*
 * SDL2App.cpp
 *
 *  Created on: 09/11/2013
 *      Author: manwe
 */

#include "SDL2App.h"

SDL2App::SDL2App() {
	// TODO Auto-generated constructor stub

}

SDL2App::~SDL2App() {
	// TODO Auto-generated destructor stub
}

int SDL2App::onExecute() {
	if(onInit() == false) {
		return -1;
	}
	
	SDL_Event event;
	
	while(m_running) {
		while(SDL_PollEvent(&event)) {
			onEvent(&event);
		}
		onLoop();
		onRender();
	}

	onCleanUp();
	return 0;
}

bool SDL2App::onInit() {

}

void SDL2App::onEvent(SDL_Event *event) {

}

void SDL2App::onLoop() {

}

void SDL2App::onRender() {

}

void SDL2App::onCleanUp() {

}

void SDL2App::onDie(const char* msg) {
	printf("%s: %s\n", msg, SDL_GetError());
	SDL_Quit();
	exit(1);
}
