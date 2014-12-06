#include "nfa.h"
#include <stdlib.h>

nfa_state* nfaStateCreate(unsigned short split, nfa_state* path, nfa_state* alternative) {

	nfa_state* construct = malloc(sizeof(nfa_state));

	construct->target = split;
	construct->path = path;
	construct->alternative = alternative;
	construct->lastid = 0;

	return construct;
}

void nfaStateFree(nfa_state* state) {
	free(state);
}
