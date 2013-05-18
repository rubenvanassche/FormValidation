/*
 * eNFA.h
 *
 *  Created on: Apr 28, 2013
 *      Author: jakob
 */

#ifndef ENFA_H_
#define ENFA_H_

#include <map>
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "common.h"


namespace FA {

/**
 * @brief Class representing the eNFA
 */
class eNFA {
public:

	/**
	 * @brief constructor for empty eNFA
	 */
	eNFA();

	/**
	 * @brief constructor
	 *
	 * @param alphabet_ the alphabet
	 * @param states_ the states
	 * @param transitions_ the transitions
	 * @param start_ pointer to start state
	 * @param acceptingStates the accepting states
	 */
	eNFA(alphabet, states, transitions, state*, acceptingStates);


	/**
	 * @brief getter for delta (the transitions)
	 *
	 * @return the transitions
	 */
	const transitions& getDelta() const {
		return delta;
	}

	/**
	 * @brief getter for F (the accepting states)
	 *
	 * @return the accepting states
	 */
	const acceptingStates& getF() const {
		return F;
	}

	/**
	 * @brief getter for Q (the states)
	 *
	 * @return the states
	 */
	const states& getQ() const {
		return Q;
	}

	/**
	 * @brief getter for Q0 (the start state)
	 *
	 * @return the start state (pointer)
	 */
	state* getQ0() const {
		return q0;
	}


	/**
	 * @brief getter for sigma (the alphabet)
	 *
	 * @return the alphabet
	 */
	const alphabet& getSigma() const {
		return sigma;
	}


	/**
	 * @brief checks if string is part of language defined by eNFA
	 *
	 * @param str the string to be processed
	 *
	 * @return true if string belongs to eNFA
	 */
	bool process(std::string) const;

	/**
	 * @brief generates File version of eNFA (can be read again)
	 *
	 * @param filename name of the file
	 */
	void toFile(std::string);

	/**
	 * @brief generate eclose of state
	 *
	 * @param workingState pointer to state to generate eclose of
	 *
	 * @return the eclose
	 */
	stateset eclose(state*);


	/**
	 * @brief << overloader for eNFA
	 */
	friend std::ostream& operator<<(std::ostream&, const eNFA&);


private:

	alphabet sigma;
	states Q;
	transitions delta;
	state *q0;
	acceptingStates F;


};

/**
 * @brief generates eNFA from input file
 *
 * @param filename name of file to read eNFA from
 */
eNFA generateNFA(std::string);


}



#endif /* ENFA_H_ */
