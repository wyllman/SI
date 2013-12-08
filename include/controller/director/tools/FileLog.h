/*
 *      Nombre: FileLog.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de contener y gestionar un registro textual de las acciones y
 *              los errores generados en la ejecución del simulador.
 *
 */

#ifndef FILELOG_H_
#define FILELOG_H_

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class FileLog {
public:
	FileLog();
	virtual ~FileLog();

	void init();
	void reset();
	void save();

	void showConsole();

	void insertLine (const char*);

private:
	vector<char*> regAccErr_;
	int lineNumber_;

	void logAction (int);

};

#endif /* FILELOG_H_ */
