/*
 * fragment_stack.c
 *
 *  Created on: 3 Dec 2014
 *      Author: blake
 */
#include "fragment_stack.h"
#include <stdlib.h>

void nfaFragmentStackAllocate(fragment_stack* stack, unsigned int max) {
	stack->items = malloc(sizeof(fragment_stack*) * max);
	stack->top = 0;
}

void nfaFragmentStackFree(fragment_stack* stack) {
	free(stack->items);
}

void nfaFragmentStackPush(fragment_stack* stack, nfa_fragment* item) {
	stack->items[stack->top++] = item;
}

nfa_fragment* nfaFragmentStackPop(fragment_stack* stack) {
	return stack->top == 0 ? NULL : stack->items[--stack->top];
}
