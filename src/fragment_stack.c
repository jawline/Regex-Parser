/*
 * fragment_stack.c
 *
 *  Created on: 3 Dec 2014
 *      Author: blake
 */
#include "fragment_stack.h"
#include <stdlib.h>
#include <stdio.h>

void nfaFragmentStackAllocate(nfa_fragment_stack* stack, unsigned int max) {
	stack->items = malloc(sizeof(nfa_fragment_stack*) * max);
	stack->top = 0;
}

void nfaFragmentStackFree(nfa_fragment_stack* stack) {
	free(stack->items);
}

void nfaFragmentStackPush(nfa_fragment_stack* stack, nfa_fragment* item) {
	stack->items[stack->top++] = item;
}

nfa_fragment* nfaFragmentStackPop(nfa_fragment_stack* stack) {
	return stack->top == 0 ? NULL : stack->items[--stack->top];
}

unsigned int nfaFragmentStackSize(nfa_fragment_stack* stack) {
	return stack->top;
}

bool nfaFragmentStackEmpty(nfa_fragment_stack* stack) {
	return stack->top > 0;
}
