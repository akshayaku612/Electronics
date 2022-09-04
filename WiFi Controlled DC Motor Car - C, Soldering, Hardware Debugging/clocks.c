// ------------------------------------------------------------------------------
//
//  Description: This file contains the Clock Initialization
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.12.1
// ------------------------------------------------------------------------------
#include  "functions.h"
#include  "macros.h"
#include  "msp430.h"

void Init_Clocks(void);
void Software_Trim(void);

void Init_Clocks(void){
// -----------------------------------------------------------------------------
// Clock Configurtaions
// This is the clock initialization for the program.
// Initial clock configuration, runs immediately after port configuration.
// Disables 1ms watchdog timer,
// Configure MCLK for 8MHz and XT1 sourcing ACLK and FLLREF.
//
// Description: Configure ACLK = 32768Hz,
//                        MCLK = DCO + XT1CLK REF = 8MHz,
//                        SMCLK = MCLK/2 = 4MHz.
// Toggle LED to indicate that the program is running.
//
// -----------------------------------------------------------------------------
  WDTCTL = WDTPW | WDTHOLD;  // Disable watchdog

  do{
    CSCTL7 &= ~XT1OFFG;      // Clear XT1 fault flag
    CSCTL7 &= ~DCOFFG;       // Clear DCO fault flag
    SFRIFG1 &= ~OFIFG;
  } while (SFRIFG1 & OFIFG); // Test oscillator fault flag
  __bis_SR_register(SCG0);   // disable FLL

  CSCTL1 = DCOFTRIMEN_1;
  CSCTL1 |= DCOFTRIM0;
  CSCTL1 |= DCOFTRIM1;       // DCOFTRIM=3
  CSCTL1 |= DCORSEL_3;       // DCO Range = 8MHz

  CSCTL2 = FLLD_0 + DCODIV;     // DCODIV = 8MHz

  CSCTL3 |= SELREF__XT1CLK;  // Set XT1CLK as FLL reference source
  __delay_cycles(DCO_FREQ_TRIM);
  __bic_SR_register(SCG0);   // enable FLL
  Software_Trim();           // Software Trim to get the best DCOFTRIM value

  CSCTL4 = SELA__XT1CLK;     // Set ACLK = XT1CLK = 32768Hz
  CSCTL4 |= SELMS__DCOCLKDIV;// DCOCLK = MCLK and SMCLK source

//  CSCTL5 |= DIVM__2;         // MCLK = DCOCLK / 2  = 4MHZ,
//  CSCTL5 |= DIVS__8;         // SMCLK = MCLK / 8 = 1MHz
  CSCTL5 |= DIVM_0;        // MCLK = DCOCLK = 8MHZ,
  CSCTL5 |= DIVS_0;        // SMCLK = MCLK = 8MHz
    
  PM5CTL0 &= ~LOCKLPM5;      // Disable the GPIO power-on default high-impedance mode
                             // to activate previously configured port settings
}

void Software_Trim(void){
// --COPYRIGHT--,BSD_EX
// Copyright (c) 2014, Texas Instruments Incorporated
// All rights reserved.
  unsigned int oldDcoTap = ALWAYS_ON;
  unsigned int newDcoTap = ALWAYS_ON;
  unsigned int newDcoDelta = ALWAYS_ON;
  unsigned int bestDcoDelta = ALWAYS_ON;
  unsigned int csCtl0Copy = RESET_STATE;
  unsigned int csCtl1Copy = RESET_STATE;
  unsigned int csCtl0Read = RESET_STATE;
  unsigned int csCtl1Read = RESET_STATE;
  unsigned int dcoFreqTrim = DCO_FREQ_TRIM;
  unsigned char endLoop = RESET_STATE;
  do{
    CSCTL0 = DCO_TAP;                         // DCO Tap = 256
    do{
      CSCTL7 &= ~DCOFFG;                    // Clear DCO fault flag
    }while (CSCTL7 & DCOFFG);               // Test DCO fault flag
    // Wait FLL lock status (FLLUNLOCK) to be stable
    // Suggest to wait 24 cycles of divided FLL reference clock
    __delay_cycles((unsigned int)DELAY_CYCLES * MCLK_FREQ_MHZ);
    while((CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)) &&
         ((CSCTL7 & DCOFFG) == RESET_STATE));
    csCtl0Read = CSCTL0;                    // Read CSCTL0
    csCtl1Read = CSCTL1;                    // Read CSCTL1
    oldDcoTap = newDcoTap;                  // Record DCOTAP value of last time
    newDcoTap = csCtl0Read & CURRENT_DCO_TAP;        // Get DCOTAP value of this time
    dcoFreqTrim = (csCtl1Read & DCOFTRIM)>>BIT_SHIFT_FOUR; // Get DCOFTRIM value
    if(newDcoTap < OLD_DCO_TAP){                    // DCOTAP < 256
      newDcoDelta = OLD_DCO_TAP - newDcoTap;        // Delta value between DCPTAP and 256
      if((oldDcoTap != ALWAYS_ON) &&
         (oldDcoTap >= OLD_DCO_TAP)){               // DCOTAP cross 256
        endLoop = ALWAYS;                        // Stop while loop
      }else{
        dcoFreqTrim--;
        CSCTL1 = (csCtl1Read & (~DCOFTRIM)) | (dcoFreqTrim<<BIT_SHIFT_FOUR);
      }
    }else{                                  // DCOTAP >= 256
      newDcoDelta = newDcoTap - OLD_DCO_TAP;        // Delta value between DCPTAP and 256
      if(oldDcoTap < OLD_DCO_TAP){                  // DCOTAP cross 256
        endLoop = ALWAYS;                        // Stop while loop
      }else{
        dcoFreqTrim++;
        CSCTL1 = (csCtl1Read & (~DCOFTRIM)) | (dcoFreqTrim<<BIT_SHIFT_FOUR);
      }
    }
    if(newDcoDelta < bestDcoDelta){         // Record DCOTAP closest to 256
      csCtl0Copy = csCtl0Read;
      csCtl1Copy = csCtl1Read;
      bestDcoDelta = newDcoDelta;
    }
  }while(endLoop == RESET_STATE);                     // Poll until endLoop == 1
  CSCTL0 = csCtl0Copy;                      // Reload locked DCOTAP
  CSCTL1 = csCtl1Copy;                      // Reload locked DCOFTRIM
  while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1));// Poll until FLL is locked
}


