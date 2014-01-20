/*
 * Intention.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef INTENTION_H_
#define INTENTION_H_

#include <string>

class BeliefSet;
class Desire;
class Agent;
class MainAgent;

class Intention {
private:
    BeliefSet* m_beliefSet;
    Desire* m_desire;
    MainAgent* m_agent;
    bool m_newDesireSelected;
    std::string m_currentDesire;

    void exploreMap();
    void findOptimalLocation();
    void gatherResources();
    void buildSettlement();
    void checkSectors();
public:
    Intention(const Agent&, BeliefSet&, Desire&);
	~Intention();
    void update();
};

#endif /* INTENTION_H_ */
