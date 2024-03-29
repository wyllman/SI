//============================================================================
// Nombre      : PreColonia.cpp
// Autores     : Tinguaro Cubas Saiz
//               Juan Henández Hernández
//               Miguel Pérez Bello
//               Guillermo Rodríguez Pardo
// Versión     : v0.003
// Descripción : Simulador de la preparación de un terreno inexplorado para la
//               la creación de una futura colonia humana. Se usará un sistema
//               inteligente basado en agentes encargados de explorar y
//               trabajar sobre la zona.
//============================================================================

#include <MVCHeaders.h>
#include <Tools.h>

#include <iostream>

using namespace std;

void logAction(int index) {
   if (BASIC_LOG) {
      switch (index) {
         case LOG_INIT:
            cout << "**********************************" << endl;
            cout << "Iniciando el Simulador PreColonia." << endl;
            break;
         case LOG_END:
            cout << "Saliendo del Simulador PreColonia." << endl;
            cout << "**********************************" << endl;
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
   View* interfaceSim = new Interface(*directorSim);
   Model* modelSim = new Simulator(*directorSim);
   directorSim->setReferences(*interfaceSim, *modelSim);

   // Inicializando la ejecución del simulador
   directorSim->init();
   directorSim->start();

   // Terminando la ejecución y
   // destruyendo los objetos creados para el patrón MVC
   directorSim->stop();
   interfaceSim = NULL;
   modelSim = NULL;

   // Destruyendo al Director del simulador
   if(directorSim != NULL) {
      delete (directorSim);
      directorSim = NULL;
   }

   logAction(LOG_END);
   return EXIT_SUCCESS;
}
