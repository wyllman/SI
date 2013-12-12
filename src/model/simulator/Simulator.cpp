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

#include <model/simulator/Simulator.h>
#include <model/map/Map.h>
#include <model/map/MapConsoleInterface.h>

#include <controller/director/Director.h>
#include <controller/director/tools/FileLog.h>
#include <Tools.h>

// ___________________________________________________________________________________
// Constructores y Destructor:
Simulator::Simulator(const Controller& controller) :
		Model(controller) {
	logAction(LOG_INIT);
}
Simulator::~Simulator() {
	logAction(LOG_END);
	stop();
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Simulator::init() {
	logAction(LOG_F_INIT);
	map_ = new Map();

	MapConsoleInterface mapci(*map_);

	for (uint32_t i = 0; i < map_->size(); i++) {
		for (uint32_t j = 0; j < map_->size(); j++) {
				std::cout << mapci(i, j);
		}
		std::cout << std::endl;
	 }
	 /* FIXME: Se libera el mapa aqui aunque no deberia, puesto que nos hace
	  * falta para el resto de la simulación
	  * Deberia ser liberado en el destructor idealmente
	  * FIX? alocar la memoria en el constructor y liberarla en el destructor
	  */
 	 if (map_ != NULL) {
 		delete map_;
 		map_ = NULL;
 	}
}
void Simulator::stop() {
	logAction(LOG_F_STOP);
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
void Simulator::logAction(int index) {
	if (BASIC_LOG) {
		switch (index) {
		case LOG_INIT:
			std::cout << "---Generado el modelo Simulator " << std::endl;
			break;
		case LOG_END:
			std::cout << "---Destruyendo el modelo Simulator " << std::endl;
			break;
		case LOG_F_INIT:
			std::cout << "---Llamano a la función init de la clase Simulator "
					<< std::endl;
			break;
		case LOG_F_STOP:
			std::cout << "---Llamano a la función stop de la clase Simulator "
					<< std::endl;
			break;
		default:
			break;
		}
	}
	if (ADVAN_LOG) {
		FileLog* fileLogTmp = const_cast<FileLog*>(
			dynamic_cast<Director*>(
				const_cast<Controller*>(refController_))->getRegAccErr());
		switch (index) {
		case LOG_INIT:
			fileLogTmp->insertLine("---Generando el modelo Simulator ");
			break;
		case LOG_END:
			fileLogTmp->insertLine("---Destruyendo el modelo Simulator ");
			break;
		case LOG_F_INIT:
			fileLogTmp->insertLine(
					"---Llamano a la función init de la clase Simulator.");
			break;
		case LOG_F_STOP:
			fileLogTmp->insertLine(
					"---Llamano a la función stop de la clase Simulator.");
			break;
		default:
			break;
		}
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

