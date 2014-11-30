#include "simulate.h"

void calculateNextStates(unsigned char c, nfa_list* current, nfa_list* next) {

	unsigned int i;
	nfa_state* state;

	next->currentSize = 0;

	for (i = 0; i < current->currentSize; i++) {
		state = current->states[current->currentSize];
		if (state->target == c) {
			addNfaListState(next, state);
		}
	}
}

bool nfaMatches(nfa_state* nfa, char const* targetString) {

	nfa_list l1, l2;
	createNfaList(&l1, 1000);
	createNfaList(&l2, 1000);

	nfa_list* currentStates, *nextStates, *t;

	currentStates = &l1;
	nextStates = &l2;

	startNfaList(currentStates, nfa);

	for (; *targetString; targetString++) {
		calculateNextStates(*targetString, currentStates, nextStates);

		//Swap temps
		t = currentStates;
		currentStates = nextStates;
		nextStates = t;
	}

	return true;
}
