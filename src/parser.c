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

nfa_fragment* basicFragment(nfa_state* state) {
	nfa_fragment* frag = nfaFragmentCreate();
	frag->start = state;
	nfaFragmentAddTail(frag, state);
	return frag;
}

void fillTails(nfa_fragment* fragment, nfa_fragment* tails) {

	unsigned int i;

	for (i = 0; i < tails->tails.currentSize; i++) {
		nfaFragmentAddTail(fragment, tails->tails.states[i]);
	}
}

bool regexParse(regex* regexStructure, char const* input) {

	fragment_stack stateStack;
	nfa_state *state;
	nfa_fragment *t1, *t2, *t3;

	//Allocate a list to keep track of regex states
	nfaListAllocate(&regexStructure->stateList, 1000);

	nfaFragmentStackAllocate(&stateStack, 100);

	for (; *input; input++) {

		switch (*input) {
		case '.':

			//Pop the two sides of the concat
			t1 = nfaFragmentStackPop(&stateStack);
			t2 = nfaFragmentStackPop(&stateStack);

			//Patch the tail states on t1 to the start state on t2
			nfaFragmentPatch(t1, t2);

			//Create a new fragment using t2's tail states and t1's start states (The concat of both)
			t3 = nfaFragmentCreate();
			t3->start = t1->start;
			fillTails(t3, t2);

			//Free the two popped fragment
			nfaFragmentFree(t1);
			nfaFragmentFree(t2);

			//Push the new one
			nfaFragmentStackPush(&stateStack, t3);
			break;
		case '|':
			t1 = nfaFragmentStackPop(&stateStack);
			t2 = nfaFragmentStackPop(&stateStack);

			state = nfaCreate(256, t1->start, t2->start);
			nfaListAddState(&regexStructure->stateList, state);

			t3 = nfaFragmentCreate();
			t3->start = state;
			fillTails(t3, t1);
			fillTails(t3, t2);

			nfaFragmentFree(t1);
			nfaFragmentFree(t2);
			nfaFragmentStackPush(&stateStack, t3);
			break;
		case '$':
			state = nfaCreate(257, NULL, NULL);
			nfaListAddState(&regexStructure->stateList, state);
			nfaFragmentStackPush(&stateStack, basicFragment(state));
			break;
		default:
			state = nfaCreate(*input, NULL, NULL);
			nfaListAddState(&regexStructure->stateList, state);
			nfaFragmentStackPush(&stateStack, basicFragment(state));
			break;
		}
	}

	t1 = nfaFragmentStackPop(&stateStack);
	regexStructure->start = t1->start;

	nfaFragmentFree(t1);

	while ((t1 = nfaFragmentStackPop(&stateStack)) != NULL) {
		printf("WARN: Stuff left in stack\n");
		nfaFragmentFree(t1);
	}

	nfaFragmentStackFree(&stateStack);

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
