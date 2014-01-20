/*
 * Package.h
 *
 *  Created on: 12/01/2014
 *      Author: maikel
 */

#ifndef PACKAGE_H_
#define PACKAGE_H_

#include <iostream>
#include <vector>
#include <Tools.h>
#include <model/agents/Agent.h>

class Agent;
/**
 * \class Package
 * \brief Paquetes de protocolo de FIPA.
 */
class Package {
public:
	/**
	 * \fn Package(char*, char* Type)
	 * \brief CTOR
	 * \param sender
	 * \param receiver
	 * \param type
	 */
	Package(char*, char*, Type);
	Package(char*, char*, Type, Agent*);
	virtual ~Package();

	char* getSender() const;
	void setSender(char* sender);
	char* getReceiver() const;
	void setReceiver(char* receiver);
	Type getType() const;
	void setType(Type type);
	unsigned int getIdComm() const;
	void setIdComm(unsigned int idComm);
	std::vector<std::string>& getContent();
	void setContent(std::vector<std::string>& content);
	Agent* getRefSenderAgent();
	void setRefSenderAgent(Agent* refSenderAgent);

private:
	char* m_sender;
	Agent* refSenderAgent_;
	char* m_receiver;
	Type m_type;
	std::vector<std::string> m_content;
	unsigned int m_idComm;
};

#endif /* PACKAGE_H_ */
