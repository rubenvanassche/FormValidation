#include "Form.h"
#include <iostream>
#include <string>
#include <cstring>
#include "Test.h"
#include "FormTest.h"
#include "DFATest.h"

int main(int argc, char* argv[]) {
	FA::Form form("Test Form");
	std::vector<std::string> usedComponents;

	if(argc == 1){
		form.readComponents("form.txt", usedComponents);
		if(form.addComponents("components.txt", usedComponents) == false)
			std::cout << "No components.txt file";
		form.load("form.txt");
	}else if(!std::strcmp(argv[1], "test")) {
		FormTest();
		FieldTest();
		ComponentTest();
		stringControlTest();
		subsetConstructionTest();
		FA::Test tester("Regex");
		tester.runAllTests();
	}else if(argc == 2){
		form.readComponents(argv[1], usedComponents);
		if(form.addComponents("components.txt", usedComponents) == false)
			std::cout << "No components.txt file";
		std::cout << argv[1] << " geladen." << std::endl;
		form.load(argv[1]);
	}else{
		std::cout << "form [formfile.txt]";
	}
	if (argc == 1 || std::strcmp(argv[1], "test"))
		form.build();


}
