/*
 * Component.cpp
 *
 *  Created on: 10 mei 2013
 *      Author: Ruben
 */

#include "Component.h"

namespace FA {

Component::Component(std::string type){
	this->fType = type;
	this->fENFA  = NULL;
}
void Component::regex(std::string value){
	this->fENFA = FA::regexToNFA(value);
}
void Component::db(std::string file){
	// todo
}
void Component::ENFA(std::string file){
	//this->fENFA = enfa;
}

bool Component::process(std::string value){
	return this->fENFA->process(value);
}

std::string Component::getType(){
	return this->fType;
}

Component::~Component() {
	// TODO Auto-generated destructor stub
}

} /* namespace FA */
