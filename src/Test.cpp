/*
 * Test.cpp
 *
 *  Created on: 18 mei 2013
 *      Author: Ruben
 */

#include "Test.h"

namespace FA {

Test::Test(std::string name) {
	this->fName = name;
	this->fFails = 0;
	this->fGoods = 0;

	std::cout << "[" << this->fName << " Test]" << std::endl;
}

bool Test::equal(bool val1, bool val2){
	if(val1 == val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is not equal to " << val2 << std::endl;
		return false;
	}
}
bool Test::equal(int val1, int val2){
	if(val1 == val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is not equal to " << val2 << std::endl;
		return false;
	}
}
bool Test::equal(float val1, float val2){
	if(val1 == val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is not equal to " << val2 << std::endl;
		return false;
	}
}
bool Test::equal(std::string val1, std::string val2){
	if(val1 == val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is not equal to " << val2 << std::endl;
		return false;
	}
}

bool Test::different(bool val1, bool val2){
	if(val1 != val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is equal to " << val2 << std::endl;
		return false;
	}
}
bool Test::different(int val1, int val2){
	if(val1 != val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is equal to " << val2 << std::endl;
		return false;
	}
}
bool Test::different(float val1, float val2){
	if(val1 != val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is equal to " << val2 << std::endl;
		return false;
	}
}
bool Test::different(std::string val1, std::string val2){
	if(val1 != val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is equal to " << val2 << std::endl;
		return false;
	}
}

bool Test::expectTrue(bool val){
	if(val == true){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : must be true, is false" << std::endl;
		return false;
	}
}
bool Test::expectFalse(bool val){
	if(val != true){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : must be false, is true" << std::endl;
		return false;
	}
}

Test::~Test() {
	std::cout << "[RESULT] " << this->fGoods << " passed " << this->fFails << "crashed." << std::endl;
}

} /* namespace FA */
