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

/**
 * @brief Class representing a field of a form
 */
class Field {
public:
	/**
	 * @brief constructor
	 *
	 * @param type Pointer to the component
	 * @param name Name of the field
	 */
	Field(Component* type, std::string name);


	/**
	 * @brief constructor
	 *
	 * @param type Pointer to the component
	 * @param name Name of the field
	 * @param length Minimal length of input
	 */
	Field(Component* type, std::string name, unsigned int length);


	/**
	 * @brief constructor
	 *
	 * @param type Pointer to the component
	 * @param name Name of the field
	 * @param length Minimal length of input
	 * @param required True if field has to be filled in
	 */
	Field(Component* type, std::string name, unsigned int length, bool required);

	/**
	 * @brief sets field to required
	 */
	void required();


	/**
	 * @brief sets field to not required
	 */
	void notRequired();


	/**
	 * @brief set minimal length of input
	 *
	 * @param value the minimal length
	 */
	void length(unsigned int value);

	/**
	 * @brief set default value for field
	 *
	 * @param value the default value
	 */
	void defaultValue(std::string value);


	/**
	 * @brief generates a label for the field
	 *
	 * @return the label
	 */
	std::string makeLabel();


	/**
	 * @brief check if input should be accepted into the field and if so: set the field's value to input
	 *
	 * @param value the input to be checked
	 *
	 * @return true if accepted and set
	 */
	bool process(std::string value);

	/**
	 * @brief check if input should be accepted into the field
	 *
	 * @param value value to be checked
	 *
	 * @return true if accepted
	 */
	bool check(std::string value);
	/**
	 * @brief Checks if field is filled in (or empty if not required)
	 *
	 * @return true if field doesn't have to be filled in anymore
	 */
	bool isAccepted();

	/**
	 * @brief Checks if field is filled in
	 *
	 * @return true if field is filled in
	 */
	bool isFilledIn();

	/**
	 * @brief Checks if field is required
	 *
	 * @return true if required
	 */
	bool isRequired();

	/**
	 * @brief Gets the type of field (the component)
	 *
	 * @return pointer to the component
	 */
	Component* getType();

	/**
	 * @brief gets the minimal length of the input
	 *
	 * @return minimal length of the input
	 */
	unsigned int getLength();

	/**
	 * @brief gets the name of the field
	 *
	 * @return name of the field
	 */
	std::string getName();

	/**
	 * @brief gets the value filled in
	 *
	 * @return the filled in value
	 */
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
