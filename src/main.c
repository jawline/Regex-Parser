#include <stdio.h>
#include <stdlib.h>
#include "match.h"
#include "postfix_parser.h"
#include "infix.h"

int main(int argc, char** argv) {

	regex reg;

	if (argc != 3) {
		printf("Incorrect Usage\n");
		return -1;
	}

	printf("Regex Definition: %s\nMatching Against: %s\n", argv[1], argv[2]);

	char* infixWithConcatenations = infixInsertExplicitConcatenation(argv[1]);
	printf("Infix with concatenations inserted %s\n", infixWithConcatenations);

	char* postFix = infixToPostfix(infixWithConcatenations);
	printf("Infix Conversion: %s\n", postFix);
   
	free(infixWithConcatenations);

	regexParse(&reg, postFix);
	free(postFix);

	printf("%s\n", nfaMatches(reg.start, argv[2]) ? "matches" : "does not match");
	regexFree(&reg);

	return 1;
}
