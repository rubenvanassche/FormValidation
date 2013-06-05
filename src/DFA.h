/*
 * DFA.h
 *
 *  Created on: 3 mei 2013
 *      Author: Ruben
 */

#ifndef DFA_H_
#define DFA_H_

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

namespace FA {

class Arc;

/**
 * @brief Class representing a state
 */
class State{
public:

	friend std::ostream& operator<<(std::ostream &out, State &state);

	/**
	 * @brief Constructor
	 *
	 * @param bool is this an accepting state
	 */
	State(bool ending);

	/**
	 * @brief Constructor
	 *
	 * @param bool is this an accepting state
	 * @param bool is this an starting state
	 */
	State(bool ending,bool starting);

	/**
	 * @brief Get the label of the state
	 *
	 * @return the state's label
	 */
	std::string getLabel();

	/**
	 * @brief Get the labels of the state(if there are more)
	 *
	 * @return vector The state's labels
	 */
	std::vector<std::string> getLabels();

	/**
	 * @brief Get the name of the state
	 *
	 * @return string All the labels of the state concatenated
	 */
	std::string getName();

	/**
	 * @brief Add's a label
	 *
	 * @param string the State's label
	 *
	 * @return bool When succes
	 */
	bool addLabel(std::string label);

	/**
	 * @brief Add's a labels
	 *
	 * @param vector the State's labels
	 *
	 * @return bool When succes
	 */
	bool addLabels(std::vector<std::string> labels);

	/**
	 * @brief Add's an arc
	 *
	 * @param arc the State's arc
	 *
	 * @return bool When succes
	 */
	bool addArc(Arc arc);

	/**
	 * @brief Add's an transition to another state
	 *
	 * @param char The symbol for the transition
	 * @param State* The state this transition goes to
	 *
	 * @return bool When succes
	 */
	bool addTransition(char symbol, State* destination);

	/**
	 * @brief Check if a state is accepting
	 *
	 * @return bool true if this state is accepting
	 */
	bool isEnding();

	/**
	 * @brief Check if a state is starting
	 *
	 * @return bool true if this state is starting
	 */
	bool isStarting();

	/**
	 * @brief Check if a state's arcs have legitimate symbols from an alphabet
	 *
	 * @param vector The alphabet
	 *
	 * @return bool true if this state is legitimate
	 */
	bool checkAlphabet(std::vector<char> &alphabet);

	/*
	 * @brief Check if a state has a specified label
	 *
	 * @param string The label
	 *
	 * @return bool true if this state has the label
	 */
	bool hasLabel(std::string label);

	/*
	 * @brief Let's this state become an accepting state
	 *
	 */
	void makeEnding();

	/**
	 * @brief Get the state when we process a symbol
	 *
	 * @param char The symbol
	 *
	 * @return State Or Null if there is no such transition
	 */
	State* process(char symbol);
private:
	bool fIsEnding;
	bool fIsStarting;
	std::vector<std::string> fLabels;
	std::vector<Arc> fArcs;
};

/**
 * @brief Class representing an arc
 */
class Arc{
public:
	friend std::ostream& operator<<(std::ostream &out, Arc &arc);

	/**
	 * @brief Constructor
	 *
	 * @param State* The State this arc is going to
	 */
	Arc(State* destination);

	/**
	 * @brief Add a symbol to the arc
	 *
	 * @param symbol The symbol
	 *
	 * @return bool True if succes
	 */
	bool addSymbol(char symbol);

	/**
	 * @brief Add symbols to the arc
	 *
	 * @param vector The symbols
	 *
	 * @return bool True if succes
	 */
	bool addSymbols(std::vector<char> symbols);

	/**
	 * @brief Check if the symbols in the arc are legitimate by the alphabet
	 *
	 * @param alphabet The alphabet
	 *
	 * @return bool True if the symbols are legitimate
	 */
	bool checkAlphabet(std::vector<char> &alphabet);

	/**
	 * @brief Process a symbol
	 *
	 * @param symbol The symbol
	 *
	 * @return state Or if there is no such symbol in the arc NULL
	 */
	State* process(char symbol);

	/**
	 * @brief Get the state this arc is going to
	 *
	 * @return state The state
	 */
	State* getDestination();
private:
	std::vector<char> fSymbols;
	State* fDestination;
};

/**
 * @brief Class representing a DFA
 */
class DFA{
public:

	friend std::ostream& operator<<(std::ostream &out, DFA &dfa);

	/**
	 * @brief Constructor
	 */
	DFA();

	/**
	 * @brief Process a string
	 *
	 * @param string The string
	 *
	 * @return bool True if string is accepted
	 */
	bool process(std::string string);

	/**
	 * @brief Process a symbol
	 *
	 * @param symbol The symbol
	 *
	 * @return bool True if symbol is accepted
	 */
	State* process(char symbol);

	/**
	 * @brief Process a symbol at a specified state
	 *
	 * @param symbol The symbol
	 * @param state* The state to process
	 *
	 * @return bool True if symbol is accepted
	 */
	State* process(char symbol, State* currentState);

	/**
	 * @brief Add a state to the DFA
	 *
	 * @param state The state
	 *
	 * @return bool True if success
	 */
	bool addState(State state);

	/**
	 * @brief Add states to the DFA
	 *
	 * @param vector The states
	 *
	 * @return bool True if success
	 */
	bool addStates(std::vector<State> states);

	/**
	 * @brief Add a symbol to the DFA's alphabet
	 *
	 * @param char The symbol
	 *
	 * @return bool True if success
	 */
	bool addAlphabet(char symbol);

	/**
	 * @brief Add symbols to the DFA's alphabet
	 *
	 * @param vector The symbols
	 *
	 * @return bool True if success
	 */
	bool addAlphabet(std::vector<char> symbols);

	/**
	 * @brief Check if symbol is in the Dfa's alphabet
	 *
	 * @param char The symbol
	 *
	 * @return bool True if symbol is in the alphabet
	 */
	bool isInAlphabet(char symbol);

	/**
	 * @brief Check if a DFA has a start state
	 *
	 * @return bool True if there is a start state
	 */
	bool hasStartState();

	/**
	 * @brief Get the states in the DFA
	 *
	 * @return vector The states
	 */
	std::vector<State> getStates();

	/**
	 * @brief Get the alphabet in the DFA
	 *
	 * @return vector The states
	 */
	std::vector<char> getAlphabet();

	/**
	 * @brief Removes all the states in the DFA
	 */
	void clearStates();

	std::vector<State> fStates;
private:
	/**
	 * @brief Find a start state in the vector of states
	 *
	 * @return state Or NULL if there is no start state found
	 */
	State* findStartState();

	std::vector<char> fAlphabet;

	State* fStartState;
};

} /* namespace FA */
#endif /* DFA_H_ */
