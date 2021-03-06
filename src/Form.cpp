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
		std::cout << "Component " << type << " not found, field(s) using it will be skipped" << std::endl;
		return false;
	}

	Field newField(fieldType, name, length, required);
	fields.push_back(newField);
	return true;
}

bool Form::addComponents(std::string file, const std::vector<std::string>& usedComps){
	bool checkUsage = false;
	if (usedComps.size())
		checkUsage = true;
	const char *filename = file.c_str();

	std::ifstream stream(filename);
	if(!stream.good()){
		// File doesn't exists
		std::cout << "Component file '" << filename << "' not found" << std::endl;
		return false;
	}

	std::string line;

	std::string type;
	bool make = false;
	int linecount = 0;
    while(std::getline(stream, line)){
    	linecount++;
    	if(line[0] != ':' and line[2] != ':'){
    		// we've got the type of the component
    		type = line;
    		make = true;
    		if (checkUsage)
    			if (std::find(usedComps.begin(), usedComps.end(), type) == usedComps.end())
    				make = false;
    	}else{
    		if(make == false && (std::find(usedComps.begin(), usedComps.end(), type) != usedComps.end())){
    			std::cout <<  "Unused line in components file at line " << linecount << ", please check file validity." << std::endl;
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
    			std::cout << "Line " << linecount << " in component file has syntax ':letter:...', only valid letters are r, d, c and e." << std::endl;
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
	for(unsigned i = 0;i < this->fName.size();i++){
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
		std::getline(std::cin, input);
		bool accepted = it->process(input);

		if(accepted == false){
			// try to find another field where we can put the value in
			std::vector<Field>::iterator it2;
			for(it2 = fields.begin();it2 != fields.end();it2++){
				if(it2->check(input)){
					std::cout << std::endl << std::endl << "Deze waarde is fout maar kan wel in het veld " << it2->getName() << " gezet worden." << std::endl;
					std::cout << "A) Doen" << std::endl << "B) Niet Doen" << std::endl;

					bool stop = true;

					while(true){
						std::string option;
						std::getline(std::cin, option);
						if(option == "A" or option == "a"){
							it2->process(input);
							break;
						}else if(option == "B" or option == "b"){
							stop = false;
							break;
						}else{
							std::cout << "De ingevulde optie is fout, gelieve opnieuw te proberen : " << std::endl;
						}
					}

					if(stop == true){
						break;
					}

				}
			}
		}

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

		std::map<std::string, std::string>::iterator valuesIt;
		std::map<std::string, std::string> values = this->getData();
		for(valuesIt = values.begin(); valuesIt != values.end();valuesIt++){
			std::cout << valuesIt->first << " => " << valuesIt->second << std::endl;
		}
	}
}

bool Form::ok(){
	bool go = true;

	for(unsigned i = 0;i < fields.size();i++){
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
	if(!stream.good()){
		// File doesn't exists
		std::cout << "Form file '" << filename <<"' not found" << std::endl;
		return false;
	}

	std::string line;

	std::string name;
	std::string type;
	std::string lengthS;
	std::string requiredS;
	int linecount = 0;

	bool make = false;

    while(std::getline(stream, line)){
    	linecount++;
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
					name = "";
				}
				else if (name.size() and !type.size()) {
					std::cout << "Field " << name << " does not have a component specified" << std::endl;
				}
				make = false;
			}

			// So set the name variable equal to the newname
    		name = line;
    		type = "";
    		lengthS = "";
    		requiredS = "";
    	}else if (name.size()){
    		// it no name but something else
    		if(line[1] == 't'){
    			type = line.substr(3);
    		}else if(line[1] == 'l'){
    			lengthS = line.substr(3);
    		}else if(line[1] == 'r'){
    			requiredS = line.substr(3);
    		}
    		else {
    			std::cout << "Line " << linecount << " in form file has syntax ':letter:...', only valid letters are t, l and r." << std::endl;
    		}

    		make = true;
    	}
    	else {
    		std::cout << "':letter:' field at line " << linecount << " in form file is not preceded by a name for the field." << std::endl;
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
	}
	else if (name.size()) {
		std::cout << "Field " << name << " has no component specified." << std::endl;
	}
	return true;
}

Component* Form::getComponent(std::string type){
	for(unsigned int i = 0;i < this->components.size();i++){
		if(components.at(i).getType() == type){
			return &(components.at(i));
		}
	}

	return NULL;
}

void Form::readComponents(std::string file, std::vector<std::string>& comps) {
	const char *filename = file.c_str();

	std::ifstream stream(filename);
	std::string line;
    while(std::getline(stream, line))
    	if (line.substr(0,3) == ":t:")
    		comps.push_back(line.substr(3));


}

Form::~Form() {
	// TODO Auto-generated destructor stub
}

} /* namespace FA */
