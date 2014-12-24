#ifndef _REGEX_H_
#define _REGEX_H_

#include "nfa.h"
#include "nfa_list.h"

typedef struct regex {
	nfa_list stateList;
	nfa_state* start;
} regex;

#endif //_REGEX_H_