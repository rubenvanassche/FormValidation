#include "Form.h"
#include <iostream>
#include <string>
#include <cstring>
#include "Test.h"

int main(int argc, char* argv[]) {
	FA::Form form("Test Form");

	if(form.addComponents("components.txt") == false){
		std::cout << "No components.txt file";
	}

	if(argc == 1){
		form.load("form.txt");
	}else if(!std::strcmp(argv[1], "test")) {
		FA::Test tester("Test");
		tester.runAllTests();
	}else if(argc == 2){
		std::cout << argv[1] << " geladen." << std::endl;
		form.load(argv[1]);
	}else{
		std::cout << "form [formfile.txt]";
	}
	if (argc == 1 || std::strcmp(argv[1], "test"))
		form.build();

}
