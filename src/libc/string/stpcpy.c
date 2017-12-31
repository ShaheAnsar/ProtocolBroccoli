/*
 *stpcpy.c by Shahe Ansar
 *An implementation of the stpcpy function
*/
#include "string.h"
#include <stdint.h>

char* stpcpy(char* dest,const char* src){
	unsigned int length = strlen(src);
	for(unsigned int i = 0; i <= length; i++){
		dest[i] = src[i];
	}
	return dest + length;
}
