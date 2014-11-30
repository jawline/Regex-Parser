#include <stdio.h>
#include <stdlib.h>
#include "match.h"
#include "parser.h"

int main(int argc, char** argv) {

	regex reg;
	regexParse(&reg, "+a");

	printf("%i\n", nfaMatches(reg.start, "a"));

	regexFree(&reg);

	return 1;
}
