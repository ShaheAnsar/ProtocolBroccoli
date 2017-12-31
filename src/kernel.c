#include <stdint.h> //For the inbuilt fixed-width data types
#include <common.h>//For common macros
#include <vga.h>
#include <descriptors.h>
#include <pit.h>




int kernel_main(struct multiboot * multiboot_pointer){
	term_init();
	term_print("OS Booted Successfully!\n");
	//Let's inform the user what we're gonna do next
	WARN("LOADING GDT!!\n");
	//And let's do the initialization-
	init_gdt();
	INFORM("GDT loaded successfully!\n");
	//Now, for the IDT
	WARN("Loading IDT!!!\n");
	init_idt();
	INFORM("IDT Loaded, switching to test mode\n");
	test_idt();
	INFORM("IDT Tested!! Seems to be functioning fine!!\n");
	WARN("INITIALIZING PIT TIMER!!!\n");
	init_pit_timer(COUNTER_0, MODE_HARDWARE_ONE_SHOT, READ_WRITE_WORD, 0, 0);
	//Kernel loop
	while(1);//Yes, the whole kernel IS a giant complex while loop. (sorta)
	while(1);//Hang loop
}
