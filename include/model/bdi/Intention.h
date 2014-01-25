/*
 * Intention.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef INTENTION_H_
#define INTENTION_H_

#include <stdint.h>
#include <string>

class BeliefSet;
class Desire;
class Agent;
class MainAgent;
class Point;

class Intention {
private:
	BeliefSet* m_beliefSet;
	Desire* m_desire;
	MainAgent* m_agent;
	bool m_newDesireSelected;
	std::string m_currentGoal;
	int loopCount_;
	
	/**
	 * \fn exploreMap()
	 * Función general de exploración del mapa.
	 * 
	 * La función exploreMap contiene todas las operaciones y llamadas
	 * para los diferentes tipos de exploración del mapa.
	 */
	void exploreMap();
	/**
	 * \fn findOptimalLocation()
	 * Elige entre los sectores del mapa cuál es el más apropiado para un
	 * asentamiento.
	 */
	void findOptimalLocation();
	/**
	 * \fn gatherResources()
	 * Función general de recolección de recursos.
	 */
	void gatherResources();
	/**
	 * \fn buildSettlement()
	 * "Construcción" del asentamiento.
	 * Pone fin a la simulación.
	 */
	void buildSettlement();
	/**
	 * \fn checkSectorsExplorationRatio()
	 * Comprueba el índice de exploración de cada sector.
	 */
	void checkSectorsExplorationRatio();
	/**
	 * \fn checkSectorBoundaries(uint32_t sector)
	 * \param sector Sector a comprobar.
	 * \return Punto de acceso al sector.
	 * Comprueba los límites de un sector.
	 * 
	 * La función comprueba los límites de un sector para saber si es accesible
	 * de alguna forma. En caso contrario devuelve NULL.
	 * Si el sector es no es accesible establece el valor del vector
	 * BeliefSet::m_sectorExploredRatio a 1
	 */
	const Point* checkSectorBoundaries(uint32_t);
	const Point* checkSectorCells(uint32_t);
	void checkSectorsFactor();
	void sectorExploration();
	void gotoOptimalLocation();
public:
	Intention(const Agent&, BeliefSet&, Desire&);
	~Intention();
	void update();
};

#endif /* INTENTION_H_ */
