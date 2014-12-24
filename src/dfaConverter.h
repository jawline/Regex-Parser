#ifndef _DFA_CONVERTER_DEF_H_
#define _DFA_CONVERTER_DEF_H_
#include "regex.h"

/**
 * Convert an input NFA to a DFA (Where there is only one path for each string)
 */
regex* convertToDfa(regex* nfa);

#endif //_DFA_CONVERTER_DEF_H_
