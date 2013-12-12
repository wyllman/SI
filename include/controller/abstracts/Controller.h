/*
 *      Nombre: Controller.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase abstracta para definir el comportamiento básico del controlador.
 *
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <view/abstracts/View.h>
#include <model/abstracts/Model.h>

class View;
class Model;

class Controller {
public:
	Controller();
	virtual ~Controller();

	virtual void init () {};
	virtual void start () {};
	virtual void stop () {};
	void setReferences (const View*, const Model*);

protected:
	const View* refView_;
	const Model* refModel_;

};

#endif /* CONTROLLER_H_ */
