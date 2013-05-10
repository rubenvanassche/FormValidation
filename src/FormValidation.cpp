#include "Form.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
	FA::Form form("Test Form");

	if(form.addComponents("components.txt") == false){
		std::cout << "bla";
	}

	/*
	if(form.add("Naam", "Name", true) == false){
		std::cout << "blaname";
	}

	if(form.add("Email", "Email", true) == false){
		std::cout << "blaemail";
	}*/

	form.load("form.txt");

	form.build();

}
