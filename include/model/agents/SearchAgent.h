/*
 * SearchAgent.h
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#ifndef SEARCHAGENT_H_
#define SEARCHAGENT_H_

#include <iostream>
#include <cstdlib>

#include <model/agents/WorkingAgent.h>
#include <model/fipa/Package.h>

class SearchAgent: public Agent {
public:
	SearchAgent();
	~SearchAgent();

	void setPosition (Point p) { m_position = p; }
	Package* readFIPAPackage (Package*);

	void localDireccionalSearch (std::string);
};

#endif /* SEARCHAGENT_H_ */
