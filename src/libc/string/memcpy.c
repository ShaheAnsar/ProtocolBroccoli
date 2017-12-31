/*
 *memcpy.c by Shahe Ansar
 *A memcpy implementatipn
*/
#include <stdint.h>
#include "string.h"

void* memcpy(void* destination, void* source, unsigned int size){
	for(unsigned int i = 0; i < size; i++){
		*((char*)destination + i) = *((char*)source + i);
	}
	return destination;
}
