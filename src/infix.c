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
#include <stdio.h>
#include <stdbool.h>

 bool isUppercase(char c) {
 	return c >= 65 && c <= 90;
 }

 bool isLowercase(char c) {
 	return c >= 97 && c <= 122;
 }

 bool isNumeric(char c) {
 	return c >= 48 && c <= 57;
 }

char nextChar(char const* str) {
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
	case '&':
		return 3;
	case '?':
	case '*':
	case '+':
		return 5;
	}

	return 6;
}

bool isOperator(char c) {
	return precidence(c) != 6;
}

void handleInsertBetween(char c, char r, generic_stack* output) {

	char temp;
	char iter;

	if (r <= c) {
		printf("Cannot insert between %c and %c\n", c, r);
	}

	if ((isUppercase(c) && isUppercase(r)) || (isLowercase(c) && isLowercase(r)) || (isNumeric(c) && isNumeric(r))) {
		for (iter = c; iter <= r; iter++) {
			stackPush(output, &iter);
			if (iter != r) {
				temp = '|';
				stackPush(output, &temp);
			}
		}
	}
}

char* infixComputeBrackets(char const* str, generic_stack* output) {
 
  char temp;

  temp = '(';
  stackPush(output, &temp);

  str++;

  for (; *str && *str != ']'; str++) {

  	if (nextChar(str) == '-') {
  		handleInsertBetween(*str, *(str+2), output);
  		str += 2;
  		if (nextChar(str) && nextChar(str) != ']') {
  			temp = '|';
  			stackPush(output, &temp);
  		}
  	} else {
	    stackPush(output, str);
	    if (nextChar(str) != ']') {
	      temp = '|';
	      stackPush(output, &temp);
	    }
	}
  }

  temp = ')';
  stackPush(output, &temp);

  return str;
}

char* infixInsertExplicitConcatenation(char const* str) {

	generic_stack* output = stackAllocate(1);
	char temp;
	bool insertPlanned = false;

	for (; *str; str++) {

		if (*str == '[') {
			str = infixComputeBrackets(str, output);
			insertPlanned = true;
		} else {

			stackPush(output, str);

			if (!isOperator(*str)) {
				insertPlanned = true;
			} else if (*str == '|') {
				insertPlanned = false;
			}
		}


		if (insertPlanned && nextChar(str) != '\0'
				&& (nextChar(str) == '(' || !isOperator(nextChar(str)))) {
			stackPush(output, "&");
			insertPlanned = false;
		}
	}

	temp = '\0';
	stackPush(output, &temp);

	char* result = malloc(strlen(output->data) + 1);
	strcpy(result, output->data);

	stackFree(output);

	return result;
}

char* infixToPostfix(char const* str) {

	generic_stack* infixStack = stackAllocate(1);
	generic_stack* output = stackAllocate(1);

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
			while (!stackEmpty(infixStack) && precidence(peek) >= precidence(*str)) {
				stackPop(infixStack, &peek);
				stackPush(output, &peek);

				//Update the peeked
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
