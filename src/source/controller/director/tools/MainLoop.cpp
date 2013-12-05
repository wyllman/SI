/*
 *      Nombre: MainLoop.cpp
 *
 *   Creado en: 02/12/2013
  *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de contener y gestionar el bucle principal de ejecución.
 *
 */

#include "../../../../headers/controller/director/tools/MainLoop.h"
#include "../../../../headers/Tools.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
MainLoop::MainLoop(const Director* director) {
	if (BASIC_LOG) {
		cout << "------Generado la herramienta MainLoop para el Director " << endl;
	}
	refDirector_ = director;
	if (ADVAN_LOG) {
		FileLog* regist = (FileLog*) refDirector_->getRegAccErr();
		regist->insertLine("------Generado la herramienta MainLoop para el Director ");
	}
}

MainLoop::~MainLoop() {
	if (BASIC_LOG) {
		cout << "------Destruyendo la herramienta MainLoop para el Director " << endl;
	}
	if (ADVAN_LOG) {
		FileLog* regist = (FileLog*) refDirector_->getRegAccErr();
		regist->insertLine("------Destruyendo la herramienta MainLoop para el Director ");
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

