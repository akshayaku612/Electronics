// ------------------------------------------------------------------------------
//
//  Description: This file contains all the display code used throughout the project
//
//  Akshay Kamalapuram Sridhar
//  Nov 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
// ------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

extern unsigned int ADC_Left_Detect_flag;
extern unsigned int ADC_Right_Detect_flag;
extern volatile unsigned char display_changed;
extern char display_line[NUM_DISPLAY_lINES][NUM_lINES_LAYER];
extern volatile unsigned char update_display;
extern unsigned int left_detector_avg;
extern unsigned int right_detector_avg;
extern unsigned int ADC_ThumbWheel_Detect;
extern unsigned int iot_initialized;
extern char ip_address[13];
extern char current_command[10];
extern unsigned int custom_command_received;
extern unsigned int display_calibration_flag;
extern unsigned int prepare_display_flag;
extern unsigned int assign_black_value;
extern unsigned int sw1_pressed;
extern unsigned int circle_timer_flag;
extern unsigned int Circle_Timer;

char adc_char[ADC_CHAR_SIZE];

char current_time_arr[current_time_arr_size];
char dot[char_length_1]=".";

void displayADC(void);
void HEXtoBCD(int hex_value,char* arr);
void displayInitialIOTDetails(void);
void displayIOTDetails(void);
void display_all(void);

//Main Display function
void display_all(void){
  if (ADC_ThumbWheel_Detect>=char_length_2) {
      displayADC();
    }
  else if (ADC_ThumbWheel_Detect<=char_length_1) {
    if (sw1_pressed) displayIOTDetails();
    else displayInitialIOTDetails();
  }
  Display_Process();
}

void Display_Process(void){
  if(update_display){
    update_display = RESET_STATE;
    if(display_changed){
      display_changed = RESET_STATE;
      Display_Update(RESET_STATE,RESET_STATE,RESET_STATE,RESET_STATE);
    }
  }
}

//ADC values will be displayed after turning the thumbwheel
void displayADC(void){
  if (ADC_Left_Detect_flag){
    ADC_Left_Detect_flag=initial_state;
    HEXtoBCD(left_detector_avg,adc_char); // Convert result to String
    strcpy(display_line[DISPLAY_lINE_0], "LD:       ");
    display_line[DISPLAY_lINE_0][DISPLAY_lINE_CHAR4]=adc_char[char_length_0];
    display_line[DISPLAY_lINE_0][DISPLAY_lINE_CHAR5]=adc_char[char_length_1];
    display_line[DISPLAY_lINE_0][DISPLAY_lINE_CHAR6]=adc_char[char_length_2];
    display_line[DISPLAY_lINE_0][DISPLAY_lINE_CHAR7]=adc_char[char_length_3];       
  }  
  
  if (ADC_Right_Detect_flag){
    ADC_Right_Detect_flag=initial_state;
    HEXtoBCD(right_detector_avg,adc_char); // Convert result to String
    strcpy(display_line[DISPLAY_lINE_1], "RD:       ");
    display_line[DISPLAY_lINE_1][DISPLAY_lINE_CHAR4]=adc_char[char_length_0];
    display_line[DISPLAY_lINE_1][DISPLAY_lINE_CHAR5]=adc_char[char_length_1];
    display_line[DISPLAY_lINE_1][DISPLAY_lINE_CHAR6]=adc_char[char_length_2];
    display_line[DISPLAY_lINE_1][DISPLAY_lINE_CHAR7]=adc_char[char_length_3];
  }
  
  if (display_calibration_flag && assign_black_value) strcpy(display_line[DISPLAY_lINE_3], "BW Set    ");
  else if (display_calibration_flag) strcpy(display_line[DISPLAY_lINE_3], "Black Set ");
  else {
    strcpy(display_line[DISPLAY_lINE_3], "          ");
  }
  strcpy(display_line[DISPLAY_lINE_2], "          ");  
  display_changed = ALWAYS;
}

//Initial display upon turning on the car
void displayInitialIOTDetails(void){
  if (!iot_initialized) return;
  strcpy(display_line[DISPLAY_lINE_0], "   ncsu   ");
  strcpy(display_line[DISPLAY_lINE_2], "          ");
  strcpy(display_line[DISPLAY_lINE_3], "          ");
  
  if (custom_command_received){
    display_line[DISPLAY_lINE_1][char_0]=current_command[char_0];
    display_line[DISPLAY_lINE_1][char_1]=current_command[char_1];
    display_line[DISPLAY_lINE_1][char_2]=current_command[char_2];
    display_line[DISPLAY_lINE_1][char_3]=current_command[char_3];
    display_line[DISPLAY_lINE_1][char_4]=current_command[char_4];
    display_line[DISPLAY_lINE_1][char_5]=current_command[char_5];
    display_line[DISPLAY_lINE_1][char_6]=current_command[char_6];
    display_line[DISPLAY_lINE_1][char_7]=current_command[char_7];
    display_line[DISPLAY_lINE_1][char_8]=current_command[char_8];
    display_line[DISPLAY_lINE_1][char_9]=current_command[char_9];
    lcd_BIG_mid();
    display_changed = ALWAYS;
    return;
  }
  
  strcpy(display_line[DISPLAY_lINE_1], "IP Address");
  display_line[DISPLAY_lINE_2][char_2]=ip_address[char_0];
  display_line[DISPLAY_lINE_2][char_3]=ip_address[char_1];
  display_line[DISPLAY_lINE_2][char_4]=ip_address[char_2];
  display_line[DISPLAY_lINE_2][char_5]=ip_address[char_3];
  display_line[DISPLAY_lINE_2][char_6]=ip_address[char_4];
  display_line[DISPLAY_lINE_2][char_7]=ip_address[char_5];
  display_line[DISPLAY_lINE_2][char_8]=ip_address[char_6];
  display_line[DISPLAY_lINE_3][char_2]=ip_address[char_7];
  display_line[DISPLAY_lINE_3][char_3]=ip_address[char_8];
  display_line[DISPLAY_lINE_3][char_4]=ip_address[char_9];
  display_line[DISPLAY_lINE_3][char_5]=ip_address[10];
  display_line[DISPLAY_lINE_3][char_6]=ip_address[11];
  display_line[DISPLAY_lINE_3][char_7]=ip_address[12];
  display_changed = ALWAYS;
}

//Details of IOT that get displayed after pressing SW1
void displayIOTDetails(void){
  strcpy(display_line[DISPLAY_lINE_1], "          ");
  strcpy(display_line[DISPLAY_lINE_2], "          ");
  strcpy(display_line[DISPLAY_lINE_3], "          ");
  if (!circle_timer_flag){
    strcpy(display_line[DISPLAY_lINE_0], "Waiting   ");
    strcpy(display_line[DISPLAY_lINE_1], "          ");
    strcpy(display_line[DISPLAY_lINE_2], "          ");
    strcpy(display_line[DISPLAY_lINE_3], "For Input ");
  }
  
  if (circle_timer_flag){
    HEXtoBCD(Circle_Timer,current_time_arr);
    display_line[DISPLAY_lINE_2][char_6]=current_time_arr[char_length_0];
    display_line[DISPLAY_lINE_2][char_7]=current_time_arr[char_length_1];
    display_line[DISPLAY_lINE_2][char_8]=current_time_arr[char_length_2];
    display_line[DISPLAY_lINE_2][char_9]=current_time_arr[char_length_3];
    //display_line[DISPLAY_lINE_2][4]=current_time_arr[char_length_3];
  }
  
  if (!iot_initialized) return;
  display_line[DISPLAY_lINE_1][char_0]=ip_address[char_0];
  display_line[DISPLAY_lINE_1][char_1]=ip_address[char_1];
  display_line[DISPLAY_lINE_1][char_2]=ip_address[char_2];
  display_line[DISPLAY_lINE_1][char_3]=ip_address[char_3];
  display_line[DISPLAY_lINE_1][char_4]=ip_address[char_4];
  display_line[DISPLAY_lINE_1][char_5]=ip_address[char_5];
  display_line[DISPLAY_lINE_1][char_6]=ip_address[char_6];
  display_line[DISPLAY_lINE_1][char_7]=ip_address[char_7];
  display_line[DISPLAY_lINE_1][char_8]=ip_address[char_8];
  display_line[DISPLAY_lINE_1][char_9]=ip_address[char_9];
  display_line[DISPLAY_lINE_2][char_0]=ip_address[char_10];
  display_line[DISPLAY_lINE_2][char_1]=ip_address[char_11];
  display_line[DISPLAY_lINE_2][char_2]=ip_address[char_12];
  
  if (custom_command_received){
    display_line[DISPLAY_lINE_3][char_0]=current_command[char_0];
    display_line[DISPLAY_lINE_3][char_1]=current_command[char_1];
    display_line[DISPLAY_lINE_3][char_2]=current_command[char_2];
    display_line[DISPLAY_lINE_3][char_3]=current_command[char_3];
    display_line[DISPLAY_lINE_3][char_4]=current_command[char_4];
    display_line[DISPLAY_lINE_3][char_5]=current_command[char_5];
    display_line[DISPLAY_lINE_3][char_6]=current_command[char_6];
    display_line[DISPLAY_lINE_3][char_7]=current_command[char_7];
    display_line[DISPLAY_lINE_3][char_8]=current_command[char_8];
    display_line[DISPLAY_lINE_3][char_9]=current_command[char_9];
  }
  
  display_changed = ALWAYS;
}

//Converting ADC Hex values to BCD
void HEXtoBCD(int hex_value,char* arr){
  int value=RESET_STATE;
  arr[char_length_0] = ascii_0;
  while (hex_value > three_digit_limit){
    hex_value = hex_value - thousandth_digit;
    value = value + single_increment;
  }
  arr[char_length_0] = hex_ascii_0 + value;
  value = RESET_STATE;
  while (hex_value > two_digit_limit){
    hex_value = hex_value - hundredth_limit;
    value = value + single_increment;
  }
  arr[char_length_1] = hex_ascii_0 + value;
  value = RESET_STATE;
  while (hex_value > one_digit_limit){
    hex_value = hex_value - tenth_limit;
    value = value + single_increment;   
  }
  arr[char_length_2] = hex_ascii_0 + value;
  arr[char_length_3] = hex_ascii_0 + hex_value;
}