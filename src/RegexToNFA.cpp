
/*
 * regexToNFA.cpp
 *
 *  Created on: Apr 28, 2013
 *      Author: jakob
 */

#include "RegexToNFA.h"
namespace FA {

eNFA* regexToNFA(regex regEx) {
	alphabet sigma;
	states Q;
	transitions delta;
	transitionsInternal deltaInt;
	startState *q0;
	acceptingStates F;
	std::string::iterator regexit = regEx.begin();
	static int stateCount = 0;
		while (regexit != regEx.end()) {
			if (*regexit != '(' && *regexit != ')' && *regexit != '+' && *regexit != '.' && *regexit != '*'
				&& sigma.find((char)*regexit) == sigma.end())
				sigma.insert((char)*regexit);
			regexit++;
		}
	regexit = regEx.begin();
	char char1;
	char char2;
	char regExOperator;
	while (regexit != regEx.end()) {
		if (*regexit != '(' && *regexit != ')' && *regexit != '+' && *regexit != '.' && *regexit != '*') {
			char1 = (char) *regexit;
			regexit++;
		}
		else
			char1 = (char) 0;
		if (regexit != regEx.end() ) {
			if (*regexit != '(' && *regexit != ')' && *regexit != '+' && *regexit != '.' && *regexit != '*')
				regExOperator = '.';
			else {
				regExOperator = (char) *regexit;
				if (*regexit != '*')
					regexit++;
			}
		}
		if (regExOperator == '*')
			/*generateKleene()*/;
		else
			char2 = (char) *regexit;
		if (regExOperator == '+')
			generateOr(char1, char2, Q, delta, stateCount);
		else if (regExOperator == '.')
			/*generateConcatenation()*/;
		regexit++;


	}
	q0 = Q[0];
	F.insert(Q[Q.size() - 1]); //Change?
	//std::cout << *(F.begin()) << std::endl;

	return new eNFA(sigma, Q, delta, q0, F);

}


void generateOr(char char1, char char2, states& Q, transitions& delta, int& stateCount) {
	transitionsInternal deltaInt;
	if (char1 != 0) {
		for (int i=0; i < 6; i++) {
			Q.push_back(new state(static_cast<std::ostringstream*>( &(std::ostringstream() << stateCount) )->str()));
			stateCount++;
		}
		int size = Q.size();
		stateset targetStates;
		targetStates.push_back(Q[size -5]);
		targetStates.push_back(Q[size -4]);
		deltaInt[0] = targetStates;
		targetStates.clear();
		delta[Q[size - 6]] = deltaInt;
		deltaInt.clear();
		targetStates.push_back(Q[size - 3]);
		deltaInt[char1] = targetStates;
		targetStates.clear();
		delta[Q[size - 5]] = deltaInt;
		deltaInt.clear();
		targetStates.push_back(Q[size - 2]);
		deltaInt[char2] = targetStates;
		targetStates.clear();
		delta[Q[size - 4]] = deltaInt;
		deltaInt.clear();
		targetStates.push_back(Q[size - 1]);
		deltaInt[0] = targetStates;
		targetStates.clear();
		delta[Q[size - 3]] = deltaInt;
		delta[Q[size - 2]] = deltaInt;
		deltaInt.clear();
		delta[Q[size - 1]] = deltaInt;




	}
}


}
