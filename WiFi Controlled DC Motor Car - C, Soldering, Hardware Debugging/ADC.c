// ------------------------------------------------------------------------------
//
//  Description: This file contains the ADC Initialization
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.12.1
// ------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

void Init_ADC(void);

void Init_ADC(void){
//------------------------------------------------------------------------------
// V_DETECT_L (0x04) // Pin 2 A2
// V_DETECT_R (0x08) // Pin 3 A3
// V_THUMB (0x20) // Pin 5 A5
//------------------------------------------------------------------------------
// ADCCTL0 Register
  ADCCTL0 = RESET_STATE; // Reset
  ADCCTL0 |= ADCSHT_2; // 16 ADC clocks
  ADCCTL0 |= ADCMSC; // MSC
  ADCCTL0 |= ADCON; // ADC ON
// ADCCTL1 Register
  ADCCTL1 = RESET_STATE; // Reset
  ADCCTL1 |= ADCSHS_0; // 00b = ADCSC bit
  ADCCTL1 |= ADCSHP; // ADC sample-and-hold SAMPCON signal from sampling timer.
  ADCCTL1 &= ~ADCISSH; // ADC invert signal sample-and-hold.
  ADCCTL1 |= ADCDIV_0; // ADC clock divider - 000b = Divide by 1
  ADCCTL1 |= ADCSSEL_0; // ADC clock MODCLK
  ADCCTL1 |= ADCCONSEQ_0; // ADC conversion sequence 00b = Single-channel single-conversion
// ADCCTL1 & ADCBUSY identifies a conversion is in process
// ADCCTL2 Register
  ADCCTL2 = RESET_STATE; // Reset
  ADCCTL2 |= ADCPDIV0; // ADC pre-divider 00b = Pre-divide by 1
  ADCCTL2 |= ADCRES_0; // ADC resolution 8b
  ADCCTL2 &= ~ADCDF; // ADC data read-back format 0b = Binary unsigned.
  ADCCTL2 &= ~ADCSR; // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
// ADCMCTL0 Register
  ADCMCTL0 |= ADCSREF_0; // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
  ADCMCTL0 |= ADCINCH_2; // 
  ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
  ADCCTL0 |= ADCENC; // ADC enable conversion.
  ADCCTL0 |= ADCSC; // ADC start conversion.
}