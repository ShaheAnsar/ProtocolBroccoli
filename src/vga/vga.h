#ifndef VGA_H
#define VGA_H
#include <stdint.h>
/**
*******************************************************
* vga.h by Shahe Ansar (animefreak1233)
* The include file used for basic VGA I/O. Will be used during the startup only.
*
* The code explanation will be in the .c file in src/vga/vga.c
*
*/
//DEFINES---------------------------------------------------
#define VGA_COLOR_BLACK  0
#define VGA_COLOR_BLUE  1
#define VGA_COLOR_GREEN  2
#define VGA_COLOR_CYAN  3
#define VGA_COLOR_RED  4
#define VGA_COLOR_MAGENTA  5
#define VGA_COLOR_BROWN  6
#define VGA_COLOR_LIGHT_GREY  7
#define VGA_COLOR_DARK_GREY  8
#define VGA_COLOR_LIGHT_BLUE  9
#define VGA_COLOR_LIGHT_GREEN  10
#define VGA_COLOR_LIGHT_CYAN  11
#define VGA_COLOR_LIGHT_RED  12
#define VGA_COLOR_LIGHT_MAGENTA  13
#define VGA_COLOR_LIGHT_BROWN  14
#define VGA_COLOR_WHITE 15
//A few macros to make life easier
#define WARN(s) {uint8_t temp_color = color;\
    color = make_color(VGA_COLOR_WHITE, VGA_COLOR_RED);	\
    term_print(s);					\
    color = temp_color;}
#define INFORM(s) {uint8_t temp_color = color;\
    color = make_color(VGA_COLOR_WHITE, VGA_COLOR_GREEN);	\
    term_print(s);					\
    color = temp_color;}
//------------------------------------------------------------

//Change this variable from kernel_main (or anywhere else), to change the color. Use the accompanying make_color function.
//Make sure to run term_init() after changing color to bring out the effect
extern uint8_t color;
///Make a color byte
extern uint8_t make_color(uint8_t color_fg, uint8_t color_bg);
//Intialize the terminal.
extern void term_init();
//Print the given char
extern void term_putc(char c);
//Print the given string
extern void term_print(char* string);

#endif
