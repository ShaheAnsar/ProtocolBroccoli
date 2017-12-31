#include <stddef.h>
#include <stdint.h>
#include <common.h>
#include <vga.h>

void null_isr_handler(uint8_t error_code){
  WARN("ISR handler run - With error code");
}

void null_isr_handler_no_error(){
  WARN("ISR handler run - With error code"); 
}
