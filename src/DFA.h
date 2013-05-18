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

/**
 * @brief struct to represent state of DFA
 */
class DFAstate{
public:
	stateset multiStates;

	/**
	 * @brief constructor
	 *
	 * @param name Name of the state
	 * @param accepting true if state is accepting state
	 */
	DFAstate(std::string name, bool accepting);

	/**
	 * @brief constructor
	 * @param name Name of the state
	 */
	DFAstate(std::string name);

	/**
	 * @brief Constructor
	 *
	 * @param states States that belong to the DFAstate
	 */
	DFAstate(stateset states);

	/**
	 * @brief returns pointer to target
	 *
	 * @return pointer to target
	 */
	DFAstate* go(char symbol);

	/**
	 * @brief Adds a new transition
	 *
	 * @param symbol The input symbol
	 * @param state Pointer to the target state
	 *
	 * @return True if the transition was added
	 */
	bool transition(char symbol, DFAstate* state);

	/**
	 * @brief Finds target states for transition with certain symbol
	 *
	 * @param symbol The input symbol
	 * @param delta The transitions
	 * @param automata The automaton of which the state is a part
	 *
	 * @return Set containing all the target states
	 */
	stateset makeTransitions(char symbol, transitions delta, eNFA automata);

	/**
	 * @brief returns pointer to target
	 *
	 * @param c The input symbol
	 *
	 * @return pointer to target
	 */
	DFAstate* getTransition(char c);

	/**
	 * @brief returns map with transitions from this state to others
	 *
	 *
	 * @return map with symbol and state pointer
	 */
	std::map<char, DFAstate*> getTransitions();

	/**
	 * @brief check whether the states in the stateset are also in this DFAstate
	 *
	 * @param checkSet the stateset to be checked
	 *
	 * @return true if all states are in the DFAstate
	 */
	bool corresponds(stateset checkSet);

	/**
	 * @brief check whether a state is part of the DFAstate
	 *
	 * @param checkState the state to be checked
	 *
	 * @return true if state is part of DFAstate
	 */
	bool isState(state* checkState);

	/**
	 * @brief returns the label of this state
	 *
	 * @return string with the label
	 */
	std::string getLabel();

	/**
	 * @brief returns the label of this state
	 *
	 * @return true if state is accepting
	 */
	bool accepts();

	/**
	 * @brief make this state accepting
	 *
	 */
	void makeAccept();

	/**
	 * @brief prints information about this state to the console
	 *
	 */
	void print();

private:

	std::string label;
	std::map<char, DFAstate*> DFAtransitions;
	bool isAccepting;
};


typedef std::vector<DFAstate> DFAstates;

/**
 * @brief Class representing a DFA
 */
class DFA {
public:
	/**
	 * @brief constructor
	 *
	 * @param alphabet_ The alphabet of the DFA
	 * @param states_ The states of the DFA
	 * @param start_ Number of start state
	 */
	DFA(alphabet, DFAstates, int);

	/**
	 * @brief getter for Q (the states)
	 *
	 * @return the states
	 */
	DFAstates& getQ() {
		return Q;
	}

	/**
	 * @brief getter for q0 (start state)
	 *
	 * @return the start state
	 */
	DFAstate* getQ0() {
		return &(Q.at(q0));
	}

	/**
	 * @brief getter for sigma (the alphabet)
	 *
	 * @return the alphabet
	 */
	alphabet& getSigma() {
		return sigma;
	}
	/**
	 * @brief Check if string is part of the DFA
	 *
	 * @param str The input string
	 */
	bool process(std::string);

	/**
	 * @brief << overloader for DFA
	 */
	friend std::ostream& operator<<(std::ostream&, DFA&);

	virtual ~DFA();
private:
	alphabet sigma;
	DFAstates Q;
	int q0;
};

} /* namespace FA */
#endif /* DFA_H_ */
