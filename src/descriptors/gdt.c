/*
 *gdt.c by Shahe Ansar
 *This file contains everything related to GDT and stuff.
 *
 * The GDT is a table, or rather an array of elements
 *called "segment descriptors". Segment descriptors are basically structs which contain information about the segments itself(where it
 *begins, its size, whether its available for use etc), and the permissions (kernel level, or userlevel) etc.
 *What we need to do is call upon the holy instruction "lgdtr DWORD PTR address_of_the_first_element_in_the_array", then we'll be fine.
 *Before we proceed though, let's see what a segment is made up of-
 *=========================================================================================
 *|  Base  | G | size | R | avl | Seg. Lim | Present | Privilege | DType | SType |  Base  |
 *| 31:24  |   |      |   |     |  19:16   |         |           |       |       | 23:16  |
 *=========================================================================================
 *^        ^   ^      ^   ^     ^          ^         ^           ^       ^       ^       ^
 *63       55  54     53  52   51          47        46          44      43      39      32
 *
 *========================
 *|  Base addr | Seg. Lim|
 *|    15:00   |  15:00  |
 *========================
 *^            ^        ^
 *31           15       0
 *Base/Base addr -> The base of the segment
 *G -> Granularity (0 => 1 byte, 1 => 4 KiB)
 *size -> Default size of operation (0 => 16-bit segment, 1 =>32-bit segment)
 *R -> Reserved (Available for 64 bit OSes, look it up in the intel manual Volume 3), set to 0
 *avl -> Whether the segment is available for use
 *Seg. Lim -> The Limit of the Segment (It's size - 1 byte)
 *Present -> Whether the segment is in memory (do you have some hardware mapped to that address space, or is it empty?)
 *Previlege -> Kernel level code execution or User level execution
 *DType -> Type of descriptor (0 => Segment, 1 => Code/Data)
 *SType -> Type of Segment
**/

#include "descriptors.h"
#include <stdint.h>

#define KERNEL_LEVEL 0b00
#define USER_LEVEL 0b11

extern void lgdt(void* gdt_ptr);//This is the function which will actually load our GDT, it's an asm only instruction. I find asm() too ugly, so I'll define it in a separate .s file
extern void jump_gdt();//Use this to far jump to the gdt Code segement

struct G_descriptor_t{
  uint16_t seg_lim_low;//The lower 16 bits of the segment limit
  uint16_t base_low;//The lower 16 bits of the base address
  uint8_t base_mid;//Bits 16:23 of the base address
  uint8_t flags;//Refer to the block diagram
  /*uint8_t lim_high : 4;//The higher 4 bits of the segment limit
  uint8_t avl : 1;//The availability flags
  uint8_t R : 1;//Reserved
  uint8_t size : 1;//The default size of operations*/
  uint8_t gran;
  uint8_t base_high;//The highest 8 bits of the base address
}__attribute__((packed));
typedef struct G_descriptor_t G_descriptor;
struct gdt_ptr_t{
  uint16_t limit;
  uint32_t base;
}__attribute((packed));
typedef struct gdt_ptr_t gdt_ptr;
//We don't have a memory manager on us right now, so forget about malloc-ing for dynamic memory. But this will change once a memory manager has been implemented
//TODO: Change to dynamic memory model.
G_descriptor G_descriptors[4];
gdt_ptr gdt_pointer;

uint8_t make_flags(uint8_t present, uint8_t privilege, uint8_t DType, uint8_t SType){
  return (present << 7) | (privilege << 5) | (DType << 4) | (SType);
}



void init_gdt(){
  asm volatile("cli");
  G_descriptors[0] = (G_descriptor){0, 0, 0, 0, 0, /*0, 0, 0, */0};//Null descriptor. Usefule for debugging
  G_descriptors[1] = (G_descriptor){0xFFFF, 0x00, 0x00, make_flags(1, KERNEL_LEVEL, 1, 0xA), /*0xF, 1, 0, 1*/0xCF, 0x00};//Code segment
  G_descriptors[2] = (G_descriptor){0xFFFF, 0x00, 0x00, make_flags(1, KERNEL_LEVEL, 1, 0x2), /*0xF, 1, 0, 1*/0xCF, 0x00};//Text segment
  G_descriptors[3] = (G_descriptor){0, 0, 0, 0, 0, 0, /*0, 0, 0*/};//Null descriptor 'cuz this where the TSS wil go. TODO:Implement TSS
  gdt_pointer = (gdt_ptr){sizeof(G_descriptor)*4 - 1, G_descriptors};
  lgdt(&gdt_pointer);
  //jump_gdt();
}
