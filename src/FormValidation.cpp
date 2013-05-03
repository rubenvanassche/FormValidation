
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
	FA::eNFA *enfa1 = FA::regexToNFA("a+b");
	std::cout << "Regex 'a+b': " << std::endl;
	std::cout << "Result for a: " << enfa1->process("a") << std::endl;
	std::cout << "Result for b: " << enfa1->process("b") << std::endl;
	std::cout << "Result for empty: " << enfa1->process("") << std::endl;
	std::cout << "Result for ab: " << enfa1->process("ab") << std::endl;
	std::cout << "Result for ba: " << enfa1->process("ba") << std::endl;
	FA::eNFA *enfa2 = FA::regexToNFA("ab");
	std::cout << "Regex 'ab':" << std::endl;
	std::cout << "Result for a: " << enfa2->process("a") << std::endl;
	std::cout << "Result for b: " << enfa2->process("b") << std::endl;
	std::cout << "Result for empty: " << enfa2->process("") << std::endl;
	std::cout << "Result for ab: " << enfa2->process("ab") << std::endl;
	std::cout << "Result for ba: " << enfa2->process("ba") << std::endl;
	FA::eNFA *enfa3 = FA::regexToNFA("a*");
	std::cout << "Regex 'a*'" << std::endl;
	std::cout << "Result for a: " << enfa3->process("a") << std::endl;
	std::cout << "Result for b: " << enfa3->process("b") << std::endl;
	std::cout << "Result for empty: " << enfa3->process("") << std::endl;
	std::cout << "Result for ab: " << enfa3->process("ab") << std::endl;
	std::cout << "Result for aaaaaaaa: " << enfa3->process("aaaaaaaa") << std::endl;
	std::cout << "Result for baaaaaaaa: " << enfa3->process("baaaaaaaa") << std::endl;
	std::cout << "Result for aaabaaaaa: " << enfa3->process("aaabaaaaa") << std::endl;
	std::cout << "Result for aaaaaaaab: " << enfa3->process("aaaaaaaab") << std::endl;
}
