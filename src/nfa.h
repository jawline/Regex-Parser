/*
 * nfa.h
 *
 *  Created on: 29 Nov 2014
 *      Author: blake
 */

#ifndef NFA_H_
#define NFA_H_
#include <stdbool.h>

/**
 * A state within an NFA, has a target (The character required to travel to it) 
 * as well as a path (The next state) or an alternative if this is a split state
 */
typedef struct nfa_state {
	unsigned short target;
	struct nfa_state* path;
	struct nfa_state* alternative;
	unsigned int lastid;
} nfa_state;

/**
 * Create a new NFA state
 */
nfa_state* nfaStateCreate(unsigned short split, nfa_state* path, nfa_state* alternative);

/**
 * Free all memory used by a specific state
 * Note: Does not free connected states, each state NFA must be explicitely freed
 */
void nfaStateFree(nfa_state* state);

#endif /* NFA_H_ */
