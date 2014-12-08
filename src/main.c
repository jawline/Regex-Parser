#include <stdio.h>
#include <stdlib.h>
#include "match.h"
#include "postfix_parser.h"
#include "infix.h"

int main(int argc, char** argv) {

	regex reg;
	unsigned int i;

	for (i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	if (argc != 3) {
		printf("Incorrect Usage\n");
		return -1;
	}

	char* postFix = infixToPostfix(argv[1]);
	printf("Infix Conversion: %s\n", postFix);
	regexParse(&reg, postFix);
	free(postFix);

	printf("%s\n", nfaMatches(reg.start, argv[2]) ? "matches" : "does not match");
	regexFree(&reg);

	return 1;
}
