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
    } else {
        if((*m_desire)["100_Percent_Explored"]) {
            std::cout << "Mapa explorado" << std::endl;
        }
        std::cout << "Explora" << std::endl;
        if (!(*m_desire)["Settlement_Place_Found"]) {
            std::cout << "Busca asentamiento" << std::endl;
            if (!(*m_desire)["Resources_Gathered"]) {
                std::cout << "Busca recursos" << std::endl;
            } else {
                std::cout << "Construye asentamiento" << std::endl;
            }
        }
    }
}
