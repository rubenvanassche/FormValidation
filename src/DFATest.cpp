/*
 * DFATest.cpp
 *
 *  Created on: 4 jun. 2013
 *      Author: Ruben
 */

#include "DFATest.h"

void stringControlTest(){
	FA::Test t("String Control");

	// States
	FA::State q0(true, true);
	t.expectTrue(q0.addLabel("q0"));
	t.expectFalse(q0.addLabel("q0"));

	FA::State q1(false);
	t.expectTrue(q1.addLabel("q1"));

	FA::State q2(true);
	t.expectTrue(q2.addLabel("q2"));

	FA::State failState(true);
	t.expectTrue(failState.addLabel("fail"));

	// Transitions
	t.expectTrue(q0.addTransition('a', &q1));
	t.expectTrue(q0.addTransition('b', &q2));

	t.expectTrue(q1.addTransition('a', &q1));
	t.expectTrue(q1.addTransition('b', &q0));

	t.expectTrue(q2.addTransition('a', &q0));
	t.expectTrue(q2.addTransition('b', &q1));
	t.expectTrue(q2.addTransition('b', &q1));
	t.expectFalse(q2.addTransition('b', &q2));

	t.expectTrue(failState.addTransition('c', &q2));

	// DFA
	FA::DFA dfa;
	t.expectTrue(dfa.addAlphabet('a'));
	t.expectTrue(dfa.addAlphabet('b'));

	t.expectTrue(dfa.addState(q0));
	t.expectTrue(dfa.addState(q1));
	t.expectTrue(dfa.addState(q2));
	t.expectFalse(dfa.addState(failState));

	t.expectFalse(dfa.process("a"));
	t.expectTrue(dfa.process("b"));

	t.expectTrue(dfa.process("ab"));
	t.expectTrue(dfa.process("ba"));
	t.expectFalse(dfa.process("bb"));

	t.expectFalse(dfa.process("aaa"));
	t.expectTrue(dfa.process("aab"));
	t.expectFalse(dfa.process("aba"));
	t.expectTrue(dfa.process("abb"));
	t.expectTrue(dfa.process("bbb"));
	t.expectFalse(dfa.process("bba"));
	t.expectTrue(dfa.process("bab"));
	t.expectFalse(dfa.process("baa"));

	t.expectTrue(dfa.process(""));
	t.expectFalse(dfa.process("c"));
	t.expectFalse(dfa.process("ac"));
	t.expectFalse(dfa.process("abc"));
}

void subsetConstructionTest(){
	using namespace FA;

	FA::Test t("SubsetConstruction");

	/*Convert regexes to dfa and test if the dfa works right*/
	eNFA *enfa1 = regexToNFA("a+b");    //a+b
	SubsetConstruction sc1(enfa1);
	DFA* dfa1 = (sc1.getDFA());
	t.expectTrue(dfa1->process("a"));
	t.expectTrue(dfa1->process("b"));
	t.expectFalse(dfa1->process(""));
	t.expectFalse(dfa1->process("ab"));
	t.expectFalse(dfa1->process("ba"));

	eNFA *enfa1b = regexToNFA("a+b+c+d+e+f");    //a+b+c+d+e+f
	SubsetConstruction sc2(enfa1b);
	DFA* dfa1b = (sc2.getDFA());
	t.expectTrue(dfa1b->process("a"));
	t.expectTrue(dfa1b->process("b"));
	t.expectTrue(dfa1b->process("c"));
	t.expectTrue(dfa1b->process("d"));
	t.expectTrue(dfa1b->process("e"));
	t.expectTrue(dfa1b->process("f"));
	t.expectFalse(dfa1b->process(""));
	t.expectFalse(dfa1b->process("ab"));
	t.expectFalse(dfa1b->process("ba"));

	eNFA *enfa2 = regexToNFA("ab");    //ab
	SubsetConstruction sc3(enfa2);
	DFA* dfa2 = (sc3.getDFA());
	t.expectFalse(dfa2->process("a"));
	t.expectFalse(dfa2->process("b"));
	t.expectFalse(dfa2->process(""));
	t.expectTrue(dfa2->process("ab"));
	t.expectFalse(dfa2->process("ba"));

	eNFA *enfa2b = regexToNFA("abcdef");   //abcdef
	SubsetConstruction sc4(enfa2b);
	DFA* dfa2b = (sc4.getDFA());
	t.expectFalse(dfa2b->process("a"));
	t.expectFalse(dfa2b->process("b"));
	t.expectFalse(dfa2b->process(""));
	t.expectFalse(dfa2b->process("abcde"));
	t.expectFalse(dfa2b->process("bcdef"));
	t.expectTrue(dfa2b->process("abcdef"));
	t.expectFalse(dfa2b->process("ba"));

	eNFA *enfa3 = regexToNFA("a*");     //a*
	SubsetConstruction sc5(enfa3);
	DFA* dfa3 = (sc5.getDFA());
	t.expectTrue(dfa3->process("a"));
	t.expectFalse(dfa3->process("b"));
	t.expectTrue(dfa3->process(""));
	t.expectFalse(dfa3->process("ab"));
	t.expectTrue(dfa3->process("aaaaaaaa"));
	t.expectFalse(dfa3->process("baaaaaaaa"));
	t.expectFalse(dfa3->process("aaabaaaaa"));
	t.expectFalse(dfa3->process("aaaaaaaab"));

	eNFA *enfa4 = regexToNFA("ab+c");    //ab+c
	SubsetConstruction sc6(enfa4);
	DFA* dfa4 = (sc6.getDFA());
	t.expectFalse(dfa4->process(""));
	t.expectFalse(dfa4->process("a"));
	t.expectFalse(dfa4->process("b"));
	t.expectTrue(dfa4->process("c"));
	t.expectTrue(dfa4->process("ab"));
	t.expectFalse(dfa4->process("ba"));
	t.expectFalse(dfa4->process("ac"));
	t.expectFalse(dfa4->process("bc"));
	t.expectFalse(dfa4->process("ca"));
	t.expectFalse(dfa4->process("cb"));
	t.expectFalse(dfa4->process("abc"));

	eNFA *enfa5 = regexToNFA("a+bcd");    //(a+b)cd
	SubsetConstruction sc7(enfa5);
	DFA* dfa5 = (sc7.getDFA());
	t.expectFalse(dfa5->process(""));
	t.expectFalse(dfa5->process("a"));
	t.expectFalse(dfa5->process("b"));
	t.expectFalse(dfa5->process("c"));
	t.expectFalse(dfa5->process("ab"));
	t.expectFalse(dfa5->process("ba"));
	t.expectFalse(dfa5->process("ac"));
	t.expectFalse(dfa5->process("bc"));
	t.expectFalse(dfa5->process("ca"));
	t.expectFalse(dfa5->process("cb"));
	t.expectFalse(dfa5->process("abc"));
	t.expectFalse(dfa5->process("abcd"));
	t.expectTrue(dfa5->process("acd"));
	t.expectTrue(dfa5->process("bcd"));
	t.expectFalse(dfa5->process("abd"));

	eNFA *enfa6 = regexToNFA("a*+b");     //a*+b
	SubsetConstruction sc8(enfa6);
	DFA* dfa6 = (sc8.getDFA());
	t.expectTrue(dfa6->process(""));
	t.expectTrue(dfa6->process("a"));
	t.expectTrue(dfa6->process("b"));
	t.expectFalse(dfa6->process("ab"));
	t.expectFalse(dfa6->process("aab"));
	t.expectTrue(dfa6->process("aa"));
	t.expectTrue(dfa6->process("aaaaaaaa"));

	eNFA *enfa7 = regexToNFA("a*b");     //a*b
	SubsetConstruction sc9(enfa7);
	DFA* dfa7 = (sc9.getDFA());
	t.expectFalse(dfa7->process(""));
	t.expectFalse(dfa7->process("a"));
	t.expectTrue(dfa7->process("b"));
	t.expectTrue(dfa7->process("ab"));
	t.expectTrue(dfa7->process("aab"));
	t.expectFalse(dfa7->process("aa"));
	t.expectFalse(dfa7->process("aaaaaaaa"));
	t.expectTrue(dfa7->process("aaaaaaaab"));
	t.expectFalse(dfa7->process("aaaaaaaabb"));

	eNFA *enfa8 = regexToNFA("a+b*");      //a+b*
	SubsetConstruction sc10(enfa8);
	DFA* dfa8 = (sc10.getDFA());
	t.expectTrue(dfa8->process(""));
	t.expectTrue(dfa8->process("a"));
	t.expectTrue(dfa8->process("b"));
	t.expectFalse(dfa8->process("ab"));
	t.expectFalse(dfa8->process("aab"));
	t.expectFalse(dfa8->process("abb"));
	t.expectFalse(dfa8->process("aa"));
	t.expectFalse(dfa8->process("aaaaaaaa"));
	t.expectFalse(dfa8->process("aaaaaaaab"));
	t.expectFalse(dfa8->process("abbbbbbbb"));
	t.expectTrue(dfa8->process("bbbbbbbb"));

	eNFA *enfa9 = regexToNFA("ab*");      //ab*
	SubsetConstruction sc11(enfa9);
	DFA* dfa9 = (sc11.getDFA());
	t.expectFalse(dfa9->process(""));
	t.expectTrue(dfa9->process("a"));
	t.expectFalse(dfa9->process("b"));
	t.expectTrue(dfa9->process("ab"));
	t.expectFalse(dfa9->process("aab"));
	t.expectTrue(dfa9->process("abb"));
	t.expectFalse(dfa9->process("aa"));
	t.expectFalse(dfa9->process("aaaaaaaa"));
	t.expectFalse(dfa9->process("aaaaaaaab"));
	t.expectTrue(dfa9->process("abbbbbbbb"));
	t.expectFalse(dfa9->process("bbbbbbbb"));

	eNFA *enfa10 = regexToNFA("a+(bc)");      //a+(bc)*
	SubsetConstruction sc12(enfa10);
	DFA* dfa10 = (sc12.getDFA());
	t.expectFalse(dfa10->process(""));
	t.expectTrue(dfa10->process("a"));
	t.expectFalse(dfa10->process("b"));
	t.expectFalse(dfa10->process("ab"));
	t.expectFalse(dfa10->process("ba"));
	t.expectFalse(dfa10->process("ac"));
	t.expectFalse(dfa10->process("ca"));
	t.expectTrue(dfa10->process("bc"));
	t.expectFalse(dfa10->process("cb"));
	t.expectFalse(dfa10->process("abc"));

	eNFA *enfa11 = regexToNFA("a(b+c)");      //a(b+c)
	SubsetConstruction sc13(enfa11);
	DFA* dfa11 = (sc13.getDFA());
	t.expectFalse(dfa11->process(""));
	t.expectFalse(dfa11->process("a"));
	t.expectFalse(dfa11->process("b"));
	t.expectTrue(dfa11->process("ab"));
	t.expectFalse(dfa11->process("ba"));
	t.expectTrue(dfa11->process("ac"));
	t.expectFalse(dfa11->process("ca"));
	t.expectFalse(dfa11->process("bc"));
	t.expectFalse(dfa11->process("cb"));
	t.expectFalse(dfa11->process("abc"));

	eNFA *enfa12 = regexToNFA("(a+b)*");    //(a+b)*
	SubsetConstruction sc14(enfa12);
	DFA* dfa12 = (sc14.getDFA());
	t.expectTrue(dfa12->process(""));
	t.expectTrue(dfa12->process("a"));
	t.expectTrue(dfa12->process("b"));
	t.expectTrue(dfa12->process("ab"));
	t.expectTrue(dfa12->process("aab"));
	t.expectTrue(dfa12->process("abb"));
	t.expectTrue(dfa12->process("aa"));
	t.expectTrue(dfa12->process("aaaaaaaa"));
	t.expectTrue(dfa12->process("aaaaaaaab"));
	t.expectTrue(dfa12->process("abbbbbbbb"));
	t.expectTrue(dfa12->process("bbbbbbbb"));
	t.expectTrue(dfa12->process("abaabaaabbbbabbaba"));
	t.expectFalse(dfa12->process("c"));
	t.expectFalse(dfa12->process("ca"));
	t.expectFalse(dfa12->process("ac"));


	eNFA *enfa14 = regexToNFA("((ab)*)+((cd)*)");    //(ab)*+(cd)*
	SubsetConstruction sc16(enfa14);
	DFA* dfa14 = (sc16.getDFA());
	t.expectTrue(dfa14->process(""));
	t.expectFalse(dfa14->process("a"));
	t.expectFalse(dfa14->process("b"));
	t.expectFalse(dfa14->process("c"));
	t.expectFalse(dfa14->process("d"));
	t.expectTrue(dfa14->process("cd"));
	t.expectFalse(dfa14->process("dc"));
	t.expectTrue(dfa14->process("ab"));
	t.expectFalse(dfa14->process("abcd"));
	t.expectTrue(dfa14->process("ababababababab"));
	t.expectFalse(dfa14->process("abababababababc"));
	t.expectTrue(dfa14->process("cdcdcdcdcdcd"));


}

void DFAreadTest(){
	FA::Test t("DFA Read");
	FA::DFA dfa;
	//dfa.load("DFAexample.txt");
	//std::cout << dfa << std::endl;
}
