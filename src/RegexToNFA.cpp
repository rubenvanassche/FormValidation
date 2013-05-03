
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
	startState *q0 = 0;
	acceptingStates F;
	std::string::iterator regexit = regEx.begin();
	while (regexit != regEx.end()) {
		if (*regexit != '(' && *regexit != ')' && *regexit != '+' && *regexit != '.' && *regexit != '*'
			&& sigma.find((char)*regexit) == sigma.end())
			sigma.insert((char)*regexit);
		regexit++;
	}
	q0 = regexToNFAInternal(regEx, Q, delta, F, 0);

	return new eNFA(sigma, Q, delta, q0, F);

}

state* regexToNFAInternal(regex regEx, states& Q, transitions& delta, acceptingStates& F, bool recursion) {
	std::string::iterator regexit = regEx.begin();
	bool upcomingConcat = 0;
	bool upcomingKleene = 0;
	static int stateCount;
	if (!recursion)
		stateCount = 0;
	startState *q0 = 0;
	states Qa;
	transitions deltaa;
	state* q0a;
	acceptingStates Fa;
	states Qb;
	transitions deltab;
	state* q0b;
	acceptingStates Fb;

	//std::cout << *regexit << std::endl;
	char char1;
	char char2;
	char regExOperator;
	while (regexit != regEx.end()) {
		if (*regexit != '(' && *regexit != ')' && *regexit != '+' && *regexit != '.' && *regexit != '*' && !upcomingConcat) {
			char1 = (char) *regexit;
			regexit++;
		}
		else if (*regexit == '(') {
			std::stringstream subRegExStream;
			regex subRegEx;
			regexit++;
			int brackets = 0;
			while (!brackets && *regexit != ')') {
				if (*regexit == '(')
					brackets++;
				if (*regexit == ')')
					brackets--;
				subRegExStream << *regexit;
				//std::cout << *regexit << std::endl;
				regexit++;
			}
			regexit++;
			//std::cout << *regexit << std::endl;
			subRegEx = subRegExStream.str();
			//std::cout << subRegExStream.str() << std::endl;
			//std::cin >> char1;
			//std::cout << subRegEx << std::endl;
			q0a = regexToNFAInternal(subRegEx, Qa, deltaa, Fa);
		}
		else
			char1 = (char) 0;
		if (regexit != regEx.end() ) {
			if ((*regexit != '+' && *regexit != '.' && *regexit != '*') || upcomingConcat)
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
			q0 = generateKleene(char1, Q, delta, stateCount, q0, Qa, deltaa, q0a, Fa);
		else if (*regexit == '(') {
			std::stringstream subRegExStream;
			regex subRegEx;
			regexit++;
			int brackets = 0;
			while (!brackets && *regexit != ')') {
				if (*regexit == '(')
					brackets++;
				if (*regexit == ')')
					brackets--;
				subRegExStream << *regexit;
				regexit++;
			}
			regexit++;
			subRegEx = subRegExStream.str();
			q0b = regexToNFAInternal(subRegEx, Qb, deltab, Fb);


		}
		else
			char2 = (char) *regexit;
		if (regExOperator == '+')
			q0 = generateOr(char1, char2, Q, delta, stateCount, q0, upcomingKleene, Qa, deltaa, q0a, Fa, Qb, deltab, q0b, Fb);
		else if (regExOperator == '.') {
			state* q0temp = generateConcatenation(char1, char2, Q, delta, stateCount, q0, upcomingKleene, Qa, deltaa, q0a, Fa, Qb, deltab, q0b, Fb);
			if (q0temp)
				q0 = q0temp;
		}
		if (upcomingKleene)
			regexit++;
		upcomingKleene = 0;
		if (regexit != regEx.end())
			regexit++;
		if (*regexit != '(' && *regexit != ')' && *regexit != '+' && *regexit != '.' && *regexit != '*')
			upcomingConcat = 1;


	}
	F.insert(Q[Q.size() - 1]); //Change?
	//std::cout << *(F.begin()) << std::endl;
	return q0;

}


state* generateOr(char char1, char char2, states& Q, transitions& delta, int& stateCount, state* q0, bool kleene,
		states& Qa, transitions& deltaa, state* q0a, acceptingStates& Fa,
		states& Qb, transitions& deltab, state* q0b, acceptingStates& Fb) {
	if (Qa.size()) {
		states::iterator stateit = Qa.begin();
		while (stateit != Qa.end()) {
			Q.push_back(*stateit);
			stateit++;
		}
		transitions::iterator transit = deltaa.begin();
		while (transit != deltaa.end()) {
			delta.insert(*transit);
			transit++;
		}
	}
	if (Qb.size()) {
		states::iterator stateit = Qb.begin();
		while (stateit != Qb.end()) {
			Q.push_back(*stateit);
			stateit++;
		}
		transitions::iterator transit = deltab.begin();
		while (transit != deltab.end()) {
			delta.insert(*transit);
			transit++;
		}
	}
	if (kleene)
		generateKleene(char2, Q, delta, stateCount, q0, Qb, deltab, q0b, Fb);
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
		if (Qa.size()) {
			targetStates.push_back(q0a);
			deltaInt[0] = targetStates;
			targetStates.clear();
			delta[Q[size - 5]] = deltaInt;
			deltaInt.clear();
			targetStates.push_back(Q[size - 3]);
			deltaInt[0] = targetStates;
			targetStates.clear();
			delta[(*Fa.begin())] = deltaInt;
			deltaInt.clear();
		}
		else if (char1 != 0) {
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
		if (Qb.size()) {
			targetStates.push_back(q0b);
			deltaInt[0] = targetStates;
			targetStates.clear();
			delta[Q[size - 4]] = deltaInt;
			deltaInt.clear();
			targetStates.push_back(Q[size - 2]);
			deltaInt[0] = targetStates;
			targetStates.clear();
			delta[(*Fb.begin())] = deltaInt;
			deltaInt.clear();
		}
		else if (kleene) {
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

state* generateConcatenation(char char1, char char2, states& Q, transitions& delta, int& stateCount, state* q0, bool kleene,
							 states& Qa, transitions& deltaa, state* q0a, acceptingStates& Fa,
							 states& Qb, transitions& deltab, state* q0b, acceptingStates& Fb) {
	if (Qa.size()) {
		states::iterator stateit = Qa.begin();
		while (stateit != Qa.end()) {
			Q.push_back(*stateit);
			stateit++;
		}
		transitions::iterator transit = deltaa.begin();
		while (transit != deltaa.end()) {
			delta.insert(*transit);
			transit++;
		}
	}
	if (Qb.size()) {
		states::iterator stateit = Qb.begin();
		while (stateit != Qb.end()) {
			Q.push_back(*stateit);
			stateit++;
		}
		transitions::iterator transit = deltab.begin();
		while (transit != deltab.end()) {
			delta.insert(*transit);
			transit++;
		}
	}
	if (kleene) {
		states Qtemp;
		transitions deltatemp;
		state *q0temp = 0;
		acceptingStates Ftemp;
		generateKleene(char2, Q, delta, stateCount, q0, Qtemp, deltatemp, q0temp, Ftemp);
	}
	transitionsInternal deltaInt;
	for (int i=0; i < 4; i++) {
		Q.push_back(new state(static_cast<std::ostringstream*>( &(std::ostringstream() << stateCount) )->str()));
		stateCount++;
	}
	int size = Q.size();
	stateset targetStates;
	if (Qa.size()) {
		targetStates.push_back(q0a);
		deltaInt[0] = targetStates;
		targetStates.clear();
		delta[Q[size - 4]] = deltaInt;
		deltaInt.clear();
		targetStates.push_back(Q[size - 3]);
		deltaInt[0] = targetStates;
		targetStates.clear();
		delta[(*Fa.begin())] = deltaInt;
		deltaInt.clear();
	}

	else if (char1) {
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
	if (Qb.size()) {
		targetStates.push_back(q0b);
		deltaInt[0] = targetStates;
		targetStates.clear();
		delta[Q[size - 2]] = deltaInt;
		deltaInt.clear();
		targetStates.push_back(Q[size - 1]);
		deltaInt[0] = targetStates;
		targetStates.clear();
		delta[(*Fb.begin())] = deltaInt;
		deltaInt.clear();
	}
	else if (kleene) {
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

state* generateKleene(char char1, states& Q, transitions& delta, int& stateCount, state* q0,
		              states& Qa, transitions& deltaa, state* q0a, acceptingStates& Fa) {
	if (Qa.size()) {
		states::iterator stateit = Qa.begin();
		while (stateit != Qa.end()) {
			Q.push_back(*stateit);
			stateit++;
		}
		transitions::iterator transit = deltaa.begin();
		while (transit != deltaa.end()) {
			delta.insert(*transit);
			transit++;
		}
	}
	transitionsInternal deltaInt;
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
	if (Qa.size()) {
		targetStates.push_back(q0a);
		deltaInt[0] = targetStates;
		targetStates.clear();
		delta[Q[size - 3]] = deltaInt;
		deltaInt.clear();
		targetStates.push_back(Q[size-2]);
		deltaInt[0] = targetStates;
		targetStates.clear();
		delta[(*Fa.begin())] = deltaInt;
		deltaInt.clear();
	}
	else {
		targetStates.push_back(Q[size -2]);
		deltaInt[char1] = targetStates;
		targetStates.clear();
		delta[Q[size - 3]] = deltaInt;
		deltaInt.clear();
	}
	targetStates.push_back(Q[size -1]);
	targetStates.push_back(Q[size -3]);
	deltaInt[0] = targetStates;
	targetStates.clear();
	delta[Q[size - 2]] = deltaInt;
	deltaInt.clear();
	delta[Q[size - 1]] = deltaInt;
	if (!q0)
		return Q[size - 4];
	else
		return q0;
}

}
