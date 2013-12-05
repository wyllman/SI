/*
 *      Nombre: Simulator.cpp
 *
 *   Creado en: 05/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Modelo específico para la ejecución del sistema inteligente. La generación del
 *              terreno y la gestión de los agentes que intervienen en la simulación.
 *
 */

#include "../../../headers/model/simulator/Simulator.h"
#include "../../../headers/Tools.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Simulator::Simulator(const Controller* controller):Model(controller) {
	if (BASIC_LOG) {
		cout << "---Generado el modelo Simulator " << endl;
	}
}
Simulator::~Simulator() {
	if (BASIC_LOG) {
		cout << "---Destruyendo el modelo Simulator " << endl;
	}
	if (ADVAN_LOG) {
		FileLog* fileLogTmp = (FileLog*)(((Director*)refController_)->getRegAccErr());
		fileLogTmp->insertLine("---Destruyendo el modelo Simulator ");
	}
	stop();
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Simulator::init() {
	if (BASIC_LOG) {
		cout << "---Llamano a la función init de la clase Simulator " << endl;
	}
	if (ADVAN_LOG) {
		FileLog* fileLogTmp = (FileLog*)(((Director*)refController_)->getRegAccErr());
		fileLogTmp->insertLine("---Llamano a la función init de la clase Simulator.");
	}
}
void Simulator::stop() {
	if (BASIC_LOG) {
		cout << "---Llamano a la función stop de la clase Simulator " << endl;
	}
	if (ADVAN_LOG) {
		FileLog* fileLogTmp = (FileLog*)(((Director*)refController_)->getRegAccErr());
		fileLogTmp->insertLine("---Llamano a la función stop de la clase Simulator.");
	}
}
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


