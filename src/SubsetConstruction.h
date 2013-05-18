#ifndef SC_H_
#define SC_H_

#include "DFA.h"
#include "eNFA.h"
#include "common.h"

namespace FA {
	/**
	 * @brief Generate DFA describing same language as an eNFA
	 *
	 * @param automata the eNFA
	 *
	 * @return the DFA
	 */
	DFA eNFAtoDFA(eNFA&);

}

#endif /* DFA_H_ */
