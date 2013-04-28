
#ifndef COMMON_H_
#define COMMON_H_


namespace FA {

typedef std::string state;
typedef char symbol;
typedef std::vector<state> states;
typedef std::map<symbol, state*> transitionsInternal;
typedef std::map<state*, transitionsInternal> transitions;
typedef std::set<state*> acceptingStates;
typedef std::set<symbol> alphabet;
typedef std::string startState;

}

#endif /* COMMON_H_ */
