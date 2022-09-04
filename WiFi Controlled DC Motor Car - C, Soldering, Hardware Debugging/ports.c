// ------------------------------------------------------------------------------
//
//  Description: This file contains the port initializations for the Microcontroller
// It consists of sub-functions that initialize each port which are ultimately called in the Init_Ports() function
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
// ------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

void Init_Ports(void); //This calls the rest of the initialization functions
void Init_Port_1(void); //This function will initialize all pins in port 1
void Init_Port_2(void); //This function will initialize all pins in port 2
void Init_Port_3(void); //This function will initialize all pins in port 3
void Init_Port_4(void); //This function will initialize all pins in port 4
void Init_Port_5(void); //This function will initialize all pins in port 5
void Init_Port_6(void); //This function will initialize all pins in port 6

// ------------------------------------------------------------------------------
//
//  Description: This file contains the port initializations for the Microcontroller
// It consists of sub-functions that initialize each port which are ultimately called in the Init_Ports() function
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//
//  Ports: Port 1 is configured as GPIO for the red LED. 1.1 to 1.5 is configured as ADC. 1.6 is configured as a Receive pin and 1.7 is configured as a trasnmitter pin
//  Alternate functions for P1.0: UCB0STE, SMCLK, VSS, ADC
//  Alternate functions for P1.1: UCB0CLK, ACLK, VSS, ADC
//  Alternate functions for P1.2: UCB0SIMO/UCB0SDA, TB0TRG, ADC
//  Alternate functions for P1.3: UCB0SOMI/UCB0SCL, ADC
//  Alternate functions for P1.4: UCA0STE, ADC, JTAG
//  Alternate functions for P1.5: UCA0CLK, ADC, JTAG
//  Alternate functions for P1.6: UCA0RXD/UCA0SOMI , TB0, ADC, JTAG
//  Alternate functions for P1.7: UCA0TXD/UCA0SIMO  , TB0, ADC, JTAG
// ------------------------------------------------------------------------------

void Init_Port_1(void){
  P1OUT = LOW; // P1 set Low
  P1DIR = DEFAULT_OUT_DIR; // Set P1 direction to output
  
  P1SEL0 &= ~RED_LED;
  P1SEL1 &= ~RED_LED;
  P1DIR |= RED_LED;
  P1OUT &= ~RED_LED;
  
  P1SEL0 |= A1_SEEED;
  P1SEL1 |= A1_SEEED;
  
  P1SEL0 |= V_DETECT_L;
  P1SEL1 |= V_DETECT_L;
  
  P1SEL0 |= V_DETECT_R;
  P1SEL1 |= V_DETECT_R;
  
  P1SEL0 |= V_BAT;
  P1SEL1 |= V_BAT;
  
  P1SEL0 |= V_THUMB;
  P1SEL1 |= V_THUMB;
  
  P1SEL0 |= UCA0RXD;
  P1SEL1 &= ~UCA0RXD;
  
  P1SEL0 |= UCA0TXD;
  P1SEL1 &= ~UCA0TXD;
  
}

// ------------------------------------------------------------------------------
//
//  Description: This file contains the port initializations for the Microcontroller
// It consists of sub-functions that initialize each port which are ultimately called in the Init_Ports() function
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//
//  Ports: Port 2 is configured as GPIO for 2.0, 2.1, 2.2, 2.4, 2.5. 2.3 is SW2 (GPIO) pin and 2.6 is LFX clock pin OUT and LFX Clock pin IN
//  Alternate functions for P2.0: TB1, COMP0
//  Alternate functions for P2.1: TB1, COMP1
//  Alternate functions for P2.2: TB1CLK
//  Alternate functions for P2.3: TB1TRG, VSS
//  Alternate functions for P2.4: COMP1
//  Alternate functions for P2.5: COMP1
//  Alternate functions for P2.6: GPIO, VSS, XOUT
//  Alternate functions for P2.7: GPIO, VSS, XIN
// ------------------------------------------------------------------------------

void Init_Port_2(void){ // Configure Port 2
//------------------------------------------------------------------------------
  P2OUT = DEFAULT_LOW; // P2 set Low
  P2DIR = DEFAULT_OUT_DIR; // Set P2 direction to output
  
  P2SEL0 &= ~DAC_ENB; // P2_0 GPIO operation
  P2SEL1 &= ~DAC_ENB; // P2_0 GPIO operation
  P2OUT &= ~DAC_ENB; // Direction = output
  P2DIR |= DAC_ENB; // Direction = output
  
  P2SEL0 &= ~IR_LED; // IR_LED GPIO operation
  P2SEL1 &= ~IR_LED; // IR_LED GPIO operation
  P2OUT |= IR_LED; // Initial Value = High / On
  P2DIR |= IR_LED; // Direction = output
  
  P2SEL0 &= ~P2_2; // P2_2 GPIO operation
  P2SEL1 &= ~P2_2; // P2_2 GPIO operation
  P2DIR &= ~P2_2; // Direction = input
  
  P2SEL0 &= ~SW2; // SW2 Operation
  P2SEL1 &= ~SW2; // SW2 Operation
  P2OUT |= SW2; // Configure pullup resistor
  P2DIR &= ~SW2; // Direction = input
  P2REN |= SW2; // Enable pullup resistor
  P2IES |= SW2; // P2.0 Hi/Lo edge interrupt
  P2IFG &= ~SW2; // Clear all P2.6 interrupt flags
  P2IE |= SW2; // P2.6 interrupt enabled
  
  P2SEL0 &= ~IOT_PROG_SEL; // IOT_PROG_SEL GPIO operation
  P2SEL1 &= ~IOT_PROG_SEL; // IOT_PROG_SEL GPIO operation
  P2OUT &= ~IOT_PROG_SEL; // Initial Value = Low / Off
  P2DIR |= IOT_PROG_SEL; // Direction = input
  
  P2SEL0 &= ~P2_5; // P2_5 GPIO operation
  P2SEL1 &= ~P2_5; // P2_5 GPIO operation
  P2DIR &= ~P2_5; // Direction = input
  
  P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
  P2SEL1 |= LFXOUT; // LFXOUT Clock operation
  P2SEL0 &= ~LFXIN; // LFXIN Clock operation
  P2SEL1 |= LFXIN; // LFXIN Clock operation
 //------------------------------------------------------------------------------
}

// ------------------------------------------------------------------------------
//
//  Description: This file contains the port initializations for the Microcontroller
// It consists of sub-functions that initialize each port which are ultimately called in the Init_Ports() function
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//
//  Ports: Port 3 is configured as GPIO for 3.0, 3.1, 3.5, 3.6 and 3.7. 3.2 is OA2N and 3.3 is OA2P. 3.4 is output for SMCLK
//  Alternate functions for P3.0: MCLK, VSS
//  Alternate functions for P3.1: OA2O
//  Alternate functions for P3.2: GPIO
//  Alternate functions for P3.3: GPIO
//  Alternate functions for P3.4: GPIO, VSS
//  Alternate functions for P3.5: OA3O
//  Alternate functions for P3.6: OA3-
//  Alternate functions for P3.7: OA3+
// ------------------------------------------------------------------------------

void Init_Port_3(void){
  P3OUT = DEFAULT_LOW; // P3 set Low
  P3DIR = DEFAULT_OUT_DIR; // Set P3 direction to input
  
  P3SEL0 &= ~TEST_PROBE;
  P3SEL1 &= ~TEST_PROBE;
  P3DIR &= ~TEST_PROBE;
  
  P3SEL0 &= ~OPT_INT;
  P3SEL1 &= ~OPT_INT;
  P3DIR &= ~OPT_INT;
  
  P3SEL0 |= OA2N;
  P3SEL1 |= OA2N;
  
  P3SEL0 |= OA2P;
  P3SEL1 |= OA2P;
  
  P3SEL0 |= SMCLK_OUT;
  P3SEL1 &= ~SMCLK_OUT;
  P3DIR |= SMCLK_OUT;
  
  P3SEL0 &= ~DAC_CNTL;
  P3SEL1 &= ~DAC_CNTL;
  P3DIR &= ~DAC_CNTL;
  
  P3SEL0 &= ~IOT_LINK;
  P3SEL1 &= ~IOT_LINK;
  P3DIR &= ~IOT_LINK;
  
  P3SEL0 &= ~IOT_RESET;
  P3SEL1 &= ~IOT_RESET;
  P3DIR &= ~IOT_RESET;
  
}

// ------------------------------------------------------------------------------
//
//  Description: This file contains the port initializations for the Microcontroller
// It consists of sub-functions that initialize each port which are ultimately called in the Init_Ports() function
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//
//  Ports: Port 4 is configured as GPIO for 4.0, 4.1, 4.4 are GPIO pins. 4.2 is a UART receiver pin. 4.3 is UART transceiver pin. 4.5 is the UCB1CLK . 4.6 is the UCB1SIMO. 4.7 is the UCB1SOMI
//  Alternate functions for P4.0: UCA1STE, UCA1RXD, UCA1TXD, TB3
//  Alternate functions for P4.1: UCA1CLK
//  Alternate functions for P4.2: GPIO, UCA1SOMI
//  Alternate functions for P4.3: GPIO, UCA1SIMO 
//  Alternate functions for P4.4: UCB1STE
//  Alternate functions for P4.5: GPIO
//  Alternate functions for P4.6: GPIO,UCB1SDA
//  Alternate functions for P4.7: GPIO, UCB1SCL
// ------------------------------------------------------------------------------

void Init_Port_4(void){ // Configure PORT 4
//------------------------------------------------------------------------------
  P4OUT = DEFAULT_LOW; // P4 set Low
  P4DIR = DEFAULT_OUT_DIR; // Set P4 direction to output
  
  P4SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
  P4SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
  P4OUT |= RESET_LCD; // Set RESET_LCD Off [High]
  P4DIR |= RESET_LCD; // Set RESET_LCD direction to output
  
  P4SEL0 &= ~SW1; // SW1 GPIO operation
  P4SEL1 &= ~SW1; // SW1 GPIO operation
  P4PUD |= SW1; // Configure pullup resistor
  P4DIR &= ~SW1; // Direction = input
  P4REN |= SW1; // Enable pullup resistor
  P4IES |= SW1; // P4.2 Hi/Lo edge interrupt
  P4IFG &= ~SW1; // Clear all P2.6 interrupt flags
  P4IE |= SW1; // P4.2 interrupt enabled
  
  P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
  P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation
  P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
  P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation
  
  P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
  P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
  P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
  P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output
  
  P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
  P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation
  P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
  P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation
  P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
  P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
//------------------------------------------------------------------------------
}

// ------------------------------------------------------------------------------
//
//  Description: This file contains the port initializations for the Microcontroller
// It consists of sub-functions that initialize each port which are ultimately called in the Init_Ports() function
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//
//  Ports: Port 5 is configured as GPIO for all pins
//  Alternate functions for P5.0: TB2, MFM.RX, A8
//  Alternate functions for P5.1: TB2, MFM.TX, A9
//  Alternate functions for P5.2: TB2CLK, VSS, A10
//  Alternate functions for P5.3: TB2, VSS, A11
// ------------------------------------------------------------------------------

void Init_Port_5(void){
  
  P5OUT = DEFAULT_LOW; // P4 set Low
  P5DIR = DEFAULT_OUT_DIR; // Set P4 direction to input
  
  P5SEL0 &= ~CHECK_BAT;
  P5SEL1 &= ~CHECK_BAT;
  P5DIR |= CHECK_BAT;
  P5OUT &= ~CHECK_BAT;
  
  P5SEL0 &= ~V_BAT1;
  P5SEL1 &= ~V_BAT1;
  P5DIR &= ~V_BAT1;
  
  P5SEL0 &= ~V_DAC;
  P5SEL1 &= ~V_DAC;
  P5DIR &= ~V_DAC;
  
  P5SEL0 &= ~V_3_3;
  P5SEL1 |= ~V_3_3;
  P5DIR |= ~V_3_3;
  
  P5SEL0 &= ~IOT_PROG_MODE;
  P5SEL1 &= ~IOT_PROG_MODE;
  P5DIR &= ~IOT_PROG_MODE;
}

// ------------------------------------------------------------------------------
//
//  Description: This file contains the port initializations for the Microcontroller
// It consists of sub-functions that initialize each port which are ultimately called in the Init_Ports() function
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//
//  Ports: Port 6 is configured as GPIO for all pins
//  Alternate functions for P6.0: TB3.CCl1A, TB3.1
//  Alternate functions for P6.1: TB3.CCl2A, TB3.2
//  Alternate functions for P6.2: TB3.CCl3A, TB3.3
//  Alternate functions for P6.3: TB3.CCl4A, TB3.4
//  Alternate functions for P6.4: TB3.CCl5A, TB3.5
//  Alternate functions for P6.5: TB3.CCl6A, TB3.6
//  Alternate functions for P6.6: TB3CLK, VSS
// ------------------------------------------------------------------------------

void Init_Port_6(void){
  
  P6OUT = DEFAULT_LOW; // P4 set Low
  P6DIR = DEFAULT_OUT_DIR; // Set P4 direction to output
  
  P6SEL0 |= R_FORWARD;
  P6SEL1 &= ~R_FORWARD;
  P6DIR |= R_FORWARD;
  
  P6SEL0 |= L_FORWARD;
  P6SEL1 &= ~L_FORWARD;
  P6DIR |= L_FORWARD;
  
  P6SEL0 |= R_REVERSE;
  P6SEL1 &= ~R_REVERSE;
  P6DIR |= R_REVERSE;
  
  P6SEL0 |= L_REVERSE;
  P6SEL1 &= ~L_REVERSE;
  P6DIR |= L_REVERSE;
  
  P6SEL0 &= ~LCD_BACKLITE;
  P6SEL1 &= ~LCD_BACKLITE;
  P6DIR |= LCD_BACKLITE;
  P6OUT |= LCD_BACKLITE;
  
  P6SEL0 &= ~P6_5;
  P6SEL1 &= ~P6_5;
  P6DIR &= ~P6_5;
  
  P6SEL0 &= ~GRN_LED;
  P6SEL1 &= ~GRN_LED;
  P6DIR |= GRN_LED;
  P6OUT &= ~GRN_LED;
  
}

// ------------------------------------------------------------------------------
//
//  Description: This file contains the port initializations for the Microcontroller
// It consists of sub-functions that initialize each port which are ultimately called in the Init_Ports() function
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//
// ------------------------------------------------------------------------------

void Init_Ports(void){
  Init_Port_1();
  Init_Port_2();
  Init_Port_3();
  Init_Port_4();
  Init_Port_5();
  Init_Port_6();
}  