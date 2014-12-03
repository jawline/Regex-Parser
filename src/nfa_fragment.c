#include "nfa_fragment.h"
#include <stdlib.h>

nfa_fragment* nfaFragmentCreate() {
	nfa_fragment* frag = (nfa_fragment*) malloc(sizeof(nfa_fragment));
	frag->start = NULL;
	nfaListAllocate(&frag->tails, 50);
	return frag;
}

void nfaFragmentFree(nfa_fragment* fragment) {
	nfaListFree(&fragment->tails);
	free(fragment);
}

void nfaFragmentAddTail(nfa_fragment* fragment, nfa_state* state) {
	nfaListAddState(&fragment->tails, state);
}
