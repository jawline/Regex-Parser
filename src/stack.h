#ifndef _STACK_H_
#define _STACK_H_
#include <stdbool.h>

typedef struct generic_stack {
	void* data;
	unsigned int current;
	unsigned int max;
	unsigned int elementSize;
} generic_stack;

generic_stack* stackAllocate(unsigned int elementSize, unsigned int max);
void stackFree(generic_stack* stack);

void stackPush(generic_stack* stack, void* elem);
bool stackPop(generic_stack* stack, void* elem);
void stackPeek(generic_stack* stack, void* elem);
bool stackEmpty(generic_stack* stack);
unsigned int stackSize(generic_stack* stack);

#endif //_STACK_H_
