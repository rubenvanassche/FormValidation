/*
 * Field.cpp
 *
 *  Created on: 10 mei 2013
 *      Author: Ruben
 */

#include "Field.h"

namespace FA {

Field::Field(Component* type, std::string name){
	this->fComponent = type;
	this->fName = name;
	this->fLength = 0;
	this->fRequired = false;
	this->fValue = "";
	this->fFilledIn = false;
}


Field::Field(Component* type, std::string name, unsigned int length){
	this->fComponent = type;
	this->fName = name;
	this->fLength = length;
	this->fRequired = false;
	this->fValue = "";
	this->fFilledIn = false;
}

Field::Field(Component* type, std::string name, unsigned int length, bool required){
	this->fComponent = type;
	this->fName = name;
	this->fLength = length;
	this->fRequired = required;
	this->fValue = "";
	this->fFilledIn = false;
}

void Field::required(){
	this->fRequired = true;
}
void Field::notRequired(){
	this->fRequired = false;
}

void Field::length(unsigned int value){
	this->fLength = value;
}


std::string Field::makeLabel(){
	std::string label;
	label = "- ";
	label += this->getName();

	if(this->fLength != 0){
		std::stringstream ss;
		ss << this->fLength;

		label += " ";
		label += "(minimum-lengte: ";
		label += ss.str();
		label += ")";
	}

	if(this->fRequired == true){
		label += " *";
	}

	label += "\n";

	return label;
}

bool Field::process(std::string value){
	if(this->isFilledIn()){
		return true;
	}

	if(this->fRequired == false and value.size() == 0){
		this->fFilledIn = true;
		return true;
	}

	if(this->fLength != 0){
		if(value.size() < this->fLength){
			return false;
		}
	}

	if(this->fComponent->process(value)){
		this->fValue = value;
		return true;
	}else{
		return false;
	}
}

bool Field::check(std::string value){
	if(this->isFilledIn()){
		return false;
	}

	if(this->fRequired == false and value.size() == 0){
		return true;
	}

	if(this->fLength != 0){
		if(value.size() < this->fLength){
			return false;
		}
	}

	if(this->fComponent->process(value)){
		return true;
	}else{
		return false;
	}
}

bool Field::isAccepted(){
	if(this->fValue.size() == 0){
		if(this->isRequired() == false){
			return true;
		}

		return false;
	}else{
		return true;
	}
}

bool Field::isFilledIn(){
	if(this->fValue.size() == 0){
		return false;
	}else{
		return true;
	}
}

bool Field::isRequired(){
	return this->fRequired;
}

Component* Field::getComponent(){
	return this->fComponent;
}

unsigned int Field::getLength(){
	return this->fLength;
}

std::string Field::getName(){
	return this->fName;
}

std::string Field::getValue(){
	return this->fValue;
}



} /* namespace FA */
