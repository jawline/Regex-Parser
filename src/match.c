#include "match.h"

void nfaBuildReachableStates(unsigned char c, nfa_list* current, nfa_list* next) {

	unsigned int i;
	nfa_state* state;

	nfaListReset(next);

	for (i = 0; i < current->currentSize; i++) {
	
                state = current->states[i];
		if (state->path && (state->target == c || state->target == 258)) {
			nfaListAddFollowPaths(next, state->path);
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

void nfaStateSwap(nfa_list** left, nfa_list** right) {
  nfa_list* temp;
  temp = *left;
  *left = *right;
  *right = temp;
}

size_t nfaMatches(nfa_state* nfa, char const* targetString) {
	
	nfa_list l1, l2;
	nfa_list* currentStates, *nextStates;
	char const* currentString = targetString;

	nfaListAllocate(&l1, 1000);
	nfaListAllocate(&l2, 1000);

	currentStates = &l1;
	nextStates = &l2;

	nfaListStart(currentStates, nfa);

	for (; *currentString; currentString++) {
		nfaBuildReachableStates(*targetString, currentStates, nextStates);
		nfaStateSwap(&currentStates, &nextStates);
		if (nfaListMatches(currentStates)) {
			return currentString - targetString;
		}
	}

	return 0;
}
