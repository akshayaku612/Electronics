// ------------------------------------------------------------------------------
//
//  Description: This file contains the code to create the adc interrupts
// It reads channels for left detector, right detector and thumbwheel
//
//  Akshay Kamalapuram Sridhar
//  Oct 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
// ------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"
#include <string.h>

unsigned int ADC_Channel=RESET_STATE;
unsigned int ADC_Left_Detect=RESET_STATE;
unsigned int ADC_Right_Detect=RESET_STATE;
unsigned int ADC_ThumbWheel_Detect=RESET_STATE;

unsigned int adc_value_count=RESET_STATE;
unsigned int left_value=RESET_STATE;
unsigned int right_value=RESET_STATE;
unsigned int left_detector_avg=RESET_STATE;
unsigned int right_detector_avg=RESET_STATE;
unsigned int ADC_Left_Detect_flag=RESET_STATE;
unsigned int ADC_Right_Detect_flag=RESET_STATE;

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
   switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
    case ADCIV_NONE:
      break;
    case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
// before its previous conversion result was read.
      break;
    case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
      break;
    case ADCIV_ADCHIIFG: // Window comparator interrupt flags
      break;
    case ADCIV_ADCLOIFG: // Window comparator interrupt flag
      break;
    case ADCIV_ADCINIFG: // Window comparator interrupt flag
      break;
    case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
      ADCCTL0 &= ~ADCENC; // Disable ENC bit.
      switch (ADC_Channel++){
        case channel_0: // Channel A2 Interrupt for left detector
          ADC_Left_Detect = ADCMEM0; // Move result into Global
          ADC_Left_Detect = ADC_Left_Detect >> bit_shift_2; // Divide the result by 4
          ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
          ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
          ADC_Left_Detect_flag=ALWAYS;
          left_value+=ADC_Left_Detect;
          break;
        case channel_1: //Right Detector
          ADC_Right_Detect = ADCMEM0; // Move result into Global
          ADC_Right_Detect = ADC_Right_Detect >> bit_shift_2; // Divide the result by 4
          ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A3
          ADCMCTL0 |= ADCINCH_5; // Enable Next channel A4
          ADC_Right_Detect_flag=ALWAYS;
          right_value+=ADC_Right_Detect;
          adc_value_count++;
          if (adc_value_count>avg_value){
            left_detector_avg = left_value/num_of_chars;
            right_detector_avg  = right_value/num_of_chars;
            adc_value_count=RESET_STATE;
            left_value=RESET_STATE;
            right_value=RESET_STATE;
          }
          break;
        case channel_2: //Thumbwheel
          ADC_ThumbWheel_Detect = ADCMEM0; // Move result into Global
          ADC_ThumbWheel_Detect = ADC_ThumbWheel_Detect >> bit_shift_2; // Divide the result by 4
          ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A3
          ADCMCTL0 |= ADCINCH_2; // Enable Next channel A4
          ADC_Channel=RESET_STATE;
          break;
        default:
          break;
      }
      ADCCTL0 |= ADCENC; // Enable Conversions
   default:
     break;
  }
}
