/*
 * MainAgent.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/agents/MainAgent.h>
#include <model/bdi/BeliefSet.h>
#include <controller/director/tools/FileLog.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/binomial_distribution.hpp>
#include <boost/random/negative_binomial_distribution.hpp>
#include <boost/random/random_device.hpp>

MainAgent::MainAgent() {
	logAction(LOG_INIT);
	m_beliefSet = new BeliefSet();
}

MainAgent::~MainAgent() {
   logAction(LOG_END);
}

void MainAgent::createRndInitialPos (Map* mainMap) {
	   logAction(LOG_F_INIT);
	boost::random::random_device rndDev;
	boost::random::mt11213b probabilityRNG;
	boost::random::mt11213b layoutRNG;
	boost::random::mt11213b positionRNG;
	boost::random::mt11213b typeRNG;
	boost::random::negative_binomial_distribution<> probabilityDistrib(3, 0.5);
	boost::random::uniform_int_distribution<> positionDistrib(0, MAP_WIDTH); // Porque WIDTH = HEIGHT
	boost::random::uniform_int_distribution<> typeDistrib(3, 5);

	bool condition = false; // Indica si está en una posición CORRECTA

	do {
		// posición x del agente principal
		positionRNG.seed(rndDev());
		positionRNG();
		positionDistrib.reset();
		m_position.first = positionDistrib(positionRNG);
		// posicion y del agente principal
		positionRNG.seed(rndDev());
		positionRNG();
		positionDistrib.reset();
		m_position.second = positionDistrib(positionRNG);

		BYTE temp = ((*mainMap)(m_position.first, m_position.second) & MASK_TERRAIN);
		if (temp == TERRAIN_GROUND){
			condition = true;
		}

	} while (!condition);

	std::cout << "Position generated on: x = " << m_position.first << " , y = " << m_position.second << std::endl;
}

void MainAgent::logAction(int index) {
   if (BASIC_LOG) {
      switch (index) {
         case LOG_INIT:
            std::cout << "---Generando el Agente principal " << std::endl;
            break;
         case LOG_END:
            std::cout << "---Destruyendo el Agente principal " << std::endl;
            break;
         case LOG_F_INIT:
        	 std::cout << "---Llamando a la función createRndInitialPos () del agente principal." << std::endl;
            break;
         default:
            break;
      }
   }
}

Point MainAgent::getPosition () {
	return m_position;
}
