
/*
 * regexToNFA.cpp
 *
 *  Created on: Apr 28, 2013
 *      Author: jakob
 */

#include "RegexToNFA.h"
namespace FA {

eNFA* regexToNFA(regex regEx, bool recursion) {
	alphabet sigma;
	states Q;
	transitions delta;
	transitionsInternal deltaInt;
	startState *q0 = 0;
	acceptingStates F;
	std::string::iterator regexit = regEx.begin();
	bool upcomingConcat = 0;
	bool upcomingKleene = 0;
	static int stateCount = 0;
	if (!recursion) {
		stateCount = 0;
	}
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
		if (*regexit != '(' && *regexit != ')' && *regexit != '+' && *regexit != '.' && *regexit != '*' && !upcomingConcat) {
			char1 = (char) *regexit;
			regexit++;
		}
		else
			char1 = (char) 0;
		if (regexit != regEx.end() ) {
			if ((*regexit != '(' && *regexit != ')' && *regexit != '+' && *regexit != '.' && *regexit != '*') || upcomingConcat)
				regExOperator = '.';
			else {
				regExOperator = (char) *regexit;
				if (*regexit != '*')
					regexit++;
			}
		}
		upcomingConcat = 0;
		upcomingKleene =  (*(regexit+1) == '*');
		if (regExOperator == '*')
			q0 = generateKleene(char1, Q, delta, stateCount, q0);
		else
			char2 = (char) *regexit;
		if (regExOperator == '+')
			q0 = generateOr(char1, char2, Q, delta, stateCount, q0, upcomingKleene);
		else if (regExOperator == '.') {
			state* q0temp = generateConcatenation(char1, char2, Q, delta, stateCount, q0, upcomingKleene);
			if (q0temp)
				q0 = q0temp;
		}
		if (upcomingKleene)
			regexit++;
		upcomingKleene = 0;
		regexit++;
		if (*regexit != '(' && *regexit != ')' && *regexit != '+' && *regexit != '.' && *regexit != '*')
			upcomingConcat = 1;


	}
	F.insert(Q[Q.size() - 1]); //Change?
	//std::cout << *(F.begin()) << std::endl;

	return new eNFA(sigma, Q, delta, q0, F);

}


state* generateOr(char char1, char char2, states& Q, transitions& delta, int& stateCount, state* q0, bool kleene) {
	if (kleene)
		generateKleene(char2, Q, delta, stateCount, q0);
	transitionsInternal deltaInt;
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
		if (char1 != 0) {
			targetStates.push_back(Q[size - 3]);
			deltaInt[char1] = targetStates;
			targetStates.clear();
			delta[Q[size - 5]] = deltaInt;
			deltaInt.clear();
		}
		else {
			targetStates.push_back(q0);
			deltaInt[0] = targetStates;
			targetStates.clear();
			delta[Q[size - 5]] = deltaInt;
			deltaInt.clear();
			targetStates.push_back(Q[size - 3]);
			deltaInt[0] = targetStates;
			targetStates.clear();
			if (kleene)
				delta[Q[size - 11]] = deltaInt;
			else
				delta[Q[size - 7]] = deltaInt;
			deltaInt.clear();

		}
		if (kleene) {
			targetStates.push_back(Q[size - 10]);
			deltaInt[0] = targetStates;
			targetStates.clear();
			delta[Q[size - 4]] = deltaInt;
			deltaInt.clear();
			targetStates.push_back(Q[size - 2]);
			deltaInt[0] = targetStates;
			targetStates.clear();
			delta[Q[size - 7]] = deltaInt;
			deltaInt.clear();
		}
		else {
			targetStates.push_back(Q[size - 2]);
			deltaInt[char2] = targetStates;
			targetStates.clear();
			delta[Q[size - 4]] = deltaInt;
			deltaInt.clear();
		}
		targetStates.push_back(Q[size - 1]);
		deltaInt[0] = targetStates;
		targetStates.clear();
		delta[Q[size - 3]] = deltaInt;
		delta[Q[size - 2]] = deltaInt;
		deltaInt.clear();
		delta[Q[size - 1]] = deltaInt;
		return Q[size-6];

}

state* generateConcatenation(char char1, char char2, states& Q, transitions& delta, int& stateCount, state* q0, bool kleene) {
	if (kleene)
		generateKleene(char2, Q, delta, stateCount, q0);
	transitionsInternal deltaInt;
	for (int i=0; i < 4; i++) {
		Q.push_back(new state(static_cast<std::ostringstream*>( &(std::ostringstream() << stateCount) )->str()));
		stateCount++;
	}
	int size = Q.size();
	stateset targetStates;
	if (char1) {
		targetStates.push_back(Q[size -3]);
		deltaInt[char1] = targetStates;
		targetStates.clear();
		delta[Q[size - 4]] = deltaInt;
		deltaInt.clear();
	}
	else {
		targetStates.push_back(q0);
		deltaInt[char1] = targetStates;
		targetStates.clear();
		delta[Q[size - 4]] = deltaInt;
		deltaInt.clear();
		targetStates.push_back(Q[size -3]);
		deltaInt[char1] = targetStates;
		targetStates.clear();
		delta[Q[size - 5]] = deltaInt;
		deltaInt.clear();

	}
	targetStates.push_back(Q[size -2]);
	deltaInt[0] = targetStates;
	targetStates.clear();
	delta[Q[size - 3]] = deltaInt;
	deltaInt.clear();
	if (kleene) {
		targetStates.push_back(Q[size - 8]);
		deltaInt[0] = targetStates;
		targetStates.clear();
		delta[Q[size - 2]] = deltaInt;
		deltaInt.clear();
		targetStates.push_back(Q[size - 1]);
		deltaInt[0] = targetStates;
		targetStates.clear();
		delta[Q[size - 5]] = deltaInt;
		deltaInt.clear();
	}
	else {
		targetStates.push_back(Q[size -1]);
		deltaInt[char2] = targetStates;
		targetStates.clear();
		delta[Q[size - 2]] = deltaInt;
		deltaInt.clear();
	}
	delta[Q[size - 1]] = deltaInt;
	if (char1)
		return Q[size-4];
	else
	return 0;

}

state* generateKleene(char char1, states& Q, transitions& delta, int& stateCount, state* q0) {
	transitionsInternal deltaInt;
	if (char1 != 0) {
		for (int i=0; i < 4; i++) {
			Q.push_back(new state(static_cast<std::ostringstream*>( &(std::ostringstream() << stateCount) )->str()));
			stateCount++;
		}
		int size = Q.size();
		stateset targetStates;
		targetStates.push_back(Q[size -1]);
		targetStates.push_back(Q[size -3]);
		deltaInt[0] = targetStates;
		targetStates.clear();
		delta[Q[size - 4]] = deltaInt;
		deltaInt.clear();
		targetStates.push_back(Q[size -2]);
		deltaInt[char1] = targetStates;
		targetStates.clear();
		delta[Q[size - 3]] = deltaInt;
		deltaInt.clear();
		targetStates.push_back(Q[size -1]);
		targetStates.push_back(Q[size -3]);
		deltaInt[0] = targetStates;
		targetStates.clear();
		delta[Q[size - 2]] = deltaInt;
		deltaInt.clear();
		delta[Q[size - 1]] = deltaInt;
	}
	if (!q0)
		return Q[0];
	else
		return q0;
}

}
