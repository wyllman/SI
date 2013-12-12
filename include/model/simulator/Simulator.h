/*
 *      Nombre: Simulator.h
 *
 *   Creado en: 05/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Modelo específico para la ejecución del sistema inteligente. La generación del
 *              terreno y la gestión de los agentes que intervienen en la simulación.
 *
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <iostream>

#include <model/abstracts/Model.h>

class Map;

class Simulator: public Model {
public:
	Simulator(const Controller*);
	virtual ~Simulator();

	void init();
	void stop();

private:
	Map* map_;

	void logAction(int);
};

#endif /* SIMULATOR_H_ */
