/*
 *      Nombre: Model.h
 *
 *   Creado en: 04/12/2013
 *     Version: v0.0
 *     Autores: tenerent
 *
 * Descripcion:
 *
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "../../controller/abstracts/Controller.h"

class Controller;

class Model {
public:
	Model(const Controller*);
	virtual ~Model();

	virtual void init () {};
	virtual void update () {};
	virtual void reset () {};

private:
	const Controller* refController_;

};

#endif /* MODEL_H_ */
