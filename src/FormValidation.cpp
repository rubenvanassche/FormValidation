#include "Form.h"
#include <iostream>
#include <string>
#include <cstring>
#include "Test.h"
#include "FormTest.h"

int main(int argc, char* argv[]) {
	FA::Form form("Test Form");

	if(form.addComponents("components.txt") == false){
		std::cout << "No components.txt file";
	}

	if(argc == 1){
		form.load("form.txt");
	}else if(!std::strcmp(argv[1], "test")) {
		FA::Test tester("Regex");
		tester.runAllTests();
		FormTest();
		FieldTest();
		ComponentTest();
	}else if(argc == 2){
		std::cout << argv[1] << " geladen." << std::endl;
		form.load(argv[1]);
	}else{
		std::cout << "form [formfile.txt]";
	}
	if (argc == 1 || std::strcmp(argv[1], "test"))
		form.build();

}
