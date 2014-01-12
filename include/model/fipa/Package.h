/*
 * Package.h
 *
 *  Created on: 12/01/2014
 *      Author: maikel
 */

#include <iostream>
#include <vector>
#include <Tools.h>

#ifndef PACKAGE_H_
#define PACKAGE_H_

class Package {
public:
	Package(char*, char*, Type);
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

private:
	char* m_sender;
	char* m_receiver;
	Type m_type;
	std::vector<std::string> m_content;
	unsigned int m_idComm;
};

#endif /* PACKAGE_H_ */
