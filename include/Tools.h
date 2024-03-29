/*
 *      Nombre: Tools.h
 *
 *   Creado en: 05/12/2013
 *     Versión: v0.003
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Archivo de cabecera con el conjunto de constantes útiles
 *              en la mqyoría de las clases del simulador.
 *
 *
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <inttypes.h>
#include <map>
#include <string>
#include <Point.h>

const bool SIMULATOR_RET_MOV_ON = false;

// Definiciones de tipos propios para el proyecto.
typedef unsigned char BYTE;

// Conjunto de constantes de configuración del sistema de seguimiento
const bool BASIC_LOG = true;
const bool ADVAN_LOG = true;
// Conjunto de constantes para la configuración del controlador
const double MIN_TIME_DIFF = 1 / 45; // Tiempo de actualización para los eventos.
const double MIN_TIME2_DIFF = 1 / 1.0; // Tiempos de actualización para el simulador.
const double MIN_TIME3_DIFF = 1 / 2.0;
const double MIN_TIME4_DIFF = 1 / 40.0;
const double MIN_TIME5_DIFF = 1 / 100.0;

// Conjunto de constantes de configuración de la interfaz gráfica
//   Ventana:
const int WIN_WIDTH = 1300;
const int WIN_HEIGHT = 650;
//   Terreno: (Nota: No modificar a la ligera!)
const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;
const float MAP_SCALE = 1;
const float MAP_UP_SCALE = 2.5;
//   Agentes:
const float MAIN_AGENT_SCALE = 1;
const float SECOND_AGENT_SCALE = 0.5;
// Tamaño del sector
const int32_t SECTOR_SIZE = 10;

// Conjunto de constantes auxiliares para la integración del sistema
// de seguimiento
enum {
   LOG_ERROR = -1,
   LOG_INIT = 1,
   LOG_END = 2,
   LOG_F_INIT = 3,
   LOG_F_STOP = 4,
   LOG_F_START = 5,
   LOG_F_LOOP = 6,

   LOG_ERROR_1 = -101,
   LOG_INIT_1 = 101,
   LOG_END_1 = 102,
   LOG_F_INIT_1 = 103,
   LOG_F_STOP_1 = 104,
   LOG_F_START_1 = 105,
   LOG_F_LOOP_1 = 106,
   LOG_ERROR_2 = -201
};

// Conjunto de constantes para la integración en los distintos sistemas
// de los datos referentes al terreno (elevación y recursos).
enum {
   TERRAIN_GROUND = 0x1,
   TERRAIN_ELEVATION = 0x2,
   TERRAIN_WATER = 0x4,
   RESOURCE_METAL = 0x8,
   RESOURCE_FOOD = 0x10,
   RESOURCE_MINERAL = 0x20,
   RESOURCE_WATER = 0x40,
   UNKNOWN_TERRAIN = 0x80
};

enum {
   MASK_TERRAIN = 0x7,	// bits 1-3 (0x1-0x4)
   MASK_RESOURCE = 0x38	// bits 4-6 (0x8-0x20)
};

enum Direction {
   NORTH = 0,
   NEAST,
   EAST,
   SEAST,
   SOUTH,
   SWEST,
   WEST,
   NWEST,
   ERROR_DIR
};

enum Type {
	NOT_UNDERSTOOD = 0,
	CONFIRM,
	MAP_UPDATE,
	LOCATED_OBSTACLE,
	END_LIMITS,
	MAP_UPDATE_OK,
	MAP_UPDATE_ERROR,
	DIRECTION_SEARCH,
	SECTOR_SEARCH,
	ARRIVED_GOAL,
	COME_BACK,
	GO_LOCATION,
	GO_RESOURCE_LOCATION,
	GO_SEARCHING_LOCATION,
	PUT_RESOURCE_LOCATION
};

enum State {
	AVAILABLE = 0, // esperando a una tarea ...
	SEARCHING,	   // realizando una exploración
	SECOND_SEARCHING,
	AWAITING_NEW_ORDER,
	RECOLECTING,   // parado frente a fuente de recursos y recolectando
	FULL_OF_RESOURCES, // Cuando ya recolectó el agente trabajador
	FOLLOWING_ROUTE, // Siguiendo una ruta enviada por paquete
	FOLLOWING_RES_ROUTE, // Siguiendo una ruta para recolectar
	FOLLOWING_RET_ROUTE, // Siguiendo una ruta de regreso a la nave.
	FOLLOWING_SEARCH_ROUTE, // Siguiendo una ruta para empezar una exploración
	PUTTING_RESOURCE // parada en emplazamiento temporal descargando recursos
};

Direction strToDirectionEnum (std::string);
std::string directionEnumToString(Direction);
/**
 * \fn euclideanDistance (const Point& origin, const Point& target)
 * \param origin El punto origin
 * \param target El punto objetivo
 * \return Distancia euclídea entre los dos puntos
 */
float euclideanDistance (const Point&, const Point&);

#endif /* TOOLS_H_ */
