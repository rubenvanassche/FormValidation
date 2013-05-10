
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
	state *q0 = 0;
	acceptingStates F;
	bool hasEpsilon = false;                   //is epsilon part of the regex?
	std::string::iterator regexit = regEx.begin();
	while (regexit != regEx.end()) {            //generate alphabet
		if (*regexit != '(' && *regexit != ')' && *regexit != '+' && *regexit != '*' && *regexit != '<'
			&& sigma.find((char)*regexit) == sigma.end())
			sigma.insert((char)*regexit);
		else if (*regexit == '<')
			hasEpsilon = true;
		regexit++;
	}
	q0 = regexToNFAInternal(regEx, Q, delta, F, 0);      //generate other four parts of the eNFA

	if (hasEpsilon) {    //Replaces all '<' with epsilon
		transitions::iterator transit = delta.begin();
		while (transit != delta.end()) {
			transitionsInternal::iterator transintit = transit->second.find('<');
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
	if (!recursion)         //Start counting states back from 0 if new regex
		stateCount = 0;
	state *q0 = 0;
	states Qa;        //Separate Q, delta, q0 and F for left and right parts of + or . if they're more than one char
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
		if (*regexit != '(' && *regexit != ')' && *regexit != '+' && *regexit != '*' && !upcomingConcat) {
			char1 = (char) *regexit;    //Not a special sign, so a character part of the alphabet
			regexit++;
		}
		else if (*regexit == '(') {
			std::stringstream subRegExStream;
			regex subRegEx;
			regexit++;
			int brackets = 0;
			while (brackets || *regexit != ')') {     //get sub-regular expression between brackets
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
			q0a = regexToNFAInternal(subRegEx, Qa, deltaa, Fa);     //generate eNFA (apart from alphabet) with subregex
		}
		else
			char1 = (char) 0;      //Left side of +.* is not a char
		if (regexit != regEx.end() ) {
			if ((*regexit != '+' && *regexit != '*') || upcomingConcat)
				regExOperator = '.';      //If previous loop noticed a following concatenation
			else {
				regExOperator = (char) *regexit;
				if (*regexit != '*')
					regexit++;
			}
		}
		upcomingConcat = 0;
		if (regExOperator == '*')       //Generate kleene closure for either char1 or the regex in the 4 final args
			q0 = generateKleene(char1, Q, delta, stateCount, q0, Qa, deltaa, q0a, Fa);
		else if (*regexit == '(') {
			std::stringstream subRegExStream;
			regex subRegEx;
			regexit++;
			int brackets = 0;
			while (brackets || *regexit != ')') {  //Get subregex
				if (*regexit == '(')
					brackets++;
				if (*regexit == ')')
					brackets--;
				subRegExStream << *regexit;
				regexit++;
			}
			regexit++;
			upcomingKleene = (*regexit == '*');    //Generate kleene closure of right side of +.?
			subRegEx = subRegExStream.str();
			q0b = regexToNFAInternal(subRegEx, Qb, deltab, Fb);


		}
		else {
			char2 = (char) *regexit;    //get second char
			upcomingKleene =  (*(regexit+1) == '*');
		}

		//std::cout << upcomingKleene << std::endl;
		if (regExOperator == '+')
			q0 = generateOr(char1, char2, Q, delta, stateCount, q0, upcomingKleene, Qa, deltaa, q0a, Fa, Qb, deltab, q0b, Fb);
		else if (regExOperator == '.') {
			state* q0temp = generateConcatenation(char1, char2, Q, delta, stateCount, q0, upcomingKleene, Qa, deltaa, q0a, Fa, Qb, deltab, q0b, Fb);
			if (q0temp)       //may return 0, in which case q0 doesn't change
				q0 = q0temp;
		}
		if (upcomingKleene)  //skip 1 character to account for * already applied
			regexit++;
		upcomingKleene = 0;

		if (regexit != regEx.end())
			regexit++;
		//std::cout << regEx << " " << *regexit << " " << (regexit == regEx.end()) << std::endl;
		if (*regexit != ')' && *regexit != '+' && *regexit != '*')
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
	if (Qa.size()) {                           //add states/transitions of left side subregex to main Q/delta
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

	if (kleene) //apply kleene closure to right side
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
	for (int i=0; i < 6; i++) {       //6 new states for OR
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
		if (Qa.size()) {     //insert subregex's partial eNFA into "top" part of new partial eNFA
			targetStates.push_back(q0a);   //beginning of subregex's partial eNFA
			deltaInt[0] = targetStates;
			targetStates.clear();
			delta[Q[size - 5]] = deltaInt;
			deltaInt.clear();
			targetStates.push_back(Q[size - 3]);
			deltaInt[0] = targetStates;
			targetStates.clear();
			delta[(*Fa.begin())] = deltaInt;      //ending of subregex's partial eNFA (Fa.size() is always 1)
			deltaInt.clear();
		}
		else if (char1 != 0) {           //regular "a+b" style partial eNFA
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
		if (Qb.size()) {     //Insert subregex's partial eNFA into "bottom" of new partial eNFA
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
		else if (kleene) {                         //Account for extra new states if kleene closure was generated
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
		else {                              //regular partial eNFA
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
	//Fairly analogous to generateOr
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
			//std::cout << "Copying delta for " << *(transit->first) << std::endl;
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
			//std::cout << *(*Fb.begin()) << std::endl;
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
	//Internal: called from generateOr/Concat
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
