/*
 *      Nombre: Scenographer.cpp
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

#include "../../../../headers/view/interface/managers/Scenographer.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Scenographer::Scenographer(const Interface* interface) {
	refInterface_ = interface;
	logAction(LOG_INIT);
}
Scenographer::~Scenographer() {
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
void Scenographer::logAction(int index) {
	if (BASIC_LOG) {
		switch (index) {
			case LOG_INIT:
				cout << "------Generado el gestor Scenographer para la vista Interfaz " << endl;
				break;
			case LOG_END:
				cout << "------Destruyendo el gestor Scenographer para la vista Interfaz "
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
					->log("------Generado el gestor Scenographer para la vista Interfaz ");
				break;
			case LOG_END:
				((Interface*)refInterface_)
					->log("------Destruyendo el gestor Scenographer para la vista Interfaz ");
				break;
			default:
				break;
		}
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


