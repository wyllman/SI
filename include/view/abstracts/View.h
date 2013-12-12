/*
 *      Nombre: View.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase abstracta para definir el comportamiento básico de la vista.
 *
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "../../controller/abstracts/Controller.h"

class Controller;

class View {
public:
	View(const Controller*);
	virtual ~View();

	virtual void init () {};
	virtual void update () {};
	virtual void reset () {};
	virtual void stop () {};

protected:
	const Controller* refController_;
};

#endif /* VIEW_H_ */
