all: FA

FA: common.o FormValidation.o eNFA.o RegexToNFA.o DFA.o SubsetConstruction.o 
	g++ FormValidation.o eNFA.o RegexToNFA.o DFA.o SubsetConstruction.o  -o FA

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

clean:
	rm -rf *o FA


