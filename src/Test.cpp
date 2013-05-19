/*
 * Test.cpp
 *
 *  Created on: 18 mei 2013
 *      Author: Ruben
 */

#include "Test.h"

namespace FA {

Test::Test(std::string name) {
	this->fName = name;
	this->fFails = 0;
	this->fGoods = 0;

	std::cout << "[" << this->fName << " Test]" << std::endl;
}

bool Test::equal(bool val1, bool val2){
	if(val1 == val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is not equal to " << val2 << std::endl;
		return false;
	}
}
bool Test::equal(int val1, int val2){
	if(val1 == val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is not equal to " << val2 << std::endl;
		return false;
	}
}
bool Test::equal(float val1, float val2){
	if(val1 == val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is not equal to " << val2 << std::endl;
		return false;
	}
}
bool Test::equal(std::string val1, std::string val2){
	if(val1 == val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is not equal to " << val2 << std::endl;
		return false;
	}
}

bool Test::different(bool val1, bool val2){
	if(val1 != val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is equal to " << val2 << std::endl;
		return false;
	}
}
bool Test::different(int val1, int val2){
	if(val1 != val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is equal to " << val2 << std::endl;
		return false;
	}
}
bool Test::different(float val1, float val2){
	if(val1 != val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is equal to " << val2 << std::endl;
		return false;
	}
}
bool Test::different(std::string val1, std::string val2){
	if(val1 != val2){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : " << val1 << " is equal to " << val2 << std::endl;
		return false;
	}
}

bool Test::expectTrue(bool val){
	if(val == true){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : must be true, is false" << std::endl;
		return false;
	}
}
bool Test::expectFalse(bool val){
	if(val != true){
		this->fGoods += 1;
		return true;
	}else{
		this->fFails += 1;
		std::cout << "    Fail : must be false, is true" << std::endl;
		return false;
	}
}

int Test::runAllTests() {
	/*Tests for basic functionality of eNFA*/
	alphabet sigma;
	//alphabet
	sigma.insert('a'); sigma.insert('b'); sigma.insert('c'); sigma.insert('d'); sigma.insert('e');
	transitions delta;
	transitionsInternal trans;
	states Q;
	//states
	Q.push_back(new state("1")); Q.push_back(new state("2")); Q.push_back(new state("3"));
	//transitions
	trans['a'] = stateset(1, Q[1]); trans['b'] = stateset(1, Q[0]); trans['c'] = stateset(1, Q[0]); trans['d'] = stateset(1, Q[2]); trans['e'] = stateset(1, Q[1]); trans[0] = stateset(1, Q[1]);
	delta[Q[0]] = trans;
	trans.clear();
	trans['d'] = stateset(1, Q[1]); trans['e'] = stateset(1, Q[0]);trans['c'] = stateset(1, Q[2]); trans[0] = stateset(1, Q[1]);
	delta[Q[1]] = trans;
	trans.clear();
	trans['a'] = stateset(1, Q[1]); trans['b'] = stateset(1, Q[2]); trans['e'] = stateset(1, Q[2]);
	delta[Q[2]] = trans;
	trans.clear();
	//start state
	state *q0 = Q[0];
	acceptingStates F;
	//accepting state
	F.insert(Q[2]);
	//generate the eNFA
	eNFA testNFA(sigma, Q, delta, q0, F);
	//Test the eNFA with some strings
	expectFalse(testNFA.process("a"));
	expectFalse(testNFA.process("b"));
	expectTrue(testNFA.process("c"));
	expectTrue(testNFA.process("d"));
	expectFalse(testNFA.process("e"));
	expectTrue(testNFA.process("ac"));
	expectTrue(testNFA.process("bc"));
	expectFalse(testNFA.process("ea"));
	expectTrue(testNFA.process("bcac"));
	expectFalse(testNFA.process("bcaca"));
	eNFA *enfa1 = regexToNFA("a+b");
	expectTrue(enfa1->process("a"));
	expectTrue(enfa1->process("b"));
	expectFalse(enfa1->process(""));
	expectFalse(enfa1->process("ab"));
	expectFalse(enfa1->process("ba"));
	eNFA *enfa1b = regexToNFA("a+b+c+d+e+f");
	//std::cout << (*enfa1b) << std::endl;
	//std::cout << "Regex 'a+b+c+d+e+f': " << std::endl;
	expectTrue(enfa1b->process("a"));
	expectTrue(enfa1b->process("b"));
	expectTrue(enfa1b->process("c"));
	expectTrue(enfa1b->process("d"));
	expectTrue(enfa1b->process("e"));
	expectTrue(enfa1b->process("f"));
	expectFalse(enfa1b->process(""));
	expectFalse(enfa1b->process("ab"));
	expectFalse(enfa1b->process("ba"));
	eNFA *enfa2 = regexToNFA("ab");
	//std::cout << *enfa2 << std::endl;
	//std::cout << "Regex 'ab':" << std::endl;
	expectFalse(enfa2->process("a"));
	expectFalse(enfa2->process("b"));
	expectFalse(enfa2->process(""));
	expectTrue(enfa2->process("ab"));
	expectFalse(enfa2->process("ba"));
	eNFA *enfa2b = regexToNFA("abcdef");
	//std::cout << *enfa2b << std::endl;
	//std::cout << "Regex 'abcdef':" << std::endl;
	expectFalse(enfa2b->process("a"));
	expectFalse(enfa2b->process("b"));
	expectFalse(enfa2b->process(""));
	expectFalse(enfa2b->process("abcde"));
	expectFalse(enfa2b->process("bcdef"));
	expectTrue(enfa2b->process("abcdef"));
	expectFalse(enfa2b->process("ba"));
	eNFA *enfa3 = regexToNFA("a*");
	//std::cout << "Regex 'a*'" << std::endl;
	expectTrue(enfa3->process("a"));
	expectFalse(enfa3->process("b"));
	expectTrue(enfa3->process(""));
	expectFalse(enfa3->process("ab"));
	expectTrue(enfa3->process("aaaaaaaa"));
	expectFalse(enfa3->process("baaaaaaaa"));
	expectFalse(enfa3->process("aaabaaaaa"));
	expectFalse(enfa3->process("aaaaaaaab"));
	eNFA *enfa4 = regexToNFA("ab+c");
	//std::cout << "Regex 'ab+c'" << std::endl;
	expectFalse(enfa4->process(""));
	expectFalse(enfa4->process("a"));
	expectFalse(enfa4->process("b"));
	expectTrue(enfa4->process("c"));
	expectTrue(enfa4->process("ab"));
	expectFalse(enfa4->process("ba"));
	expectFalse(enfa4->process("ac"));
	expectFalse(enfa4->process("bc"));
	expectFalse(enfa4->process("ca"));
	expectFalse(enfa4->process("cb"));
	expectFalse(enfa4->process("abc"));
	eNFA *enfa5 = regexToNFA("a+bcd");
	//std::cout << "Regex '(a+b)cd'" << std::endl;
	expectFalse(enfa5->process(""));
	expectFalse(enfa5->process("a"));
	expectFalse(enfa5->process("b"));
	expectFalse(enfa5->process("c"));
	expectFalse(enfa5->process("ab"));
	expectFalse(enfa5->process("ba"));
	expectFalse(enfa5->process("ac"));
	expectFalse(enfa5->process("bc"));
	expectFalse(enfa5->process("ca"));
	expectFalse(enfa5->process("cb"));
	expectFalse(enfa5->process("abc"));
	expectFalse(enfa5->process("abcd"));
	expectTrue(enfa5->process("acd"));
	expectTrue(enfa5->process("bcd"));
	expectFalse(enfa5->process("abd"));
	eNFA *enfa6 = regexToNFA("a*+b");
	//std::cout << *enfa6 << std::endl;
	//std::cout << "Regex 'a*+b'" << std::endl;
	expectTrue(enfa6->process(""));
	expectTrue(enfa6->process("a"));
	expectTrue(enfa6->process("b"));
	expectFalse(enfa6->process("ab"));
	expectFalse(enfa6->process("aab"));
	expectTrue(enfa6->process("aa"));
	expectTrue(enfa6->process("aaaaaaaa"));
	eNFA *enfa7 = regexToNFA("a*b");
	//std::cout << *enfa7 << std::endl;
	//std::cout << "Regex 'a*b'" << std::endl;
	expectFalse(enfa7->process(""));
	expectFalse(enfa7->process("a"));
	expectTrue(enfa7->process("b"));
	expectTrue(enfa7->process("ab"));
	expectTrue(enfa7->process("aab"));
	expectFalse(enfa7->process("aa"));
	expectFalse(enfa7->process("aaaaaaaa"));
	expectTrue(enfa7->process("aaaaaaaab"));
	expectFalse(enfa7->process("aaaaaaaabb"));

	eNFA *enfa8 = regexToNFA("a+b*");
	//std::cout << *enfa8 << std::endl;
	//std::cout << "Regex 'a+b*'" << std::endl;
	expectTrue(enfa8->process(""));
	expectTrue(enfa8->process("a"));
	expectTrue(enfa8->process("b"));
	expectFalse(enfa8->process("ab"));
	expectFalse(enfa8->process("aab"));
	expectFalse(enfa8->process("abb"));
	expectFalse(enfa8->process("aa"));
	expectFalse(enfa8->process("aaaaaaaa"));
	expectFalse(enfa8->process("aaaaaaaab"));
	expectFalse(enfa8->process("abbbbbbbb"));
	expectTrue(enfa8->process("bbbbbbbb"));

	eNFA *enfa9 = regexToNFA("ab*");
	//std::cout << *enfa9 << std::endl;
	//std::cout << "Regex 'ab*'" << std::endl;
	expectFalse(enfa9->process(""));
	expectTrue(enfa9->process("a"));
	expectFalse(enfa9->process("b"));
	expectTrue(enfa9->process("ab"));
	expectFalse(enfa9->process("aab"));
	expectTrue(enfa9->process("abb"));
	expectFalse(enfa9->process("aa"));
	expectFalse(enfa9->process("aaaaaaaa"));
	expectFalse(enfa9->process("aaaaaaaab"));
	expectTrue(enfa9->process("abbbbbbbb"));
	expectFalse(enfa9->process("bbbbbbbb"));

	eNFA *enfa10 = regexToNFA("a+(bc)");
	//std::cout << *enfa10 << std::endl;
	//std::cout << "Regex 'a+(bc)'" << std::endl;
	expectFalse(enfa10->process(""));
	expectTrue(enfa10->process("a"));
	expectFalse(enfa10->process("b"));
	expectFalse(enfa10->process("ab"));
	expectFalse(enfa10->process("ba"));
	expectFalse(enfa10->process("ac"));
	expectFalse(enfa10->process("ca"));
	expectTrue(enfa10->process("bc"));
	expectFalse(enfa10->process("cb"));
	expectFalse(enfa10->process("abc"));


	eNFA *enfa11 = regexToNFA("a(b+c)");
	//std::cout << *enfa11 << std::endl;
	//std::cout << "Regex 'a(b+c)'" << std::endl;
	expectFalse(enfa11->process(""));
	expectFalse(enfa11->process("a"));
	expectFalse(enfa11->process("b"));
	expectTrue(enfa11->process("ab"));
	expectFalse(enfa11->process("ba"));
	expectTrue(enfa11->process("ac"));
	expectFalse(enfa11->process("ca"));
	expectFalse(enfa11->process("bc"));
	expectFalse(enfa11->process("cb"));
	expectFalse(enfa11->process("abc"));

	eNFA *enfa12 = regexToNFA("(a+b)*");
	//std::cout << *enfa12 << std::endl;
	//std::cout << "Regex '(a+b)*'" << std::endl;
	expectTrue(enfa12->process(""));
	expectTrue(enfa12->process("a"));
	expectTrue(enfa12->process("b"));
	expectTrue(enfa12->process("ab"));
	expectTrue(enfa12->process("aab"));
	expectTrue(enfa12->process("abb"));
	expectTrue(enfa12->process("aa"));
	expectTrue(enfa12->process("aaaaaaaa"));
	expectTrue(enfa12->process("aaaaaaaab"));
	expectTrue(enfa12->process("abbbbbbbb"));
	expectTrue(enfa12->process("bbbbbbbb"));
	expectTrue(enfa12->process("abaabaaabbbbabbaba"));
	expectFalse(enfa12->process("c"));
	expectFalse(enfa12->process("ca"));
	expectFalse(enfa12->process("ac"));

	eNFA inputNFA = generateNFA("NFAexample.txt");
	//std::cout << inputNFA << std::endl;
	expectFalse(inputNFA.process(""));
	expectFalse(inputNFA.process("a"));
	expectTrue(inputNFA.process("b"));
	expectTrue(inputNFA.process("c"));
	expectFalse(inputNFA.process("d"));
	expectTrue(inputNFA.process("da"));
	expectTrue(inputNFA.process("db"));
	expectTrue(inputNFA.process("dc"));
	expectFalse(inputNFA.process("dd"));
	inputNFA.toFile("NFAOUT.txt");
	eNFA inputNFA2 = generateNFA("NFAOUT.txt");

	expectFalse(inputNFA2.process(""));
	expectFalse(inputNFA2.process("a"));
	expectTrue(inputNFA2.process("b"));
	expectTrue(inputNFA2.process("c"));
	expectFalse(inputNFA2.process("d"));
	expectTrue(inputNFA2.process("da"));
	expectTrue(inputNFA2.process("db"));
	expectTrue(inputNFA2.process("dc"));
	expectFalse(inputNFA2.process("dd"));

	eNFA *enfa13 = regexToNFA("(((0+(10))*)((1+(01))*))(0+<)");
	//std::cout << *enfa13 << std::endl;
	//std::cout << "Regex '(0+10)*(1+01)*(0+_)'" << std::endl;
	expectTrue(enfa13->process(""));
	expectTrue(enfa13->process("0"));
	expectTrue(enfa13->process("1"));
	expectTrue(enfa13->process("01"));
	expectTrue(enfa13->process("10"));
	expectTrue(enfa13->process("001"));
	expectTrue(enfa13->process("0011"));
	expectFalse(enfa13->process("1100"));
	expectTrue(enfa13->process("110"));
	expectTrue(enfa13->process("0001001011010"));
	expectFalse(enfa13->process("110001001011010"));
	expectFalse(enfa13->process("001011001110"));
	expectTrue(enfa13->process("00101001110"));
	expectTrue(enfa13->process("0000000"));
	expectTrue(enfa13->process("1111111"));
	expectTrue(enfa13->process("000010001001010110111011110"));


	eNFA *enfa14 = regexToNFA("((ab)*)+((cd)*)");
	//std::cout << *enfa14 << std::endl;
	//std::cout << "Regex '(ab)*+(cd)*'" << std::endl;
	expectTrue(enfa14->process(""));
	expectFalse(enfa14->process("a"));
	expectFalse(enfa14->process("b"));
	expectFalse(enfa14->process("c"));
	expectFalse(enfa14->process("d"));
	expectTrue(enfa14->process("cd"));
	expectFalse(enfa14->process("dc"));
	expectTrue(enfa14->process("ab"));
	expectFalse(enfa14->process("abcd"));
	expectTrue(enfa14->process("ababababababab"));
	expectFalse(enfa14->process("abababababababc"));
	expectTrue(enfa14->process("cdcdcdcdcdcd"));

	eNFA *test = regexToNFA("(((((((A+B+C+D+E+F+G+H+I+J+K+L+M+N+O+P+Q+R+S+T+U+V+W+X+Y+Z+a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+0+1+2+3+4+5+6+7+8+9+!+#+$+%+&+'+-+/+=+?+^+_+`+{+}+|+~+.)((A+B+C+D+E+F+G+H+I+J+K+L+M+N+O+P+Q+R+S+T+U+V+W+X+Y+Z+a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+0+1+2+3+4+5+6+7+8+9+!+#+$+%+&+'+-+/+=+?+^+_+`+{+}+|+~+.)*))@)(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+0+1+2+3+4+5+6+7+8+9+-+.))((a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+0+1+2+3+4+5+6+7+8+9+-+.)*)).)(a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+.))((a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p+q+r+s+t+u+v+w+x+y+z+.)*)");
	expectTrue(test->process("jakob.struye@ua.ac.be"));
	expectFalse(test->process("jakob.struye@ua.aXc.be"));
	return fFails;
}

Test::~Test() {
	std::cout << "[RESULT] " << this->fGoods << " passed " << this->fFails << "crashed." << std::endl;
}

} /* namespace FA */
