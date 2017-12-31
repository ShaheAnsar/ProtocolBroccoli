/*
 *strcmp.c by Shahe Ansar
 *An implementation of the strcmp and strncmp functions
*/

#include "string.h"
#include <stdint.h>

int strcmp(const char* s1, const char* s2){
	unsigned int length_s1 = strlen(s1);
	unsigned int length_s2 = strlen(s2);
	for(unsigned int i = 0; (s1[i] != '\0') && (s2[i] != '\0'); i++){
		if(s1[i] > s2[i]){
			return 1;
		}
		else if(s2[i] > s1[i]){
			return -1;
		}
	}
	return 0;
}

int strncmp(const char* s1, const char* s2, size_t n){
	unsigned int length_s1 = strlen(s1);
	unsigned int length_s2 = strlen(s2);
	for(unsigned int i = 0; i < n; i++){
		if(s1[i] > s2[i]){
			return 1;
		}
		else if(s2[i] > s1[i]){
			return -1;
		}
	}
	return 0;
}
