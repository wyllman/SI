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
	Model();
	virtual ~Model();

	virtual void init () {};
	virtual void update () {};
	virtual void reset () {};
	void setReferences (const Controller*);
private:
	const Controller* refController_;

};

#endif /* MODEL_H_ */
