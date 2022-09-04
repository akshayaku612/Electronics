// ------------------------------------------------------------------------------
//
//  Description: This file contains the code to create the serial interrupts
// It includes the man-in-the-middle implementation
//
//  Akshay Kamalapuram Sridhar
//  Oct 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
// ------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"
#include <stdio.h>
#include <string.h>

//UCA0 - IOT
char process_buffer0[process_buffer_size]; // Size for appropriate Command Length
char pb0_index=RESET_STATE; // Index for process_buffer
volatile char IOT_2_PC[SMALL_RING_SIZE];
unsigned int iot_write_index; 
volatile unsigned int iot_rx_wr=RESET_STATE;
unsigned int iot_rx_rd=RESET_STATE; //only use in main

//UCA1 - PC
char process_buffer1[process_buffer_size]; // Size for appropriate Command Length
char pb1_index=RESET_STATE; // Index for process_buffer
volatile char PC_2_IOT[SMALL_RING_SIZE];
unsigned int usb_write_index; 
volatile unsigned int usb_rx_wr=RESET_STATE;
unsigned int usb_rx_rd=RESET_STATE; //only use in main

unsigned int receive_flag=RESET_STATE;
unsigned int response_buffer_current_buffer_size=RESET_STATE;
extern char* response_buffer[];
extern char iot_buffer_command_type_index;
extern char iot_buffer_response_index;

//Serial Port 0 - MCU/PC
#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){ // Echo back RXed character, confirm TX buffer is ready first
  switch(__even_in_range(UCA0IV,serial_limit)){
    case no_interrupt: break; // Vector 0 - no interrupt
    case rx:  // Vector 2 - RXIFG -> receives the output of commands here
      iot_write_index = iot_rx_wr++;
      IOT_2_PC[iot_write_index] = UCA0RXBUF; // Rx -> IOT_2_PC character array
      
      if (iot_rx_wr!=iot_rx_rd){
        process_buffer0[pb0_index]=IOT_2_PC[iot_write_index];
        iot_rx_rd++;
        UCA1IE |= UCTXIE;
      }
         
      if (iot_rx_wr >= (sizeof(IOT_2_PC))){
        iot_rx_wr = BEGINNING; // Circular buffer back to beginning
      }
      if (iot_rx_rd >= (sizeof(IOT_2_PC))){
        iot_rx_rd = BEGINNING; // Circular buffer back to beginning
      }
      
      response_buffer[iot_buffer_command_type_index][iot_buffer_response_index++]=process_buffer0[pb0_index];
      receive_flag=TRUE;
      break;
    case tx: // Vector 4 - TXIFG -> For sending messages to the IOT
      UCA0TXBUF = process_buffer1[pb1_index]; // Transmit Current Indexed value
      process_buffer1[pb1_index++] = NULL; // Null Location of Transmitted value
      if (pb1_index >= (sizeof(process_buffer1))){
        pb1_index = BEGINNING; // Circular buffer back to beginning
      }
      if(process_buffer1[pb1_index] == NULL){ // Is the next pb_index location NULL - End of Command
        UCA0IE &= ~UCTXIE; // Disable TX interrupt
      }
      break;
    default: 
      break;
  }
}  

//Serial Port 1 - IOT
#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){ // Echo back RXed character, confirm TX buffer is ready first
  switch(__even_in_range(UCA1IV,serial_limit)){
    case no_interrupt: break; // Vector 0 - no interrupt
    case rx: // Vector 2 - RXIFG
      usb_write_index = usb_rx_wr++;
      PC_2_IOT[usb_write_index] = UCA1RXBUF;
      
      if (usb_rx_wr!=usb_rx_rd){
        process_buffer1[pb1_index]=PC_2_IOT[usb_write_index];
        usb_rx_rd++;
        UCA0IE |= UCTXIE;
      }

      if (usb_rx_wr >= (sizeof(PC_2_IOT))){ // Rx -> PC_2_IOT character array
        usb_rx_wr = BEGINNING; // Circular buffer back to beginning
      }
      if (usb_rx_rd >= (sizeof(PC_2_IOT))){
        usb_rx_rd = BEGINNING; // Circular buffer back to beginning
      }
      break;
    case tx:  // Vector 4 - TXIFG
      UCA1TXBUF = process_buffer0[pb0_index]; // Transmit Current Indexed value
      process_buffer0[pb0_index++] = NULL; // Null Location of Transmitted value
      if (pb0_index >= (sizeof(process_buffer0))){
        pb0_index = BEGINNING; // Circular buffer back to beginning
      }
      if(process_buffer0[pb0_index] == NULL){ // Is the next pb_index location NULL - End of Command
        UCA1IE &= ~UCTXIE; // Disable TX interrupt
      }
      break;
    default: 
      break;     
  }
}
