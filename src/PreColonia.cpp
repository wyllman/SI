//============================================================================
// Nombre      : PreColonia.cpp
// Autores     : Tinguaro Cubas Saiz
//               Juan Henández Hernández
//               Miguel Pérez Bello
//               Guillermo Rodríguez Pardo
// Versión     : v0.0
// Descripción : Simulador de la preparación de un terreno inexplorado para la
//               la creación de una futura colonia humana. Se usará un sistema
//               inteligente basado en agentes encargados de explorar y
//               trabajar sobre la zona.
//============================================================================

#include <iostream>
using namespace std;

#include "headers/controller/abstracts/Controller.h"
#include "headers/controller/director/Director.h"

int main() {
	cout << "**********************************" << endl;
	cout << "Iniciando el Simulador PreColonia." << endl;

	Controller* directorSim = new Director;

	directorSim->init();


	directorSim->stop();

	delete (directorSim);

	cout << "Saliendo del Simulador PreColonia." << endl;
	cout << "**********************************" << endl;
	return 0;
}
