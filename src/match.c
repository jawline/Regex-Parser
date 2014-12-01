#include "match.h"

void nfaBuildReachableStates(unsigned char c, nfa_list* current, nfa_list* next) {

	unsigned int i;
	nfa_state* state;

	nfaListReset(next);

	for (i = 0; i < current->currentSize; i++) {
		state = current->states[i];

		if (state->target == c) {
			nfaListAddState(next, state->path);
		}
	}
}

bool nfaListMatches(nfa_list* nfa) {

	unsigned int i;

	for (i = 0; i < nfa->currentSize; i++) {
		if (nfa->states[i]->target == 257) {
			return true;
		}
	}

	return false;
}

bool nfaMatches(nfa_state* nfa, char const* targetString) {

	nfa_list l1, l2;
	nfaListAllocate(&l1, 1000);
	nfaListAllocate(&l2, 1000);

	nfa_list* currentStates, *nextStates, *t;

	currentStates = &l1;
	nextStates = &l2;

	nfaListStart(currentStates, nfa);

	for (; *targetString; targetString++) {
		nfaBuildReachableStates(*targetString, currentStates, nextStates);

		//Swap temps
		t = currentStates;
		currentStates = nextStates;
		nextStates = t;
	}

	return nfaListMatches(currentStates);
}
