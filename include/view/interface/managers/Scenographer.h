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

#include <view/interface/Interface.h>
#include <view/interface/tools/Scene.h>
#include <model/map/Map.h>
#include <model/map/MapConsoleInterface.h>
#include <Tools.h>

class Interface;
class Scene;

class Scenographer {
public:
	Scenographer(const Interface&, const Scene&, const Map&);
	virtual ~Scenographer();

	void init ();
	void update ();
	void projZoom (float);
	void camPosX (float);

private:
	const Interface* refInterface_;
	const Scene* refScene_;
	const Map* refMap_;

	float projAng_;
	float projRatio_;
	int projNear_;
	int projFar_;

	float camPos_[3];
	float camViewPoint_[3];
	float camVectorUp_[3];

	void initProy (float, float, int, int);
	void initCam (float [3], float [3], float [3]);
	void initFloor ();

	void updateProy ();
	void updateCam ();
	void updateFloor (int, int);
	void createUp (int, int, float, float [3], float*, float*, int);
	void createLeft ();

	void logAction(int);
};

#endif /* SCENOGRAPHER_H_ */
