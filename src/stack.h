#ifndef _STACK_H_
#define _STACK_H_
#include <stdbool.h>

/**
 * A generic stack object.
 * Can store a stack of fixed sized items accessed with accompnying function
 */
typedef struct generic_stack {
	void* data;
	unsigned int current;
	unsigned int max;
	unsigned int elementSize;
} generic_stack;

/**
 * Allocate a stack with a given element size
 */
generic_stack* stackAllocate(unsigned int elementSize);

/**
 * Allocate a stack object given an element size and the initial amount of space to allocate
 */
generic_stack* stackAllocateWithSize(unsigned int elementSize, unsigned int max);

/**
 * Free a stack
 */
void stackFree(generic_stack* stack);

/**
 * Push an element to the stack
 */
void stackPush(generic_stack* stack, void* elem);

/**
 * Pop an element to the stack
 */
bool stackPop(generic_stack* stack, void* elem);

/**
 * Peek the top element from the stack
 */
void stackPeek(generic_stack* stack, void* elem);

/**
 * Returns true if the stack is empty
 */
bool stackEmpty(generic_stack* stack);

/**
 * Returns the number of elements on the stack
 */
unsigned int stackSize(generic_stack* stack);

#endif //_STACK_H_
