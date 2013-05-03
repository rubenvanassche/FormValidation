
#include <iostream>
#include "eNFA.h"
#include "RegexToNFA.h"

int main() {
	/*FA::alphabet sigma;
	sigma.insert('a'); sigma.insert('b'); sigma.insert('c'); sigma.insert('d'); sigma.insert('e');
	FA::transitions delta;
	FA::transitionsInternal trans;
	FA::states Q;
	Q.push_back(new FA::state("1")); Q.push_back(new FA::state("2")); Q.push_back(new FA::state("3"));
	trans['a'] = FA::stateset(1, Q[1]); trans['b'] = FA::stateset(1, Q[0]); trans['c'] = FA::stateset(1, Q[0]); trans['d'] = FA::stateset(1, Q[2]); trans['e'] = FA::stateset(1, Q[1]); trans[0] = FA::stateset(1, Q[1]);
	delta[Q[0]] = trans;
	trans.clear();
	trans['d'] = FA::stateset(1, Q[1]); trans['e'] = FA::stateset(1, Q[0]);trans['c'] = FA::stateset(1, Q[2]); trans[0] = FA::stateset(1, Q[1]);
	delta[Q[1]] = trans;
	trans.clear();
	trans['a'] = FA::stateset(1, Q[1]); trans['b'] = FA::stateset(1, Q[2]); trans['e'] = FA::stateset(1, Q[2]);
	delta[Q[2]] = trans;
	trans.clear();
	FA::startState *q0 = Q[0];
	FA::acceptingStates F;
	F.insert(Q[2]);
	FA::eNFA testNFA(sigma, Q, delta, q0, F);
	std::cout << testNFA.process("ac") << std::endl;*/
	FA::eNFA *enfa = FA::regexToNFA("a+b");
	std::cout << *(enfa) << std::endl;
	std::cout << "Result: " << enfa->process("a") << std::endl;
}
