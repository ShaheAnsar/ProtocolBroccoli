#ifndef PIC_H
#define PIC_H
#include <common.h>
#include <stddef.h>
#include <stdint.h>

extern void pic_init();
extern void pic_disable();
extern void set_mask(int i, uint8_t m);//i = 0 => master, i = 1 => slave; m -> mask
extern void send_eoi(uint8_t irq);
#endif
