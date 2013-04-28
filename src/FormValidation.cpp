
#include <iostream>
#include "eNFA.h"

int main() {
	FA::alphabet sigma;
	sigma.insert('a'); sigma.insert('b'); sigma.insert('c'); sigma.insert('d'); sigma.insert('e');
	FA::transitions delta;
	FA::transitionsInternal trans;
	FA::states Q;
	Q.push_back("1"); Q.push_back("2"); Q.push_back("3");
	trans['a'] = &(Q[1]); trans['b'] = &(Q[0]); trans['c'] = &(Q[0]); trans['d'] = &(Q[2]); trans['e'] = &(Q[1]); trans[0] = &(Q[1]);
	delta[&(Q[0])] = trans;
	trans.clear();
	trans['d'] = &(Q[1]); trans['e'] = &(Q[0]); trans[0] = &(Q[1]);
	delta[&(Q[1])] = trans;
	trans.clear();
	trans['a'] = &(Q[1]); trans['b'] = &(Q[2]); trans['e'] = &(Q[2]);
	delta[&(Q[2])] = trans;
	trans.clear();
	FA::startState *q0 = &(Q[0]);
	FA::acceptingStates F;
	F.insert(&Q[2]);
	FA::eNFA testNFA(sigma, Q, delta, q0, F);
	std::cout << testNFA.process("d") << std::endl;


}
