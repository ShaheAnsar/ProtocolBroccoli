#include <stdint.h> //For the inbuilt fixed-width data types
#include <common.h>//For common macros
#include <vga.h>
#include <descriptors.h>
#include <pit.h>
#include <keyboard.h>



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
	init_pit_timer(COUNTER_0, MODE_SQUARE_WAVE, READ_WRITE_WORD, 0, 0);
	WARN("INITIALIZED PIT TIMER!!!\n");
	WARN("SHOULD RECEIVE MULTIPLE INTERRUPTS\n");
	init_pit_timer(COUNTER_0, MODE_HARDWARE_ONE_SHOT, READ_WRITE_WORD, 0, 65535);
	//Note: The PIT TIMER seems to work fine
	INFORM("PIT TESTING FINISHED\n");
	WARN("TESTING KEYBOARD, GO AHEAD, TYPE->\n");
	//Kernel loop
	while(1){
	  char pressed[] = "Pressed\r";
	  char released[] = "Released \r";
	  char key = kbd_get_char();
	  if((key == '\n') && (kbd_flags.pressed == 0)){
	    continue;
	  }
	  if(key == '\n'){
	    for(volatile long int i = 0; i < 0xFFFFFF; i++){
	    }
	  }
	  key = key?key:'U';
	  char string[2] = {key, 0};
	  INFORM(string);
	  if(kbd_flags.pressed){	 
	    INFORM(pressed);
	  }
	  else{
	    INFORM(released);
	  }
	    
	}//Yes, the whole kernel IS a giant complex while loop. (sorta)
	while(1);//Hang loop
}
