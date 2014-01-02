/*
 *      Nombre: Simulator.h
 *
 *   Creado en: 05/12/2013
 *     Versión: v0.003
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Modelo específico para la ejecución del sistema inteligente. La generación del
 *              terreno y la gestión de los agentes que intervienen en la simulación.
 *
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_
 
class Map;
class MainAgent;

class Simulator: public Model {
   public:
      Simulator(const Controller&);
      virtual ~Simulator();

      void init();
      void stop();
      const Map* getMap() const;
      const MainAgent* getMainAgent () const;

   private:
      Map* map_;
      MainAgent* m_MainAgent;
      void logAction(int);
};

#endif /* SIMULATOR_H_ */
