// ------------------------------------------------------------------------------
//
//  Description: This file contains the code for the entire black line following
//
//
//  Akshay Kamalapuram Sridhar
//  Nov 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
// ------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

extern unsigned int left_detector_avg;
extern unsigned int right_detector_avg;
extern unsigned int follow_flag;
extern unsigned int line_follower_timer_flag;
extern volatile unsigned char display_changed;
extern unsigned int sw2_pressed;
extern char display_line[NUM_DISPLAY_lINES][NUM_lINES_LAYER];
extern unsigned int timer_flag;
extern unsigned int Movement_Timer;
extern unsigned int Circle_Timer;
extern unsigned int prepare_display_flag;
extern unsigned int sw1_pressed;
extern unsigned int flag;

unsigned int sw2_press_count=RESET_STATE;
unsigned int traverse_state=RESET_STATE;
unsigned int assign_black_value=RESET_STATE;
unsigned int black_border_value=RESET_STATE;
unsigned int turn_left_flag=RESET_STATE;
unsigned int display_calibration_flag=RESET_STATE;
unsigned int circle_timer_flag=RESET_STATE;
unsigned int line_follower_state=RESET_STATE;

void turn_time(void);
void line_traversal(void);
void setThreshold(void);
void intercept_line(void);
void intercept_turn(void);
void follow_black_line(void);
void turn_towards_center(void);
void move_towards_center(void);
void turn_2(void);

//high level function for line traversal
void line_traversal(void){
  switch(traverse_state){
    case initial_state:
      if (sw1_pressed) {
        traverse_state=pause;
        line_follower_state=initial_state;
        strcpy(display_line[DISPLAY_lINE_1], "BL Start  ");
        prepare_display_flag=incrementer;
      }  
      break;
    case black_intercept:
      intercept_line();
      break;
    case black_turn:
      intercept_turn();
      break; 
    case line_follow:
      if(!circle_timer_flag){
        Circle_Timer=initial_state;
        circle_timer_flag=ALWAYS;
      }
      follow_black_line();
      break;
    case turn_to_center:
      turn_towards_center();
      break;
    case move_to_center:
      move_towards_center();
      break;
    case end:
      stop_all_motors();
      break;
    case pause:
      if (!timer_flag) wait(seconds_2);
      else {
        stop_all_motors();
        traverse_state=line_follower_state+incrementer;
        timer_flag=RESET_STATE;
        Movement_Timer=RESET_STATE;
        if (traverse_state==black_intercept) strcpy(display_line[DISPLAY_lINE_0], "Intercept ");
        else if (traverse_state==black_turn) strcpy(display_line[DISPLAY_lINE_0], "BL Travel ");
        else if (traverse_state==line_follow) strcpy(display_line[DISPLAY_lINE_0],"BL Circle ");
        else if (traverse_state==turn_to_center) strcpy(display_line[DISPLAY_lINE_0]," Exit Turn");
        else if (traverse_state==move_to_center) strcpy(display_line[DISPLAY_lINE_0]," Exit Move");
        else if (traverse_state==end) strcpy(display_line[DISPLAY_lINE_0]," BL Exit  ");
      }
      break;  
    default: break;  
  }  
}  

//calibration for detectors
void setThreshold(void){
  if (sw2_pressed && !assign_black_value){ //assigning value of black_border_value
    if (sw2_press_count==RESET_STATE) {
      black_border_value=right_detector_avg;
      sw2_press_count++;
      sw2_pressed=FALSE;
      display_calibration_flag=ALWAYS;
    }
    else {
      black_border_value=(black_border_value+right_detector_avg)/2;
      assign_black_value=ALWAYS;
      sw2_pressed=FALSE;
    }
  }
}

//intercept line function
void intercept_line(void){
  if (line_follower_timer_flag) {
    stop_all_motors();
  }
  else if (follow_flag){
    move_forward(speed_val);
    if (right_detector_avg>=black_border_value || left_detector_avg>=black_border_value){ //finding black line when going forward
      stop_all_motors();
      follow_flag=RESET_STATE;
      line_follower_state=black_intercept;
      traverse_state=pause;
      Movement_Timer=RESET_STATE;
    }
  }  
}

//turning on the line after interception
void turn_2(void){
  if (timer_flag) {
     traverse_state=pause;
     line_follower_state=black_turn;
     traverse_state=pause;
     return;
  }
  movement(right, seconds2_str);
}  

//timed turning on the line
void turn_time(void){
  if (timer_flag) {
     traverse_state=pause;
     line_follower_state=black_turn;
     traverse_state=pause;
     return;
  }
 turn_right_timed(seconds_2);
}

//moving forward 
void forward_time(void){
  if (timer_flag) {
     traverse_state=pause;
     line_follower_state=black_turn;
     traverse_state=pause;
     return;
  }
 forward_timed(seconds_2);
}

//intercept turning function
void intercept_turn(void){
  if (flag) {
    stop_all_motors();
  }  
  else if (follow_flag){
    turn_both(speed_val);
    if (right_detector_avg>=black_border_value && left_detector_avg<black_border_value){ //finding black line when going forward
      stop_all_motors();
      follow_flag=RESET_STATE;
      line_follower_state=black_turn;
      traverse_state=pause;
      Movement_Timer=RESET_STATE;
    }
  }
}  

//circle following
void follow_black_line(void){
  if (line_follower_timer_flag) {
    stop_all_motors();
    move_forward(speed_val);
  }  
  else {
    if (right_detector_avg>=(black_border_value-avg_value) && left_detector_avg>=(black_border_value-avg_value)){
      if (turn_left_flag) {
        turn_right(speed_val);
      } 
      else {
        turn_left(speed_val);
        turn_left_flag=RESET_STATE;
      }  
    }  
    else if (right_detector_avg>=(black_border_value-avg_value) && left_detector_avg<(black_border_value+avg_value)){
      move_forward(speed_val);
      turn_left_flag=RESET_STATE;
    } 
    else if (left_detector_avg<black_border_value && right_detector_avg<black_border_value){
      if (turn_left_flag) return;
      turn_right(speed_val);
    }
    else if (left_detector_avg>=black_border_value && right_detector_avg<black_border_value) {
      turn_left(speed_val);
      turn_left_flag=ALWAYS;
    }
    follow_flag=RESET_STATE;
  }  
}

//turning towards center after finishing 2 circle rounds
void turn_towards_center(void){
  if (timer_flag) {
     traverse_state=pause;
     line_follower_state=turn_to_center;
     return;
  }
  movement(right, seconds2_str);
}  

//moving towards center
void move_towards_center(void){
  if (timer_flag) {
     traverse_state=pause;
     line_follower_state=move_to_center;
     return;
  }
  movement(forward, seconds2_str);
}  

