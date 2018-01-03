#include <stdint.h>
#include "vga.h"
/**
 *  vga.c by Shahe Ansar
 *
 *  These conatin the necessary functions needed to implement a rudimentary display driver for the early boot stated of the OS.
 *  The resolution is therefore very low, but it works just fine when you want to relay information during the boot. It's single buffered because you aren't going to be drawing a thousand polugons per secind.
 *
 */

volatile uint16_t* VGA_MEM = (uint16_t*)0xB8000;
unsigned int vga_cols = 0, vga_rows = 0;

static unsigned int current_row = 0;
static unsigned int current_column = 0;
//Start with the defaukt black and white color scheme
uint8_t color = 0xF0;
/**
    make video_word
    This function basically makes the actual word that goes into the video memory.
    The data word is made up of the background and foreground colors of the character entered, along with the actual character.
*/
uint16_t make_video_word(uint8_t color, char character){
  return ((uint16_t)color << 8) | ((uint16_t)character); //The video word is structured lke this -
  /*
   *  ---------------------------------------
   *  | color byte | character byte (ASCII) |
   *  ---------------------------------------
   * We return exactly that.
   */
}


/**
   make_color
   Returns a byte which has the encoded values of the foreground and background color. Currently a dummy
*/
uint8_t make_color(uint8_t color_fg, uint8_t color_bg){
  //The color byte is in the form  - 0xBF
  //B - Background color nibble
  //F - Foreground color nibble
  return (color_bg << 4)|(color_fg);
}

/**
   term_init
   Intializes the terminal by clearing the terminal.
*/
void term_init(){
  current_row = 0;
  current_column = 0;
  vga_cols = 80;
  vga_rows = 25;
  uint16_t clear_word = make_video_word(color, ' ');//We make a video word which is effectively a space character. We fill the whole screen with this to clear it visually.
  //The actual process of clearing
  for(unsigned int i = 0; i < vga_cols; i++){
    for(unsigned int j = 0; j < vga_rows; j++){
      VGA_MEM[j*vga_cols + i] = clear_word;
    }
  }
}

/*
  term_puts
  Inputs a character at the next blank position. Processes both printable and non-printable characters.
 */
void term_putc(char c){
  switch(c){
    //In case of a new line character
  case '\n':
    current_row++;//We increase the row index by 1, causing the next bit of data to be entered at the next line
    current_column = 0;//We set the column index to 0, causing the next bit of data to start from the first (or zeroth, whatever indexing you prefer) column.
    break;
  case '\t':
    current_column += 4;//Incase of a tab, the column index is incremented by 4, leaving 4 blank spaces
    break;
  case '\r':
    current_column = 0;
    break;
  default:
    VGA_MEM[current_row*vga_cols + current_column] = make_video_word(color, c); //In case of any other character, just print it.
    current_column++;//Also increase the column index by one, so the next character gets printed in the next column.
  }
  //The remaining just handles what happends when the indexes step outside of their ranges.
  if(current_column > vga_cols - 1){
    if(current_row > vga_rows - 1){
      current_row = 0;
    }
    current_column = 0;
  }
  if(current_row > vga_rows - 1){
    current_row = 0;
    current_column = 0;
  }
}


/*
  term_print
  Prints the character string out to the screen
*/
void term_print(char* string){
  int i = 0;
  while(string[i] != '\0'){
    //Call term_puts till the whole string is printed.
    term_putc(string[i]);
    i++;
  }
}
