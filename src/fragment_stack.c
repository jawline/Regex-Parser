/*
 * fragment_stack.c
 *
 *  Created on: 3 Dec 2014
 *      Author: blake
 */
#include "fragment_stack.h"
#include <stdlib.h>

void nfaFragmentStackAllocate(fragment_stack* stack, unsigned int max) {
	stack->items = (fragment_stack**) malloc(sizeof(fragment_stack*) * max);
	stack->top = 0;
}

void nfaFragmentStackFree(fragment_stack* stack) {
	free(stack->items);
}
