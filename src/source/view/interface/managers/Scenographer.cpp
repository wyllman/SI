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
#include "../../../../headers/Tools.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Scenographer::Scenographer(const Interface* interface) {
	if (BASIC_LOG) {
		cout << "------Generado el gestor Scenographer para la vista Interfaz " << endl;
	}
	refInterface_ = interface;
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
				->log("------Generado el gestor Scenographer para la vista Interfaz ");
	}
}
Scenographer::~Scenographer() {
	if (BASIC_LOG) {
		cout << "------Destruyendo el gestor Scenographer para la vista Interfaz " << endl;
	}
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
				->log("------Destruyendo el gestor Scenographer para la vista Interfaz ");
	}
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

// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

