#include "SubsetConstruction.h"

namespace FA{

SubsetConstruction::SubsetConstruction(eNFA* automata){
	this->fENFA = automata;
}

DFA* SubsetConstruction::getDFA(){
	this->makeAlphabet();
	this->makeStartState();
	this->makeTable();
	this->makeStates();
	this->makeTransitions();
	this->makeEndingStates();

	return &(this->fDFA);
}

bool SubsetConstruction::makeAlphabet(){
	std::set<symbol> sigma = this->fENFA->getSigma();
	std::vector<char> alphabet;

	std::set<symbol>::iterator it;
	for(it = sigma.begin();it != sigma.end();it++){
		alphabet.push_back(*it);
	}

	// Now add the new alphabet to the DFA
	this->fDFA.addAlphabet(alphabet);

	return true;
}

bool SubsetConstruction::makeStates(){
	// Now we're going to loop over each state in out table
	std::map<std::string, std::map<char, std::vector<std::string> > >::iterator tableIt;

	for(tableIt = this->fTable.begin();tableIt != this->fTable.end();tableIt++){
		std::map<char, std::vector<std::string> > transitions = tableIt->second;
		std::map<char, std::vector<std::string> >::iterator  transitionsIt;
		// now loop over each symbol in this map
		for(transitionsIt = transitions.begin();transitionsIt != transitions.end();transitionsIt++){
			std::vector<std::string> labels = transitionsIt->second;

			if(labels.size() == 0){
				continue;
			}

			// Now check if the DFA already has a state with these labels
			if(this->findState(labels) == NULL){
				// Nope so add this new state
				State newState(false, false);
				newState.addLabels(labels);

				this->fDFA.addState(newState);
			}

		}
	}

	return true;
}

bool SubsetConstruction::makeTransitions(){
	// Now let's make those transitions
	std::vector<State>::iterator stateIt;

	for(stateIt = this->fDFA.fStates.begin();stateIt != this->fDFA.fStates.end();stateIt++){
		this->makeTransition(&(*stateIt));
	}

	return true;
}

bool SubsetConstruction::makeTransition(State* worker){
	std::vector<std::string> labels = worker->getLabels();
	std::vector<std::string>::iterator labelsIt;
	std::vector<char> alphabet = this->fDFA.getAlphabet();
	std::vector<char>::iterator alphabetIt;

	// Now loop over the alpabet

	for(alphabetIt = alphabet.begin();alphabetIt != alphabet.end();alphabetIt++){
		char symbol = *alphabetIt;

		std::vector<std::string> goToState;
		for(labelsIt = labels.begin();labelsIt != labels.end();labelsIt++){
			std::vector<std::string> newLabels = this->fTable[*labelsIt][symbol];

			if(newLabels.size() != 0){
				goToState.insert( goToState.end(), newLabels.begin(), newLabels.end() );
			}
		}

		if(goToState.size() != 0){
			State* destination;
			destination = this->findState(goToState);

			if(destination != NULL){
				worker->addTransition(symbol, destination);
			}else{
				std::cout << "Probleem met staat" << std::endl;
			}
		}

	}

	return true;
}

bool SubsetConstruction::makeStartState(){
	std::vector<std::string*> stateSet = this->fENFA->eclose(this->fENFA->getQ0());
	std::vector<std::string*>::iterator stateSetIt;

	std::vector<std::string> states;

	// This stateset exists of string*'s we need string's
	for(stateSetIt = stateSet.begin();stateSetIt != stateSet.end();stateSetIt++){
		states.push_back(**stateSetIt);
	}

	State q0(false, true);
	q0.addLabels(states);

	this->fDFA.addState(q0);

	return true;
}

bool SubsetConstruction::makeTable(){
	std::vector<state*> states = this->fENFA->getQ();
	std::vector<state*>::iterator statesIt;

	std::map<state*, transitionsInternal> delta = this->fENFA->getDelta();

	for(statesIt = states.begin();statesIt != states.end();statesIt++){
		std::map<char, std::vector<std::string> > transitions;
		std::map<char, std::vector<std::string> >::iterator transitionsIt;

		// Now add to the map(transitions) for each symbol in the alphabet a empty vector
		for(unsigned int i = 0;i < this->fDFA.getAlphabet().size();i++){
			std::vector<std::string> emptyVector;
			char symbol = this->fDFA.getAlphabet().at(i);
			transitions[symbol] = emptyVector;
		}

		// Now we need to add the transitions for each symbol this current state is going to
		std::map<symbol, stateset> deltaInternal = delta[*statesIt];
		std::map<symbol, stateset>::iterator deltaInternalIt;

		for(deltaInternalIt = deltaInternal.begin();deltaInternalIt != deltaInternal.end();deltaInternalIt++){
			char symbol =  deltaInternalIt->first;
			if(symbol == 0){
				// Epsilon transition, so add the states it is going to to all symbols in transitions
				// NOTHING TO DO OVER HEERE
				/*
				for(transitionsIt = transitions.begin();transitionsIt != transitions.end();transitionsIt++){
					char transitionsSymbol = transitionsIt->first;
					std::vector<std::string> labels = this->mergeLabels(transitionsIt->second, deltaInternalIt->second);
					transitions[transitionsSymbol] = labels;
				}
				*/
			}else{
				// Just a transition
				std::vector<std::string> labels = this->stateSetEclose(deltaInternalIt->second);
				labels = this->mergeLabels(transitions[symbol], labels);
				transitions[symbol] = labels;
			}
		}

		this->fTable[**statesIt] = transitions;
	}


	return true;
}

bool SubsetConstruction::makeEndingStates(){
	acceptingStates endingStates = this->fENFA->getF();
	acceptingStates::iterator endingStatesIt;

	std::vector<State>::iterator statesIt;

	for(endingStatesIt = endingStates.begin();endingStatesIt != endingStates.end();endingStatesIt++){
		for(statesIt = this->fDFA.fStates.begin();statesIt != this->fDFA.fStates.end();statesIt++){
			if(statesIt->isEnding()){
				// This one is already ending so go to teh next one
				continue;
			}

			if(statesIt->hasLabel(**endingStatesIt)){
				// Acceptor state
				statesIt->makeEnding();
			}
		}
	}

	return true;
}

std::vector<std::string> SubsetConstruction::mergeLabels(std::vector<std::string> original, std::vector<std::string> stateSet){
	std::vector<std::string> out = original;

	std::vector<std::string>::iterator stateSetIt;
	for(stateSetIt = stateSet.begin();stateSetIt != stateSet.end();stateSetIt++){
		if(std::find(out.begin(), out.end(), *stateSetIt) == out.end()){
			// label in stateSet is not in out so add it
			out.push_back(*stateSetIt);
		}
	}

	return out;
}

/*
void SubsetConstruction::printTable(){
	std::cout << "DFA Table" << std::endl << "--------------" << std::endl;

	std::map<std::string, std::map<char, std::vector<std::string> > >::iterator tableIt;
	std::map<char, std::vector<std::string> >::iterator transitionsIt;
	std::vector<std::string>::iterator labelsIt;

	for(tableIt = this->fTable.begin();tableIt != this->fTable.end();tableIt++){
		std::map<char, std::vector<std::string> > transitions = tableIt->second;

		std::cout << "  " << tableIt->first <<std::endl;
		for(transitionsIt = transitions.begin();transitionsIt != transitions.end();transitionsIt++){
			std::cout << "    " << transitionsIt->first << " => ";
			for(labelsIt = transitionsIt->second.begin();labelsIt != transitionsIt->second.end();labelsIt++){
				std::cout << *labelsIt << ", ";
			}
			std::cout << std::endl;
		}
	}
}
*/

std::vector<std::string> SubsetConstruction::stateSetEclose(stateset stateSet){
	std::vector<std::string> out;

	std::vector<state*>::iterator it;
	std::vector<state*>::iterator it2;
	for(it = stateSet.begin();it != stateSet.end();it++){
		stateset ecloseStates = this->fENFA->eclose(*it);
		for(it2 = ecloseStates.begin();it2 != ecloseStates.end();it2++){
			out.push_back(**it2);
		}
	}

	return out;
}

bool SubsetConstruction::correspondingStates(std::vector<std::string> first, std::vector<std::string> second){
	unsigned int counter = 0;
	std::vector<std::string> controlset = first;

	for(unsigned int i = 0;i < controlset.size();i++){
		std::vector<state>::iterator stateIt;
		stateIt = std::find(second.begin(), second.end(), first.at(i));
		if(stateIt != second.end()){
			second.erase(stateIt);
			counter++;
		}
	}

	if(controlset.size() == counter and second.size() == 0){
		return true;
	}else{
		return false;
	}
}

State* SubsetConstruction::findState(std::vector<std::string> labels){
	std::vector<State>::iterator it;

	for(it = this->fDFA.fStates.begin();it != this->fDFA.fStates.end();it++){
		std::vector<std::string> checkLabels = it->getLabels();
		if(this->correspondingStates(checkLabels, labels)){
			return &(*it);
		}
	}

	return NULL;

}


}
