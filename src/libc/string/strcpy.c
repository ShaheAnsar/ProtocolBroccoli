/*
 *strcpy.c by Shahe Ansar
 *An implementation of the strcpy and strncpy functions
*/

#include "string.h"
#include <stdint.h>

char* strcpy(char* dest, const char* src){
	unsigned int length = strlen(src);
	for(unsigned int i = 0; i <= length; i++){
		dest[i] = src[i];
	}
	return dest;
}

char* strncpy(char* dest, const char* src, size_t n){
	//TODO: Implement function
}
