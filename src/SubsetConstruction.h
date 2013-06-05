#ifndef SC_H_
#define SC_H_

#include "DFA.h"
#include "eNFA.h"
#include "common.h"
#include <algorithm>

namespace FA {
/*
 * @brief Class for generating a DFA from an eNFA
 */
class SubsetConstruction{
public:
	/**
	 * @brief Constructor
	 *
	 * @param automata the eNFA
	 */
	SubsetConstruction(eNFA* automata);

	/**
	 * @brief Get the generated DFA
	 *
	 * @return DFA The generated DFA
	 */
	DFA* getDFA();
private:
	eNFA* fENFA;
	DFA fDFA;

	/**
	 * @brief Add the alphabet to the DFA from the eNFA
	 *
	 * @return bool If succes true
	 */
	bool makeAlphabet();

	/**
	 * @brief Add the states to the DFA from the eNFA
	 *
	 * @return bool If succes true
	 */
	bool makeStates();

	/**
	 * @brief Add the transitions to the DFA from the eNFA
	 *
	 * @return bool If succes true
	 */
	bool makeTransitions();

	/**
	 * @brief Add the transitions from the eNFA to a specified state
	 *
	 * @param State* the state
	 *
	 * @return bool If succes true
	 */
	bool makeTransition(State* worker);

	/**
	 * @brief Add the start state to the DFA from the eNFA
	 *
	 * @return bool If succes true
	 */
	bool makeStartState();

	/**
	 * @brief Builds a table for each state in the eNFA where it's going to + eclose
	 *
	 * @return bool If succes true
	 */
	bool makeTable();

	/**
	 * @brief Add the accepting states to the DFA from the eNFA
	 *
	 * @return bool If succes true
	 */
	bool makeEndingStates();

	/**
	 * @brief Performs an eclose on a stateset
	 *
	 * @param stateset The stateset
	 *
	 * @return vector the states eclosed
	 */
	std::vector<std::string> stateSetEclose(stateset stateSet);

	/**
	 * @brief Merges two label vectors so there are no duplicate labels
	 *
	 * @param vector the first vector
	 * @param vector the second vector
	 *
	 * @return vector the merged vector
	 */
	std::vector<std::string> mergeLabels(std::vector<std::string>, std::vector<std::string>);

	/**
	 * @brief Find a state with corresponding labels from a vector
	 *
	 * @param vector The labels to be used
	 *
	 * @return state* Or Null if there is no such state
	 */
	State* findState(std::vector<std::string> labels);

	/**
	 * @brief checks if two vectors with labels are the same
	 *
	 * @param vector the first vector
	 * @param vector the second vector
	 *
	 * @return bool True if the vectors are the same
	 */
	bool correspondingStates(std::vector<std::string> first, std::vector<std::string> second);

	std::map<std::string, std::map<char, std::vector<std::string> > > fTable;

};

}

#endif /* DFA_H_ */
