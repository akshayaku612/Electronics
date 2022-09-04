//------------------------------------------------------------------------------
//
//  Description: This file contain Macros
//
//
//  Akshay Kamalapuram Sridhar
//  Sept 2021
//  Built with IAR Embedded Workbench Version: V7.21.1
//------------------------------------------------------------------------------


// MACROS========================================================================

// main.c values
#define RESET_STATE          (0)
#define ALWAYS               (1)
#define TRUE          (1)
#define FALSE               (0)
#define ORIGINAL             (0x00)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // 6 GREEN LED
#define SW2                  (0x08) // 2.3 SW2
#define SW1                  (0x02) // 4.1 SW1
#define NUM_DISPLAY_lINES    4
#define NUM_lINES_LAYER      11
#define DISPLAY_LINE_LAYER_10 10
#define DISPLAY_LINE_LAYER_0 0
#define DISPLAY_lINE_0       0
#define DISPLAY_lINE_1       1
#define DISPLAY_lINE_2       2
#define DISPLAY_lINE_3       3
#define RUN_NUMBERS          5
#define ADC_CHAR_SIZE        4

// clocks.c value
#define MCLK_FREQ_MHZ        8  // MCLK = 8MHz
#define CLEAR_REGISTER       (0X0000)
#define ALWAYS_ON (0xffff)
#define DCO_FREQ_TRIM (3)
#define DCOFTRIM (0x0070)
#define DCO_TAP (0x100)
#define CURRENT_DCO_TAP (0x01ff)
#define DELAY_CYCLES (3000)
#define OLD_DCO_TAP (256)
#define BIT_SHIFT_FOUR (4)
#define DCODIV (243)

// ports.c default values
#define DEFAULT_LOW          (0x00)
#define DEFAULT_OUT_DIR      (0x00)
#define LOW      (0xFF)

// Port 1 Pins
#define RED_LED              (0x01) // 0 RED LED 0
#define A1_SEEED             (0x02) // 1 A1_SEEED
#define V_DETECT_L           (0x04) // 2 V_DETECT_L
#define V_DETECT_R           (0x08) // 3 V_DETECT_R
#define V_BAT             (0x10) // 4 A4_SEEED
#define V_THUMB              (0x20) // 5 V_THUMB
#define UCA0RXD              (0x40) // 6 Back Channel UCA0RXD
#define UCA0TXD              (0x80) // 7 Back Channel UCA0TXD

// Port 2 Pins
#define DAC_ENB              (0x01) // 0 DAC Power Circuit Enable
#define IR_LED               (0x02) // 1 IR LED on/off signal
#define P2_2                 (0x04) // 2
#define SW2                  (0x08) // 3 SW2
#define IOT_PROG_SEL         (0x10) // 4 IOT_PROG_SEL
#define P2_5                 (0x20) // 5
#define LFXOUT               (0x40) // 6 XOUTR
#define LFXIN                (0x80) // 7 XINR

// Port 3 Pins
#define TEST_PROBE           (0x01) // 0 TEST PROBE
#define OPT_INT              (0x02) // 1 OPT_INT
#define OA2N                 (0x04) // 2 Photodiode Circuit
#define OA2P                 (0x08) // 3 Photodiode Circuit
#define SMCLK_OUT            (0x10) // 4 SMCLK
#define DAC_CNTL             (0x20) // 5 DAC signal from Processor
#define IOT_LINK             (0x40) // 6 IOT_LINK
#define IOT_RESET            (0x80) // 7 IOT_RESET

// Port 4 Pins
#define RESET_LCD            (0x01) // 0 LCD Reset
#define SW1                  (0x02) // 1 SW1
#define UCA1RXD              (0x04) // 2 Back Channel UCA1RXD
#define UCA1TXD              (0x08) // 3 Back Channel UCA1TXD
#define UCB1_CS_LCD          (0x10) // 4 Chip Select
#define UCB1CLK              (0x20) // 5 SPI mode - clock output—UCB1CLK
#define UCB1SIMO             (0x40) // 6 UCB1SIMO
#define UCB1SOMI             (0x80) // 7 UCB1SOMI
#define P4PUD                (P4OUT)

// Port 5 Pins
#define CHECK_BAT            (0x01) // 0 Battery Check
#define V_BAT1                (0x02) // 1 Battery Voltage
#define V_DAC                (0x04) // 2 DAC Voltage
#define V_3_3                (0x08) // 3 Voltage 3.3
#define IOT_PROG_MODE        (0x10) // 4 IOT Mode

// Port 6 Pins
#define R_FORWARD            (0x01) // 0 Right side Forward
#define L_FORWARD            (0x02) // 1 Left side Forward
#define R_REVERSE            (0x04) // 2 Right side Reverse
#define L_REVERSE            (0x08) // 3 Left side Reverse
#define LCD_BACKLITE         (0x10) // 4 LCD Display
#define P6_5                 (0x20) // 5 
#define GRN_LED              (0x40) // 6 Green LED

//timers_interrupts.c
#define TB0CCR0_INTERVAL     (25000) // 8,000,000 / 2 / 8 / (1 / 50msec)
#define TB0CCR1_INTERVAL     (6000) // 8,000,000 / 2 / 8 / (1 / 120msec)
#define TB0CCR2_INTERVAL     (10000) // 8,000,000 / 2 / 8 / (1 / 20msec)
#define TB1CCR0_INTERVAL     (50000) // 8,000,000 / 2 / 8 / (1 / 100msec)
#define TB1CCR1_INTERVAL     (2500) // 8,000,000 / 2 / 8 / (1 / 5 msec)
#define TB1CCR2_INTERVAL     (20) 
#define CCR1 (2)
#define CCR2 (4)
#define OVERFLOW (14)
#define DEBOUNCE_LIMIT (10)

//movements ->wheels.c, timers.c, main.c
#define WHEEL_OFF (RESET_STATE)
#define PWM_PERIOD (50000)
#define LEFT_FORWARD_SPEED (TB3CCR1)
#define RIGHT_FORWARD_SPEED (TB3CCR2)
#define LEFT_REVERSE_SPEED (TB3CCR3)
#define RIGHT_REVERSE_SPEED (TB3CCR4)
#define incrementer (1)
#define right ('R')
#define forward ('F')
#define seconds2_str ('2')
#define second_count (10)
#define limit_time (100)
#define iot_reset_time (4)

//adc_interrupts.c
#define channel_0 (0x00)
#define channel_1 (0x01)
#define channel_2 (0x02)
#define char_length (4)
#define char_length_0 (0)
#define char_length_1 (1)
#define char_length_2 (2)
#define char_length_3 (3)
#define hex_ascii_0 (0x30)
#define ascii_0 ('0')
#define single_increment (1)
#define DISPLAY_lINE_CHAR4 (4)
#define DISPLAY_lINE_CHAR5 (5)
#define DISPLAY_lINE_CHAR6 (6)
#define DISPLAY_lINE_CHAR7 (7)
#define three_digit_limit (999)
#define two_digit_limit (99)
#define one_digit_limit (9)
#define thousandth_digit (1000)
#define hundredth_limit (100)
#define tenth_limit (10)
#define avg_value (9)
#define num_of_chars (10)
#define DAC_limit (750)
#define DAC_value (4000)
#define current_time_arr_size (4)

#define char_0 (0)
#define char_1 (1)
#define char_2 (2)
#define char_3 (3)
#define char_4 (4)
#define char_5 (5)
#define char_6 (6)
#define char_7 (7)
#define char_8 (8)
#define char_9 (9)
#define char_10 (10)
#define char_11 (11)
#define char_12 (12)

//serial communications
#define BEGINNING (0)
#define SMALL_RING_SIZE (10)
#define no_interrupt (0)
#define rx (2)
#define tx (4)
#define mctl_value (0x5551)
#define brw_value (4)
#define serial_limit (0x08)

//Line Following
#define initial_state (0)
#define black_intercept (1)
#define black_turn (2)
#define line_follow (3)
#define turn_to_center (4)
#define move_to_center (5)
#define end (6)
#define pause (7)
#define bit_shift_2 (2)
#define seconds_2 (2)
#define speed_val (20000)

//iot commands
#define campus_profile (0)
#define reset_profile (1)
#define tcp_server (2)
#define tcp_client (3)
#define custom_command (4)
#define movements (5)
#define display_number (6)
#define black_line_navigation (7)
#define end (8)
#define response (9)
#define campus_profile_response_size (50)
#define reset_response_size (150)
#define tcp_server_response_size (150)
#define tcp_client_connect_response_size (50)
#define custom_command_response_size (35)
#define ip_address_size (13)
#define current_command_size (10)
#define process_buffer_size (25)

//Characters
#define D ('D')
#define B ('B')
#define R ('R')
#define C ('C')
#define O ('O')
#define N ('N')
#define S ('S')
#define K ('K')
#define U ('U')
#define L ('L')
#define num_1 ('1')
#define num_2 ('2')
#define num_3 ('3')
#define num_4 ('4')
#define num_5 ('5')
#define num_6 ('6')
#define num_7 ('7')
#define num_8 ('8')
#define num_0 ('0')
#define CR ('\r')