#include "nfa.h"
#include <stdlib.h>

nfa_state* createNfa(bool split, nfa_state* path, nfa_state* alternative) {

	nfa_state* construct = (nfa_state*) malloc(sizeof(nfa_state));

	construct->target = split;
	construct->path = path;
	construct->alternative = alternative;
	construct->lastid = 0;

	return construct;
}

void freeNfa(nfa_state* nfa) {

	if (nfa->path) {
		freeNfa(nfa->path);
	}

	if (nfa->alternative) {
		freeNfa(nfa->alternative);
	}

	free(nfa);
}
