#;;;	OS By Shahe Ansar
#;;;
#;;;Locations of external functions:
#;;;	kernel_main: src/kernel.c
#;;;
#;;;start is the entry point of the OS. The specifics of how the OS connects together as a data structure can be seen in the linker script src/linker.ld
#;;;The very first thing in the OS is the multiboot header. This tells grub that there's an OS here. Then the stack is set up, and after that we call our kernel_main function.
#;;;
#;;;


	.set MB_MAGIC, 0x1BADB002	#;MB_MAGIC is the magic number for GRUB's multiboot spec
#;;; The flags are structured like this -
#;;;	-------------------------
#;;;	|  load on   |  give    |
#;;;    |pg boundary |	 mmap   |
#;;;	-------------------------
#;;; 	mmap - > memory map
	.set MB_ALIGN, (1 << 1)
	.set MB_MMAP, (1)
	.set MB_FLAGS, MB_ALIGN | MB_MMAP	 #;The actual flags.
	.set MB_CHECKSUM, -(MB_MAGIC + MB_FLAGS) #;A checksum used for verification. It's simply the negative of the sum of both the flags and the magic number

	.section .multiboot 	#;This is how the linker knows where the declaration of multiboot is. We need to know that if we are to put that first.
	.align 4		#;All data should start at an address which is a multiple of 4. I think it's 16 if you implement the later versions of multiboot, which don't
				#;really offer much.
	.long MB_MAGIC		#;Declarations
	.long MB_FLAGS		#;||
	.long MB_CHECKSUM	#;||
#;;;------------------------------------------------------------

	.section .bss 		#;Uninitialized data goes here
	.align 16
stack_bottom:
	.skip 1024*16		#;Skip 16 Kbytes. This will be our stack. This seems really low, and in fact is, but it's more thn enough for us till the memory manager takes
				#;over
stack_top:

	

	.section .text 		#;Code goes here
	.global start
	
start:				#;The entry point of the code. This is where the OS starts executing
	mov $stack_top, %esp	#;Load the address of the top of the stack into the stack pointer (register %esp)

	call kernel_main	#;Call our OS's main function - this will be C

	.hang:			#;Just in case our kernel returns due to some error, hang the CPU
	cli
	hlt
	jmp .hang
