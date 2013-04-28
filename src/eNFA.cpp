/*
 * eNFA.cpp
 *
 *  Created on: Apr 28, 2013
 *      Author: jakob
 */

#include "eNFA.h"

namespace FA {

eNFA::eNFA(alphabet alphabet_, states states_, transitions transitions_,startState* start_, acceptingStates accepting_) :
			sigma(alphabet_), Q(states_), delta(transitions_), q0(start_), F(accepting_) {}

bool eNFA::process(std::string str) const {
	std::string::iterator inputit = str.begin();
	std::vector<state*> currentStates;
	std::vector<state*> oldStates;
	currentStates.push_back(q0);
	while (inputit != str.end()) {
		oldStates = currentStates;
		currentStates.clear();
		std::vector<state*>::iterator stateit = oldStates.begin();
		while (stateit != oldStates.end()) {
			transitionsInternal theseTransitions = delta.find(*stateit)->second;
			std::map<symbol, state*>::iterator transit = theseTransitions.begin();
			while (transit != theseTransitions.end()) {

				if (transit->first == *inputit || transit->first == 0)
					if (std::find(currentStates.begin(), currentStates.end(), transit->second) == currentStates.end())
					currentStates.push_back(transit->second);
				transit++;
			}
			stateit++;
		}
		inputit++;
	}

	std::vector<state*>::iterator stateit = currentStates.begin();
	int size = currentStates.size();
	for(int i=0; i < size; i++) {
		transitionsInternal theseTransitions = delta.find(*stateit)->second;
		std::map<symbol, state*>::iterator transit = theseTransitions.begin();
		while (transit != theseTransitions.end()) {

			if (transit->first == 0)
				currentStates.push_back(transit->second);
			transit++;
		}
		stateit++;
	}

	stateit = currentStates.begin();
	while (stateit != currentStates.end()) {
		if (F.find(*stateit) != F.end())
			return true;
		stateit++;
	}
	return false;
}



}
