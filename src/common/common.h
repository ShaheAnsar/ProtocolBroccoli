#ifndef COMMON_H
#define COMMON_H
/*
 *common.h by Shahe Ansar
 *A bunch of useful macros that are obvious, so I won't bother putting them in separate source files.
*/

#include <vga.h>

//A macro for a debug print, which magically disappears, like the star dust thrown off from a fairy's wings, when -DNDEBUG is given to gcc
//and excuse the slightly colorful language :3
#ifndef NDEBUG
  #define debug(x) term_print(x)
#endif
#define NULL (void*)0

//typedef unsigned int size_t;

#endif
