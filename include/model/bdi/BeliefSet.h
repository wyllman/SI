/*
 * BeliefSet.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef BELIEFSET_H_
#define BELIEFSET_H_

#include <model/map/Map.h>

#include <map>
#include <string>
#include <vector>

class Belief;

/**
 * \class BeliefSet
 * \brief Clase para almacenar el conjunto de creencias.
 * 
 * La clase BeliefSet almacena el conjunto de creencias en un hashmap.
 * La excepción son el mapa y la localizacón, que por conveniencia
 * son independientes y con sus propios operadores.
 */

class Map;

class BeliefSet {
private:
	std::map<std::string, const Belief*> m_beliefSet;
	const Map* m_map;
	bool** m_knownMap;
	int m_exploredCells;
	float m_exploredPercentage;
	float m_sectorExplorationAverage;
	Point m_position;
	std::vector<float> m_sectorExploredRatio;
	std::vector<float> m_sectorSettlementFactor;

public:
	BeliefSet(const Map&);
	~BeliefSet();

	const Belief* operator[](std::string belief) {
		return m_beliefSet[belief];
	}
	const Map* map() {
		return m_map;
	}
	void setKnownMapCell(int, int, bool);
	bool knownMapCell(int i, int j) {
		return m_knownMap[i][j];
	}
	void setMap(Map* map);
	bool** getKnownMap();
	bool getKnownMapCell(uint32_t, uint32_t);
	bool getKnownMapCell(const Point&);
	Point position() {
		return m_position;
	}
	void setPosition(Point);
	void add(std::string, const Belief*);
	void remove(std::string);
	void sumExploredCells(int);
	float exploredPercentage() {
		return m_exploredPercentage;
	}
	void sumSectorExploredRatio(uint32_t, float);
	void setSectorSettlementFactor(uint32_t, float);
	void resetSectorExploredRatio();
	bool exists(std::string);
	float getSectorExploredRatio(int32_t cell);
	float getSectorSettlementFactor(int32_t cell) {
		return m_sectorSettlementFactor[cell];
	}
};

#endif /* BELIEFSET_H_ */
