#ifndef _NFA_SIMULATE_H_
#define _NFA_SIMULATE_H_
#include "nfa.h"
#include "nfa_list.h"
#include <stdbool.h>
#include <stddef.h>

/**
 * Returns the number of characters until the first match, or 0 if the string doesn't match
 */
size_t nfaMatches(nfa_state* nfa, char const* targetString);

#endif //_NFA_SIMULATE_H_
