/*
 * nfa.h
 *
 *  Created on: 29 Nov 2014
 *      Author: blake
 */

#ifndef NFA_H_
#define NFA_H_
#include <stdbool.h>

typedef struct nfa_state {
	unsigned short target;
	struct nfa_state* path;
	struct nfa_state* alternative;
	unsigned int lastid;
} nfa_state;

nfa_state* createNfa(bool split, nfa_state* path, nfa_state* alternative);
void freeNfa(nfa_state* nfa);

#endif /* NFA_H_ */
