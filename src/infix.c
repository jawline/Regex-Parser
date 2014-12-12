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
#include <stdbool.h>

char nextChar(char* str) {
	return *(str + 1);
}

int precidence(char c) {

	switch (c) {
	case '(':
		return 1;
	case ')': 
	        return 1;
	case '|':
		return 2;
       	case '.':
		return 3;
	case '*':
	case '+':
		return 5;
	}

	return 6;
}

char* insertInfixDots(char* str) {

  generic_stack* output = stackAllocate(1, 1000);
  char temp;
  bool insertPlanned = false;

  for (; *str; str++) {
    stackPush(output, str);

    if (precidence(*str) == 6) {
      insertPlanned = true;
    }

    if (insertPlanned && nextChar(str) != '\0' && precidence(nextChar(str)) == 6) {
      stackPush(output, ".");
      insertPlanned = false;
    }
  }
 
  temp = '\0';
  stackPush(output, &temp);
  return output->data;
}

char* infixToPostfix(char* str) {
  str = insertInfixDots(str);
  printf(str);

	generic_stack* infixStack = stackAllocate(1, 1000);
	generic_stack* output = stackAllocate(1, 1000);

	char peek;

	for (; *str; ++str) {

		stackPeek(infixStack, &peek);

		if (*str == '(') {
		        peek = '(';
			stackPush(infixStack, &peek);
		} else if (*str == ')') {

			while (peek != '(') {
      				stackPop(infixStack, &peek);
				stackPush(output, &peek);
				stackPeek(infixStack, &peek);
			}

			//Discard the '('
			stackPop(infixStack, &peek);

		} else {

			while (!stackEmpty(infixStack)
					&& precidence(peek) >= precidence(*str)) {

				stackPop(infixStack, &peek);
				stackPush(output, &peek);

				//Update the peek
				stackPeek(infixStack, &peek);
			}

			stackPush(infixStack, str);
		}
	}

	while (!stackEmpty(infixStack)) {
		stackPop(infixStack, &peek);
		stackPush(output, &peek);
	}

	peek = '\0';
	stackPush(output, &peek);

	char* result = malloc(stackSize(output));
	memcpy(result, output->data, output->current);

	stackFree(infixStack);
	stackFree(output);

	return result;
}
