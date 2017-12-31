/*
 *strlen.c b Shahe Ansar
 *Contains a strlen implementation
*/

#include <stdint.h>
#include "string.h"

size_t strlen(const char* string){
	unsigned int i = 0;
	while(string[i] != '\0'){
		i++;
	}
	return i;
}
