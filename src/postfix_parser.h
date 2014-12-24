/*
 * parser.h
 *
 *  Created on: 30 Nov 2014
 *      Author: blake
 */

#ifndef PARSER_H_
#define PARSER_H_
#include "regex.h"

bool regexParse(regex* regexStructure, char const* input);
void regexFree(regex* regexStructure);

#endif /* PARSER_H_ */
