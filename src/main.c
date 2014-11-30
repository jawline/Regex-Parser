#include <stdio.h>
#include <stdlib.h>
#include "nfa.h"

int main(int argc, char** argv) {

	nfa_state* start = createNfa(256, createNfa('a', NULL, NULL),
			createNfa('b', createNfa(257, NULL, NULL), NULL));

	freeNfa(start);
}
