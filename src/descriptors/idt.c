/**
  idt.c by Shahe Ansar
  This file contains all the information needed to fill the IDT.
  The IDT is an array of 8 byte structures, each representing an interrupt,
  and containing information about the interrupt (the address of the ISR, the segment type,
  type of interrupt - task gate, interrupt gate, trap gate etc

  The IDT is loaded into the CPU by lidt function. For that to be done a structure of the form given below is used-
  ------------------------
  | limit | base address |
  |       |              |
  ------------------------
  ^       ^              ^
  0       16             47

  limit -> the last byte occupied by the IDT
  base_address -> the address to the first gate in the IDT

  The structure of an IDT interrupt gate/trap gate is this -
  ---------------------
  | address | segment |
  |  low    |         |
  ---------------------
  ^         ^         ^
  0         16        31


  ------------------------------
  | Zero |    Type   | Address |
  |      | Attribute |  high   |
  ------------------------------
  ^      ^           ^         ^
  32     40          48        63

  Address -> Address to the ISR to be executed
  Segment -> Offset to a segment which provides valid access to the ISR (MUST BE A CODE SEGMENT)
  Zero -> Must always be zero
  Type Attribute -> Info about the type of the descriptor
  -------------------------------------
  | I or T | Size | 0 | DPL | Present |
  |        |      |   |     |         |
  -------------------------------------
  I or T -> Decides whether the gate is an interrupt gate or a trap gate. 0b110 if an interrupt, 0b111 if a trap
  Size -> 32 bit or 16 bit //NOTE: not sure about this
  DPL -> Previlige level
  Present -> Set if the interrupt handler is present, 0 if not
  */


#include "descriptors.h"
#include <stddef.h>
#include <stdint.h>
#include <common.h>
#include <pic.h>
#include <libc/string/string.h>

extern void lidt(void* idt_ptr);
//Interrupts
extern void reserved_handler();
extern void divide_error_handler();
extern void debug_exception_handler();
extern void nmi_handler();
extern void breakpoint_handler();
extern void overflow_handler();
extern void bound_exceeded_handler();
extern void undefined_opcode_handler();
extern void device_NA_handler();
extern void double_fault_handler();
extern void coprocessor_segment_overrun_handler();
extern void invalid_tss_handler();
extern void segment_NA_handler();
extern void stack_segment_fault_handler();
extern void general_protection_fault_handler();
extern void page_fault_handler();
extern void math_fault_handler();
extern void machine_check_abort_handler();
extern void alignment_check_handler();
extern void simd_exception_handler();
//Interrupts caused by the PIC
extern void pit_handler();
extern void keyboard_handler();
extern void cascade_handler();
extern void COM2_handler();
extern void COM1_handler();
extern void LPT2_handler();
extern void floppy_handler();
extern void rtc_handler();
extern void periph1_handler();
extern void periph2_handler();
extern void periph3_handler();
extern void mouse_handler();
extern void fpu_handler();
extern void hdd1_handler();
extern void hdd2_handler();

typedef struct I_descriptor_T{
  uint16_t address_low;//The lower word of the address to the entry point of the interrupt
  uint16_t selector;//Points to a valid selector in the GDT
  uint8_t zero;//Must always be zero
  uint8_t type_attrib;//See above
  uint16_t address_high;//Higher word of the address to the entry point of tyhe ISR
}__attribute__((packed)) I_descriptor;

typedef struct idt_ptr_T{
   uint16_t limit;//Limit of the IDT
  uint32_t base_address;//Base address of the IDT
}__attribute__((packed)) idt_ptr;

I_descriptor idt_entries[256];
idt_ptr idt_pointer;

static uint8_t make_flags(uint8_t present, uint8_t dpl, uint8_t isInterrupt, uint8_t size){
  return (present << 7) | (dpl << 5) | (isInterrupt?(0b110):(0b111)) | ((size & 0x01) << 3) ;
}

I_descriptor make_interrupt_gate(uint32_t interrupt_handler, uint16_t segment, uint8_t type_attrib){
  return (I_descriptor){interrupt_handler & 0xFFFF, segment, 0, type_attrib, ((interrupt_handler & (0xFFFF0000)) >> 16)};
}

I_descriptor make_null_gate(){
  //TODO Make a null interrupt handler
  return make_interrupt_gate(0, 0, 0);
}

void init_idt(){
  asm volatile("cli");
  idt_pointer.base_address = idt_entries;
  idt_pointer.limit = sizeof(I_descriptor)*256 - 1;
  memset(idt_entries, 0, sizeof(idt_entries));
  unsigned int i = 0;
  idt_entries[i++] = make_interrupt_gate((uint32_t)divide_error_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)debug_exception_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)nmi_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)breakpoint_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)overflow_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)bound_exceeded_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)undefined_opcode_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)device_NA_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)double_fault_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)coprocessor_segment_overrun_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)invalid_tss_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)segment_NA_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)stack_segment_fault_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)general_protection_fault_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)page_fault_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)reserved_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)math_fault_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)machine_check_abort_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)alignment_check_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)simd_exception_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)reserved_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)reserved_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)reserved_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)reserved_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)reserved_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)reserved_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)reserved_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)reserved_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)reserved_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)reserved_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)reserved_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)reserved_handler, 0x08, make_flags(1, 0, 1, 1));
  i += 9;
  idt_entries[i++] = make_interrupt_gate((uint32_t)pit_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)keyboard_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)cascade_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)COM2_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)COM1_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)LPT2_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)floppy_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)rtc_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)periph1_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)periph2_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)periph3_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)mouse_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)fpu_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)hdd1_handler, 0x08, make_flags(1, 0, 1, 1));
  idt_entries[i++] = make_interrupt_gate((uint32_t)hdd2_handler, 0x08, make_flags(1, 0, 1, 1));
  lidt(&idt_pointer);
  pic_init();
  set_mask(0, 0x0);
  set_mask(1, 0x0);
  //asm volatile("int $32");
  asm volatile("sti");
}

void test_idt(){
  //asm volatile("int $32");
}
