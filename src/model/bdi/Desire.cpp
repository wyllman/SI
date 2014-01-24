/*
 * Desires.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/bdi/Desire.h>

using namespace std;

Desire::Desire() {
}

Desire::~Desire() {
}

void Desire::add(string desire, bool value) {
    m_desire.insert(pair<string, bool>(desire, value));
}

void Desire::set(string desire, bool value) {
    m_desire[desire] = value;
}
