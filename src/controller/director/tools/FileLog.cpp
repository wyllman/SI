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

#include "../../../../include/controller/director/tools/FileLog.h"


// ___________________________________________________________________________________
// Constructores y Destructor:
FileLog::FileLog() {
	logAction(LOG_INIT);
	lineNumber_ = 0;
}

FileLog::~FileLog() {
	logAction(LOG_END);
	reset ();
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void FileLog::init() {
	reset ();
	logAction(LOG_F_INIT);
}
void FileLog::reset() {
	int regSize = regAccErr_.size();
	if (regSize > 0) {
		for (int i = 0; i < regSize; i++) {
			delete[] (regAccErr_[i]);
		}
		regAccErr_.clear();
	}
	lineNumber_ = 0;
}
void FileLog::save() {
	int regSize = regAccErr_.size();
	if (regSize > 0) {
		ofstream outfile ("LogAE.txt",std::ofstream::binary);
		for (int i = 0; i < regSize; i++) {
			outfile.write (regAccErr_[i],strlen(regAccErr_[i]));
			outfile.write ("\n",1);
		}
		outfile.close();
	}

}
void FileLog::showConsole() {
	int tmpSize = regAccErr_.size();
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "+++ Mostrando el registro de acciones y errores         +++" << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	if (tmpSize > 0) {
		for (int i = 0; i < tmpSize; i++) {
			cout << "+++ " << regAccErr_[i] << endl;
		}
		cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	} else if (tmpSize == 0) {
		cout << "+++ ¡Error! El registro está vacío.                     +++" << endl;
		cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	}
}
void FileLog::insertLine(const char* line) {
	string tempLine;
	char* finalLine;
	int lineSize = strlen(line);
	stringstream ss;

	lineNumber_ += 1;
	ss << lineNumber_;//add number to the stream
	tempLine = "" + ss.str();
	tempLine += ". ";
	if ( lineSize > 0) {
		for (int i = 0; i < lineSize; i++) {
			tempLine += line[i];
		}
	}
	finalLine = new char [tempLine.size() + 1];
	strcpy(finalLine, tempLine.c_str());
	regAccErr_.push_back(finalLine);
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
				cout << "------Generado la herramienta FileLog para el Director " << endl;
				break;
			case LOG_END:
				cout << "------Destruyendo la herramienta FileLog para el Director " << endl;
				break;
			default:
				break;
		}
	}
	if(ADVAN_LOG) {
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

