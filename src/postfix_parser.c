/*
 * parser.c
 *
 *  Created on: 30 Nov 2014
 *      Author: blake
 */
#include "postfix_parser.h"
#include "nfa_fragment.h"
#include "fragment_stack.h"
#include "nfa.h"

#include <stdlib.h>
#include <stdio.h>

nfa_fragment* basicFragment(nfa_state* state) {
	nfa_fragment* frag = nfaFragmentCreate();
	frag->start = state;
	nfaFragmentAddTail(frag, state);
	return frag;
}

nfa_state* createState(unsigned short condition, regex* regex) {
	nfa_state* state = nfaStateCreate(condition, NULL, NULL);
	nfaListAdd(&regex->stateList, state);
	return state;
}

bool regexParse(regex* regexStructure, char const* input) {

	nfa_fragment_stack stateStack;
	nfa_state *state, *state2;
	nfa_fragment *t1, *t2, *t3;

	nfaListAllocate(&regexStructure->stateList, 1000);
	nfaFragmentStackAllocate(&stateStack, 100);

	for (; *input; input++) {

		switch (*input) {
		case '.':

			//Pop the two sides of the concat
			t2 = nfaFragmentStackPop(&stateStack);
			t1 = nfaFragmentStackPop(&stateStack);

			//Patch the tail states on t1 to the start state on t2
			nfaFragmentPatch(t1, t2->start);

			//Create a new fragment using t2's tail states and t1's start states (The concat of both)
			t3 = nfaFragmentCreate();
			t3->start = t1->start;
			nfaFragmentFillTails(t3, t2);

			//Free the two popped fragment
			nfaFragmentFree(t1);
			nfaFragmentFree(t2);

			//Push the new one
			nfaFragmentStackPush(&stateStack, t3);
			break;
		case '|':

			t2= nfaFragmentStackPop(&stateStack);
			t1 = nfaFragmentStackPop(&stateStack);

			state = createState(256, regexStructure);
			state->path = t1->start;
			state->alternative = t2->start;

			t3 = nfaFragmentCreate();
			t3->start = state;

			nfaFragmentFillTails(t3, t1);
			nfaFragmentFillTails(t3, t2);

			nfaFragmentFree(t1);
			nfaFragmentFree(t2);

			nfaFragmentStackPush(&stateStack, t3);
			break;
		case '+':
			t1 = nfaFragmentStackPop(&stateStack);

			state = createState(256, regexStructure);
			state->path = NULL;
			state->alternative = t1->start;

			nfaFragmentPatch(t1, state);

			t3 = nfaFragmentCreate();
			t3->start = t1->start;
			nfaFragmentAddTail(t3, state);

			nfaFragmentFree(t1);
			nfaFragmentStackPush(&stateStack, t3);
			break;
		case '*':
			t1 = nfaFragmentStackPop(&stateStack);

			state2 = createState(256, regexStructure);
			state2->path = NULL;
			state2->alternative = t1->start;

			state = createState(256, regexStructure);
			state->path = NULL;
			state->alternative = state2;

			nfaFragmentPatch(t1, state2);

			t3 = nfaFragmentCreate();
			t3->start = state;

			nfaFragmentAddTail(t3, state);
			nfaFragmentAddTail(t3, state2);

			nfaFragmentFree(t1);
			nfaFragmentStackPush(&stateStack, t3);
			break;
		case '?':
		        t1 = nfaFragmentStackPop(&stateStack);
		        
			state = createState(256, regexStructure);
			state->path = NULL;
			state->alternative = t1->start;
			
			t2 = nfaFragmentCreate();
			t2->start = state;
			nfaFragmentAddTail(t2, state);
			nfaFragmentFillTails(t2, t1);

			nfaFragmentFree(t1);
			nfaFragmentStackPush(&stateStack, t2);
			break;
		case '$':
			state = createState(257, regexStructure);
			nfaFragmentStackPush(&stateStack, basicFragment(state));
			break;
		default:
			state = createState(*input, regexStructure);
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
