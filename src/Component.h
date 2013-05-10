/*
 * Component.h
 *
 *  Created on: 10 mei 2013
 *      Author: Ruben
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>
#include "eNFA.h"
#include "RegexToNFA.h"

namespace FA {

class Component {
public:
	Component(std::string type);
	void regex(std::string value);
	void db(std::string file);
	void ENFA(std::string file);

	bool process(std::string);

	std::string getType();


	virtual ~Component();
private:
	eNFA* fENFA;
	std::string fType;
};

} /* namespace FA */
#endif /* COMPONENT_H_ */
