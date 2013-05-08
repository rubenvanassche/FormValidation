#ifndef SC_H_
#define SC_H_

#include "DFA.h"
#include "eNFA.h"
#include "common.h"

namespace FA {

	DFA eNFAtoDFA(eNFA&);

}

#endif /* DFA_H_ */
