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

/**
 * @brief Class to represent a component (field) of a form
 */

class Component {
public:

	/**
	 * @brief Constructor
	 *
	 * @param type type of the component
	 */
	Component(std::string type);


	/**
	 * @brief add eNFA described by regex to component
	 *
	 * @param value the regex
	 *
	 * @pre No database should be present
	 */
	bool regex(std::string value);


	/**
	 * @brief add database to regex
	 *
	 * @param file Name of the database file
	 *
	 * @pre No database should be present
	 */
	bool db(std::string file);


	/**
	 * @brief add database to regex
	 *
	 * @param file Name of the database file
	 * @param corrector Indicates where input correction should be applied
	 *
	 * @pre No database should be present
	 */
	bool db(std::string file, bool corrector);

	/**
	 * @brief add eNFA described by file to component
	 *
	 * @param file The filename
	 *
	 * @pre No database should be present
	 */
	bool ENFA(std::string file);


	/**
	 * @brief generates corrected version of input string
	 *
	 * @param value the string to be corrected
	 *
	 * @return the corrected string
	 */
	std::string DBcorrector(std::string value);


	/**
	 * @brief check if string is accepted by component
	 *
	 * @return true if accepted
	 */
	bool process(std::string);

	/**
	 * @brief returns the type of the component
	 *
	 * @return the type
	 */

	std::string getType();


	virtual ~Component();
private:
	eNFA* fENFA;
	std::string fType;
	std::vector<std::string> fDB;
	bool fDBCorrectionOn; // Do we need to check if strings are almost correct and equivalent to the ones in the db?
};

} /* namespace FA */
#endif /* COMPONENT_H_ */
