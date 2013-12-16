/*
 *      Nombre: FileLog.h
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.003
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

#include <vector>
#include <string>

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
      std::vector<std::string> regAccErr_;
      int lineNumber_;

      void logAction (int);
};

#endif /* FILELOG_H_ */
