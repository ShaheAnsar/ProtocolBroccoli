/*
 *strcoll.c by Shahe Ansar
 *An implementation of the strcoll function
*/
#include "string.h"
#include <stdint.h>

/*NOTE: The function strcoll.c has not been implemented due to the author's inexperience with locale based code
TODO: Implement strcoll.c*/
int strcoll(const char* s1, const char *s2){
	return strcmp(s1, s2);
}