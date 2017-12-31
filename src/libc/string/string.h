#ifndef STRING_H
#define STRING_H
/*
 *string.h implementation by Shahe Ansar
 *All the functions declared here are defined in a c file of the same name, in the src/libc/string/ directory.
*/
#include <stdint.h>
#include <stddef.h>
#include <common.h>

extern void* memcpy(void* destination, void* source, unsigned int size);

extern void* memset(void* destination, int c, unsigned int size);

extern char *stpcpy(char *dest, const char *src);

extern char *strcat(char *dest, const char *src);

extern char *strchr(const char *s, int c);

extern int strcmp(const char *s1, const char *s2);

extern int strcoll(const char *s1, const char *s2);

extern char *strcpy(char *dest, const char *src);

extern size_t strcspn(const char *s, const char *reject);

extern char *strdup(const char *s);

extern char *strfry(char *string);

extern size_t strlen(const char *s);

extern char *strncat(char *dest, const char *src, size_t n);

extern int strncmp(const char *s1, const char *s2, size_t n);

extern char *strncpy(char *dest, const char *src, size_t n);

extern char *strpbrk(const char *s, const char *accept);

extern char *strrchr(const char *s, int c);

extern char *strsep(char **stringp, const char *delim);

extern size_t strspn(const char *s, const char *accept);

extern char *strstr(const char *haystack, const char *needle);

extern char *strtok(char *s, const char *delim);

extern size_t strxfrm(char *dest, const char *src, size_t n);

#endif
