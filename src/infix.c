/*
 * infix.c
 *
 *  Created on: 7 Dec 2014
 *      Author: blake
 */
#include "infix.h"
#include "stack.h"
#include <string.h>
#include <stdlib.h>

char nextChar(char* str) {
	return *(str + 1);
}

int precidence(char c) {

	switch (c) {
	case '(':
		return 1;
	case '|':
		return 2;
	case '.':
		return 3;
	case '?':
		return 4;
	case '*':
		return 4;
	case '+':
		return 4;
	case '^':
		return 5;
	}

	return 6;
}

char* infixToPostfix(char* str) {

	generic_stack* infixStack = stackAllocate(1, 1000);
	generic_stack* output = stackAllocate(1, 1000);

	char peek;

	for (; *str; ++str) {

		stackPeek(infixStack, &peek);

		if (*str == '(') {
			stackPush(infixStack, "(");
		} else if (*str == ')') {

			stackPop(infixStack, &peek);
			while (peek != '(') {
				stackPush(output, &peek);
				stackPop(infixStack, &peek);
			}

		} else {
			while (!stackEmpty(infixStack)
					&& precidence(peek) >= precidence(*str)) {
				stackPop(infixStack, &peek);
				stackPush(output, &peek);
			}

			stackPush(infixStack, str);
		}
	}

	while (!stackEmpty(infixStack)) {
		stackPop(infixStack, &peek);
		stackPush(output, &peek);
	}

	char* result = malloc(stackSize(output));
	memcpy(result, output->data, output->current);

	stackFree(infixStack);
	stackFree(output);

	return result;
}
