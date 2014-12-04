/*
 * fragment_stack.h
 *
 *  Created on: 3 Dec 2014
 *      Author: blake
 */

#ifndef FRAGMENT_STACK_H_
#define FRAGMENT_STACK_H_
#include "nfa_fragment.h"

typedef struct fragment_stack {
	nfa_fragment** items;
	unsigned int top;
} fragment_stack;

void nfaFragmentStackAllocate(fragment_stack* stack, unsigned int max);
void nfaFragmentStackFree(fragment_stack* stack);

void nfaFragmentStackPush(fragment_stack* stack, nfa_fragment* item);
nfa_fragment* nfaFragmentStackPop(fragment_stack* stack);

#endif /* FRAGMENT_STACK_H_ */
