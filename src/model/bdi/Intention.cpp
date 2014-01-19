/*
 * Intention.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/bdi/Intention.h>
#include <model/bdi/BeliefSet.h>
#include <model/bdi/Desire.h>
#include <model/agents/MainAgent.h>
#include <model/agents/Agent.h>
#include <model/agents/SearchAgent.h>
#include <model/agents/WorkingAgent.h>
#include <model/fipa/Package.h>

#include <iostream>
#include <sstream>

Intention::Intention(const Agent& agent, BeliefSet& beliefSet, Desire& desire) :
    m_beliefSet(&beliefSet),
    m_desire(&desire),
    m_agent(&dynamic_cast<MainAgent&>(const_cast<Agent&>(agent)))
{
}

Intention::~Intention() {
}

void Intention::update() {
    if (!(*m_desire)["50_Percent_Explored"]) {
        std::cout << "Explora" << std::endl;
        exploreMap();
    } else {
        if((*m_desire)["100_Percent_Explored"]) {
            std::cout << "Mapa explorado" << std::endl;
            exploreMap();
        }
        std::cout << "Explora" << std::endl;
        if (!(*m_desire)["Settlement_Place_Found"]) {
            std::cout << "Busca asentamiento" << std::endl;
            findOptimalLocation();
            if (!(*m_desire)["Resources_Gathered"]) {
                std::cout << "Busca recursos" << std::endl;
                gatherResources();
            } else {
                std::cout << "Construye asentamiento" << std::endl;
                buildSettlement();
            }
        }
    }
}

void Intention::exploreMap() {
    //TODO: Comprobar el mapa y enviar a los agentes
	Package* pack;
    for (uint8_t i = 0; i < m_agent->getVAgents().size(); ++i) {
        if (m_agent->getVAgents()[i]->getState() == AVAILABLE) {
        	pack = new Package(m_agent->getNameAgent(), m_agent->getVAgents()[i]->getNameAgent(), DIRECTION_SEARCH);
        	std::vector<std::string> packContent;
        	std::stringstream ss;
        	ss << i * 2;
        	packContent.push_back(ss.str());
        	pack->setContent(packContent);
        	m_agent->getVAgents()[i]->readFIPAPackage(pack);
        }
    }
    if (m_beliefSet->exploredPercentage() >= 0.5) {
        m_desire->set("50_Percent_Explored", true);
    }
    if (m_beliefSet->exploredPercentage() >= 0.9) {
        m_desire->set("100_Percent_Explored", true);
    }
}

void Intention::findOptimalLocation() {
    //TODO: Calcular la localizacion optima
    /*Valor agua 4, comida 2, otros 1
     * div d^2
     */
}

void Intention::gatherResources() {
    //TODO: Recolectar recursos
}

void Intention::buildSettlement() {
    //TODO: Mostrar algo y fin del programa
}
