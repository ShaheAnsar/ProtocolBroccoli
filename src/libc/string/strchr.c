/*
 *strchr.c by Shahe Ansar
 *An implementation of the strchr, strrchr and strchrnul functions
*/
#include "string.h"
#include <stdint.h>

char* strchr(const char* s, int c){
	unsigned int length = strlen(s);
	for(unsigned int i = 0; i <= length; i++){
		if(s[i] == c){
			return s + i;
		}
	}
	return NULL;
}

char* strrchr(const char* s, int c){
	unsigned int length = strlen(s);
	for(unsigned int i = length; 1; i--){
		if(s[i] == c){
			return s + i;
		}
		if(i == 0){
			break;
		}
	}
	return NULL;
}

char* strchrnul(const char* s, int c){
	unsigned int length = strlen(s);
	for(unsigned int i = 0; i <= length; i++){
		if(s[i] == c){
			return s + i;
		}
	}
	return s + length;
}
