#ifndef _NFA_LIST_DEF_H_
#define _NFA_LIST_DEF_H_
#include "nfa.h"

typedef struct nfa_list {
	nfa_state** states;
	int currentSize;
} nfa_list;

void createNfaList(nfa_list* list, int maxSize);
void startNfaList(nfa_list* list, nfa_state* state);
void addNfaListState(nfa_list* list, nfa_state* state);
void freeNfaList(nfa_list* list);

#endif //_NFA_LIST_DEF_H_
