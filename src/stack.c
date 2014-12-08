#include "stack.h"
#include <string.h>
#include <stdlib.h>

generic_stack* stackAllocate(unsigned int elementSize, unsigned int max) {

	generic_stack* newStack = malloc(sizeof(generic_stack));

	newStack->data = malloc(elementSize * max);
	newStack->current = 0;
	newStack->elementSize = elementSize;
	newStack->max = max;

	return newStack;
}

void stackFree(generic_stack* stack) {
	free(stack->data);
	free(stack);
}

void stackPush(generic_stack* stack, void* elem) {
	memcpy(stack->data + stack->current, elem, stack->elementSize);
	stack->current += stack->elementSize;
}

bool stackPop(generic_stack* stack, void* elem) {

	if (!stack->current) {
		return false;
	}

	stackPeek(stack, elem);
	stack->current -= stack->elementSize;
	return true;
}

bool stackEmpty(generic_stack* stack) {
	return stackSize(stack) == 0;
}

unsigned int stackSize(generic_stack* stack) {
	return stack->current / stack->elementSize;
}

void stackPeek(generic_stack* stack, void* elem) {
	if (!stackEmpty(stack)) {
		memcpy(elem, stack->data + (stack->current - stack->elementSize),
				stack->elementSize);
	}
}
