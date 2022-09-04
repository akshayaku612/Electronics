// ------------------------------------------------------------------------------
//
//  Description: This file contains the DAC interrupt code which is unused
//
//  Akshay Kamalapuram Sridhar
//  Nov 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
// ------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

// The interrupt is not used
#pragma vector = SAC1_SAC3_VECTOR
__interrupt void SAC3_ISR(void){
  switch(__even_in_range(SAC0IV,SACIV_4)){
  case SACIV_0: break;
  case SACIV_2: break;
  case SACIV_4:
//   DAC_data++;
//   DAC_data &= 0xFFF;
//   SAC3DAT = DAC_data;                 // DAC12 output positive ramp
    break;
  default: break;
  }
}