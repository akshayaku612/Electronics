// ------------------------------------------------------------------------------
//
//  Description: This file contains the code to create the timer interrupts
// It includes the Pragma vector and the ISR for all the timer interrupts
//
//  Akshay Kamalapuram Sridhar
//  Oct 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
// ------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

extern unsigned int Time_Sequence;
extern unsigned int Movement_Timer;
extern unsigned int Counter_Timer;
extern unsigned int Circle_Timer;
extern unsigned int sw1_pressed_interrupt;
extern unsigned int sw2_pressed_interrupt;
extern volatile unsigned char update_display;
extern unsigned int line_follower_state;
extern unsigned int traverse_state;
extern unsigned int circle_timer_flag;

unsigned int debounce_counter=RESET_STATE;
unsigned int Movement_Timer_count=RESET_STATE;
unsigned int counter_timer_count=RESET_STATE;
unsigned int circle_timer_count=RESET_STATE;
unsigned int line_follower_timer_flag=RESET_STATE;
unsigned int flag=RESET_STATE;
unsigned int display_update_count=RESET_STATE;
unsigned int follow_flag=RESET_STATE;
unsigned int iot_ready=RESET_STATE;


// ------------------------------------------------------------------------------
//
//  Description: This file contains the code to create the timer interrupts
// It includes the Pragma vector and the ISR for all the timer interrupts
//
//  Akshay Kamalapuram Sridhar
//  Oct 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//
//  ISR contains interrupt for the timer-sequence and state machine timer
//
// ------------------------------------------------------------------------------

#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB0 0 Interrupt handler
//----------------------------------------------------------------------------
  TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
  follow_flag=ALWAYS;
  iot_ready=ALWAYS;
  if (Time_Sequence>limit_time) P2OUT |= DAC_ENB; // Value = High [enabled]
  if (Time_Sequence<iot_reset_time) {
    P3OUT &= ~IOT_RESET;
    iot_ready=RESET_STATE;
  }
  if (Time_Sequence<iot_reset_time) { 
    iot_ready=RESET_STATE;
  }
  ++Time_Sequence;
//----------------------------------------------------------------------------
}

// ------------------------------------------------------------------------------
//
//  Description: This file contains the code to create the timer interrupts
// It includes the Pragma vector and the ISR for all the timer interrupts
//
//  Akshay Kamalapuram Sridhar
//  Oct 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//
//  ISR contains interrupts debounce switches and for updating the display
//
// ------------------------------------------------------------------------------

#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){ 
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
  switch(__even_in_range(TB0IV,OVERFLOW)){
    case RESET_STATE: break; // No interrupt
    case CCR1:
        if (sw1_pressed_interrupt){
          debounce_counter++;
          if (debounce_counter>DEBOUNCE_LIMIT){
            TB0CCR1 += TB0CCR1_INTERVAL;
            P4IE |= SW1; // P4.6 interrupt enabled
            debounce_counter=RESET_STATE;
            sw1_pressed_interrupt=RESET_STATE;
          }
        }
        if (sw2_pressed_interrupt){
          debounce_counter++;
          if (debounce_counter>DEBOUNCE_LIMIT){
            TB0CCR1 += TB0CCR1_INTERVAL;
            P2IE |= SW2; // P2.6 interrupt enabled
            debounce_counter=RESET_STATE;
            sw2_pressed_interrupt=RESET_STATE;
          }
        } 
        break;
    case CCR2:
        TB0CCR2 += TB0CCR2_INTERVAL;
        display_update_count++;
        if (display_update_count>=second_count){
          update_display = ALWAYS;
          display_update_count = RESET_STATE;
        }
        flag=!flag;
        break;
    case OVERFLOW: // overflow
        break;
    default: break;
  }
//----------------------------------------------------------------------------
}


//Timer Interrupt for movement and for counting expended time
#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void){
//------------------------------------------------------------------------------
// TimerB1 0 Interrupt handler
//----------------------------------------------------------------------------
  TB1CCR0 += TB1CCR0_INTERVAL; // Add Offset to TBCCR0
  Movement_Timer_count++;
  counter_timer_count++;
  circle_timer_count++;
  
  if (counter_timer_count>=second_count) {
    Counter_Timer=Counter_Timer+incrementer;
    counter_timer_count=RESET_STATE;
  }
  if (Movement_Timer_count>=second_count) {
    Movement_Timer=Movement_Timer+incrementer;
    Movement_Timer_count=RESET_STATE;
  }
  if (circle_timer_count>=second_count){
    Circle_Timer=Circle_Timer+incrementer;
    circle_timer_count=RESET_STATE;
  }
  if (circle_timer_flag && Circle_Timer>=second_count) {
    line_follower_state=line_follow;
    traverse_state=pause;
    circle_timer_flag=RESET_STATE;
  }
  line_follower_timer_flag=!line_follower_timer_flag;  
//----------------------------------------------------------------------------
}

#pragma vector=TIMER1_B1_VECTOR
__interrupt void TIMER1_B1_ISR(void){ 
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
  switch(__even_in_range(TB1IV,OVERFLOW)){
    case RESET_STATE: break; // No interrupt
    case CCR1:
        ADCCTL0 |= ADCSC;
        TB1CCR1 += TB1CCR1_INTERVAL;
        break;
    case CCR2: break;    
    case OVERFLOW: // overflow
        break;
    default: break;
  }
//----------------------------------------------------------------------------
}