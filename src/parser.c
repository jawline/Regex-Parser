/*
 * parser.c
 *
 *  Created on: 30 Nov 2014
 *      Author: blake
 */
#include "parser.h"
#include "nfa_fragment.h"
#include "fragment_stack.h"
#include <stdlib.h>
#include <stdio.h>

bool empty(nfa_list* list) {
	return list->currentSize == 0;
}

nfa_state* pop(nfa_list* list) {

	if (!empty(list)) {
		list->currentSize -= 1;
		return list->states[list->currentSize];
	}

	return NULL;
}

void push(nfa_list* list, nfa_state* state) {
	list->states[list->currentSize] = state;
	list->currentSize += 1;
}

bool regexParse(regex* regexStructure, char const* input) {

	nfa_list stateStack;
	nfa_state *state, *other, *t1;

	//Allocate a list to keep track of regex states
	nfaListAllocate(&regexStructure->stateList, 1000);

	nfaListAllocate(&stateStack, 1000);

	for (; *input; input++) {

		switch (*input) {
		case '.':
			state = pop(&stateStack);
			other = pop(&stateStack);
			state->path = other;
			push(&stateStack, state);
			break;
		case '|':
			other = pop(&stateStack);
			state = pop(&stateStack);
			printf("%c %c\n", state->target, other->target);

			t1 = nfaCreate(256, state, other);
			nfaListAddState(&regexStructure->stateList, t1);

			push(&stateStack, t1);
			break;
		case '+':
			state = pop(&stateStack);

			other = nfaCreate(256, NULL, NULL);
			nfaListAddState(&regexStructure->stateList, other);
			other->alternative = state;
			state->path = other;
			break;
		case '$':
			state = nfaCreate(257, NULL, NULL);
			nfaListAddState(&regexStructure->stateList, state);
			push(&stateStack, state);
			break;
		default:
			state = nfaCreate(*input, NULL, NULL);
			nfaListAddState(&regexStructure->stateList, state);
			push(&stateStack, state);
			break;
		}
	}

	regexStructure->start = pop(&stateStack);

	nfaListFree(&stateStack);

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
