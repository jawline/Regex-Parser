#include "nfa_list.h"
#include <stdlib.h>

unsigned int listid = 0;

void createNfaList(nfa_list* list, int maxSize) {
	list->states = (nfa_state**) malloc(sizeof(nfa_state*) * maxSize);
}

void freeNfaList(nfa_list* list) {
	free(list->states);
	list->currentSize = 0;
}

void startNfaList(nfa_list* list, nfa_state* state) {
	list->currentSize = 0;
	addNfaListState(list, state);
}

void addNfaListState(nfa_list* list, nfa_state* state) {

	if (!state || state->lastid == listid) {
		return;
	}

	state->lastid = listid;

	if (state->target == 256) {
		addNfaListState(list, state->path);
		addNfaListState(list, state->alternative);
	}

	list->states[list->currentSize++] = state;
}
