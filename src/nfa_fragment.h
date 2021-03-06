#ifndef _NFA_FRAGMENT_H_
#define _NFA_FRAGMENT_H_
#include "nfa.h"
#include "nfa_list.h"

/**
 * NFA fragments are a set of NFA states. NFA fragments are concatenated together to generate the NFA
 * Example: (a|c) would become a NFA fragment which accepted either a or c, (a|c)d would be created by 
 * creating concatenating the NFA fragment generated by d with the NFA fragment generated from (a|c)
 */
typedef struct nfa_fragment {
	nfa_state* start;
	nfa_list tails;
} nfa_fragment;

/**
 * Allocate and initialise a new NFA fragment
 */
nfa_fragment* nfaFragmentCreate();

/**
 * Free an NFA fragment
 */
void nfaFragmentFree(nfa_fragment* fragment);

/*
 * Add a new tail state to the NFA fragment. tail states are all the states at the end of
 * the fragment which have no current target state
 */
void nfaFragmentAddTail(nfa_fragment* fragment, nfa_state* state);

/**
 * Patch is used to connect two fragments together
 * Sets the target of each tail in a fragment to the specified target state
 */
void nfaFragmentPatch(nfa_fragment* fragment, nfa_state* target);

/**
 * Fill tails adds all tails in other to the tails of the fragment
 */
void nfaFragmentFillTails(nfa_fragment* fragment, nfa_fragment* other);

#endif //_NFA_FRAGMENT_H_