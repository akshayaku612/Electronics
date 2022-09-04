// ------------------------------------------------------------------------------
//
//  Description: This file contains the code to create the switch interrupts
// It includes the Pragma vector and the ISR for all the switch interrupts
//
//  Akshay Kamalapuram Sridhar
//  Oct 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
// ------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"
#include <string.h>

unsigned int sw1_pressed_interrupt=FALSE;
unsigned int sw2_pressed_interrupt=FALSE;
unsigned int sw2_pressed=FALSE;
unsigned int sw1_pressed=FALSE;
unsigned int prepare_display_flag=FALSE;

// ------------------------------------------------------------------------------
//
//  Description: This file contains the code to create the switch interrupts
// It includes the Pragma vector and the ISR for all the switch interrupts
//
//  Akshay Kamalapuram Sridhar
//  Oct 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//
//  ISR contains interrupt for the toggling the switch
//
// ------------------------------------------------------------------------------

#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
//Switch 1
  if (P4IFG & SW1) {
    P4IFG &= ~SW1; // IFG SW1 cleared
    P4IE &= ~SW1; // P2.6 interrupt disabled
    P6OUT ^= LCD_BACKLITE;
    sw1_pressed_interrupt=TRUE;
    sw1_pressed=TRUE;
  }  
}

// ------------------------------------------------------------------------------
//
//  Description: This file contains the code to create the switch interrupts
// It includes the Pragma vector and the ISR for all the switch interrupts
//
//  Akshay Kamalapuram Sridhar
//  Oct 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//
//  ISR contains interrupt for the toggling the switch
//
// ------------------------------------------------------------------------------

#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
// Switch 2
  if (P2IFG & SW2) {
    P2IFG &= ~SW2; // IFG SW2 cleared
    P2IE &= ~SW2; // P2.6 interrupt disabled
    P6OUT ^= LCD_BACKLITE;
    sw2_pressed_interrupt=TRUE;
    sw2_pressed=TRUE;
  }   
}