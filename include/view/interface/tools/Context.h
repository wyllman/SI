/*
 *      Nombre: Context.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de gestionar e inicializar la libreria de openGL.
 *
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <iostream>

#include <GL.h>
#include <GLU.h>

#include "../Interface.h"
#include "../../../Tools.h"

using namespace std;

class Context {
public:
	Context(const Interface*);
	virtual ~Context();

	void init ();
	GLuint getProgramGsl() const;

private:
	const Interface* refInterface_;

	GLuint programGSL_;
	GLuint bufferVertex_;
	GLuint vertexShader_;
	GLuint fragmentShader_;
	GLint compilerStateOK_;
	GLint linkerStateOK_;

	void initShaders();
	void initBuffers();

	void logAction(int);

};

#endif /* CONTEXT_H_ */
