#ifndef COMMON_H_
#define COMMON_H_

#include <string>
#include <map>
#include <set>
#include <vector>


namespace FA {

typedef std::string state;
typedef std::vector<state*> stateset;
typedef char symbol;
typedef std::vector<state*> states;
typedef std::map<symbol, stateset> transitionsInternal;
typedef std::map<state*, transitionsInternal> transitions;
typedef std::set<state*> acceptingStates;
typedef std::set<symbol> alphabet;
typedef std::string regex;
}

#endif /* COMMON_H_ */
