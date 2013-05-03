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
	transitionsInternal initialTransitions = delta.find(q0)->second;
	if (initialTransitions.find((char) 0) != initialTransitions.end()) {
		stateset::iterator stateit = initialTransitions[(char) 0].begin();
		while (stateit != initialTransitions[(char) 0].end()) {
			currentStates.push_back(*stateit);
			stateit++;
		}
		int size = currentStates.size();
		bool moreEpsilon = 1;
		int i = 1;
		//std::cout << "MORE" << i << " " << size << std::endl;
		while (moreEpsilon) {
			moreEpsilon = 0;
			stateit = currentStates.begin() + i;
			for(; i < size; i++) {
				transitionsInternal theseTransitions = delta.find(*stateit)->second;
				std::map<symbol, stateset>::iterator transit = theseTransitions.begin();
				while (transit != theseTransitions.end()) {

					if (transit->first == 0) {
						std::vector<state*>::iterator deltastateit = transit->second.begin();
						while (deltastateit != transit->second.end()) {
							//if (**deltastateit == "7") testbool = 1;
							if (std::find(currentStates.begin(), currentStates.end(), *deltastateit) == currentStates.end()) {
								currentStates.push_back(*deltastateit);
								//transitionsInternal *temp = delta.find(*deltastateit)->second;
								//if ((delta.find(*deltastateit)->second).find((char) 0) != (delta.find(*deltastateit)->second).end())
									//moreEpsilon = 1;
							}
							deltastateit++;
						}
					}
					transit++;
				}
				stateit++;
			}
			i = 1;
			if (size != currentStates.size()) {
				size = currentStates.size();
				moreEpsilon = 1;
			}
			//std::cout << "MORE" << i << " " << size << std::endl;
		}


	}
	/*std::cout << "CURRENTSTATES" << std::endl;
	std::vector<state*>::iterator currentit = currentStates.begin();
	while (currentit != currentStates.end()) {
		std::cout << **(currentit) << std::endl;
		currentit++;
	}
	std::cout << "ENDCURRENTSTATES" << std::endl;*/
	while (inputit != str.end()) {
		oldStates = currentStates;
		currentStates.clear();
		std::vector<state*>::iterator stateit = oldStates.begin();
		while (stateit != oldStates.end()) {
			transitionsInternal theseTransitions = delta.find(*stateit)->second;
			std::map<symbol, stateset>::iterator transit = theseTransitions.begin();
			while (transit != theseTransitions.end()) {

				if (transit->first == *inputit) {
					std::vector<state*>::iterator deltastateit = transit->second.begin();
					while (deltastateit != transit->second.end()) {
						if (std::find(currentStates.begin(), currentStates.end(), *deltastateit) == currentStates.end())
							currentStates.push_back(*deltastateit);
						deltastateit++;
					}
				}
				transit++;
			}
			stateit++;
		}
		stateit = currentStates.begin();
		int size = currentStates.size();
		bool moreEpsilon = 1;
		int i = 0;
		/*std::cout << "CURRENTSTATES" << std::endl;
		std::vector<state*>::iterator currentit = currentStates.begin();
		while (currentit != currentStates.end()) {
			std::cout << **(currentit) << std::endl;
			currentit++;
		}
		std::cout << "ENDCURRENTSTATES" << std::endl;*/
		while (moreEpsilon) {
			moreEpsilon = 0;
			stateit = currentStates.begin() + i;
			for(; i < size; i++) {
				transitionsInternal theseTransitions = delta.find(*stateit)->second;
				std::map<symbol, stateset>::iterator transit = theseTransitions.begin();
				while (transit != theseTransitions.end()) {

					if (transit->first == 0) {
						std::vector<state*>::iterator deltastateit = transit->second.begin();
						while (deltastateit != transit->second.end()) {
							currentStates.push_back(*deltastateit);
							//transitionsInternal *temp = delta.find(*deltastateit)->second;
							if ((delta.find(*deltastateit)->second).find((char) 0) != (delta.find(*deltastateit)->second).end())
								moreEpsilon = 1;
							deltastateit++;
						}
					}
					transit++;
				}
				stateit++;
			}
			i = size;
			size = currentStates.size();
			//std::cout << "ENDMORE " << i << " " << size << std::endl;
		}


		inputit++;

	}


	std::vector<state*>::iterator stateit = currentStates.begin();
	while (stateit != currentStates.end()) {
		//std::cout << "State: " << **(stateit) << std::endl;
		if (F.find(*stateit) != F.end())
			return true;
		stateit++;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const eNFA& enfa) {
	os << "Alphabet: ";
	alphabet::iterator alphit = enfa.sigma.begin();
	while (alphit != enfa.sigma.end()) {
		os << *alphit << " ";
		alphit++;
	}
	os << std::endl << "States: ";
	states theStates = enfa.Q;
	states::iterator stateit = theStates.begin();
	while (stateit != theStates.end()) {
		os << **(stateit) << " ";
		stateit++;
	}
	os << std::endl << "Transitions" << std::endl;
	transitions theTransitions = enfa.delta;
	transitions::iterator transit = theTransitions.begin();
	while (transit != theTransitions.end()) {
		std::cout << "State " <<  *(transit->first) << " ";
		transitionsInternal::iterator transintit = transit->second.begin();
		while (transintit != transit->second.end()) {
			std::cout << "via " << transintit->first << " to";
			stateset::iterator stateit = transintit->second.begin();
			while (stateit != transintit->second.end()) {
				std::cout << " " << **(stateit);
				stateit++;
			}
			std::cout << std::endl;
			transintit++;
		}
		if (transit->second.size() == 0)
			os << std::endl;
		transit++;
	}
	os << "Start State " << *(enfa.q0) << std::endl;
	os << "Accepting states ";
	acceptingStates::iterator acceptingit = enfa.F.begin();
	while (acceptingit != enfa.F.end()) {
		os << **(acceptingit) << " ";
		acceptingit++;
	}
	return os;
}


}
