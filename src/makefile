all: FA

FA: common.o FormValidation.o RegexToNFA.o eNFA.o
	g++ FormValidation.o RegexToNFA.o eNFA.o -o FA

FormValidation.o: FormValidation.cpp
	g++ -c FormValidation.cpp

RegexToNFA.o: RegexToNFA.cpp
	g++ -c RegexToNFA.cpp RegexToNFA.h

eNFA.o: eNFA.cpp
	g++ -c eNFA.cpp eNFA.h

common.o: common.h
	g++ -c common.h

clean:
	rm -rf *o FA


