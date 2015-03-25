/*
 * parser.h
 *
 *  Created on: 30 Nov 2014
 *      Author: blake
 */

#ifndef PARSER_H_
#define PARSER_H_
#include "regex.h"

/**
 * Parses a regex string in infix notation and populates a given regex
 */
bool regexParse(regex* regexStructure, char const* input);

/**
 * Parses a regex string written in postfix notation and populates a given regexStructure with the results
 */
bool regexParsePostfix(regex* regexStructure, char const* input);

/**
 * Free all memory associated with the regex structure
 * Should clear all NFA States and lists
 */
void regexFree(regex* regexStructure);

#endif /* PARSER_H_ */
