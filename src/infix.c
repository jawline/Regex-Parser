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

char *strrev(char *str) {
	char *p1, *p2;

	if (!str || !*str)
		return str;
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	return str;
}

char* infixToPostfix(char* input) {

	char* start, *str;
	start = str = malloc(strlen(input));
	strncpy(str, input, strlen(input));
	strrev(str);

	generic_stack* infixStack = stackAllocate(1, 1000);
	generic_stack* output = stackAllocate(1, 1000);
	unsigned int precidenceCurrent, precidencePeek;

	char peek;

	for (; *str; ++str) {

		stackPeek(infixStack, &peek);

		if (*str == '(') {
			stackPush(infixStack, "(");
		} else if (*str == ')') {

			while (peek != ')') {
				stackPop(infixStack, &peek);
				stackPush(output, &peek);
			}

		} else {

			while (!stackEmpty(infixStack)) {
				precidenceCurrent = precidence(*str);
				precidencePeek = precidence(peek);

				if (precidencePeek >= precidenceCurrent) {
					stackPop(infixStack, &peek);
					stackPush(output, &peek);
				} else {
					break;
				}
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
	free(start);

	return result;
}
