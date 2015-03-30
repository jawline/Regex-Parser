#ifndef DEBUG_PRINT_DEF_H_
#define DEBUG_PRINT_DEF_H_

#ifdef DEBUG
#define DEBUG_PRINT(...) do{ fprintf( stderr, __VA_ARGS__ ); } while( false )
#else
#define DEBUG_PRINT(...) do{ } while ( false )
#endif

#endif //DEBUG_PRINT_DEF_H_
