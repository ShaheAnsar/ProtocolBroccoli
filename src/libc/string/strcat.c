/*
 *strcat.c by Shahe Ansar
 *An implementation of the strcat and strncat functions
*/

#include "string.h"
#include <stdint.h>

char* strcat(char* dest, const char* src){
	unsigned int length_d = strlen(dest);
	unsigned int length_s = strlen(src);
	for(unsigned int i = 0; i < length_s;i++){
		dest[length_d + i] = src[i];
	}
	dest[length_d + length_s] = '\0';
	return dest;
}

char* strncat(char* dest, const char* src, size_t n){
	unsigned int length_d = strlen(dest);
	for(unsigned int i = 0; i < n; i++){
		dest[length_d + i] = src[i];
	}
	dest[length_d + n] = '\0';
	return dest;
}
