// ------------------------------------------------------------------------------
//
//  Description: This file contains the code to initialize the starting conditions of the program
// It enables the interrupts, and resets the wheels pins.
//
// GLobal Variables: display_line, display, update_display, update_display_count, wheel_on_count, wheels_on
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
// ------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

// Global Variables
extern char display_line[NUM_DISPLAY_lINES][NUM_lINES_LAYER];
extern char *display[NUM_DISPLAY_lINES];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern unsigned int wheel_on_count;
extern char wheels_on;

void Init_Conditions(void);

// ------------------------------------------------------------------------------
//
//  Description: This file contains the code to initialize the starting conditions of the program
// It enables the interrupts, and resets the wheels pins.
//
// GLobal Variables: display_line, display, update_display, update_display_count, wheel_on_count, wheels_on
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//
// ------------------------------------------------------------------------------

void Init_Conditions(void){
//------------------------------------------------------------------------------

  int i;
  for(i=DISPLAY_LINE_LAYER_0;i<NUM_lINES_LAYER;i++){
    display_line[DISPLAY_lINE_0][i] = RESET_STATE;
    display_line[DISPLAY_lINE_1][i] = RESET_STATE;
    display_line[DISPLAY_lINE_2][i] = RESET_STATE;
    display_line[DISPLAY_lINE_3][i] = RESET_STATE;
  }
  display_line[DISPLAY_lINE_0][DISPLAY_LINE_LAYER_10] = RESET_STATE;
  display_line[DISPLAY_lINE_1][DISPLAY_LINE_LAYER_10] = RESET_STATE;
  display_line[DISPLAY_lINE_2][DISPLAY_LINE_LAYER_10] = RESET_STATE;
  display_line[DISPLAY_lINE_3][DISPLAY_LINE_LAYER_10] = RESET_STATE;

  display[DISPLAY_lINE_0] = &display_line[DISPLAY_lINE_0][RESET_STATE];
  display[DISPLAY_lINE_1] = &display_line[DISPLAY_lINE_1][RESET_STATE];
  display[DISPLAY_lINE_2] = &display_line[DISPLAY_lINE_2][RESET_STATE];
  display[DISPLAY_lINE_3] = &display_line[DISPLAY_lINE_3][RESET_STATE];
  update_display = RESET_STATE;


// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}