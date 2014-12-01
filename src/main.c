#include <stdio.h>
#include <stdlib.h>
#include "match.h"
#include "parser.h"

int main(int argc, char** argv) {


	unsigned int i;

	for (i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	if (argc != 3) {
		printf("Incorrect Usage\n");
		return -1;
	}

	regex reg;
	regexParse(&reg, argv[1]);

	printf("%i\n", nfaMatches(reg.start, argv[2]));

	regexFree(&reg);

	return 1;
}
