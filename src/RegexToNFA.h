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


eNFA* regexToNFA(regex);


state* regexToNFAInternal(regex, states&, transitions&, acceptingStates&, bool=1);


state* generateOr(char, char, states&, transitions&, int&, state*, bool,
		          states&, transitions&, state*, acceptingStates&,
		          states&, transitions&, state*, acceptingStates&);


state* generateConcatenation(char, char, states&, transitions&, int&, state*, bool,
                             states&, transitions&, state*, acceptingStates&,
                             states&, transitions&, state*, acceptingStates&);


state* generateKleene(char, states&, transitions&, int&, state*,
					  states&, transitions&, state*, acceptingStates&);
}
#endif /* REGEXTONFA_H_ */
