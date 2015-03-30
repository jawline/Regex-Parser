#include "nfa_list.h"
#include <stdlib.h>
#include <string.h>

unsigned int listid = 0;
unsigned int defaultGrowSize = 128;

void nfaListAllocate(nfa_list* list, int maxSize) {
	list->states = malloc(sizeof(nfa_state*) * maxSize);
	nfaListReset(list, maxSize);
}

void nfaListFree(nfa_list* list) {
	free(list->states);
	list->currentSize = 0;
}

void nfaListReset(nfa_list* list, unsigned int currentMax) {
	listid++;
	list->currentSize = 0;
	list->currentMax = currentMax;
}

void nfaListStart(nfa_list* list, nfa_state* state) {
	nfaListReset(list, list->currentMax);
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

void nfaListGrow(nfa_list* list, unsigned int growSize) {
	nfa_state** mem = malloc(sizeof(nfa_state*) * (list->currentMax + growSize));
	memcpy(mem, list->states, sizeof(nfa_state*) * list->currentMax);
	free(list->states);
	list->states = mem;
	list->currentMax = list->currentMax + growSize;
}

void nfaListAdd(nfa_list* list, nfa_state* state) {
	if (list->currentSize == list->currentMax) {
		nfaListGrow(list, defaultGrowSize);
	}
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
