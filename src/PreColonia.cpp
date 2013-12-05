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
#include "headers/view/abstracts/View.h"
#include "headers/view/interface/Interface.h"
#include "headers/model/abstracts/Model.h"
#include "headers/model/simulator/Simulator.h"

int main() {
	cout << "**********************************" << endl;
	cout << "Iniciando el Simulador PreColonia." << endl;

	// Inicializando las clases base del patrón MVC y enlazar las referencias
	Controller* directorSim = new Director;
	View* interfaceSim = new Interface (directorSim);
	Model* modelSim = new Simulator (directorSim);
	directorSim->setReferences(interfaceSim, modelSim);
	interfaceSim->init();

	// Inicializando la ejecución del simulador
	directorSim->init();
	directorSim->stop();
	interfaceSim->stop();

	// Destruyendo los objetos creados para el patrón MVC
	delete (directorSim);
	delete (interfaceSim);
	delete (modelSim);

	cout << "Saliendo del Simulador PreColonia." << endl;
	cout << "**********************************" << endl;
	return 0;
}
