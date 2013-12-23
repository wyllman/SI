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

const bool BASIC_LOG = true;
const bool ADVAN_LOG = true;

enum {
   LOG_ERROR = -1,
   LOG_INIT = 1,
   LOG_END = 2,
   LOG_F_INIT = 3,
   LOG_F_STOP = 4,
   LOG_F_START = 5,
   LOG_F_LOOP = 6
};

const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;

const int WIN_WIDTH = 1300;
const int WIN_HEIGHT = 650;

enum {
   LOG_ERROR_1 = -101,
   LOG_INIT_1 = 101,
   LOG_END_1 = 102,
   LOG_F_INIT_1 = 103,
   LOG_F_STOP_1 = 104,
   LOG_F_START_1 = 105,
   LOG_F_LOOP_1 = 106,
   LOG_ERROR_2 = -201
};

#endif /* TOOLS_H_ */
