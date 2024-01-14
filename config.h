#ifndef config_h
#define config_h
#include "stepam.h" // For Arduino IDE compatibility.

#define PI 3.141592

// Define CPU pin map and default settings.
#define CPU_MAP_ATMEGA328P // Arduino Uno CPU
#define MAX_INT_DIGITS 8

// Serial baud rate
// #define BAUD_RATE 230400
#define BAUD_RATE 115200
#define LINE_BUFFER_SIZE 256

// Define realtime command special characters. These characters are 'picked-off' directly from the
// serial read data stream and are not passed to the line execution parser.
#define CMD_RESET 'R' // ctrl-x.
#define CMD_STATUS_REPORT '?'
#define CMD_CYCLE_START '~'
#define CMD_FEED_HOLD '!'

//Define axis settings
#define NB_STEP 			800
#define MAX_POS 			1000
#define MIN_POS				0
#define MAX_SPEED			500
#define FILTER_SIZE			250

#define MM_PER_STEP 		0.02

#endif