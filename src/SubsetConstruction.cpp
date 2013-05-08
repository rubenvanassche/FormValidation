#include "SubsetConstruction.h"

namespace FA{

	DFA eNFAtoDFA(eNFA& automata){
		// Create the states
		states oldStates = automata.getQ();
		DFAstates newStates;
		for(unsigned int i = 0;i < oldStates.size();i++){
			stateset newStateStateSet = automata.eclose(oldStates.at(i));
			DFAstate newState(newStateStateSet);
			newStates.push_back(newState);
		}

		// Now let's add to each newState his transitions
		for(int i = 0;i < newStates.size();i++){
			alphabet sigma = automata.getSigma();
			std::set<symbol>::iterator alphabetIt;


			for(alphabetIt = sigma.begin();alphabetIt != sigma.end();alphabetIt++){

				// iterate over each symbol to check for each symbol the transitions for each state
				stateset destiny = newStates.at(i).makeTransitions(*alphabetIt, automata.getDelta(), automata);
				// now let's find out which state we're searching

				for(int j = 0;j < newStates.size();j++){
					if(newStates.at(j).corresponds(destiny)){
						// Yeey this is the state we want our transition to go to
						newStates.at(i).transition(*alphabetIt, &(newStates.at(j)));
					}
				}
			}
		}

		// now check for each state if it is accepting
		acceptingStates acceptors = automata.getF();
		std::set<state*>::iterator acceptingIt;

		for(acceptingIt = acceptors.begin();acceptingIt != acceptors.end();acceptingIt++){
			for(int i = 0;i < newStates.size();i++){
				if(newStates.at(i).isState(*acceptingIt)){
					newStates.at(i).isAccepting = true;
				}
			}
		}

		// What is our start state?
		stateset startStateSet = automata.eclose(automata.getQ0());
		int startstate;
		for(int i = 0; i < newStates.size();i++){
			if(newStates.at(i).corresponds(startStateSet)){
				startstate = i;
			}
		}

		// we're done
		DFA dfa(automata.getSigma(), newStates, startstate);
		return dfa;
	}

}
