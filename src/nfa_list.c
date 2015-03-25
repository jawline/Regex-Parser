#include "nfa_list.h"
#include <stdlib.h>

unsigned int listid = 0;

void nfaListAllocate(nfa_list* list, int maxSize) {
	list->states = malloc(sizeof(nfa_state*) * maxSize);
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
	nfaListAddFollowPaths(list, state);
}

bool nfaListContains(nfa_list* list, nfa_state* state) {
	unsigned int i;
	for (i = 0; i < list->currentSize; i++) {
		if (list->states[i] == state) {
			return true;
		}
	}
	return false;
}

void nfaListAdd(nfa_list* list, nfa_state* state) {
	list->states[list->currentSize++] = state;
}

void nfaListAddFollowPaths(nfa_list* list, nfa_state* state) {

	if (state->lastid == listid) {
		return;
	}

	state->lastid = listid;

	if (state->target == 256) {
		nfaListAddFollowPaths(list, state->path);
		nfaListAddFollowPaths(list, state->alternative);
	} else {
		nfaListAdd(list, state);
	}
}
