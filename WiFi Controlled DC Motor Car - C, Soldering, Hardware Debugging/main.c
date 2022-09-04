//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Akshay Kamalapuram Sridhar
//  Oct 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "macros.h"
#include  "functions.h"
#include  "msp430.h"
#include <string.h>
//#include  "LCD.h"

// Function Prototypes
void main(void);

// Global Variables
volatile char slow_input_down;

//Display
extern char display_line[NUM_DISPLAY_lINES][NUM_lINES_LAYER];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
unsigned int Time_Sequence;
unsigned int Movement_Timer;
unsigned int Counter_Timer;
unsigned int Circle_Timer;

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------

// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;

  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_DAC();
  Init_LCD();                          // Initialize LCD
  Init_ADC();                          //Initialize ADC
  Init_Timer_B0();                       // Initialize Timers
  Init_Timer_B1();
  Init_Timer_B3();
  Init_Serial_UCA0();                     //Initialize Serial
  Init_Serial_UCA1();
  
  //ClrDisplay();
// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
  strcpy(display_line[DISPLAY_lINE_0], "   ncsu   ");
  strcpy(display_line[DISPLAY_lINE_1], "IP Address");
  strcpy(display_line[DISPLAY_lINE_2], "          ");
  strcpy(display_line[DISPLAY_lINE_3], "          ");

  enable_display_update();
  display_changed = ALWAYS;
  update_display = ALWAYS;
  Time_Sequence=RESET_STATE;
  Movement_Timer=RESET_STATE;
  Counter_Timer=RESET_STATE;
  Circle_Timer=RESET_STATE;

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run 
    setThreshold();
    //line_traversal();
    Iot_cycle();
    display_all();
  }
}