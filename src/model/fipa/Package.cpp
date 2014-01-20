/*
 * Package.cpp
 *
 *  Created on: 12/01/2014
 *      Author: maikel
 */

#include <model/fipa/Package.h>

Package::Package(char* send, char* receiv, Type type) {
	setSender(send);
	setReceiver(receiv);
	setType(type);
	setIdComm(0);
	setRefSenderAgent(NULL);
}
Package::Package(char* send, char* receiv, Type type, Agent* senderAgent) {
	setSender(send);
	setReceiver(receiv);
	setType(type);
	setIdComm(0);
	setRefSenderAgent(senderAgent);
}

Package::~Package() {
	delete getSender();
	delete getReceiver();
}

char* Package::getSender() const {
	return m_sender;
}

void Package::setSender(char* sender) {
	m_sender = sender;
}

char* Package::getReceiver() const {
	return m_receiver;
}

void Package::setReceiver(char* receiver) {
	m_receiver = receiver;
}

Type Package::getType() const {
	return m_type;
}

void Package::setType(Type type) {
	m_type = type;
}

unsigned int Package::getIdComm() const {
	return m_idComm;
}

void Package::setIdComm(unsigned int idComm) {
	m_idComm = idComm;
}

std::vector<std::string>& Package::getContent() {
	return m_content;
}

void Package::setContent(std::vector<std::string>& content) {
	m_content = content;
}

Agent* Package::getRefSenderAgent() {
	return refSenderAgent_;
}

void Package::setRefSenderAgent(Agent* refSenderAgent) {
	refSenderAgent_ = refSenderAgent;
}
