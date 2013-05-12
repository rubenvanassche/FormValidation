#include "Form.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
	FA::Form form("Test Form");

	if(form.addComponents("components.txt") == false){
		std::cout << "No components.txt file";
	}

	if(argc == 1){
		form.load("form.txt");
	}else if(argc == 2){
		std::cout << argv[1] << " geladen." << std::endl;
		form.load(argv[1]);
	}else{
		std::cout << "form [formfile.txt]";
	}

	form.build();

}
