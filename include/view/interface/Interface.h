/*
 *      Nombre: Interface.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
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

#include <iostream>

#include <SDL.h>
#include <GL.h>
#include <GLU.h>

#include <view/abstracts/View.h>
#include <view/interface/managers/Bureaucrat.h>
#include <view/interface/managers/Scenographer.h>
#include <view/interface/tools/Window.h>
#include <view/interface/tools/Context.h>
#include <view/interface/tools/Scene.h>
#include <controller/director/Director.h>
#include <Tools.h>

using namespace std;

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
