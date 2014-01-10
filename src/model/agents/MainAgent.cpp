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

MainAgent::MainAgent(Simulator* refModel): refSimulator_(refModel) {
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
   boost::random::uniform_int_distribution<> positionDistrib(1, MAP_WIDTH - 1); // Porque WIDTH = HEIGHT
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

		// Comprobación de vecindad de la nave -> para la colocación de agentes
		BYTE tempCentro = ((*mainMap)(m_position.first, m_position.second) & MASK_TERRAIN);
		BYTE tempArrIzq = ((*mainMap)(m_position.first - 1, m_position.second - 1) & MASK_TERRAIN);
		BYTE tempArr = ((*mainMap)(m_position.first, m_position.second - 1) & MASK_TERRAIN);
		BYTE tempArrDer = ((*mainMap)(m_position.first + 1, m_position.second - 1) & MASK_TERRAIN);
		BYTE tempIzq = ((*mainMap)(m_position.first - 1, m_position.second) & MASK_TERRAIN);
		BYTE tempDer = ((*mainMap)(m_position.first + 1, m_position.second) & MASK_TERRAIN);
		BYTE tempAbjIzq = ((*mainMap)(m_position.first - 1, m_position.second + 1) & MASK_TERRAIN);
		BYTE tempAbj = ((*mainMap)(m_position.first, m_position.second + 1) & MASK_TERRAIN);
		BYTE tempAbjDer = ((*mainMap)(m_position.first + 1, m_position.second + 1) & MASK_TERRAIN);

		if (tempCentro == TERRAIN_GROUND && tempArrIzq == TERRAIN_GROUND && tempArr == TERRAIN_GROUND
				&& tempArrDer == TERRAIN_GROUND && tempIzq == TERRAIN_GROUND && tempDer == TERRAIN_GROUND &&
				tempAbjIzq == TERRAIN_GROUND && tempAbj == TERRAIN_GROUND && tempAbjDer == TERRAIN_GROUND){
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
   if (ADVAN_LOG) {
      switch (index) {
         case LOG_INIT:
            refSimulator_->log("---Generando el Agente principal ");
            break;
         case LOG_END:
            refSimulator_->log("---Destruyendo el Agente principal ");
            break;
         case LOG_F_INIT:
            refSimulator_->log("---Llamando a la función createRndInitialPos () del agente principal.");
            break;
         default:
            break;
      }
   }
}

std::vector<Agent*>& MainAgent::getVAgents () {
	return m_Vagents;
}

std::vector<Agent*>& MainAgent::getWorVecAgents() {
   return m_WorVecAgents;
}
