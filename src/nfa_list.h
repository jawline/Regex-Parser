#ifndef _NFA_LIST_DEF_H_
#define _NFA_LIST_DEF_H_
#include "nfa.h"
#include <stdbool.h>

typedef struct nfa_list {
	nfa_state** states;
	int currentSize;
} nfa_list;

void nfaListAllocate(nfa_list* list, int maxSize);
void nfaListReset(nfa_list* list);
void nfaListStart(nfa_list* list, nfa_state* state);
void nfaListAddState(nfa_list* list, nfa_state* state);
void nfaListFree(nfa_list* list);
bool nfaListContains(nfa_list* list, nfa_state* state);

#endif //_NFA_LIST_DEF_H_
