;;; 	gdt.s by Shahe Ansar
;;; 	The function lgdt and jump_gdt is defined here.


	global lgdt
	section .text
lgdt:
	push ebp
	mov ebp, esp
;	lgdt [ebp + 8]
;	pop ebp
;	ret
	mov eax, [ebp + 8]  ; Get the pointer to the GDT, passed as a parameter.
	lgdt [eax]        ; Load the new GDT pointer

	mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
	mov ds, ax        ; Load all data segment selectors
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush   ; 0x08 is the offset to our code segment: Far jump!
.flush:
	pop ebp
	ret


	global jump_gdt
jump_gdt:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush
.flush:
	ret
