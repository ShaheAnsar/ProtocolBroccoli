#include <string.h>
#include <common.h>
#include <stddef.h>
#include <stdint.h>

void* memset(void* destination, int c, unsigned int size){
  char* ptr = destination;
  for(unsigned int i = 0; i < size; i++){
    *(ptr + i) = (char)(c & 0xFF);
  }
  return destination;
}
