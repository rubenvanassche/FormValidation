/*
 * eNFA.h
 *
 *  Created on: Apr 28, 2013
 *      Author: jakob
 */

#ifndef ENFA_H_
#define ENFA_H_

#include <map>
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "common.h"


namespace FA {


class eNFA {
public:

	eNFA();

	eNFA(alphabet, states, transitions, startState*, acceptingStates);

	const transitions& getDelta() const {
		return delta;
	}

	const acceptingStates& getF() const {
		return F;
	}

	const states& getQ() const {
		return Q;
	}

	const startState* getQ0() const {
		return q0;
	}

	const alphabet& getSigma() const {
		return sigma;
	}

	bool process(std::string) const;


	friend std::ostream& operator<<(std::ostream&, const eNFA&);


private:

	alphabet sigma;
	states Q;
	transitions delta;
	startState *q0;
	acceptingStates F;


};


eNFA generateNFA(std::string);
}



#endif /* ENFA_H_ */
