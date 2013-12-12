//============================================================================
// Nombre      : PreColonia.cpp
// Autores     : Tinguaro Cubas Saiz
//               Juan Henández Hernández
//               Miguel Pérez Bello
//               Guillermo Rodríguez Pardo
// Versión     : v0.002
// Descripción : Simulador de la preparación de un terreno inexplorado para la
//               la creación de una futura colonia humana. Se usará un sistema
//               inteligente basado en agentes encargados de explorar y
//               trabajar sobre la zona.
//============================================================================

#include <MVCHeaders.h>
#include <Tools.h>

#include <iostream>
#include <cstdlib>

void logAction(int index) {
	if (BASIC_LOG) {
		switch (index) {
		case LOG_INIT:
			std::cout << "**********************************" << std::endl;
			std::cout << "Iniciando el Simulador PreColonia." << std::endl;
			break;
		case LOG_END:
			std::cout << "Saliendo del Simulador PreColonia." << std::endl;
			std::cout << "**********************************" << std::endl;
			break;
		default:
			break;
		}

	}
}

int main() {
	logAction(LOG_INIT);

	// Creando las clases base del patrón MVC y enlazar las referencias
 	Controller* directorSim = new Director;
 	View* interfaceSim = new Interface(directorSim);
 	Model* modelSim = new Simulator(directorSim);


	// Inicializando la ejecución del simulador
	directorSim->init();
	modelSim->init();
	directorSim->start();

	// Terminando la ejecución del simulador
	interfaceSim->stop();
	modelSim->stop();

	// Destruyendo los objetos creados para el patrón MVC
	if (interfaceSim != NULL) {
		delete interfaceSim;
		interfaceSim = NULL;
	}
	if (modelSim != NULL) {
		delete modelSim;
		modelSim = NULL;
	}

	// Terminando y destruyendo al Director del simulador
	directorSim->stop();
	if(directorSim != NULL) {
		delete directorSim;
		directorSim = NULL;
	}

	logAction(LOG_END);
	return EXIT_SUCCESS;
}
