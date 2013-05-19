/*
 * test.h
 *
 *  Created on: 18 mei 2013
 *      Author: Ruben
 */

#ifndef TEST_H_
#define TEST_H_

#include <string>
#include <iostream>
#include "common.h"
#include "eNFA.h"
#include "RegexToNFA.h"

namespace FA {

class Test {
public:
	Test(std::string name);

	bool equal(bool val1, bool val2);
	bool equal(int val1, int val2);
	bool equal(float val1, float val2);
	bool equal(std::string val1, std::string val2);

	bool different(bool val1, bool val2);
	bool different(int val1, int val2);
	bool different(float val1, float val2);
	bool different(std::string val1, std::string val2);

	bool expectTrue(bool val);
	bool expectFalse(bool val);

	int runAllTests();

	virtual ~Test();
private:
	std::string fName;
	int fFails;
	int fGoods;
};

} /* namespace FA */
#endif /* TEST_H_ */
