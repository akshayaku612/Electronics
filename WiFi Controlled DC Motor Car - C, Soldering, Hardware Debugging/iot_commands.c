// ------------------------------------------------------------------------------
//
//  Description: This file contains the code for all the commands that need to be sent to iot for initialization and also contains the code to tell the iot how it needs to respond to commands
//
//
//  Akshay Kamalapuram Sridhar
//  Nov 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
// ------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"
#include <string.h>

//global variables
extern unsigned int Time_Sequence;
extern unsigned int timer_flag;
extern unsigned int Movement_Timer;
extern char process_buffer1[process_buffer_size];
extern char process_buffer0[process_buffer_size]; 
extern unsigned int iot_ready;
extern unsigned int receive_flag;
extern unsigned int response_buffer_current_buffer_size;
extern unsigned int circle_timer_flag;
extern volatile unsigned char display_changed;
extern char display_line[NUM_DISPLAY_lINES][NUM_lINES_LAYER];
extern unsigned int Circle_Timer;

unsigned int command=initial_state;
unsigned int high_flag=initial_state;
unsigned int i=initial_state;
unsigned previous_state=initial_state;
unsigned int iot_initialized=initial_state;
unsigned int exit_flag=initial_state;
unsigned int custom_command_received=initial_state;
unsigned int command_received_internal=initial_state;

//IOT Initialization Commands
char campus_profile_command[]="\rAT&W0\r";
char reset_command[]="\rAT+RESET=1\r";
char tcp_server_command[]="\rAT+NSTCP=1210,1\r";

//IOT Response variables
char campus_profile_response[campus_profile_response_size];
char reset_response[reset_response_size];
char tcp_server_response[tcp_server_response_size];
char tcp_client_connect_response[tcp_client_connect_response_size];
char custom_command_response[custom_command_response_size];
int command_check_flag=initial_state;
char* response_buffer[]={campus_profile_response, reset_response, tcp_server_response, tcp_client_connect_response, custom_command_response};
unsigned int iot_buffer_command_type_index=initial_state;
unsigned int iot_buffer_response_index=initial_state;
char ip_address[ip_address_size];
char direction,duration;
char current_command[current_command_size];

void response_handler(void);
void Iot_cycle(void);

//response handler function that handles all possible responses from iot
void response_handler(void){
  switch (iot_buffer_command_type_index){
    case campus_profile: //campus profile response handler
      for (int j=initial_state; j<tcp_client_connect_response_size;j++){
        if (response_buffer[campus_profile][j]==O && response_buffer[campus_profile][j+char_1]==K) {
          command_check_flag=ALWAYS;
          break;
        }
      }  
      break;
    case reset_profile:  //reset profile command response handler
      for (int j=initial_state; j<tcp_server_response_size;j++){
        if (response_buffer[reset_profile][j]==S && response_buffer[reset_profile][j+char_1]==U && response_buffer[reset_profile][j+char_2]==C) {
          command_check_flag=ALWAYS;
          int index=j-campus_profile_response_size;
          ip_address[char_0]=response_buffer[reset_profile][index++];
          ip_address[char_1]=response_buffer[reset_profile][index++];
          ip_address[char_2]=response_buffer[reset_profile][index++];
          ip_address[char_3]=response_buffer[reset_profile][index++];
          ip_address[char_4]=response_buffer[reset_profile][index++];
          ip_address[char_5]=response_buffer[reset_profile][index++];
          ip_address[char_6]=response_buffer[reset_profile][index++];
          ip_address[char_7]=response_buffer[reset_profile][index++];
          ip_address[char_8]=response_buffer[reset_profile][index++];
          ip_address[char_9]=response_buffer[reset_profile][index++];
          ip_address[char_10]=response_buffer[reset_profile][index++];
          ip_address[char_11]=response_buffer[reset_profile][index++];
          ip_address[char_12]=response_buffer[reset_profile][index];
          break;
        }
      }
      break;
    case tcp_server: //tcp_server connection response handler
      for (int j=initial_state; j<tcp_server_response_size;j++){
        if (response_buffer[tcp_server][j]==C && response_buffer[tcp_server][j+char_1]==O && response_buffer[tcp_server][j+char_2]==N) {
          command_check_flag=ALWAYS;
          iot_initialized=ALWAYS;
          break;
        }
      }  
      break;
    case tcp_client: //tcp client connection response handler
      for (int j=RESET_STATE; j<campus_profile_response_size;j++){
        if (response_buffer[tcp_client][j]==C && response_buffer[tcp_client][j+1]==O && response_buffer[tcp_client][j+2]==N) {
          command_check_flag=ALWAYS;
          break;
        }
      } 
      break;
    case custom_command: //custom commands handler
      for (int j=RESET_STATE; j<custom_command_response_size;j++){
        if (response_buffer[custom_command][j]==R && response_buffer[custom_command][j+char_1]==num_1 && response_buffer[custom_command][j+char_2]==num_2 && response_buffer[custom_command][j+char_3]==num_1 && response_buffer[custom_command][j+char_4]==num_0 && response_buffer[custom_command][j+char_9]==CR) { //verifies command is a valid authorized command by verifying the pin
          command_check_flag=ALWAYS;
          int index=j;
          if (!circle_timer_flag){
            circle_timer_flag=ALWAYS;
            Circle_Timer=RESET_STATE;
            strcpy(display_line[DISPLAY_lINE_0], "          ");
            strcpy(display_line[DISPLAY_lINE_3], "          ");
          }
          current_command[char_0]=response_buffer[custom_command][index++];
          current_command[char_1]=response_buffer[custom_command][index++];
          current_command[char_2]=response_buffer[custom_command][index++];
          current_command[char_3]=response_buffer[custom_command][index++];
          current_command[char_4]=response_buffer[custom_command][index++];
          current_command[char_5]=response_buffer[custom_command][index++];
          current_command[char_6]=response_buffer[custom_command][index++];
          current_command[char_7]=response_buffer[custom_command][index++];
          current_command[char_8]=response_buffer[custom_command][index++];
          current_command[char_9]=response_buffer[custom_command][index++];

           if (current_command[char_5]==D) { //display
            command=display_number;
            if (current_command[char_8]==num_1) strcpy(display_line[DISPLAY_lINE_0], "1         ");
            else if (current_command[char_8]==num_2) strcpy(display_line[DISPLAY_lINE_0], "2         ");
            else if (current_command[char_8]==num_3) strcpy(display_line[DISPLAY_lINE_0], "3         ");
            else if (current_command[char_8]==num_4) strcpy(display_line[DISPLAY_lINE_0], "4         ");
            else if (current_command[char_8]==num_5) strcpy(display_line[DISPLAY_lINE_0], "5         ");
            else if (current_command[char_8]==num_6) strcpy(display_line[DISPLAY_lINE_0], "6         ");
            else if (current_command[char_8]==num_7) strcpy(display_line[DISPLAY_lINE_0], "7         ");
            else if (current_command[char_8]==num_8) strcpy(display_line[DISPLAY_lINE_0], "8         ");
            else if (current_command[char_8]==num_0) strcpy(display_line[DISPLAY_lINE_0], "0         ");
            
          }
          else if (current_command[char_5]==B) command=black_line_navigation;
          else{
            command=movements;
            direction=current_command[char_6];
            duration=current_command[char_8];
          }
          command_received_internal=ALWAYS;
          custom_command_received=ALWAYS;
          timer_flag=initial_state;
          break;  
        }
      }
      break;
    default: 
      iot_buffer_command_type_index=custom_command;
      break;  
  }  
}

//IOT commands cycle
void Iot_cycle(void){
  switch(command){
    case campus_profile: //campus profile command
      if (!iot_ready) break;
      process_buffer1[i]=campus_profile_command[i];
      i++;
      UCA0IE |= UCTXIE;
      if (i>current_command_size) {
        i=initial_state;
        command=response;
        previous_state=campus_profile;
        iot_buffer_response_index=initial_state;
        Movement_Timer=initial_state;
      }
      break;
    case reset_profile: //reset profile command
      process_buffer1[i]=reset_command[i];
      i++;
      UCA0IE |= UCTXIE;
      if (i>current_command_size) {
        i=initial_state;
        command=response;
        previous_state=reset_profile;
        iot_buffer_response_index=initial_state;
        Movement_Timer=initial_state;
      }
      break;
    case tcp_server:  //starting tcp server command
      process_buffer1[i]=tcp_server_command[i];
      i++;
      UCA0IE |= UCTXIE;
      if (i>current_command_size) {
        i=initial_state;
        command=response;
        previous_state=tcp_server;
        iot_buffer_response_index=initial_state;
        Movement_Timer=initial_state;
      }
      break;
    case tcp_client:
      if (!receive_flag) {
        iot_buffer_response_index=initial_state;
        break;  
      } 
      command=response;
      previous_state=tcp_client;
      iot_buffer_response_index=initial_state;
      Movement_Timer=initial_state;
      break;  
    case response: // response handling state
      if (command_check_flag!=TRUE) response_handler();
      
      if (previous_state==custom_command && command_check_flag){
        command_check_flag=initial_state;
        timer_flag=initial_state;
        iot_buffer_response_index=initial_state;
        receive_flag=initial_state;
        break;
      }
      else if (!timer_flag && !high_flag) wait(seconds_2);
      else if (timer_flag && command_check_flag==RESET_STATE) {
        command=previous_state;
        timer_flag=initial_state;
      }  
      else if (timer_flag && command_check_flag==ALWAYS) {
        command=previous_state+incrementer;
        iot_buffer_command_type_index=previous_state+incrementer;
        command_check_flag=BEGINNING;
        timer_flag=BEGINNING;
        receive_flag=BEGINNING;
      }  
      break;  
    case custom_command: //Custom commands received from tcp client
      high_flag=ALWAYS;
      if (!receive_flag) {
        iot_buffer_response_index=BEGINNING;
        break;  
      }
      command=response;
      previous_state=custom_command;
      iot_buffer_response_index=BEGINNING;
      Movement_Timer=BEGINNING;
      break;
    case movements: //State for handling all timed movements for iot track
      if (timer_flag) {
        stop_all_motors();
        command=custom_command;
        command_received_internal=BEGINNING;
        timer_flag=BEGINNING;
        for (int i=BEGINNING;i<custom_command_response_size;i++) {
          custom_command_response[i]=NULL;
        }
        if (exit_flag) { //exit circle
          command=end;
        }
        break;
      }
      movement(direction, duration);
      break;
    case display_number: //displaying number on square
      command=custom_command;
      break;
    case black_line_navigation:    //Black line course handling state
      line_traversal();
      command=end;
      break;
    case end: 
      stop_all_motors();
      break;
    default: break;   
  }  
}  