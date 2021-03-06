#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H
/*
 *descriptors.h by Shahe Ansar
 *This file contains all the functions related to descriptors.
 *All the function declarations are preceded by the source file in which they're declared. Please go and look at them if you want to understand the code.
*/

#include <stdint.h>
#include <common.h>

extern void init_descriptors();
extern void init_gdt();
extern void init_idt();
extern void test_idt();

#endif
