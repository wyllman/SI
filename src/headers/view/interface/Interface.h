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

#include "../abstracts/View.h"
#include "managers/Bureaucrat.h"
#include "managers/Scenographer.h"
#include "tools/Window.h"
#include "tools/Context.h"
#include "tools/Scene.h"

using namespace std;

class Interface: public View {
public:
	Interface(const Controller*);
	virtual ~Interface();

	void init();
	void stop();

private:
	Bureaucrat* bureaucrat_;
	Scenographer* scenographer_;

	Window* window_;
	Context* context_;
	Scene* scene_;
};

#endif /* INTERFACE_H_ */
