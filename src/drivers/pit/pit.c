#include <stddef.h>
#include <stdint.h>
#include <common.h>
#include <vga.h>
#include "pit.h"
//Defines to make life easier


//Functions defined in the pit_s.s file
extern void write_control_word(uint8_t control_word);
extern void write_counter_0(uint16_t count);
extern void write_counter_1(uint16_t count);
extern void write_counter_2(uint16_t count);
extern void write_counter_byte_0(uint8_t count);
extern void write_counter_byte_1(uint8_t count);
extern void write_counter_byte_2(uint8_t count);

void write_counter(uint8_t timer, uint16_t count){
  switch(timer){
    case COUNTER_0:
      write_counter_0(count);
      break;
    case COUNTER_1:
      write_counter_1(count);
      break;
    case COUNTER_2:
      write_counter_2(count);
  }
}

void write_counter_byte(uint8_t timer, uint8_t count){
  switch(timer){
    case COUNTER_0:
      write_counter_byte_0(count);
      break;
    case COUNTER_1:
      write_counter_byte_1(count);
      break;
    case COUNTER_2:
      write_counter_byte_2(count);
  }
}

void init_pit_timer(uint8_t timer, uint8_t timer_mode, uint8_t read_write_mode, uint8_t bcd, uint16_t count){
  uint8_t control_word = (timer << COUNTER_OFFSET) | (timer_mode << MODE_OFFSET) | (read_write_mode << READ_WRITE_OFFSET) | bcd;
  write_control_word(control_word);
  switch(read_write_mode){
    case READ_WRITE_WORD:
      write_counter(timer, count);
      break;
    case READ_WRITE_LSB:
    case READ_WRITE_MSB:
      write_counter_byte(timer, (uint8_t)(count & 0xFF));
  }
}
