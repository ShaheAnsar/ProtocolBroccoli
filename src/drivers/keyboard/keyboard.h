#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <stddef.h>
#include <stdint.h>
//IRQ handler. Defined in keyboard.c. Called by an asm handler in descriptors/interrupts.s
//extern void keyboard_handler();
extern uint8_t kbd_get_char();

typedef struct kbd_flags_s{
  uint8_t caps : 1;
  uint8_t lshift : 1;
  uint8_t rshift : 1;
  uint8_t lctrl : 1;
  uint8_t rctrl : 1;
  uint8_t super : 1;
  uint8_t lalt : 1;
  uint8_t ralt : 1;
  uint8_t fnmod : 1;
  uint8_t nmlck : 1;
  uint8_t insrt : 1;
  uint8_t pressed : 1;
}__attribute__((packed)) kbd_flags_t;

extern kbd_flags_t kbd_flags;

#endif
