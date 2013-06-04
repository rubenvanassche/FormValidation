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


/**
 * @brief Class representing a form
 */
class Form {
public:

	/**
	 * @brief constructor
	 *
	 * @param name Name of the form
	 */
	Form(std::string name);

	/**
	 * @brief add non-required field without minimal length to form
	 *
	 * @param name name of the field
	 * @param type of the field (its component)
	 */

	bool add(std::string name, std::string type);

	/**
	 * @brief add field without minimum length to form
	 *
	 * @param name name of the field
	 * @param type of the field (its component)
	 * @param required true if required
	 */
	bool add(std::string name, std::string type, bool required);

	/**
	 * @brief add non-required field to form
	 *
	 * @param name name of the field
	 * @param type of the field (its component)
	 * @param length minimal length of input
	 */
	bool add(std::string name, std::string type, unsigned int length);

	/**
	 * @brief add field to form
	 *
	 * @param name name of the field
	 * @param type of the field (its component)
	 * @param required true if required
	 * @param length minimal length of input
	 */
	bool add(std::string name, std::string type, bool required, unsigned int length);

	/**
	 * @brief add field to form
	 *
	 * @param name name of the field
	 * @param type of the field (its component)
	 * @param length minimal length of input
	 * @param required true if required
	 */
	bool add(std::string name, std::string type, unsigned int length, bool required);

	/**
	 * @brief adds all of the possible components to the form
	 *
	 * @param file file name of textfile containing components
	 *
	 * @return true if success
	 */
	bool addComponents(std::string file, const std::vector<std::string>& = std::vector<std::string>());


	/**
	 * @brief run the form
	 */
	void build();

	/**
	 * @brief check if form is complete
	 *
	 * @return true if complete
	 */
	bool ok();

	/**
	 * @brief run the form (without printing name of form)
	 */
	void process();

	/**
	 * @brief Get the filled in data from the form
	 *
	 * @return the data
	 */
	std::map<std::string, std::string> getData();


	/**
	 * @brief load form from file
	 *
	 * @param file the file name of file containing form
	 */
	bool load(std::string file);

	/**
	 * @brief get vector of components used by form
	 *
	 * @param file the file name of file containing form
	 *
	 * @param usedComps vector to contain the names of the components used by the form
	 */

	void readComponents(std::string file, std::vector<std::string>& usedComps);

	virtual ~Form();
private:
	Component* getComponent(std::string type);

	std::string fName;
	std::vector<Field> fields;
	std::vector<Component> components;
};

} /* namespace FA */
#endif /* FORM_H_ */
