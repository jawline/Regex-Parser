/*
 * parser.c
 *
 *  Created on: 30 Nov 2014
 *      Author: blake
 */
#include "parser.h"
#include <stdlib.h>

bool regexParse(regex* regexStructure, char const* input) {

	//Allocate a list to keep track of regex states
	nfaListAllocate(&regexStructure->stateList, 1000);

	regexStructure->start = nfaCreate('b', nfaCreate(257, NULL, NULL), NULL);
	nfaListAddState(&regexStructure->stateList, regexStructure->start);

	return true;
}

void regexFree(regex* regexStructure) {

	//Free the regex states
	unsigned int i;

	for (i = 0; i < regexStructure->stateList.currentSize; i++) {
		free(regexStructure->stateList.states[i]);
	}

	nfaListFree(&regexStructure->stateList);
}
