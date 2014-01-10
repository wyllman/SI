/*
 *      Nombre: Model.h
 *
 *   Creado en: 04/12/2013
 *     Version: v0.03
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase abstracta para el model base del simulador.
 *
 */

#ifndef MODEL_H_
#define MODEL_H_

class Controller;

class Model {
   public:
      Model(const Controller&);
      virtual ~Model();

      virtual void init () {};
      virtual bool update () {};
      virtual void reset () {};
      virtual void stop () {};

   protected:
   const Controller* refController_;
};

#endif /* MODEL_H_ */
