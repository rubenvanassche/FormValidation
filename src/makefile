all: FA

FA: common.o FormValidation.o eNFA.o RegexToNFA.o DFA.o SubsetConstruction.o Component.o Field.o Form.o
	g++ FormValidation.o eNFA.o RegexToNFA.o DFA.o SubsetConstruction.o Component.o Field.o Form.o  -o FA

FormValidation.o: FormValidation.cpp
	g++ -c FormValidation.cpp

eNFA.o: eNFA.cpp
	g++ -c eNFA.cpp

RegexToNFA.o: RegexToNFA.cpp
	g++ -c RegexToNFA.cpp

common.o: common.h
	g++ -c common.h

DFA.o: DFA.cpp
	g++ -c DFA.cpp

SubsetConstruction.o: SubsetConstruction.cpp
	g++ -c SubsetConstruction.cpp

Component.o: Component.cpp
	g++ -c Component.cpp

Field.o: Field.cpp
	g++ -c Field.cpp

Form.o: Form.cpp
	g++ -c Form.cpp

clean:
	rm -rf *o FA


