/*
 *      Nombre: Context.cpp
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

#include "../../../../headers/view/interface/tools/Context.h"
#include "../../../../headers/Tools.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Context::Context(const Interface* interface) {
	if (BASIC_LOG) {
		cout << "------Generado la herramienta Context para la vista Interfaz " << endl;
	}
	refInterface_ = interface;
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
				->log("------Generado la herramienta Context para la vista Interfaz ");
	}
}

Context::~Context() {
	if (BASIC_LOG) {
		cout << "------Destruyendo la herramienta Context para la vista Interfaz " << endl;
	}
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
				->log("------Destruyendo la herramienta Context para la vista Interfaz ");
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

