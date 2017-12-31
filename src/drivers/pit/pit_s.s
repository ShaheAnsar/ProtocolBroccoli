;;;pit_s.s by Shahe Ansar
%define COUNTER_PORT(a) (0x40 | a)
%define COMMAND_PORT 0x43

%define param(a) ebp + 4*a + 4

%macro WRITE_COUNTER 1

global write_counter_%1
;;;write_counter_<0-2>(uint16_t count)
write_counter_%1:
  push ebp
  mov ebp, esp
  mov ax, [param(1)]
  out byte COUNTER_PORT(%1), al
  shr ax, 4
  out byte COUNTER_PORT(%1), al

  pop ebp
  ret
%endmacro


%macro WRITE_COUNTER_BYTE 1

global write_counter_byte_%1
;;;write_counter_lsb_<0-2>(uint8_t count)
write_counter_byte_%1:
  push ebp
  mov ebp, esp
  mov al, [param(1)]
  out byte COUNTER_PORT(%1), al

  pop ebp
  ret
%endmacro


global write_control_word
;;;write_to_command(uint8_t control word)
write_control_word:
  push ebp
  mov ebp, esp
  mov al, [param(1)]
  out byte COMMAND_PORT, al
  pop ebp
  ret

WRITE_COUNTER 0
WRITE_COUNTER 1
WRITE_COUNTER 2
WRITE_COUNTER_BYTE 0
WRITE_COUNTER_BYTE 1
WRITE_COUNTER_BYTE 2
