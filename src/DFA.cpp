/*
 * DFA.cpp
 *
 *  Created on: 3 mei 2013
 *      Author: Ruben
 */

#include "DFA.h"

namespace FA {
////////  STATE  //////
std::ostream& operator<<(std::ostream &out, State &state){
	out << "State " << state.getName() << std::endl;

	if(state.isEnding()){
		out << "  Accepting State" << std::endl;
	}

	if(state.isStarting()){
		out << "  Start State" << std::endl;
	}

	out << "  Arcs: " << std::endl;
	for(unsigned int i = 0;i < state.fArcs.size();i++){
		out << state.fArcs.at(i);
	}

	out << std::endl;

	return out;
}

State::State(bool ending){
	this->fIsEnding = ending;
	this->fIsStarting = false;
}

State::State(bool ending,bool starting){
	this->fIsEnding = ending;
	this->fIsStarting = starting;
}

std::string State::getLabel(){
	if(this->fLabels.size() >= 1){
		return this->fLabels[0];
	}else{
		return "";
	}
}

std::vector<std::string> State::getLabels(){
	return this->fLabels;
}

std::string State::getName(){
	std::string out;
	for(unsigned int i = 0;i < this->fLabels.size();i++){
		out += this->fLabels.at(i);
		out += ", ";
	}

	return out;
}

bool State::addLabel(std::string label){
	if(std::find(this->fLabels.begin(), this->fLabels.end(), label) == this->fLabels.end()){
		// Label not in vector so add
		if(label.size() > 0){
			this->fLabels.push_back(label);
			return true;
		}else{
			return false;
		}
	}else{
		// Label in vector
		return false;
	}
}

bool State::addLabels(std::vector<std::string> labels){
	bool passed = true;

	for(unsigned int i = 0;i < labels.size();i++){
		if(this->addLabel(labels[i]) == false){
			passed = false;
		}
	}

	return passed;
}

bool State::addArc(Arc arc){
	this->fArcs.push_back(arc);
	return true;
}

bool State::addTransition(char symbol, State* destination){
	// Check if there is already an arc like this one
	std::vector<Arc>::iterator it;

	for(it = this->fArcs.begin();it != this->fArcs.end();it++){
		State* checkState = it->process(symbol);
		if(checkState != NULL){
			// There is already an arc with this symbol
			if(checkState == destination){
				// This arc points to the same destination so just return true, nothing needs to happen
				return true;
			}else{
				// In an DFA it is impossible to create 2 arcs with the same symbol
				return false;
			}
		}
	}

	// Find another arc with the same destination
	for(it = this->fArcs.begin();it != this->fArcs.end();it++){
		if(it->getDestination() == destination){
			// We found an arc with the same destination
			it->addSymbol(symbol);
			return true;
		}
	}

	// There is no arc with the same destination, we're going to create one
	Arc arc(destination);
	arc.addSymbol(symbol);

	this->addArc(arc);
	return true;
}

bool State::isEnding(){
	return this->fIsEnding;
}

bool State::isStarting(){
	return this->fIsStarting;
}

bool State::checkAlphabet(std::vector<char> &alphabet){
	std::vector<Arc>::iterator it;

	for(it = this->fArcs.begin();it != this->fArcs.end();it++){
		if(it->checkAlphabet(alphabet) == false){
			// An arc with a symbol not in the alphabet
			return false;
		}
	}

	return true;
}

bool State::hasLabel(std::string label){
	if(std::find(this->fLabels.begin(), this->fLabels.end(), label) == this->fLabels.end()){
		// label not in vector
		return false;
	}else{
		// Label in vector
		return true;
	}
}

void State::makeEnding(){
	this->fIsEnding = true;
}

State* State::process(char symbol){
	std::vector<Arc>::iterator it;
	for(it = this->fArcs.begin(); it != this->fArcs.end();it++){
		State* checkState = it->process(symbol);
		if(checkState != NULL){
			return checkState;
		}
	}
	return NULL;
}

////////  Arc  /////////

std::ostream& operator<<(std::ostream &out, Arc &arc){
	for(unsigned int i = 0;i < arc.fSymbols.size();i++){
		out << "    " << arc.fSymbols.at(i) << " => " << arc.fDestination->getName() << std::endl;
	}

	return out;
}

Arc::Arc(State* destination){
	this->fDestination = destination;
}

bool Arc::addSymbol(char symbol){
	if(std::find(this->fSymbols.begin(), this->fSymbols.end(), symbol) == this->fSymbols.end()){
		// symbol not in vector so add
		if(symbol != '\0'){
			this->fSymbols.push_back(symbol);
			return true;
		}else{
			return false;
		}
	}else{
		// Label in vector
		return false;
	}
}

bool Arc::addSymbols(std::vector<char> symbols){
	bool passed = true;

	for(unsigned int i = 0;i < symbols.size();i++){
		if(this->addSymbol(symbols[i]) == false){
			passed = false;
		}
	}

	return passed;
}

bool Arc::checkAlphabet(std::vector<char> &alphabet){
	std::vector<char>::iterator it;

	for(it = this->fSymbols.begin();it != this->fSymbols.end();it++){
		if(std::find(alphabet.begin(), alphabet.end(), *it) == alphabet.end()){
				// symbol not in alphabet
				return false;
			}
	}

	return true;
}

State* Arc::process(char symbol){
	if(std::find(this->fSymbols.begin(), this->fSymbols.end(), symbol) != this->fSymbols.end()){
		// symbol in vector so return state
		return this->fDestination;
	}else{
		// No symbol found so return NULL
		return NULL;
	}
}

State* Arc::getDestination(){
	return this->fDestination;
}

////// DFA ///////

std::ostream& operator<<(std::ostream &out, DFA &dfa){
	out << "DFA" << std::endl << "-----------" << std::endl;
	out << "Alphabet: ";

	for(unsigned int i =0;i < dfa.fAlphabet.size();i++){
		out << dfa.fAlphabet.at(i) << ", ";
	}

	out << std::endl << std::endl;

	for(unsigned int i = 0;i < dfa.fStates.size();i++){
		out << (dfa.fStates.at(i));
	}

	return out;
}

DFA::DFA(){
	this->fStartState = NULL;
}

bool DFA::process(std::string string){
	std::string::iterator it;

	if(this->hasStartState() == false){
		// Without a startState we can't do anything
		return false;
	}

	State* currentState = this->fStartState;

	for(it = string.begin();it != string.end();it++){
		State* checkState = currentState->process(*it);

		if(checkState == NULL){
			// No arc avaible so go to garbage stand
			//std::cout << "Check with symbol " << *it << " no state avaible" << std::endl;
			return false;
		}

		//std::cout << "Check with symbol " << *it << " to " << checkState->getLabel() << std::endl;

		currentState = checkState;
	}

	// Is it ending?
	if(currentState->isEnding()){
		//std::cout << "In state " << currentState->getLabel() << " that's ending" << std::endl;
		return true;
	}else{
		//std::cout << "In state " << currentState->getLabel() << " that's not ending" << std::endl;
		return false;
	}
}

State* DFA::process(char symbol){
	return this->process(symbol, this->fStartState);
}

State* DFA::process(char symbol, State* currentState){
	return currentState->process(symbol);
}

bool DFA::addState(State state){
	// check if all the symbols from the arcs in the state are part of the alphabet
	if(state.checkAlphabet(this->fAlphabet) == false){
		return false;
	}

	// State must have at least one label
	if(state.getLabel() == ""){
		return false;
	}

	this->fStates.push_back(state);

	return true;
}

bool DFA::addStates(std::vector<State> states){
	for(unsigned int i = 0;i < states.size();i++){
		this->fStates.push_back(states[i]);
	}

	return true;
}

bool DFA::addAlphabet(char symbol){
	if(std::find(this->fAlphabet.begin(), this->fAlphabet.end(), symbol) == this->fAlphabet.end()){
		// symbol not in vector so add
		this->fAlphabet.push_back(symbol);
		return true;
	}else{
		// Label in vector
		return false;
	}
}

bool DFA::addAlphabet(std::vector<char> symbols){
	bool passed = true;

	for(unsigned int i = 0;i < symbols.size();i++){
		if(this->addAlphabet(symbols[i]) == false){
			passed = false;
		}
	}

	return passed;
}

bool DFA::isInAlphabet(char symbol){
	if(std::find(this->fAlphabet.begin(), this->fAlphabet.end(), symbol) != this->fAlphabet.end()){
		// symbol in vector
		return true;
	}else{
		// symbol not in vector
		return false;
	}
}

bool DFA::hasStartState(){
	if(this->fStartState != NULL){
		return true;
	}else{
		// Try to find one
		State* checkState = this->findStartState();
		if(checkState != NULL){
			this->fStartState = checkState;
			return true;
		}else{
			return false;
		}
	}
}

std::vector<State> DFA::getStates(){
	return this->fStates;
}

std::vector<char> DFA::getAlphabet(){
	return this->fAlphabet;
}

void DFA::clearStates(){
	this->fStates.clear();
}

void DFA::clear(){
	this->clearStates();
	this->fStartState = NULL;
	this->fAlphabet.clear();
}
/*
bool DFA::load(std::string filename){
	const char *file = filename.c_str();

	std::ifstream stream(file);
	if(!stream.good()){
		// File doesn't exists
		std::cout << "DFA file bestaat niet" << std::endl;
		return false;
	}

	std::string line;
	int lineCounter = 1;

	std::string::iterator it;

	std::vector<std::string> states;
	std::string startStateLabel = "";
	std::vector<std::string> endingStates;

	std::vector<State> finalStates;
	std::vector<State>::iterator stateIt;


	while(std::getline(stream, line)){
		if(lineCounter == 1){
			// We are reading the alphabet
			std::vector<char> alphabet;

			bool letter = true;

			for(it = line.begin();it != line.end();it++){
				if(letter == true){
					// There should be a letter here
					if(*it != ' ' or *it != '\0' or *it != '\n'){
						alphabet.push_back(*it);
					}else{
						std::cout << "Hier moet een letter staan" << std::endl;
					}
					letter = false;
				}else{
					// There should be a space here
					if(*it == ' ' or *it == '\0' or *it == '\n'){
						letter = true;
						continue;
					}else{
						std::cout << "Hier moet een spatie staan" << std::endl;
					}
				}
			}

			this->fAlphabet = alphabet;
		}else if(lineCounter == 3){
			// We are reading the states
			std::vector<std::string> fileStates;
			std::string newState;
			for(it = line.begin();it != line.end();it++){
				if(*it == ' ' or *it == '\n'){
					fileStates.push_back(newState);
					newState = "";
				}else if(*it == '\0'){
					// Do nothing
				}else{
					newState += *it;
				}
			}

			// Add those states to the states vector
			for(unsigned int i = 0;i < fileStates.size();i++){
				states.push_back(fileStates.at(i));
			}
		}else if(lineCounter == 5){
			// We're reading the start state
			std::string startState;

			for(it = line.begin();it != line.end();it++){
				if(*it != ' ' or *it != '\0' or *it != '\n'){
					startState += *it;
				}
			}

			if(startState.size() == 0){
				std::cout << "Er kan geen automaat gemaakt worden zonder start staat" << std::endl;
				return false;
			}

			if(std::find(states.begin(), states.end(), startState) == states.end()){
				std::cout << "De start staat bestaat niet" << std::endl;
				return false;
			}
			startStateLabel = startState;
		}else if(lineCounter == 7){
			// We're reading the ending states
			std::vector<std::string> fileStates;
			std::string newState;
			for(it = line.begin();it != line.end();it++){
				if(*it == ' ' or *it == '\n'){
					fileStates.push_back(newState);
					newState = "";
				}else if(*it == '\0'){
					// Do nothing
				}else{
					newState += *it;
				}
			}

			// Add those states to the states vector
			for(unsigned int i = 0;i < fileStates.size();i++){
				endingStates.push_back(fileStates.at(i));
			}
		}else if(lineCounter == 8){
			// Make the states
			for(unsigned int i = 0;i < states.size();i++){
				std::string stateLabel = states.at(i);

				State *q;
				if(stateLabel == startStateLabel){
					// It's the start state
					State Q(false, true);
					q = &Q;
				}else{
					// Just another state
					State Q(false, false);
					q = &Q;
				}

				// Is this q ending?
				if(std::find(endingStates.begin(), endingStates.end(), stateLabel) != endingStates.end()){
					// Jup
					q->makeEnding();
				}

				q->addLabel(stateLabel);

				finalStates.push_back(*q);
			}

			// add them to the DFA
			this->fStates.clear();
			this->fStates = finalStates;

		}else if(lineCounter > 8){
			// We're reading the arcs
			std::string state1;
			std::string state2;
			char symbol;

			int delimiterCounter = 0;

			for(it = line.begin();it != line.end();it++){
				if(delimiterCounter == 0){
					// Read the first state
					if(*it == ' ' or *it == '\n'){
						delimiterCounter++;
					}else{
						state1 += *it;
					}
				}else if(delimiterCounter == 1){
					// We're reading the second state
					if(*it == ' ' or *it == '\n'){
						delimiterCounter++;
					}else{
						state2 += *it;
					}
				}else if(delimiterCounter == 2){
					if(*it != ' ' or *it != '\0' or *it != '\n'){
						symbol = *it;
						break;
					}
				}
			}

			if(std::find(states.begin(), states.end(), state1) == states.end()){
				std::cout << "De 1ste staat bestaat niet bij transities" << std::endl;
				continue;
			}

			if(std::find(states.begin(), states.end(), state2) == states.end()){
				std::cout << "De 2de staat bestaat niet bij transities" << std::endl;
				continue;
			}

			if(symbol == '\0' or symbol == ' ' or symbol == '\n'){
				std::cout << "Geen geldig symbool" << std::endl;
				continue;
			}

			State* first;
			State* second;

			// Now find the first state
			for(stateIt = this->fStates.begin();stateIt != this->fStates.end();stateIt++){
				if(stateIt->hasLabel(state1)){
					first = &(*stateIt);
					continue;
				}

				if(stateIt->hasLabel(state2)){
					second = &(*stateIt);
					continue;
				}
			}

			std::cout << "Add transition from " << first->getName() << " => " << second->getName() << "  via" << symbol << std::endl;

			if(first->addTransition(symbol, second) == false){
				std::cout << "Er ging iets mis bij het toevoegen van de transitie van" << first->getName() << " => " << second->getName() << " met " << symbol << std::endl;
			}
		}

		lineCounter++;
	}

	for(stateIt = finalStates.begin();stateIt != finalStates.end();stateIt++){
		if(this->addState(*stateIt) == false){
			std::cout << "Er ging iets mis bij het toevoegen van de staat " << stateIt->getName() << std::endl;
		}
	}

	return true;
}

bool DFA::save(std::string filename){

}
*/

State* DFA::findStartState(){
	std::vector<State>::iterator it;
	for(it = this->fStates.begin();it != this->fStates.end();it++){
		if(it->isStarting() == true){
			return &(*it);
		}
	}

	return NULL;
}

} /* namespace FA */
