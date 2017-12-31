;;;pic_s.s by Shahe Ansar
;;;This file contains necessary functions needed by pic.c
section .bss
mMask:
	resb 1
sMask:
	resb 1

section .text
%define mPicCommand 0x0020
%define mPicData 0x0021
%define sPicCommand 0x00A0
%define sPicData 0x00A1
%define eoi 0x20
;;;ICW1 Bit positions
%define ICW4_NEEDED 0 		;Set if ICW4 is needed
%define SINGLE_MODE 1		;Set if running independently, and not in a master slave cascade
%define STRIDE4 2		;Set if you want the stride of interrupt descriptors to be 4
%define LEVEL_TRIGGER 3		;Set if you want to trigger off of the level rather than the edge
;;;ICW2 Bit positions
%define OFFSET 3		;Shift a 5 bit number to set the offset
;;;ICW3 Master Literal
%define HAS_SLAVE(a) ((1 << a) | (0x8)) ;Sets the ID of the slave. Or the Literal for different bytes if the wiring differs from the default (a = 2)
;;;ICW3 Slave Literal
%define ID(a) a
;;;ICW4 Bit positions
%define MODE_x86 0		;Set if in x86 mode (like we are), clear if in MCS 80/85 mode
%define AUTO_EOI 1		;Set if you want to risk it by not sending the EOI, clear if you want to manually send the EOI command
%define BUFFERED_MODE 2		;Bit shift a 2 bit number to set the buffering (the hardware one, as in hi power output) mode. 0X - Unbuffered, 10 -  Buffered | Slave, 11 - Buffered | Master
%define SPECIAL_F_NESTED_MODE 4	;Set if you want to switch to special fully nested mode, else leave it alone.
;;;Common ICWs
%define ICW1 ((1 << 4) | (1 << ICW4_NEEDED)) ;The (1 << 4) and the last bit of the address bus being 0 denote the conditions for an initalization command
%define ICW4 (1 << MODE_x86)
;;;Master ICWs
%define mICW2 (32 | 0x8)			;Since the first 32 vectors are reserved by CPU special ISRs, we want to shift this to the next divisible by 8 address, or 32
%define mICW3 (HAS_SLAVE(2))
;;;Slave ICWs
%define sICW2 ((0x05 << OFFSET) | 0x08)			;This needs to start from vector 40
%define sICW3 (ID(2))

global pic_init
pic_init:
	push ebp
	mov ebp, esp
	;Save the interrupt mask of the slave and master PICs
	in byte al, mPicData
	mov [mMask], al
	in byte al, sPicData
	mov [sMask], al

	mov al, ICW1
	out byte mPicCommand, al ;Send the initilize code to the PICs
	out byte sPicCommand, al
	nop			;Delay because PICs are supposedly slow as hell
	nop
	nop
	mov al, mICW2
	out byte mPicData, al ;Send the second init word to the master and slave
	mov al, sICW2
	out byte sPicData, al
	nop
	nop
	nop
	mov al, mICW3
	out byte mPicData, al	;Send the third word to the PICs
	mov al, sICW3
	out byte sPicData, al
	nop
	nop
	nop
	mov al, ICW4
	out byte mPicData, al	;Send the last word to the PICs
	out byte sPicData, al
	nop
	nop
	nop

	mov al, [mMask]		;Restore the masks
	out byte mPicData, al
	mov al, [sMask]
	out byte sPicData, al

	pop ebp
	ret


global pic_disable
pic_disable:			;You don't really disable the PIC, but rather mask all the interrupts
	mov al, 0xFF
	out byte mPicData, al
	out byte sPicData, al
	ret


global set_mask
;;;set_mask(int i, uint8_t m)
;;;i = 0 => master PIC, 1 = 1 => slave PIC
set_mask:
	push ebp
	mov ebp, esp
	cmp byte [ebp + 8], 1
	je .slave
	mov al, [ebp + 12] 
	out byte mPicData, al
	jmp .ret
.slave:
	mov al, [ebp + 12] 
	out byte sPicData, al
.ret:
	pop ebp
	ret

global send_eoi
;;;send_eoi(uint8_t irq)
send_eoi:
	push ebp
	mov ebp, esp

	cmp byte [ebp + 8], 7
	jle .master
.slave:
	mov al, eoi
	out byte sPicCommand, al
.master:
	mov al, eoi
	out byte mPicCommand, al

	pop ebp
	ret
	
