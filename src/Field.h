/*
 * Field.h
 *
 *  Created on: 10 mei 2013
 *      Author: Ruben
 */

#ifndef FIELD_H_
#define FIELD_H_

#include "Component.h"
#include <string>

namespace FA {

class Field {
public:
	Field(Component* type, std::string name);
	Field(Component* type, std::string name, unsigned int length);
	Field(Component* type, std::string name, unsigned int length, bool required);

	void required();
	void notRequired();
	void length(unsigned int value);
	void defaultValue(std::string value);

	std::string makeLabel();
	bool process(std::string value);
	// checks if value is correct + if so set the fValue variable
	bool check(std::string value);
	// checks if value is corretc
	bool isAccepted();
	// true : if field is filled in + not required
	bool isFilledIn();
	// true : if field is filled in

	bool isRequired();
	Component* getType();
	unsigned int getLength();
	std::string getName();
	std::string getValue();
private:
	unsigned int fLength;
	bool fRequired;
	Component* fType;
	std::string fName;

	bool fFilledIn;
	std::string fValue; // value if string is accepted
};

} /* namespace FA */
#endif /* FIELD_H_ */
