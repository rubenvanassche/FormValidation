/*
 * RegexToNFA.h
 *
 *  Created on: Apr 28, 2013
 *      Author: jakob
 */

#ifndef REGEXTONFA_H_
#define REGEXTONFA_H_

#include "common.h"
#include "eNFA.h"
#include <string>
#include <sstream>

namespace FA {

/**
 * @brief Generates eNFA describing same language as a regex
 *
 * @param regex The regex to be transformed into eNFA
 *
 * @return pointer to the eNFA
 */
eNFA* regexToNFA(regex);

//Following functions are only to be used by the regexToNFA(regex) function
state* regexToNFAInternal(regex, states&, transitions&, acceptingStates&, bool=1);


state* generateOr(char, char, states&, transitions&, int&, state*, bool,
		          states&, transitions&, state*, acceptingStates&,
		          states&, transitions&, state*, acceptingStates&);


state* generateConcatenation(char, char, states&, transitions&, int&, state*, bool,
                             states&, transitions&, state*, acceptingStates&,
                             states&, transitions&, state*, acceptingStates&);


state* generateKleene(char, states&, transitions&, int&, state*,
					  states&, transitions&, state*, acceptingStates&, bool=0);
}
#endif /* REGEXTONFA_H_ */
