#ifndef STRINGS_H
#define STRINGS_H
/*
 *strings.h by Shahe Ansar
 *An implementation of the std libc strings.h file
*/
#include <stdint.h>
#include <common.h>
#include <string.h>

extern int strcasecmp(const char* s1, const char* s2);

extern int strncasecmp(const char* s1, const char* s2, size_t n);

extern char* index(const char* s, int c);

extern char* rindex(const char* s, int c);
#endif
