#ifndef SC_H_
#define SC_H_

#include "DFA.h"
#include "eNFA.h"
#include "common.h"

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

	void printTable();
	bool correspondingStates(std::vector<std::string> first, std::vector<std::string> second);
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

	bool makeTransition(State* worker);

	bool makeStartState();

	bool makeTable();

	bool makeEndingStates();

	std::vector<std::string> stateSetEclose(stateset stateSet);

	std::vector<std::string> mergeLabels(std::vector<std::string>, std::vector<std::string>);



	/**
	 * @brief Find a state with corresponding labels from a vector
	 *
	 * @param vector The labels to be used
	 *
	 * @return state* Or Null if there is no such state
	 */
	State* findState(std::vector<std::string> labels);

	std::map<std::string, std::map<char, std::vector<std::string> > > fTable;

};

}

#endif /* DFA_H_ */
