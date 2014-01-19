/*
 * Desires.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/bdi/Desire.h>

Desire::Desire() {
}

Desire::~Desire() {
}

void Desire::add(std::string desire, bool value) {
    m_desire.insert(std::pair<std::string, bool>(desire, value));
}

void Desire::set(std::string desire, bool value) {
    m_desire[desire] = value;
}
