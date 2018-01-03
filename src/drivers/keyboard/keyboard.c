#include "keyboard.h"
#include <stddef.h>
#include <stdint.h>

#define QWERTY 0
//TODO: Define proper constants, for now, they're all 0
#define ESC 0
#define F1 0
#define F2 0
#define F3 0
#define F4 0
#define F5 0
#define F6 0
#define F7 0
#define F8 0
#define F9 0
#define F10 0
#define F11 0
#define F12 0
#define PRTSCR 0
#define INSERT 0
#define DELETE 0
#define PGUP 0
#define PGDN 0
#define HOME 0
#define END 0
#define BCKTICK '`'
#define BCKSPC '\b'
#define NMLCK 0
#define CAPSLCK 0
#define ENTER '\n'
#define LSHIFT 0
#define RSHIFT 0
#define LCTRL 0
#define RCTRL 0
#define LALT 0
#define RALT 0
#define FnMOD 0
#define SUPER 0
#define SPC ' '
#define LEFT 0
#define RIGHT 0
#define UP 0
#define DOWN 0
#define getChar(num) ('0' + (num))

#define QWERTY_CHARACTER_SET {						\
  ESC, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, PRTSCR, INSERT, DELETE, PGUP, PGDN, HOME, END, /* 20 Chars */ \
    BCKTICK, getChar(1), getChar(2), getChar(3), getChar(4), getChar(5), getChar(6), getChar(7), getChar(8), getChar(9), getChar(0), '-', '=', BCKSPC, NMLCK, '/', '*', '-', 0, 0, /*18 chars*/\
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', ENTER, '7', '8', '9', '+', 0, 0, /*18 chars*/ \
    CAPSLCK, 'a', 's', 'd', 'f', 'g', 'h',  'j', 'k', 'l', ';', '\'','\\', '4', '5', '6', 0, 0, 0, 0, /*16 Chars*/  \
    LSHIFT, 'z', 'x', 'c', 'v', 'b', 'n','m', ',', '.', '/', RSHIFT, '1', '2', '3', ENTER, 0, 0, 0, 0,/*16 Chars*/\
    LCTRL, FnMOD, SUPER, LALT, SPC, RALT, RCTRL, LEFT, DOWN, UP, RIGHT, '0', '.', 0, 0, 0, 0, 0, 0, 0 /*13 chars*/ \
  }						\

//TODO: Get a proper keyboard driver working
//NOTE: This is a palceholder driver to be used only in early
//Deveopment stages
extern uint8_t  kbd_get_code();

typedef struct scancode_s{
  unsigned int size;
  unsigned int type;
  char keys[120];
}__attribute__((packed)) scancode_t;


kbd_flags_t kbd_flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
scancode_t qwerty_set = {107, QWERTY, QWERTY_CHARACTER_SET};


uint8_t  kbd_get_char(){
  // NOTE: Only for debugging purposes
  char code = kbd_get_code();
  if(code & 0x80){
    kbd_flags.pressed = 0;
  }
  else{
    kbd_flags.pressed = 1;
  }
  switch(code & 0x7F){
  case 0x01:
    return qwerty_set.keys[0*20 + 0];
    break;
  case 0x02:
  case 0x03:
  case 0x04:
  case 0x05:
  case 0x06:
  case 0x07:
  case 0x08:
  case 0x09:
  case 0x0A:
  case 0x0B:
  case 0x0C:
  case 0xD:
  case 0xE:
    return qwerty_set.keys[1*20 + (code & 0x7F) - 1];
    break;
  case 0xF:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x19:
  case 0x1A:
  case 0x1B:
  case 0x1C:
    return qwerty_set.keys[2*20 + (code & 0x7F) - 0xF];
    break;
  case 0x1D:
    return qwerty_set.keys[5*20];
  case 0x1E:
  case 0x1F:
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
  case 0x27:
  case 0x28:
    return qwerty_set.keys[3*20 + (code & 0x7F) - 0x1D];
    break;
  case 0x29:
    return qwerty_set.keys[1*20];
    break;
  case 0x2A:
    return qwerty_set.keys[4*20];
    break;
  case 0x2B:
    return qwerty_set.keys[3*20 + 12];
  case 0x2C:
  case 0x2D:
  case 0x2E:
  case 0x2F:
  case 0x30:
  case 0x31:
  case 0x32:
  case 0x33:
  case 0x34:
  case 0x35:
  case 0x36:
    return qwerty_set.keys[4*20 + (code & 0x7F) - 0x2B];
  default:
    return 'L';
  }
  return code;  
}



