/*
 *      Nombre: Scenographer.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de gestionar y renderizar la escena a mostrar en el simulador.
 *
 */

#ifndef SCENOGRAPHER_H_
#define SCENOGRAPHER_H_

#ifdef __linux
	#include <GL/glew.h>
#else
	#include <GL.h>
	#include <GLU.h>
#endif

using namespace std;

class Interface;
class Scene;

class Scenographer {
public:
	Scenographer(const Interface*, const Scene*);
	virtual ~Scenographer();

	void init ();
	void update ();

private:
	const Interface* refInterface_;
	const Scene* refScene_;

	void initProy ();
	void initCam ();
	void initFloor ();

	void updateProy (float, float, int, int);
	void updateCam (int [3], int [3], int [3]);
	void updateFloor (int, int);

	void logAction(int);
};

#endif /* SCENOGRAPHER_H_ */
