/*
 *      Nombre: Scene.cpp
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de gestionar y contener los objetos a mostrar en la escena.
 *
 */

#include "../../../../headers/view/interface/tools/Scene.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Scene::Scene(const Interface* interface) {
	refInterface_ = interface;
	logAction(LOG_INIT);
}

Scene::~Scene() {
	logAction(LOG_END);
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:

// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Manejadores públicos:

// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos privados:
void Scene::logAction(int index) {
	if (BASIC_LOG) {
		switch (index) {
			case LOG_INIT:
				cout << "------Generado la herramienta Scene para la vista Interfaz " << endl;
				break;
			case LOG_END:
				cout << "------Destruyendo la herramienta Scene para la vista Interfaz "
					<< endl;
				break;
			default:
				break;
		}
	}
	if(ADVAN_LOG) {
		switch (index) {
			case LOG_INIT:
				((Interface*)refInterface_)
					->log("------Generado la herramienta Scene para la vista Interfaz ");
				break;
			case LOG_END:
				((Interface*)refInterface_)
					->log("------Destruyendo la herramienta Scene para la vista Interfaz ");
				break;
			default:
				break;
		}
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


