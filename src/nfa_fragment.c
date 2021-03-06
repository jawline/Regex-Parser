#include "nfa_fragment.h"
#include <stdlib.h>

nfa_fragment* nfaFragmentCreate() {
	nfa_fragment* frag = malloc(sizeof(nfa_fragment));
	frag->start = NULL;
	nfaListAllocate(&frag->tails, 50);
	return frag;
}

void nfaFragmentFree(nfa_fragment* fragment) {
	nfaListFree(&fragment->tails);
	free(fragment);
}

void nfaFragmentAddTail(nfa_fragment* fragment, nfa_state* state) {
	nfaListAdd(&fragment->tails, state);
}

void nfaFragmentPatch(nfa_fragment* fragment, nfa_state* target) {
	unsigned int i;
	for (i = 0; i < fragment->tails.currentSize; i++) {
		fragment->tails.states[i]->path = target;
	}
}

void nfaFragmentFillTails(nfa_fragment* fragment, nfa_fragment* other) {
	unsigned int i;
	for (i = 0; i < other->tails.currentSize; i++) {
		nfaFragmentAddTail(fragment, other->tails.states[i]);
	}
}
