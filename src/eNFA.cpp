/*
 * eNFA.cpp
 *
 *  Created on: Apr 28, 2013
 *      Author: jakob
 */

#include "eNFA.h"

namespace FA {

eNFA::eNFA() {}

eNFA::eNFA(alphabet alphabet_, states states_, transitions transitions_,state* start_, acceptingStates accepting_) :
			sigma(alphabet_), Q(states_), delta(transitions_), q0(start_), F(accepting_) {}

bool eNFA::process(std::string str) const {
	std::string::iterator inputit = str.begin();
	std::vector<state*> currentStates;
	std::vector<state*> oldStates;
	currentStates.push_back(q0);
	transitionsInternal initialTransitions = delta.find(q0)->second;
	if (initialTransitions.find((char) 0) != initialTransitions.end()) {       //e-transitions from q0?
		stateset::iterator stateit = initialTransitions[(char) 0].begin();
		while (stateit != initialTransitions[(char) 0].end()) {
			currentStates.push_back(*stateit);
			stateit++;
		}
		int size = currentStates.size();
		bool moreEpsilon = 1;
		int i = 1;
		while (moreEpsilon) {              //more e-transitions to go?
			moreEpsilon = 0;
			stateit = currentStates.begin() + i;    //dont't check twice
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
			if (size != currentStates.size()) {    //Another round?
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
		while (stateit != oldStates.end()) {                                   //Regular transitions
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
		while (moreEpsilon) {                               //Check for e-transitions, same method as before
			moreEpsilon = 0;
			stateit = currentStates.begin() + i;
			for(; i < size; i++) {
				transitionsInternal theseTransitions = delta.find(*stateit)->second;
				std::map<symbol, stateset>::iterator transit = theseTransitions.begin();
				while (transit != theseTransitions.end()) {

					if (transit->first == 0) {
						std::vector<state*>::iterator deltastateit = transit->second.begin();
						while (deltastateit != transit->second.end()) {
							if (find(currentStates.begin(), currentStates.end(), *deltastateit) == currentStates.end())
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


	std::vector<state*>::iterator stateit = currentStates.begin();    //Any of the accepting states in the final states?
	while (stateit != currentStates.end()) {
		//std::cout << "State: " << **(stateit) << std::endl;
		if (F.find(*stateit) != F.end())
			return true;
		stateit++;
	}
	return false;
}


stateset eNFA::eclose(state* workingState){
	stateset states;
	states.push_back(workingState);
	transitions::iterator itTransitions = delta.find(workingState);
	// now get the transitions for this state
	if (itTransitions != delta.end()) {
		transitionsInternal::iterator itSet = itTransitions->second.find(0);
		if (itSet != itTransitions->second.end()) {
			stateset::iterator stateit = itSet->second.begin();
			while (stateit != itSet->second.end()) {
				stateset newstates = eclose(*stateit);
				stateset::iterator newstateit = newstates.begin();
				while (newstateit != newstates.end()) {
					// check for each state in newstates if there is an equivalent in states if not add the current state to states
					if (std::find(states.begin(), states.end(), *newstateit) == states.end())
						states.push_back(*newstateit);
					newstateit++;
				}
				stateit++;
			}
		}

	}
	return states;
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
		std::cout << "State " <<  *(transit->first) << std::endl;;
		transitionsInternal::iterator transintit = transit->second.begin();
		while (transintit != transit->second.end()) {
			std::cout << "    via " << transintit->first << " to";
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



eNFA generateNFA(std::string filename) {          //Input file to eNFA
	std::ifstream file(filename.c_str());
	std::string line;
	alphabet sigma;
	states Q;
	std::map<std::string, int> tempQ;
	transitions delta;
	state* q0;
	acceptingStates F;
	//std::cout << "Alphabet" << std::endl;
	std::getline(file, line);
	std::string::iterator lineit = line.begin();
	//std::cout << line << std::endl;
	while (lineit != line.end()) {
		if (*lineit != ' ' && *lineit != '_' && sigma.find(*lineit) == sigma.end())
			sigma.insert(*lineit);
		else {
			std::cout << "Invalid input in alphabet" << std::endl;
			return eNFA();
		}
		lineit++;
		if (lineit == line.end()) break;
		else if (*lineit != ' ') {
			std::cout << "Invalid input in alphabet" << std::endl;
			return eNFA();
		}
		lineit++;
		//std::cout << "Invalid input in alphabet" << std::endl;
		//return eNFA();


	}
	//std::cout << "States" << std::endl;
	std::getline(file, line);
	if (!line.empty()) {
		std::cout << "Missing blank line" << std::endl;
		return eNFA();
	}
	//std::cout << line << std::endl;
	std::getline(file, line);
	int i = 0;
	//std::cout << line << std::endl;
	lineit = line.begin();
	while (lineit != line.end()) {
		std::stringstream namestream;
		std::string name;
		while (*lineit != ' ' && lineit != line.end()) {
			namestream << *lineit;
			lineit++;
		}
		name = namestream.str();
		//std::cout << name << std::endl;
		//std::cin >> i;
		if (name !=  "" && tempQ.find(name) == tempQ.end()) {
			Q.push_back(new state(name));
			tempQ[name] = i;
			i++;
		}
		else {
			std::cout << "Invalid state in states" << std::endl;
			return eNFA();
		}
		if (lineit == line.end()) break;
		if (*lineit == ' ') {
			lineit++;
			continue;
		}
		std::cout << "Invalid input in states" << std::endl;
		return eNFA();


	}
	//std::cout << "transitions" << std::endl;
	std::getline(file, line);
	if (!line.empty()) {
		std::cout << "Missing blank line" << std::endl;
		return eNFA();
	}
	transitionsInternal deltaInt;
	stateset stateSet;
	std::string state = "";
	std::getline(file, line);
	while (!line.empty()) {
		//std::cout << "LINE" << line << std::endl;
		std::stringstream namestream;
		std::string thisState;
		std::string word;
		std::string targetState;
		lineit = line.begin();
		while (*lineit != ' ' && lineit != line.end()) {
			namestream << *lineit;
			lineit++;
		}
		thisState = namestream.str();
		namestream.str("");
		if (state.empty()) state = thisState;
		if (tempQ.find(thisState) == tempQ.end()) {
			std::cout << "Invalid state name in transition" << std::endl;
			return eNFA();
		}
		if (thisState != state) {
			int pos = tempQ[state];
			delta[Q[pos]] = deltaInt;
			deltaInt.clear();
			state = thisState;
		}
		lineit++;
		while (*lineit != ' ' && lineit != line.end()) {
			namestream << *lineit;
			lineit++;
		}
		word = namestream.str();
		namestream.str("");
		if (word != "via") {
			std::cout << "Missing 'via'" << std::endl;
			return eNFA();
		}
		lineit++;
		if (*lineit != '_' && sigma.find(*lineit) == sigma.end()) {
			std::cout << "Character not in alphabet" << std::endl;
			return eNFA();
		}
		char c = *lineit;
		lineit++;
		lineit++;
		while (*lineit != ' ' && lineit != line.end()) {
			namestream << *lineit;
			lineit++;
		}
		word = namestream.str();
		namestream.str("");
		if (word != "to") {
			std::cout << "Missing 'to'" << std::endl;
			return eNFA();
		}
		lineit++;
		while (lineit != line.end()) {
			while (lineit != line.end() && *lineit != ' ') {
				namestream << *lineit;
				lineit++;
			}
			targetState = namestream.str();
			namestream.str("");
			int pos = tempQ[targetState];

			//deltaInt[Q[tempQ.find(name)]] =
			stateSet.push_back(Q[pos]);
			if (lineit != line.end()) lineit++;
		}
		if (c == '_') deltaInt[0] = stateSet;
		else deltaInt[c] = stateSet;
		stateSet.clear();

		std::getline(file, line);
	}
	int pos = tempQ[state];
	delta[Q[pos]] = deltaInt;
	deltaInt.clear();

	std::getline(file, line);
	if (tempQ.find(line) == tempQ.end()) {
		std::cout << "Invalid start state" << std::endl;
		return eNFA();
	}
	q0 = Q[0];

	std::getline(file, line);
	if (!line.empty()) {
		std::cout << "Missing blank line" << std::endl;
		return eNFA();
	}

	std::getline(file, line);
	lineit = line.begin();
	std::stringstream namestream;
	while (lineit != line.end()) {
		while (*lineit != ' ' && lineit != line.end()) {
			namestream << *lineit;
			lineit++;
		}
		state = namestream.str();
		namestream.str("");
		if (tempQ.find(state) == tempQ.end()) {
			std::cout << "Invalid accepting state" << std::endl;
			return eNFA();
		}
		int pos = tempQ[state];
		F.insert(Q[pos]);
		if (lineit != line.end()) lineit++;
	}
	//std::cout << "Generated" << std::endl;
	return eNFA(sigma, Q, delta, q0, F);

}

void eNFA::toFile(std::string filename) {   //Save eNFA to file, can be read again
	std::ofstream file(filename.c_str());
	alphabet::iterator alphit = sigma.begin();
	int size = sigma.size();
	int i = 0;
	while (alphit != sigma.end()) {
		i++;
		file << *alphit;
		if (i != size)
			file << ' ';
		alphit++;
	}
	file << std::endl << std::endl;
	states::iterator stateit = Q.begin();
	size = Q.size();
	i = 0;
	while (stateit != Q.end()) {
		i++;
		file << **stateit;
		if (i != size)
			file << ' ';
		stateit++;
	}
	file << std::endl << std::endl;

	transitions::iterator transit = delta.begin();
	while (transit != delta.end()) {
		transitionsInternal::iterator transintit = transit->second.begin();
		while (transintit != transit->second.end()) {
			if (transintit->first != 0)
				file << *(transit->first) << " via " << (transintit->first) << " to ";
			else
				file << *(transit->first) << " via _ to ";
			states::iterator targetStatesit = transintit->second.begin();
			while (targetStatesit != transintit->second.end()) {
				file << **targetStatesit;
				if (targetStatesit + 1 != transintit->second.end())
					file << ' ';
				targetStatesit++;
			}
			file << std::endl;
			transintit++;
		}
		transit++;
	}
	file << std::endl;

	file << *q0 << std::endl << std::endl;

	acceptingStates::iterator acceptit = F.begin();
	size = F.size();
	i = 0;
	while (acceptit != F.end()) {
		i++;
		file << **acceptit;
		if (i != size)
			file << ' ';
		acceptit++;
	}
	file << std::endl;



}

}
