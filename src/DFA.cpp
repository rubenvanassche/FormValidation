/*
 * DFA.cpp
 *
 *  Created on: 3 mei 2013
 *      Author: Ruben
 */

#include "DFA.h"

namespace FA {

bool DFAstate::transition(char symbol, DFAstate* state){
	if(DFAtransitions.find(symbol) == DFAtransitions.end()){
		DFAtransitions[symbol] = state;
		return true;
	}else{
	  return false;
	}
}

DFAstate* DFAstate::go(char symbol){
	std::map<char, DFAstate*>::iterator it;
	if(DFAtransitions.size() == 0){
		return NULL;
	}

	for(it = DFAtransitions.begin(); it != DFAtransitions.end();++it){
		if(symbol == it->first){
			return it->second;
		}
	}

	return NULL;
}

stateset DFAstate::makeTransitions(char symbol, transitions delta, eNFA automata){
	stateset destiny;
	for(unsigned int j = 0;j < multiStates.size();j++){
		// iterate over each state so we can check the transition
		transitionsInternal transInt = delta.find(multiStates.at(j))->second; // transitions from the current state
		stateset tempStates = transInt[symbol]; // States it is going to without eclose applied to it
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

bool DFAstate::corresponds(stateset checkSet){
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

bool DFAstate::isState(state* checkState){
	for(int i = 0;i < multiStates.size();i++){
		if(multiStates.at(i) == checkState){
			return true;
		}
	}

	return false;
}

DFAstate::DFAstate(std::string name, bool accepting){
	isAccepting = accepting;
	label = name;
	multiStates.push_back(&label);
}


DFAstate::DFAstate(std::string name){
	isAccepting = false;
	label = name;
	multiStates.push_back(&label);
}

DFAstate::DFAstate(stateset states){
	isAccepting = false;
	for(unsigned int i = 0;i < states.size();i++){
		label += *(states.at(i));
		label += ",";
	}
	multiStates = states;
}

std::string DFAstate::getLabel(){
	return this->label;
}

bool DFAstate::accepts(){
	return this->isAccepting;
}

DFAstate* DFAstate::getTransition(char c){
	return this->DFAtransitions[c];
}

void DFAstate::print(){
	std::cout << "DFAstate " << this->label << "  -    (" << this << ")" << std::endl;
	std::cout << "------------------" << std::endl;
	std::cout << "accepts : " << this->isAccepting << std::endl;
	std::cout << "transitions(" << this->DFAtransitions.size() << ") :" << std::endl;

	std::map<char, DFAstate*>::iterator it;
	for(it = this->DFAtransitions.begin();it != this->DFAtransitions.end();++it){
		std::cout << "via : ";
		std::cout << it->first << " to: " << it->second->getLabel() << std::endl;
	}

	std::cout << std::endl << std::endl;
}


DFA::DFA(alphabet alphabet_, DFAstates states_,int start_) : sigma(alphabet_), Q(states_), q0(start_){}

bool DFA::process(std::string str){
	if(str.size() == 0){
		return false;
	}

	std::string::iterator it = str.begin();

	DFAstate *current = &(Q.at(q0));

	for(it = str.begin();it != str.end();++it){
		if(current->go(*it) != NULL){
			current = current->go(*it);
		}else{
			return false;
		}
	}

	if(current->accepts()){
		return true;
	}else{
		return false;
	}

}

std::map<char, DFAstate*> DFAstate::getTransitions(){
	return this->DFAtransitions;
}

void DFAstate::makeAccept(){
	this->isAccepting = true;
}

std::ostream& operator<<(std::ostream& os, DFA& dfa) {
	os << "Alphabet: ";
	alphabet::iterator alphit = dfa.sigma.begin();
	while (alphit != dfa.sigma.end()) {
		os << *alphit << " ";
		alphit++;
	}

	os << "\n";

	DFAstates states = dfa.getQ();

	os << "States: ";
	for(unsigned int i = 0; i < states.size();i++){
		os << states.at(i).getLabel() << "   ";
	}


	os << "\nStart State : " << dfa.getQ0()->getLabel() << "\n";

	os << "Transitions :\n";
	for(unsigned int i = 0;i < states.size();i++){
		std::map<char,DFAstate*>::iterator it;
		std::map<char,DFAstate*> transitions = states.at(i).getTransitions();
		for(it = transitions.begin(); it != transitions.end(); ++it){
		    os << states.at(i).getLabel();
		    os << " => " << it->second->getLabel();
		    os << "   via:" << it->first << '\n';
		}
	}

	os << "\nAccepting states: \n";
	int counter;
	for(int i = 0;i < states.size();i++){
		if(states.at(i).accepts()){
			os << states.at(i).getLabel() << "\n";
			counter++;
		}
	}
	os << "total : " << counter << "\n";


	return os;

}

DFA::~DFA() {
	// TODO Auto-generated destructor stub
}

} /* namespace FA */
