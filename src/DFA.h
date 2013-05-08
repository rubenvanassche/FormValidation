/*
 * DFA.h
 *
 *  Created on: 3 mei 2013
 *      Author: Ruben
 */

#ifndef DFA_H_
#define DFA_H_

#include <map>
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include "common.h"
#include "eNFA.h"

namespace FA {

struct DFAstate{
	std::string label;
	std::map<char, DFAstate*> DFAtransitions;
	bool isAccepting;
	stateset multiStates;

	bool transition(char symbol, DFAstate* state){
		if(DFAtransitions.find(symbol) == DFAtransitions.end()){
			DFAtransitions[symbol] = state;
			return true;
		}else{
		  return false;
		}
	}

	DFAstate* go(char symbol){
		std::map<char, DFAstate*>::iterator it;
		for(it = DFAtransitions.begin(); it != DFAtransitions.end();it++){
			if(symbol == it->first){
				return it->second;
			}
		}
		return NULL;
	}

	stateset makeTransitions(char symbol, transitions delta, eNFA automata){
		stateset destiny;
		for(unsigned int j = 0;j < multiStates.size();j++){
			// iterate over each state so we can check the transition
			transitionsInternal transInt = delta.find(multiStates.at(j))->second; // transitions from the current state
			stateset tempStates = transInt.find(symbol)->second; // States it is going to without eclose applied to it
			stateset transStates; // Final states


			// Now apply eclose to this transitions
			for(unsigned int i = 0;i < tempStates.size();i++){
				stateset tempEcloseStates = automata.eclose(tempStates.at(i));
				for(int k = 0;k < tempEcloseStates.size();k++){
					transStates.push_back(tempEcloseStates.at(k));
				}
			}

			// we've got all the states now check if we must place them in destiny
			std::vector<state*>::iterator stateSetIt;
			for(unsigned int i = 0;i < transStates.size();i++){
				stateSetIt = std::find(destiny.begin(), destiny.end(), transStates.at(i));
				if(stateSetIt == destiny.end()){
					// jeej the state is not yet in destiny so add it to that vector
					destiny.push_back(transStates.at(i));
				}
			}
		}
		// now get the state corresponding to destiny

		return destiny;

	}

	// check wheter the states in the stateset are also in this DFAstate
	bool corresponds(stateset checkSet){
		unsigned int counter = 0;
		stateset controlset = multiStates;

		for(unsigned int i = 0;i < controlset.size();i++){
			std::vector<state*>::iterator stateIt;
			stateIt = std::find(checkSet.begin(), checkSet.end(), controlset.at(i));
			if(stateIt != checkSet.end()){
				checkSet.erase(stateIt);
				counter++;
			}
		}

		if(controlset.size() == counter and checkSet.size() == 0){
			return true;
		}else{
			return false;
		}
	}

	// check wheter this state is in this DFAstate
	bool isState(state* checkState){
		for(int i = 0;i < multiStates.size();i++){
			if(multiStates.at(i) == checkState){
				return true;
			}
		}

		return false;
	}

	DFAstate(std::string name, bool accepting){
		isAccepting = accepting;
		label = name;
		multiStates.push_back(&label);
	}


	DFAstate(std::string name){
		isAccepting = false;
		label = name;
		multiStates.push_back(&label);
	}

	DFAstate(stateset states){
		isAccepting = false;
		for(unsigned int i = 0;i < states.size();i++){
			label += *(states.at(i));
			label += ",";
		}
		multiStates = states;
	}
};


typedef std::vector<DFAstate> DFAstates;

class DFA {
public:
	DFA(alphabet, DFAstates, int);

	DFAstates& getQ() {
		return Q;
	}

	DFAstate* getQ0() {
		return &(Q.at(q0));
	}

	alphabet& getSigma() {
		return sigma;
	}

	bool process(std::string);

	friend std::ostream& operator<<(std::ostream&, DFA&);

	virtual ~DFA();
private:
	alphabet sigma;
	DFAstates Q;
	int q0;
};

} /* namespace FA */
#endif /* DFA_H_ */
