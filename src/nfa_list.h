#ifndef _NFA_LIST_DEF_H_
#define _NFA_LIST_DEF_H_
#include "nfa.h"
#include <stdbool.h>

/**
 * Stores a list of NFAs
 * TODO: Grow list if reaching number of allocated elements
 */
typedef struct nfa_list {
	nfa_state** states;
	int currentSize;
} nfa_list;

/**
 * Create a new NFA list
 */
void nfaListAllocate(nfa_list* list, int maxSize);

/**
 * Reset the list, removing all items
 */
void nfaListReset(nfa_list* list);

/**
 * Start the list, resetting it before adding the given state
 */
void nfaListStart(nfa_list* list, nfa_state* state);

/**
 * Add a state to the list
 */
void nfaListAdd(nfa_list* list, nfa_state* state);

/**
 * If the state is a state with two possibilities, add both
 * possibilities to the list, otherwise add the state to the list
 */
void nfaListAddFollowPaths(nfa_list* list, nfa_state* state);

/**
 * Free the NFA list
 * Note: The NFA states in the list are not freed, they should be
 * freed explicitely
 */
void nfaListFree(nfa_list* list);

/**
 * Returns true if an NFA list contains a specified state
 */
bool nfaListContains(nfa_list* list, nfa_state* state);

#endif //_NFA_LIST_DEF_H_
