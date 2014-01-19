/*
 * Intention.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/bdi/Intention.h>
#include <model/bdi/BeliefSet.h>
#include <model/bdi/Desire.h>

#include <iostream>

Intention::Intention(BeliefSet& beliefSet, Desire& desire) {
    m_beliefSet = &beliefSet;
    m_desire = &desire;
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
    if (m_beliefSet->exploredPercentage() >= 0.5) {
        m_desire->set("50_Percent_Explored", true);
    }
    if (m_beliefSet->exploredPercentage() >= 0.8) {
        m_desire->set("100_Percent_Explored", true);
    }
}

void Intention::findOptimalLocation() {
    //TODO: Calcular la localizacion optima
}

void Intention::gatherResources() {
    //TODO: Recolectar recursos
}

void Intention::buildSettlement() {
    //TODO: Mostrar algo y fin del programa
}
