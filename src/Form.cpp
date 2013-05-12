/*
 * Form.cpp
 *
 *  Created on: 10 mei 2013
 *      Author: Ruben
 */

#include "Form.h"

namespace FA {

Form::Form(std::string name){
	this->fName = name;
}

bool Form::add(std::string name, std::string type){
	return this->add(name, type, 0, false);
}

bool Form::add(std::string name, std::string type, bool required){
	return this->add(name, type, 0, required);
}

bool Form::add(std::string name, std::string type, unsigned int length){
	return this->add(name, type, length, false);
}

bool Form::add(std::string name, std::string type, bool required, unsigned int length){
	return this->add(name, type, length, required);
}

bool Form::add(std::string name, std::string type, unsigned int length, bool required){
	Component* fieldType = this->getComponent(type);

	if(fieldType == NULL){
		// there is no such type
		return false;
	}

	Field newField(fieldType, name, length, required);
	fields.push_back(newField);
	return true;
}

bool Form::addComponents(std::string file){
	const char *filename = file.c_str();

	std::ifstream stream(filename);
	if(stream == false){
		// File doesn't exists
		return false;
	}

	std::string line;

	std::string type;
	bool make = false;

    while(std::getline(stream, line)){
    	if(line[0] != ':' and line[2] != ':'){
    		// we've got the type of the comonent
    		type = line;
    		make = true;
    	}else{
    		if(make == false){
    			continue;
    		}

    		// We've got a regex or something else
    		Component component(type);

    		if(line[1] == 'r'){
    			//regex
    			component.regex(line.substr(3));
    		}else if(line[1] == 'd'){
    			// db file
    			component.db(line.substr(3));
    		}else if(line[1] == 'c'){
				// db file with corrector
				component.db(line.substr(3), true);
    		}else if(line[1] == 'e'){
    			// eNFA
    			component.ENFA(line.substr(3));
    		}else{
    			// no idea just jump to the next one
    			make = false;
    			continue;
    		}

    		components.push_back(component);

    		make = false;
    	}
    }

	return true;
}

void Form::build(){
	std::cout << this->fName << std::endl;
	for(int i = 0;i < this->fName.size();i++){
		std::cout << "-";
	}
	std::cout << std::endl << std::endl;

	this->process();
}

void Form::process(){
	std::vector<Field>::iterator it;
	for(it = fields.begin();it != fields.end();it++){
		if(it->isFilledIn()){
			continue;
		}

		std::cout << it->makeLabel();

		std::string input;
		std::cin >> input;
		it->process(input);
	}

	if(this->ok() == false){
		// Oh no we failed!
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "Gelieve deze velden opnieuw in te vullen, ze zijn verkeerd!" << std::endl;
		std::cout << "-----------------------------------------------------------" << std::endl << std::endl;
		this->process();
	}else{
		// we can continue
		std::cout << std::endl << std::endl << std::endl;
		std::cout << "-------------------------------------------" << std::endl;
		std::cout << "Dank u voor het invullen van dit formulier." << std::endl;
	}
}

bool Form::ok(){
	bool go = true;

	for(int i = 0;i < fields.size();i++){
		if(fields.at(i).isAccepted() == false){
			go = false;
			break;
		}
	}

	return go;
}

std::map<std::string, std::string> Form::getData(){
	std::map<std::string, std::string> data;

	std::vector<Field>::iterator it;
	for(it = fields.begin();it != fields.end();it++){
		data[it->getName()] = it->getValue();
	}

	return data;
}

bool Form::load(std::string file){
	const char *filename = file.c_str();

	std::ifstream stream(filename);
	if(stream == false){
		// File doesn't exists
		return false;
	}

	std::string line;

	std::string name;
	std::string type;
	std::string lengthS;
	std::string requiredS;

	bool make = false;

    while(std::getline(stream, line)){
    	if(line[0] != ':' and line[2] != ':'){
    		// It's the name
    		// Do we need to make this field?
			if(make == true){
				if(name.size() != 0 and type.size() != 0){
					bool required = false;
					unsigned int length = 0;

					if(lengthS.size() != 0){
						length = std::atoi(lengthS.c_str());
					}

					if(requiredS == "1" or requiredS == "true" or requiredS == "yes"){
						required = true;
					}

					this->add(name, type, length, required);
					std::cout << "Added " << name << " a " << type << " field with length: " << length << " and required: " << required << std::endl;
				}

				make = false;
			}

			// So set the name variable equal to the newname
    		name = line;
    		type = "";
    		lengthS = "";
    		requiredS = "";
    	}else{
    		// it no name but something else
    		if(line[1] == 't'){
    			type = line.substr(3);
    		}else if(line[1] == 'l'){
    			lengthS = line.substr(3);
    		}else if(line[1] == 'r'){
    			requiredS = line.substr(3);
    		}

    		make = true;
    	}

    }

    // Do it once again
	if(name.size() != 0 and type.size() != 0){
		bool required = false;
		unsigned int length = 0;

		if(lengthS.size() != 0){
			length = std::atoi(lengthS.c_str());
		}

		if(requiredS == "1" or requiredS == "true" or requiredS == "yes"){
			required = true;
		}

		this->add(name, type, length, required);
		std::cout << "Added " << name << " a " << type << " field with length: " << length << " and required: " << required << std::endl;
	}

}

Component* Form::getComponent(std::string type){
	for(unsigned int i = 0;i < this->components.size();i++){
		if(components.at(i).getType() == type){
			return &(components.at(i));
		}
	}

	return NULL;
}

Form::~Form() {
	// TODO Auto-generated destructor stub
}

} /* namespace FA */
