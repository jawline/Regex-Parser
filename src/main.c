#include <stdio.h>
#include <stdlib.h>
#include "nfa.h"
#include "match.h"

int main(int argc, char** argv) {

	nfa_state* looped = nfaCreate('b', NULL, NULL);
	nfa_state* end = nfaCreate(257, NULL, NULL);
	nfa_state* inner = nfaCreate(256, looped, end);
	looped->path = inner;

	printf("%i\n", nfaMatches(looped, "bbb"));
	nfaFree(looped);
	return 1;
}
