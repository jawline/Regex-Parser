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

nfa_state* nfaStateCreate(unsigned short split, nfa_state* path, nfa_state* alternative);
void nfaFree(nfa_state* state);

#endif /* NFA_H_ */
