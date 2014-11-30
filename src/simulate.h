#ifndef _NFA_SIMULATE_H_
#define _NFA_SIMULATE_H_
#include "nfa.h"
#include "nfa_list.h"
#include <stdbool.h>

bool nfaMatches(nfa_state* nfa, char* string);

#endif //_NFA_SIMULATE_H_
