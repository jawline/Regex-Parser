/*
 * infix.h
 *
 *  Created on: 7 Dec 2014
 *      Author: blake
 */

#ifndef INFIX_H_
#define INFIX_H_
#include "stack.h"

/**
 * Insert . symbols into NFA's in an infix notation (so abc$ becomes a.b.c.$)
 */
char* infixInsertExplicitConcatenation(char const* str);

/**
 * Convert a regular expression string in infix notation to postfix notation
 */
char* infixToPostfix(char const* str);

#endif //INFIX_H_
