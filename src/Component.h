/*
 * Component.h
 *
 *  Created on: 10 mei 2013
 *      Author: Ruben
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include "eNFA.h"
#include "RegexToNFA.h"

namespace FA {

class Component {
public:
	Component(std::string type);
	bool regex(std::string value);
	bool db(std::string file);
	bool db(std::string file, bool corrector);
	bool ENFA(std::string file);

	std::string DBcorrector(std::string value);

	bool process(std::string);

	std::string getType();


	virtual ~Component();
private:
	eNFA* fENFA;
	std::string fType;
	std::vector<std::string> fDB;
	bool fDBcorrector; // Do we need to check if strings are almost correct and equivalent to the ones in the db?
};

} /* namespace FA */
#endif /* COMPONENT_H_ */
