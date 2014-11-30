#include "nfa_list.h"
#include <stdlib.h>

unsigned int listid = 0;

void nfaListAllocate(nfa_list* list, int maxSize) {
	list->states = (nfa_state**) malloc(sizeof(nfa_state*) * maxSize);
	nfaListReset(list);
}

void nfaListFree(nfa_list* list) {
	free(list->states);
	list->currentSize = 0;
}

void nfaListReset(nfa_list* list) {
	listid++;
	list->currentSize = 0;
}

void nfaListStart(nfa_list* list, nfa_state* state) {
	nfaListReset(list);
	nfaListAddState(list, state);
}

void nfaListAddState(nfa_list* list, nfa_state* state) {

	if (!state || state->lastid == listid) {
		return;
	}

	state->lastid = listid;

	if (state->target == 256) {
		nfaListAddState(list, state->path);
		nfaListAddState(list, state->alternative);
		return;
	}

	list->states[list->currentSize++] = state;
}
