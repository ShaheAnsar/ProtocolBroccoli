/*
 *strcasecmp.c by Shahe Ansar
 *An Implementation of strcasecmp and strncasecmp functions
*/

#include "strings.h"
#include <common.h>

int strcasecmp(const char* s1, const char* s2){
	for(int i = 0; (s1[i] != '\0') && (s2[i] != '\0'); i++){
		//s1[i] is a capital character
		if((s1[i] <= 0x5A)  && (s1[i] >= 0x41)){
			//s2[i] is a lower case character
			if((s2[i] >= 0x61) && (s2[i] <= 0x7A)){
				if(s1[i] > s2[i] - 0x20){
					return 1;
				}
				else if(s1[i] == s2[i] - 0x20){
					//return 0;
				}
				else{
					return -1;
				}
			}
			//s2[i] is an upper case character
			else if((s2[i] <= 0x5A)  && (s2[i] >= 0x41)){
				if(s1[i] > s2[i]){
					return 1;
				}
				else if(s1[i] == s2[i]){
					//return 0;
				}
				else{
					return -1;
				}
			}
		}
		//s1[i] is a lower case character
		else if((s1[i] >= 0x61) && (s1[i] <= 0x7A)){
			//s2[i] is a lower case character
			if((s2[i] >= 0x61) && (s2[i] <= 0x7A)){
				if(s1[i] > s2[i]){
					return 1;
				}
				else if(s1[i] == s2[i]){
					//return 0;
				}
				else{
					return -1;
				}
			}
			//s2[i] is an upper case character
			else if((s2[i] <= 0x5A)  && (s2[i] >= 0x41)){
				if(s1[i] > s2[i] + 0x20){
					return 1;
				}
				else if(s1[i] == s2[i] + 0x20){
					//return 0;
				}
				else{
					return -1;
				}
			}
		}
	}
	return 0;
}

int strncasecmp(const char* s1, const char* s2, size_t n){
	for(unsigned int i = 0; i < n; i++){
		//s1[i] is a capital character
		if((s1[i] <= 0x5A)  && (s1[i] >= 0x41)){
			//s2[i] is a lower case character
			if((s2[i] >= 0x61) && (s2[i] <= 0x7A)){
				if(s1[i] > s2[i] - 0x20){
					return 1;
				}
				else if(s1[i] == s2[i] - 0x20){
					return 0;
				}
				else{
					return -1;
				}
			}
			//s2[i] is an upper case character
			else if((s2[i] <= 0x5A)  && (s2[i] >= 0x41)){
				if(s1[i] > s2[i]){
					return 1;
				}
				else if(s1[i] == s2[i]){
					return 0;
				}
				else{
					return -1;
				}
			}
		}
		//s1[i] is a lower case character
		else if((s1[i] >= 0x61) && (s1[i] <= 0x7A)){
			//s2[i] is a lower case character
			if((s2[i] >= 0x61) && (s2[i] <= 0x7A)){
				if(s1[i] > s2[i]){
					return 1;
				}
				else if(s1[i] == s2[i]){
					return 0;
				}
				else{
					return -1;
				}
			}
			//s2[i] is an upper case character
			else if((s2[i] <= 0x5A)  && (s2[i] >= 0x41)){
				if(s1[i] > s2[i] + 0x20){
					return 1;
				}
				else if(s1[i] == s2[i] + 0x20){
					return 0;
				}
				else{
					return -1;
				}
			}
		}
	}
}
