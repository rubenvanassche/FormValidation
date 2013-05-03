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

void generateOr(char, char, states&, transitions&, int&);


void generateConcatenation(char, char, states&, transitions&, int&);


void generateKleene(char, states&, transitions&, int&);
}
#endif /* REGEXTONFA_H_ */
