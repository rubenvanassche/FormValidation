/*
 * DFA.cpp
 *
 *  Created on: 3 mei 2013
 *      Author: Ruben
 */

#include "DFA.h"

namespace FA {

DFA::DFA(alphabet alphabet_, DFAstates states_,int start_) : sigma(alphabet_), Q(states_), q0(start_){}

bool DFA::process(std::string str){
	if(str.size() == 0){
		return false;
	}

	std::string::iterator it = str.begin();

	DFAstate *current = &(Q.at(q0));

	for(it = str.begin();it != str.end();it++){
		if(current->go(*it) != NULL){
			current = current->go(*it);
		}else{
			return false;
		}
	}

	if((*current).isAccepting){
		return true;
	}else{
		return false;
	}

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
	for(int i = 0; i < states.size();i++){
		os << states.at(i).label << "   ";
	}


	os << "\nStart State : " << dfa.getQ0()->label << "\n";

	os << "Transitions :\n";
	std::map<char,DFAstate*>::iterator it;
	for(int i = 0;i < states.size();i++){
		for(it = states.at(i).DFAtransitions.begin(); it != states.at(i).DFAtransitions.end(); ++it){
		    os << states.at(i).label << " => " << it->second->label << "   via:" << it->first << '\n';
		}
	}

	os << "\nAccepting states: \n";
	int counter;
	for(int i = 0;i < states.size();i++){
		if(states.at(i).isAccepting){
			os << states.at(i).label << "\n";
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
