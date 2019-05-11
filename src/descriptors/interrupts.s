ALIGN 4

section .data
message:
	db "Recieved interrupt", 0x0A, 0x00
message_irq:
	db "Recieved IRQ", 0x0A, 0x00
pit_handler_msg:
	db "PIT IRQ", 0x0D, 0x0A, 0x00
divide_error_handler_msg:
	db "divide_error_handler", 0x0A, 0x00
debug_exception_handler_msg:
	db "debug_exception_handler", 0x0A, 0x00
nmi_handler_msg:
	db "nmi_handler", 0x0A, 0x00
breakpoint_handler_msg:
	db "breakpoint_handler", 0x0A, 0x00
overflow_handler_msg:
	db "overflow_handler", 0x0A, 0x00
bound_exceeded_handler_msg:
	db "bound_exceeded_handler", 0x0A, 0x00
undefined_opcode_handler_msg:
	db "undefined_opcode_handler", 0x0A, 0x00
device_NA_handler_msg:
	db "device_NA_handler", 0x0A, 0x00
double_fault_handler_msg:
	db "double_fault_handler", 0x0A, 0x00
coprocessor_segment_overrun_handler_msg:
	db "coprocessor_segment_overrun_handler", 0x0A, 0x00
invalid_tss_handler_msg:
	db "invalid_tss_handler", 0x0A, 0x00
segment_NA_handler_msg:
	db "segment_NA_handler", 0x0A, 0x00
stack_segment_fault_handler_msg:
	db "stack_segment_fault_handler", 0x0A, 0x00
general_protection_fault_handler_msg:
	db "general_protection_fault_handler", 0x0A, 0x00
page_fault_handler_msg:
	db "page_fault_handler", 0x0A, 0x00
math_fault_handler_msg:
	db "math_fault_handler", 0x0A, 0x00
machine_check_abort_handler_msg:
	db "machine_check_abort_handler", 0x0A, 0x00
alignment_check_handler_msg:
	db "alignment_check_handler", 0x0A, 0x00
simd_exception_handler_msg:
	db "simd_exception_handler", 0x0A, 0x00
reserved_handler_msg:
	db "reserved_handler", 0x0A, 0x00
cascade_handler_msg:
	db "cascade_handler, 2", 0x0A, 0x00
COM2_handler_msg:
	db "COM2_handler, 3", 0x0A, 0x00
COM1_handler_msg:
	db "COM1_handler, 4", 0x0A, 0x00
LPT2_handler_msg:
	db "LPT2_handler, 5", 0x0A, 0x00
floppy_handler_msg:
	db "floppy_handler, 6", 0x0A, 0x00
rtc_handler_msg:
	db "rtc_handler, 8", 0x0A, 0x00
periph1_handler_msg:
	db "periph1_handler, 9", 0x0A, 0x00
periph2_handler_msg:
	db "periph2_handler, 10", 0x0A, 0x00
periph3_handler_msg:
	db "periph3_handler, 11", 0x0A, 0x00
mouse_handler_msg:
	db "mouse_handler, 12", 0x0A, 0x00
fpu_handler_msg:
	db "fpu_handler, 13", 0x0A, 0x00
hdd1_handler_msg:
	db "hdd1_handler, 14", 0x0A, 0x00
hdd2_handler_msg:
	db "hdd2_handler, 15", 0x0A, 0x00






extern term_putc

section .text
extern null_isr_handler
extern term_print
extern null_isr_handler_no_error
extern send_eoi
%macro NULL_ISR_NOERROR 1
global %1
	%1:
	pushad
	cld
	push %1_msg
	call term_print
	add esp, 4
	popad
	iret
%endmacro

%macro NULL_ISR_ERROR 1
global %1
	%1:
	add esp, 4
	pushad
	cld
	push %1_msg
	call term_print
	add esp, 4
	popad
	iret
%endmacro

%macro ISR_HANDLER_NOERROR 1
extern %1_c
global %1
	%1:
	call %1_c
	iret
%endmacro

%macro NULL_IRQ_HANDLER 2
section .data
	message_%1:
	db "IRQ", '0' + %2,'\n', 0
section .text
global %1
	%1:
	pushad
	cld
	push message_%1
	call term_print
	push %2
	call send_eoi
	push %1_msg
	call term_print
	add esp, 12
	popad
	iret
%endmacro

	NULL_ISR_NOERROR divide_error_handler
	NULL_ISR_NOERROR debug_exception_handler
	NULL_ISR_NOERROR nmi_handler
	NULL_ISR_NOERROR breakpoint_handler
	NULL_ISR_NOERROR overflow_handler
	NULL_ISR_NOERROR bound_exceeded_handler
	NULL_ISR_NOERROR undefined_opcode_handler
	NULL_ISR_NOERROR device_NA_handler
	NULL_ISR_ERROR double_fault_handler
	NULL_ISR_NOERROR coprocessor_segment_overrun_handler
	NULL_ISR_ERROR invalid_tss_handler
	NULL_ISR_ERROR segment_NA_handler
	NULL_ISR_ERROR stack_segment_fault_handler
	NULL_ISR_ERROR general_protection_fault_handler
	NULL_ISR_ERROR page_fault_handler
	NULL_ISR_NOERROR math_fault_handler
	NULL_ISR_NOERROR machine_check_abort_handler
	NULL_ISR_ERROR alignment_check_handler
	NULL_ISR_NOERROR simd_exception_handler
	NULL_ISR_NOERROR reserved_handler
;;;IRQs for the PIC
	; NULL_IRQ_HANDLER pit_handler, 0
;; NULL_IRQ_HANDLER keyboard_handler, 1 
	NULL_IRQ_HANDLER cascade_handler, 2
	NULL_IRQ_HANDLER COM2_handler, 3
	NULL_IRQ_HANDLER COM1_handler, 4
	NULL_IRQ_HANDLER LPT2_handler, 5
	NULL_IRQ_HANDLER floppy_handler, 6
	NULL_IRQ_HANDLER rtc_handler, 8
	NULL_IRQ_HANDLER periph1_handler, 9
	NULL_IRQ_HANDLER periph2_handler, 10
	NULL_IRQ_HANDLER periph3_handler, 11
	NULL_IRQ_HANDLER mouse_handler, 12
	NULL_IRQ_HANDLER fpu_handler, 13
	NULL_IRQ_HANDLER hdd1_handler, 14
	NULL_IRQ_HANDLER hdd2_handler, 15


global spurious_interrupt_handler
spurious_interrupt_handler:
	iret

global pit_handler
pit_handler:
	pushad
	cld
	push pit_handler_msg
	call term_print
	add esp, 4
	push 0x0
	call send_eoi
	add esp, 4
	popad
	iret


;;; NOTE: This handler is only to be used during the early stages
;;; of development when a proper scheduler isn't available
;;; TODO: Replace keyboard_handler_primitive with a proper handler
global keyboard_handler
keyboard_handler:
	push 0x1
	call send_eoi
	add esp, 4
	iret

