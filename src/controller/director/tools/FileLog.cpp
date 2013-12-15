/*
 *      Nombre: FileLog.cpp
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

#include <controller/director/tools/FileLog.h>
#include <Tools.h>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstring>

// ___________________________________________________________________________________
// Constructores y Destructor:
FileLog::FileLog() {
	logAction(LOG_INIT);
	lineNumber_ = 0;
}

FileLog::~FileLog() {
	logAction(LOG_END);
	reset();
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void FileLog::init() {
	reset();
	logAction(LOG_F_INIT);
}
void FileLog::reset() {
	if (!regAccErr_.empty()) {
		regAccErr_.clear();
	}
	lineNumber_ = 0;
}
void FileLog::save() {
	if (!regAccErr_.empty()) {
		std::ofstream outfile("LogAE.txt", std::ofstream::out);
		for (int i = 0; i < regAccErr_.size(); i++) {
			outfile.write(regAccErr_[i].c_str(), regAccErr_[i].size());
			outfile.write("\n", 1);
		}
		outfile.close();
	}

}
void FileLog::showConsole() {
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
			<< std::endl;
	std::cout << "+++ Mostrando el registro de acciones y errores         +++"
			<< std::endl;
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
			<< std::endl;

	if (!regAccErr_.empty()) {
		for (int i = 0; i < regAccErr_.size(); i++) {
			std::cout << "+++ " << regAccErr_[i] << std::endl;
		}
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
				<< std::endl;
	} else {
		std::cout << "+++ ¡Error! El registro está vacío.                     +++"
				<< std::endl;
		std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
				<< std::endl;
	}
}
void FileLog::insertLine(const char* line) {
	std::string tempLine;
	int lineSize = strlen(line);
	std::stringstream ss;

	lineNumber_ += 1;
	ss << lineNumber_; //add number to the stream
	tempLine = "" + ss.str();
	tempLine += ". ";
	if (lineSize > 0) {
		for (int i = 0; i < lineSize; i++) {
			tempLine += line[i];
		}
	}
	regAccErr_.push_back(tempLine);
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
void FileLog::logAction(int index) {
	if (BASIC_LOG) {
		switch (index) {
		case LOG_INIT:
			std::cout << "------Generado la herramienta FileLog para el Director "
					<< std::endl;
			break;
		case LOG_END:
			std::cout << "------Destruyendo la herramienta FileLog para el Director "
					<< std::endl;
			break;
		default:
			break;
		}
	}
	if (ADVAN_LOG) {
		switch (index) {
		case LOG_F_INIT:
			insertLine("**********************************");
			insertLine("Iniciando el Simulador PreColonia.");
			insertLine("---Generado el coordinador Director ");
			break;
		default:
			break;
		}
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

