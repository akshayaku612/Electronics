// ------------------------------------------------------------------------------
//
//  Description: This file contains the code to initialize both the red and green led.
// It contains a function Init_LEDs that turns on both the red and green LEDs
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
// ------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

void Init_LEDs(void);

// ------------------------------------------------------------------------------
//
//  Description: This file contains the code to initialize both the red and green led.
// It contains a function Init_LEDs that turns on both the red and green LEDs
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//
//  Ports: The POUT bits of P1.0 and P6.0 are changed to 0. They are configured as GPIO pins.
//  Alternate functions for P1.0: UCB0STE, SMCLK, VSS, ADC
//  Alternate functions for P6.0: TB3.CCI1A, TB3.1
// ------------------------------------------------------------------------------

void Init_LEDs(void){
  //------------------------------------------------------------------------------
  // LED Configurations
  //------------------------------------------------------------------------------
  // Turns on both LEDs
  P1OUT &= ~RED_LED;
  P6OUT &= ~GRN_LED;
  //------------------------------------------------------------------------------
}