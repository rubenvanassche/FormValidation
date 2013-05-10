/*
 * Form.h
 *
 *  Created on: 10 mei 2013
 *      Author: Ruben
 */

#ifndef FORM_H_
#define FORM_H_

#include "Field.h"
#include "Component.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <fstream>

namespace FA {

class Form {
public:
	Form(std::string name);

	bool add(std::string name, std::string type);
	bool add(std::string name, std::string type, bool required);
	bool add(std::string name, std::string type, unsigned int length);
	bool add(std::string name, std::string type, bool required, unsigned int length);
	bool add(std::string name, std::string type, unsigned int length, bool required);

	bool addComponents(std::string file);

	void build();

	bool ok();
	void process();

	std::map<std::string, std::string> getData();

	bool load(std::string file);

	virtual ~Form();
private:
	Component* getComponent(std::string type);

	std::string fName;
	std::vector<Field> fields;
	std::vector<Component> components;
};

} /* namespace FA */
#endif /* FORM_H_ */
