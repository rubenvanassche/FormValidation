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


eNFA* regexToNFA(regex, bool=0);

state* generateOr(char, char, states&, transitions&, int&, state*, bool);


state* generateConcatenation(char, char, states&, transitions&, int&, state*, bool);


state* generateKleene(char, states&, transitions&, int&, state*);
}
#endif /* REGEXTONFA_H_ */
