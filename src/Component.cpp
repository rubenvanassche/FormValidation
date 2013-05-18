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
	this->fDBCorrectionOn = false;
}
bool Component::regex(std::string value){
	if(this->fDB.size() != 0){
		// There is a DB present
		return false;
	}

	this->fENFA = FA::regexToNFA(value);

	return true;
}
bool Component::db(std::string file){
	return this->db(file, false);
}

bool Component::db(std::string file, bool corrector){
	if(this->fENFA != NULL){
		// There is a ENFA present
		return false;
	}

	const char *filename = file.c_str();

	std::ifstream stream(filename);
	if(!stream.good()){
		// File doesn't exists
		return false;
	}

	std::string line;

	while(std::getline(stream, line)){
		this->fDB.push_back(line);
	}

	this->fDBCorrectionOn = corrector;

	return true;
}

bool Component::ENFA(std::string file){
	if(this->fDB.size() != 0){
		// There is a DB present
		return false;
	}
	return true;
	//this->fENFA = enfa;
}

std::string Component::DBcorrector(std::string value){
	std::string::iterator it;

	for(it = value.begin();it != value.end();it++){
		*it = std::tolower(*it);

		if(*it == ' ' or *it == '-'){
			value.erase(it);
		}

		if(*it == '�'){
			*it = 'e';
		}

		if(*it == '�'){
			*it = 'e';
		}

		if(*it == '�'){
			*it = 'e';
		}

		if(*it == '�'){
			*it = 'a';
		}

	}

	return value;
}

bool Component::process(std::string value){
	if(this->fDB.size() == 0){
		return this->fENFA->process(value);
	}else{
		// Do we need to correct the string?
		if(this->fDBCorrectionOn == true){
			// yes
			value = this->DBcorrector(value);
			for(unsigned i = 0; i < fDB.size();i++){
				if(this->DBcorrector(fDB.at(i)) == value){
					return true;
				}
			}
			return false;
		}else{
			// no just search
			if(std::find(fDB.begin(), fDB.end(), value) != fDB.end()){
				return true;
			}else{
				return false;
			}
		}
	}
}

std::string Component::getType(){
	return this->fType;
}

Component::~Component() {
	// TODO Auto-generated destructor stub
}

} /* namespace FA */
