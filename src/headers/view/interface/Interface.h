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

using namespace std;

class Interface: public View {
public:
	Interface(const Controller*);
	virtual ~Interface();

private:
	// Atributos privdos

};

#endif /* INTERFACE_H_ */
