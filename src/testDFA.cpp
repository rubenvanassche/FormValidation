/*
 * testDFA.cpp
 *
 *  Created on: 7 mei 2013
 *      Author: Ruben
 */
#include <iostream>
#include "eNFA.h"
#include "DFA.h"
#include "common.h"
#include "SubsetConstruction.h"
#include "RegexToNFA.h"

int main(){
	/*
	// stateset DFAstate constructor
	FA::state a = "q0";
	FA::state b = "q1";
	FA::state c = "q2";
	FA::state d = "q3";
	FA::state e = "q4";
	FA::state f = "nene";

	FA::stateset set;
	set.push_back(&a);
	set.push_back(&b);
	set.push_back(&c);
	set.push_back(&d);
	set.push_back(&e);

	FA::stateset altSet;
	altSet.push_back(&a);
	altSet.push_back(&b);
	altSet.push_back(&c);
	altSet.push_back(&d);

	FA::stateset altSet2;

	FA::DFAstate dfa(set);
	std::cout << "q0,q1,q2,q3,q4, : " << dfa.label << std::endl;
	std::cout << "1 : " << dfa.corresponds(set) << std::endl;
	std::cout << "0 : " << dfa.corresponds(altSet) << std::endl;
	std::cout << "0 : " << dfa.corresponds(altSet2) << std::endl;
	std::cout << "1 : " << dfa.isState(&a) << std::endl;
	std::cout << "1 : " << dfa.isState(&e) << std::endl;
	std::cout << "0 : " << dfa.isState(&f) << std::endl;
	*/


	// the verdict
	FA::eNFA *enfa1 = FA::regexToNFA("ab");
	std::cout << *enfa1 << std::endl;
	FA::DFA dfa1 = FA::eNFAtoDFA(*enfa1);
	std::cout << dfa1 << std::endl;

	/*
	std::cout << "ENFA" << std::endl;
	std::cout << "Result for a: " << enfa1->process("a") << std::endl;
	std::cout << "Result for b: " << enfa1->process("b") << std::endl;
	std::cout << "Result for empty: " << enfa1->process("") << std::endl;
	std::cout << "Result for ab: " << enfa1->process("ab") << std::endl;
	std::cout << "Result for ba: " << enfa1->process("ba") << std::endl;

	std::cout << "DFA" << std::endl;
	std::cout << "Result for a: " << dfa1.process("a") << std::endl;
	std::cout << "Result for b: " << dfa1.process("b") << std::endl;
	std::cout << "Result for empty: " << dfa1.process("") << std::endl;
	std::cout << "Result for ab: " << dfa1.process("ab") << std::endl;
	std::cout << "Result for ba: " << dfa1.process("ba") << std::endl;
	*/


}
