/*
 * Desires.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef DESIRE_H_
#define DESIRE_H_

#include <string>
#include <map>

/**
 * \class Desire
 * \brief Clase para el modelado de intenciones
 * 
 * Sigue la estructura básica de la clase Belief, pero no se presupone
 * cierta.
 */
class Desire {
private:
    std::map<std::string, bool> m_desire;
public:
    Desire();
    ~Desire();
    void add(std::string, bool);
    bool operator[](std::string str) { return m_desire[str]; }
};

#endif /* DESIRE_H_ */
