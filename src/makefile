all: FA

FA: common.o FormValidation.o eNFA.o RegexToNFA.o DFA.o SubsetConstruction.o Component.o Field.o Form.o Test.o FormTest.o
	g++ -pedantic -Wall  FormValidation.o eNFA.o RegexToNFA.o DFA.o SubsetConstruction.o Component.o Field.o Form.o Test.o FormTest.o -o FA

FormValidation.o: FormValidation.cpp
	g++ -c -pedantic -Wall  FormValidation.cpp

eNFA.o: eNFA.cpp
	g++ -c -pedantic -Wall  eNFA.cpp

RegexToNFA.o: RegexToNFA.cpp
	g++ -c -pedantic -Wall  RegexToNFA.cpp

common.o: common.h
	g++ -c -pedantic -Wall  common.h

DFA.o: DFA.cpp
	g++ -c -pedantic -Wall  DFA.cpp

SubsetConstruction.o: SubsetConstruction.cpp
	g++ -c -pedantic -Wall  SubsetConstruction.cpp

Component.o: Component.cpp
	g++ -c -pedantic -Wall  Component.cpp

Field.o: Field.cpp
	g++ -c -pedantic -Wall  Field.cpp

Form.o: Form.cpp
	g++ -c -pedantic -Wall  Form.cpp

FormTest.o: FormTest.cpp
	g++ -c -pedantic -Wall  FormTest.cpp

Test.o: Test.cpp
	g++ -c -pedantic -Wall Test.cpp

clean:
	rm -rf *o FA




