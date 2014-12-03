#ifndef _NFA_FRAGMENT_H_
#define _NFA_FRAGMENT_H_
#include "nfa.h"
#include "nfa_list.h"

typedef struct nfa_fragment {
	nfa_state* start;
	nfa_list tails;
} nfa_fragment;

nfa_fragment* nfaFragmentCreate();
void nfaFragmentFree(nfa_fragment* fragment);
void nfaFragmentAddTail(nfa_fragment* fragment, nfa_state* state);

#endif //_NFA_FRAGMENT_H_
