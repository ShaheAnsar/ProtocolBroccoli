/*
 *index.c by Shahe Ansar
 *An implementationn of the index and rindex functions
*/
#include "strings.h"
#include <string.h>
#include <stdint.h>

char* index(const char* s, int c){
	unsigned int length = strlen(s);
	for(unsigned i = 0; i <= length; i++){
		if(s[i] == c){
			return s + i;
		}
	}
	return NULL;
}

char* rindex(const char* s, int c){
	unsigned int length = strlen(s);
	for(unsigned int i = length; i >= 0; i--){
		if(s[i] == c){
			return s + i;
		}
		if(i == 0){
			break;
		}
	}
	return NULL;
}
