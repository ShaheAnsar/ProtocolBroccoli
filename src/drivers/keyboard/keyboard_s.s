section .text
%define KBD_PORT 0x60
global kbd_get_code
;;; Get the cwurrent scan code
;;; uint8_t kbd_get_code()
kbd_get_code:
	mov eax, 0
	in al, KBD_PORT
	ret
