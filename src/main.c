#include <stdio.h>
#include <stdlib.h>
#include "match.h"
#include "parser.h"

int main(int argc, char** argv) {
	regex reg;

	if (argc != 3) {
		printf("Incorrect Usage\n");
		return -1;
	}

	if (!regexParse(&reg, argv[1])) {
		printf("Error parsing regex %s\n", argv[1]);
		return -1;
	}

	printf("%s, %lu characters match from the start of the string\n", nfaMatches(reg.start, argv[2]) > 0 ? "matches" : "does not match", nfaMatches(reg.start, argv[2]));
	regexFree(&reg);

	return 1;
}
