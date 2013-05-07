
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
	bool hasEpsilon = false;
	std::string::iterator regexit = regEx.begin();
	while (regexit != regEx.end()) {
		if (*regexit != '(' && *regexit != ')' && *regexit != '+' && *regexit != '.' && *regexit != '*' && *regexit != '_'
			&& sigma.find((char)*regexit) == sigma.end())
			sigma.insert((char)*regexit);
		else if (*regexit == '_')
			hasEpsilon = true;
		regexit++;
	}
	q0 = regexToNFAInternal(regEx, Q, delta, F, 0);

	if (hasEpsilon) {    //Replaces all '_' with epsilon
		transitions::iterator transit = delta.begin();
		while (transit != delta.end()) {
			transitionsInternal::iterator transintit = transit->second.find('_');
			if (transintit != transit->second.end()) {
				std::swap(transit->second[0], transintit->second);
				transit->second.erase(transintit);
			}
			transit++;
		}
	}

	return new eNFA(sigma, Q, delta, q0, F);

}

state* regexToNFAInternal(regex regEx, states& Q, transitions& delta, acceptingStates& F, bool recursion) {
	//std::cout << "RegEx: "<< regEx << std::endl;
	//int testint;
	//std::cin >> testint;
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
		//if (!recursion)
			//std::cout << "Letter " << *regexit << std::endl;
		if (*regexit != '(' && *regexit != ')' && *regexit != '+' && *regexit != '.' && *regexit != '*' && !upcomingConcat) {
			char1 = (char) *regexit;
			regexit++;
		}
		else if (*regexit == '(') {
			std::stringstream subRegExStream;
			regex subRegEx;
			regexit++;
			int brackets = 0;
			while (brackets || *regexit != ')') {
				if (*regexit == '(')
					brackets++;
				else if (*regexit == ')')
					brackets--;
				subRegExStream << *regexit;
				//std::cout << brackets << " "<<  subRegExStream.str() << std::endl;
				//int testint;
				//std::cin >> testint;
				regexit++;
			}
			regexit++;
			//std::cout << *regexit << std::endl;
			subRegEx = subRegExStream.str();
			//if (subRegEx == "(")
				//std::cout << "A WRONG";
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
		if (regExOperator == '*') {
			//std::cout << "KLEENE: " << regEx << std::endl;
			q0 = generateKleene(char1, Q, delta, stateCount, q0, Qa, deltaa, q0a, Fa);
		}
		else if (*regexit == '(') {
			std::stringstream subRegExStream;
			regex subRegEx;
			regexit++;
			int brackets = 0;
			while (brackets || *regexit != ')') {
				if (*regexit == '(')
					brackets++;
				if (*regexit == ')')
					brackets--;
				subRegExStream << *regexit;
				regexit++;
			}
			regexit++;
			upcomingKleene = (*regexit == '*');
			subRegEx = subRegExStream.str();
			q0b = regexToNFAInternal(subRegEx, Qb, deltab, Fb);


		}
		else {
			char2 = (char) *regexit;
			upcomingKleene =  (*(regexit+1) == '*');
		}

		//std::cout << upcomingKleene << std::endl;
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
		//std::cout << regEx << " " << *regexit << " " << (regexit == regEx.end()) << std::endl;
		if (*regexit != ')' && *regexit != '+' && *regexit != '.' && *regexit != '*')
			upcomingConcat = 1;


	}
	F.insert(Q[Q.size() - 1]);
	//std::cout << *(F.begin()) << std::endl;
	//std::cout << "Finished " << regEx << std::endl;
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

	if (kleene)
		generateKleene(char2, Q, delta, stateCount, q0, Qb, deltab, q0b, Fb);

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
	if (kleene) {
		states Qtemp;
		transitions deltatemp;
		state *q0temp = 0;
		acceptingStates Ftemp;
		if (char2)
			generateKleene(char2, Q, delta, stateCount, q0, Qtemp, deltatemp, q0temp, Ftemp);
		else {
			q0b = generateKleene(char2, Q, delta, stateCount, q0, Qb, deltab, q0b, Fb, 1);
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
			std::cout << "Copying delta for " << *(transit->first) << std::endl;
			delta.insert(*transit);
			transit++;
		}
	}
	//std::cout << "SIZES " << Qa.size() << " " << Qb.size() << " "<< q0b << std::endl;

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
		if (kleene) {
			targetStates.push_back(q0b);
			deltaInt[0] = targetStates;
			targetStates.clear();
			delta[Q[size - 2]] = deltaInt;
			deltaInt.clear();
			targetStates.push_back(Q[size - 1]);
			deltaInt[0] = targetStates;
			targetStates.clear();
			std::cout << *(*Fb.begin()) << std::endl;
			delta[(*Fb.begin())] = deltaInt;
			deltaInt.clear();
		}
		else {
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
	//if (char1)
		return Q[size-4];
	//else
	//return 0;

}

state* generateKleene(char char1, states& Q, transitions& delta, int& stateCount, state* q0,
		              states& Qa, transitions& deltaa, state* q0a, acceptingStates& Fa, bool internal) {
	std::cout << stateCount << " " << internal << std::endl;
	std::cout << "SIZE" << deltaa.size() << std::endl;
	//if (internal)
		//std::cout << "INTERNAL" << std::endl;
	//std::cout << "Kleene with " << char1 << " " << Qa.size() << std::endl;
	if (!internal) {
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
	}
		for (int i=0; i < 4; i++) {
			Q.push_back(new state(static_cast<std::ostringstream*>( &(std::ostringstream() << stateCount) )->str()));
			stateCount++;
		}


	transitionsInternal deltaInt;
	int size = Q.size();

	stateset targetStates;
	targetStates.push_back(Q[size -1]);
	targetStates.push_back(Q[size -3]);
	deltaInt[0] = targetStates;
	targetStates.clear();
	//if (!internal)
		delta[Q[size - 4]] = deltaInt;
	//else
	//	deltaa[Q[size - 4]] = deltaInt;
	deltaInt.clear();
	if (Qa.size()) {
		targetStates.push_back(q0a);
		deltaInt[0] = targetStates;
		targetStates.clear();
		//if (!internal)
			delta[Q[size - 3]] = deltaInt;
		//else
		//	deltaa[Q[size - 3]] = deltaInt;
		deltaInt.clear();
		targetStates.push_back(Q[size-2]);
		deltaInt[0] = targetStates;
		targetStates.clear();
		//if (!internal)
			delta[(*Fa.begin())] = deltaInt;
		//else
		//	deltaa[(*Fa.begin())] = deltaInt;
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
	std::cout << "27? " << *(Q[size - 1])  << std::endl;
	//if (!internal)
		delta[Q[size - 1]] = deltaInt;
	//else
	//	deltaa[Q[size - 1]] = deltaInt;
	std::cout << "SIZE" << deltaa.size() << std::endl;
	if (internal) {
		Fa.clear();
		Fa.insert(Q[size-1]);
	}
	if (!q0)
		return Q[size - 4];
	else
		return q0;
}

}
