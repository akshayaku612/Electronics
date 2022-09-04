// ------------------------------------------------------------------------------
//
//  Description: This file contains the code for wheel movements
// There are forward, turn left, turn right and stop movements
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
// ------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

extern unsigned int Movement_Timer;
extern unsigned int timer_flag;

void movement(char direction, char duration);
void forward_timed(int duration);
void backward_timed(int duration);
void turn_left_timed(int duration);
void turn_right_timed(int duration);
void stop_all_motors(void);
void turn_both(unsigned int speed);

//without time
void move_forward(unsigned int speed);
void move_backward(unsigned int speed);
void turn_left(unsigned int speed);
void turn_right(unsigned int speed);

void movement(char direction, char duration){
  int t=duration-ascii_0;
  if (t<RESET_STATE || t>tenth_limit) t=(incrementer+incrementer);
  if (direction==forward) forward_timed(t);
  else if (direction==B) backward_timed(t);
  else if (direction==L) turn_left_timed(t);
  else if (direction==right) turn_right_timed(t);
  else if (direction==S) stop_all_motors();
}

void forward_timed(int duration){
  move_forward(speed_val);
  if (Movement_Timer>=duration) {
    timer_flag=ALWAYS;
  }  
}

void backward_timed(int duration){
  move_backward(speed_val);
  if (Movement_Timer>=duration) {
    timer_flag=ALWAYS;
  }  
}

void turn_left_timed(int duration){
  turn_left(speed_val);
  if (Movement_Timer>=duration) {
    timer_flag=ALWAYS;
  }  
}

void turn_right_timed(int duration){
  turn_right(speed_val);
  if (Movement_Timer>=duration) {
    timer_flag=ALWAYS;
  }  
}  

void turn_both(unsigned int speed){
  LEFT_FORWARD_SPEED = speed;  
  RIGHT_REVERSE_SPEED =speed;
}

void stop_all_motors(void){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}  

void move_forward(unsigned int speed){
  RIGHT_FORWARD_SPEED = speed+speed_val; // P6.0 Right Forward PWM ON amount
  LEFT_FORWARD_SPEED = speed; // P6.1 Left Forward PWM ON amount
}

void move_backward(unsigned int speed){
  RIGHT_REVERSE_SPEED = speed; // P6.0 Right Forward PWM ON amount
  LEFT_REVERSE_SPEED = speed; // P6.1 Left Forward PWM ON amount
}

void turn_left(unsigned int speed){
  RIGHT_FORWARD_SPEED = speed;
  LEFT_FORWARD_SPEED = speed; 
}

void turn_right(unsigned int speed){
  LEFT_FORWARD_SPEED = speed;  
  RIGHT_FORWARD_SPEED =speed;
}

