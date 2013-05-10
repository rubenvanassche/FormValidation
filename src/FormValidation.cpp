
#include <iostream>
#include "eNFA.h"
#include "RegexToNFA.h"

int main(int argc, char* argv[]) {
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
	std::cout << testNFA << std::endl;
	std::cout << testNFA.process("ac") << std::endl;*/
	/*FA::eNFA *enfa1 = FA::regexToNFA("a+b");
	std::cout << "Regex 'a+b': " << std::endl;
	std::cout << "Result for a: " << enfa1->process("a") << std::endl;
	std::cout << "Result for b: " << enfa1->process("b") << std::endl;
	std::cout << "Result for empty: " << enfa1->process("") << std::endl;
	std::cout << "Result for ab: " << enfa1->process("ab") << std::endl;
	std::cout << "Result for ba: " << enfa1->process("ba") << std::endl;
	FA::eNFA *enfa1b = FA::regexToNFA("a+b+c+d+e+f");
	//std::cout << (*enfa1b) << std::endl;
	std::cout << "Regex 'a+b+c+d+e+f': " << std::endl;
	std::cout << "Result for a: " << enfa1b->process("a") << std::endl;
	std::cout << "Result for b: " << enfa1b->process("b") << std::endl;
	std::cout << "Result for c: " << enfa1b->process("c") << std::endl;
	std::cout << "Result for d: " << enfa1b->process("d") << std::endl;
	std::cout << "Result for e: " << enfa1b->process("e") << std::endl;
	std::cout << "Result for f: " << enfa1b->process("f") << std::endl;
	std::cout << "Result for empty: " << enfa1b->process("") << std::endl;
	std::cout << "Result for ab: " << enfa1b->process("ab") << std::endl;
	std::cout << "Result for ba: " << enfa1b->process("ba") << std::endl;
	FA::eNFA *enfa2 = FA::regexToNFA("ab");
	//std::cout << *enfa2 << std::endl;
	std::cout << "Regex 'ab':" << std::endl;
	std::cout << "Result for a: " << enfa2->process("a") << std::endl;
	std::cout << "Result for b: " << enfa2->process("b") << std::endl;
	std::cout << "Result for empty: " << enfa2->process("") << std::endl;
	std::cout << "Result for ab: " << enfa2->process("ab") << std::endl;
	std::cout << "Result for ba: " << enfa2->process("ba") << std::endl;
	FA::eNFA *enfa2b = FA::regexToNFA("abcdef");
	//std::cout << *enfa2b << std::endl;
	std::cout << "Regex 'abcdef':" << std::endl;
	std::cout << "Result for a: " << enfa2b->process("a") << std::endl;
	std::cout << "Result for b: " << enfa2b->process("b") << std::endl;
	std::cout << "Result for empty: " << enfa2b->process("") << std::endl;
	std::cout << "Result for abcde: " << enfa2b->process("abcde") << std::endl;
	std::cout << "Result for bcdef: " << enfa2b->process("bcdef") << std::endl;
	std::cout << "Result for abcdef: " << enfa2b->process("abcdef") << std::endl;
	std::cout << "Result for ba: " << enfa2b->process("ba") << std::endl;
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
	FA::eNFA *enfa4 = FA::regexToNFA("ab+c");
	std::cout << "Regex 'ab+c'" << std::endl;
	std::cout << "Result for empty: " << enfa4->process("") << std::endl;
	std::cout << "Result for a: " << enfa4->process("a") << std::endl;
	std::cout << "Result for b: " << enfa4->process("b") << std::endl;
	std::cout << "Result for c: " << enfa4->process("c") << std::endl;
	std::cout << "Result for ab: " << enfa4->process("ab") << std::endl;
	std::cout << "Result for ba: " << enfa4->process("ba") << std::endl;
	std::cout << "Result for ac: " << enfa4->process("ac") << std::endl;
	std::cout << "Result for bc: " << enfa4->process("bc") << std::endl;
	std::cout << "Result for ca: " << enfa4->process("ca") << std::endl;
	std::cout << "Result for cb: " << enfa4->process("cb") << std::endl;
	std::cout << "Result for abc: " << enfa4->process("abc") << std::endl;
	FA::eNFA *enfa5 = FA::regexToNFA("a+bcd");
	std::cout << "Regex '(a+b)cd'" << std::endl;
	std::cout << "Result for empty: " << enfa5->process("") << std::endl;
	std::cout << "Result for a: " << enfa5->process("a") << std::endl;
	std::cout << "Result for b: " << enfa5->process("b") << std::endl;
	std::cout << "Result for c: " << enfa5->process("c") << std::endl;
	std::cout << "Result for ab: " << enfa5->process("ab") << std::endl;
	std::cout << "Result for ba: " << enfa5->process("ba") << std::endl;
	std::cout << "Result for ac: " << enfa5->process("ac") << std::endl;
	std::cout << "Result for bc: " << enfa5->process("bc") << std::endl;
	std::cout << "Result for ca: " << enfa5->process("ca") << std::endl;
	std::cout << "Result for cb: " << enfa5->process("cb") << std::endl;
	std::cout << "Result for abc: " << enfa5->process("abc") << std::endl;
	std::cout << "Result for abcd: " << enfa5->process("abcd") << std::endl;
	std::cout << "Result for acd: " << enfa5->process("acd") << std::endl;
	std::cout << "Result for bcd: " << enfa5->process("bcd") << std::endl;
	std::cout << "Result for abd: " << enfa5->process("abd") << std::endl;
	FA::eNFA *enfa6 = FA::regexToNFA("a*+b");
	//std::cout << *enfa6 << std::endl;
	std::cout << "Regex 'a*+b'" << std::endl;
	std::cout << "Result for empty: " << enfa6->process("") << std::endl;
	std::cout << "Result for a: " << enfa6->process("a") << std::endl;
	std::cout << "Result for b: " << enfa6->process("b") << std::endl;
	std::cout << "Result for ab: " << enfa6->process("ab") << std::endl;
	std::cout << "Result for aab: " << enfa6->process("aab") << std::endl;
	std::cout << "Result for aa: " << enfa6->process("aa") << std::endl;
	std::cout << "Result for aaaaaaaa: " << enfa6->process("aaaaaaaa") << std::endl;
	FA::eNFA *enfa7 = FA::regexToNFA("a*b");
	//std::cout << *enfa7 << std::endl;
	std::cout << "Regex 'a*b'" << std::endl;
	std::cout << "Result for empty: " << enfa7->process("") << std::endl;
	std::cout << "Result for a: " << enfa7->process("a") << std::endl;
	std::cout << "Result for b: " << enfa7->process("b") << std::endl;
	std::cout << "Result for ab: " << enfa7->process("ab") << std::endl;
	std::cout << "Result for aab: " << enfa7->process("aab") << std::endl;
	std::cout << "Result for aa: " << enfa7->process("aa") << std::endl;
	std::cout << "Result for aaaaaaaa: " << enfa7->process("aaaaaaaa") << std::endl;
	std::cout << "Result for aaaaaaaab: " << enfa7->process("aaaaaaaab") << std::endl;
	std::cout << "Result for aaaaaaaabb: " << enfa7->process("aaaaaaaabb") << std::endl;

	FA::eNFA *enfa8 = FA::regexToNFA("a+b*");
	//std::cout << *enfa8 << std::endl;
	std::cout << "Regex 'a+b*'" << std::endl;
	std::cout << "Result for empty: " << enfa8->process("") << std::endl;
	std::cout << "Result for a: " << enfa8->process("a") << std::endl;
	std::cout << "Result for b: " << enfa8->process("b") << std::endl;
	std::cout << "Result for ab: " << enfa8->process("ab") << std::endl;
	std::cout << "Result for aab: " << enfa8->process("aab") << std::endl;
	std::cout << "Result for abb: " << enfa8->process("abb") << std::endl;
	std::cout << "Result for aa: " << enfa8->process("aa") << std::endl;
	std::cout << "Result for aaaaaaaa: " << enfa8->process("aaaaaaaa") << std::endl;
	std::cout << "Result for aaaaaaaab: " << enfa8->process("aaaaaaaab") << std::endl;
	std::cout << "Result for abbbbbbbb: " << enfa8->process("abbbbbbbb") << std::endl;
	std::cout << "Result for bbbbbbbb: " << enfa8->process("bbbbbbbb") << std::endl;

	FA::eNFA *enfa9 = FA::regexToNFA("ab*");
	//std::cout << *enfa9 << std::endl;
	std::cout << "Regex 'ab*'" << std::endl;
	std::cout << "Result for empty: " << enfa9->process("") << std::endl;
	std::cout << "Result for a: " << enfa9->process("a") << std::endl;
	std::cout << "Result for b: " << enfa9->process("b") << std::endl;
	std::cout << "Result for ab: " << enfa9->process("ab") << std::endl;
	std::cout << "Result for aab: " << enfa9->process("aab") << std::endl;
	std::cout << "Result for abb: " << enfa9->process("abb") << std::endl;
	std::cout << "Result for aa: " << enfa9->process("aa") << std::endl;
	std::cout << "Result for aaaaaaaa: " << enfa9->process("aaaaaaaa") << std::endl;
	std::cout << "Result for aaaaaaaab: " << enfa9->process("aaaaaaaab") << std::endl;
	std::cout << "Result for abbbbbbbb: " << enfa9->process("abbbbbbbb") << std::endl;
	std::cout << "Result for bbbbbbbb: " << enfa9->process("bbbbbbbb") << std::endl;

	FA::eNFA *enfa10 = FA::regexToNFA("a+(bc)");
	//std::cout << *enfa10 << std::endl;
	std::cout << "Regex 'a+(bc)'" << std::endl;
	std::cout << "Result for empty: " << enfa10->process("") << std::endl;
	std::cout << "Result for a: " << enfa10->process("a") << std::endl;
	std::cout << "Result for b: " << enfa10->process("b") << std::endl;
	std::cout << "Result for ab: " << enfa10->process("ab") << std::endl;
	std::cout << "Result for ba: " << enfa10->process("ba") << std::endl;
	std::cout << "Result for ac: " << enfa10->process("ac") << std::endl;
	std::cout << "Result for ca: " << enfa10->process("ca") << std::endl;
	std::cout << "Result for bc: " << enfa10->process("bc") << std::endl;
	std::cout << "Result for cb: " << enfa10->process("cb") << std::endl;
	std::cout << "Result for abc: " << enfa10->process("abc") << std::endl;


	FA::eNFA *enfa11 = FA::regexToNFA("a(b+c)");
	//std::cout << *enfa11 << std::endl;
	std::cout << "Regex 'a(b+c)'" << std::endl;
	std::cout << "Result for empty: " << enfa11->process("") << std::endl;
	std::cout << "Result for a: " << enfa11->process("a") << std::endl;
	std::cout << "Result for b: " << enfa11->process("b") << std::endl;
	std::cout << "Result for ab: " << enfa11->process("ab") << std::endl;
	std::cout << "Result for ba: " << enfa11->process("ba") << std::endl;
	std::cout << "Result for ac: " << enfa11->process("ac") << std::endl;
	std::cout << "Result for ca: " << enfa11->process("ca") << std::endl;
	std::cout << "Result for bc: " << enfa11->process("bc") << std::endl;
	std::cout << "Result for cb: " << enfa11->process("cb") << std::endl;
	std::cout << "Result for abc: " << enfa11->process("abc") << std::endl;

	FA::eNFA *enfa12 = FA::regexToNFA("(a+b)*");
	//std::cout << *enfa12 << std::endl;
	std::cout << "Regex '(a+b)*'" << std::endl;
	std::cout << "Result for empty: " << enfa12->process("") << std::endl;
	std::cout << "Result for a: " << enfa12->process("a") << std::endl;
	std::cout << "Result for b: " << enfa12->process("b") << std::endl;
	std::cout << "Result for ab: " << enfa12->process("ab") << std::endl;
	std::cout << "Result for aab: " << enfa12->process("aab") << std::endl;
	std::cout << "Result for abb: " << enfa12->process("abb") << std::endl;
	std::cout << "Result for aa: " << enfa12->process("aa") << std::endl;
	std::cout << "Result for aaaaaaaa: " << enfa12->process("aaaaaaaa") << std::endl;
	std::cout << "Result for aaaaaaaab: " << enfa12->process("aaaaaaaab") << std::endl;
	std::cout << "Result for abbbbbbbb: " << enfa12->process("abbbbbbbb") << std::endl;
	std::cout << "Result for bbbbbbbb: " << enfa12->process("bbbbbbbb") << std::endl;
	std::cout << "Result for abaabaaabbbbabbaba: " << enfa12->process("abaabaaabbbbabbaba") << std::endl;
	std::cout << "Result for c: " << enfa12->process("c") << std::endl;
	std::cout << "Result for ca: " << enfa12->process("ca") << std::endl;
	std::cout << "Result for ac: " << enfa12->process("ac") << std::endl;

	FA::eNFA inputNFA = FA::generateNFA("NFAexample.txt");
	//std::cout << inputNFA << std::endl;
	std::cout << "NFA specified in NFAexample.txt" << std::endl;
	std::cout << "Result for Empty: " << inputNFA.process("") << std::endl;
	std::cout << "Result for a: " << inputNFA.process("a") << std::endl;
	std::cout << "Result for b: " << inputNFA.process("b") << std::endl;
	std::cout << "Result for c: " << inputNFA.process("c") << std::endl;
	std::cout << "Result for d: " << inputNFA.process("d") << std::endl;
	std::cout << "Result for da: " << inputNFA.process("da") << std::endl;
	std::cout << "Result for db: " << inputNFA.process("db") << std::endl;
	std::cout << "Result for dc: " << inputNFA.process("dc") << std::endl;
	std::cout << "Result for dd: " << inputNFA.process("dd") << std::endl;
	inputNFA.toFile("NFAOUT.txt");
	FA::eNFA inputNFA2 = FA::generateNFA("NFAOUT.txt");
	std::cout << "Same NFA, after saving to file and reading from file again" << std::endl;
	std::cout << "Result for Empty: " << inputNFA2.process("") << std::endl;
	std::cout << "Result for a: " << inputNFA2.process("a") << std::endl;
	std::cout << "Result for b: " << inputNFA2.process("b") << std::endl;
	std::cout << "Result for c: " << inputNFA2.process("c") << std::endl;
	std::cout << "Result for d: " << inputNFA2.process("d") << std::endl;
	std::cout << "Result for da: " << inputNFA2.process("da") << std::endl;
	std::cout << "Result for db: " << inputNFA2.process("db") << std::endl;
	std::cout << "Result for dc: " << inputNFA2.process("dc") << std::endl;
	std::cout << "Result for dd: " << inputNFA2.process("dd") << std::endl;

	FA::eNFA *enfa13 = FA::regexToNFA("(((0+(10))*)((1+(01))*))(0+_)");
	//std::cout << *enfa13 << std::endl;
	std::cout << "Regex '(0+10)*(1+01)*(0+_)'" << std::endl;
	std::cout << "Result for empty: " << enfa13->process("") << std::endl;
	std::cout << "Result for 0: " << enfa13->process("0") << std::endl;
	std::cout << "Result for 1: " << enfa13->process("1") << std::endl;
	std::cout << "Result for 01: " << enfa13->process("01") << std::endl;
	std::cout << "Result for 10: " << enfa13->process("10") << std::endl;
	std::cout << "Result for 001: " << enfa13->process("001") << std::endl;
	std::cout << "Result for 0011: " << enfa13->process("0011") << std::endl;
	std::cout << "Result for 1100: " << enfa13->process("1100") << std::endl;
	std::cout << "Result for 110: " << enfa13->process("110") << std::endl;
	std::cout << "Result for 0001001011010: " << enfa13->process("0001001011010") << std::endl;
	std::cout << "Result for 001011001110: " << enfa13->process("001011001110") << std::endl;
	std::cout << "Result for 00101001110: " << enfa13->process("00101001110") << std::endl;
	std::cout << "Result for 0000000: " << enfa13->process("0000000") << std::endl;
	std::cout << "Result for 1111111: " << enfa13->process("1111111") << std::endl;
	std::cout << "Result for 000010001001010110111011110: " << enfa13->process("000010001001010110111011110") << std::endl;


	FA::stateset ecloseStates;
	ecloseStates = enfa13->eclose(enfa13->getQ0());



	FA::eNFA *enfa14 = FA::regexToNFA("((ab)*)+((cd)*)");
	//std::cout << *enfa14 << std::endl;
	std::cout << "Regex '(ab)*+(cd)*'" << std::endl;
	std::cout << "Result for empty: " << enfa14->process("") << std::endl;
	std::cout << "Result for a: " << enfa14->process("a") << std::endl;
	std::cout << "Result for b: " << enfa14->process("b") << std::endl;
	std::cout << "Result for c: " << enfa14->process("c") << std::endl;
	std::cout << "Result for d: " << enfa14->process("d") << std::endl;
	std::cout << "Result for cd: " << enfa14->process("cd") << std::endl;
	std::cout << "Result for dc: " << enfa14->process("dc") << std::endl;
	std::cout << "Result for ab: " << enfa14->process("ab") << std::endl;
	std::cout << "Result for abcd: " << enfa14->process("abcd") << std::endl;
	std::cout << "Result for abababababab: " << enfa14->process("ababababababab") << std::endl;
	std::cout << "Result for ababababababc: " << enfa14->process("abababababababc") << std::endl;
	std::cout << "Result for cdcdcdcdcdcd: " << enfa14->process("cdcdcdcdcdcd") << std::endl;*/


	if (argc != 1) {
		FA::eNFA *enfaArg = FA::regexToNFA(argv[1]);
		std::cout << "Regex: " << argv[1] << std::endl;
		int i = 2;
		while (i != argc) {
			std::cout << argv[i] << " was ";
			if (!enfaArg->process(argv[i]))
				std::cout << "NOT ";
			std::cout << "accepted." << std::endl;
			i++;
		}

	}
	else {
		std::cout << "Please enter a regular expression" << std::endl;
		FA::regex regEx;
		std::cin >> regEx;
		FA::eNFA *enfaCin = FA::regexToNFA(regEx);
		//bool cont = true;
		while (true) {
			std::cout << "Please enter a string" << std::endl;
			std::string str;
			std::cin >> str;
			bool accepted = enfaCin->process(str);
			if (accepted)
				std::cout << "This string belongs to the language expressed by the given regex" << std::endl;
			else
				std::cout << "This string does not belong to the language expressed by the given regex" << std::endl;
			//std::cout << "Would you like to enter another string (Y/n): " << std::endl;
			//char response;
			//std::cin >> response;
			//if (response == 'n' || response == 'N')
			//	cont = false;
		}
	}

}
