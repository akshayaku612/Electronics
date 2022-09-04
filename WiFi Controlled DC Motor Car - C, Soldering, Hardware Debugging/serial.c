// ------------------------------------------------------------------------------
//
//  Description: This file contains the code for initializing serial ports
//
//
//  Akshay Kamalapuram Sridhar
//  Nov 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
// ------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

void Init_Serial_UCA0(void);
void Init_Serial_UCA1(void);

extern volatile unsigned int usb_rx_wr;
extern volatile unsigned int usb_rx_rd;
extern volatile unsigned int iot_rx_wr;
extern volatile unsigned int iot_rx_rd;

extern volatile char IOT_2_PC[SMALL_RING_SIZE]; //ring buffer
extern volatile char PC_2_IOT[SMALL_RING_SIZE]; //ring buffer

//UCA0 Port initialization
void Init_Serial_UCA0(void){

  for(int i=BEGINNING; i<SMALL_RING_SIZE; i++){
    IOT_2_PC[i] = BEGINNING; // USB Rx Buffer
  }
  iot_rx_wr = BEGINNING;
  iot_rx_rd = BEGINNING;
  
// Configure eUSCI_A0 for UART mode
  UCA0CTLW0 = BEGINNING; // Use word register
  UCA0CTLW0 |= UCSWRST; // Set Software reset enable
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
  UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
  UCA0CTLW0 &= ~UCPEN; // No Parity
  UCA0CTLW0 &= ~UCSYNC;
  UCA0CTLW0 &= ~UC7BIT;
  UCA0CTLW0 |= UCMODE_0;
  
  // 115200 Baud Rate
  UCA0BRW = brw_value;
  UCA0MCTLW = mctl_value ; // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
  
  UCA0CTLW0 &= ~ UCSWRST; // Set Software reset enable
  UCA0IE |= UCRXIE; // Enable RX interrupt
}

//UCA1 Port initialization
void Init_Serial_UCA1(void){
  
  for(int i=BEGINNING; i<SMALL_RING_SIZE; i++){
    PC_2_IOT[i] = BEGINNING; // USB Rx Buffer
  }
  usb_rx_wr = BEGINNING;
  usb_rx_rd = BEGINNING;
  
// Configure eUSCI_A1 for UART mode
  UCA1CTLW0 = BEGINNING; // Use word register
  UCA1CTLW0 |= UCSWRST; // Set Software reset enable
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
  UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
  UCA1CTLW0 &= ~UCPEN; // No Parity
  UCA1CTLW0 &= ~UCSYNC;
  UCA1CTLW0 &= ~UC7BIT;
  UCA1CTLW0 |= UCMODE_0;
  
  // 115200 Baud Rate
  UCA1BRW = brw_value;
  UCA1MCTLW = mctl_value ; // UCA1MCTLW = UCSx concatenate UCFx concatenate UCOS16;
  
  UCA1CTLW0 &= ~ UCSWRST; // Set Software reset enable
  UCA1IE |= UCRXIE; // Enable RX interrupt
}  