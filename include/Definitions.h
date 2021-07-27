#include "Arduino.h"

// lcd screen
#define RS 4
#define EN 5
#define D4 6
#define D5 7
#define D6 8
#define D7 12

// rgb light
#define RED_LED 9
#define GREEN_LED 10
#define BLUE_LED 11

// buttons
#define LEFT_BUTTON A3
#define RIGHT_BUTTON A2
#define SPRAY_BUTTON 3 // External interrupts only allowed on D2 & D3
#define FLUSH_BUTTON 0

// motion sensor
#define PIR_SENSOR 2

// temperature sensor
#define TEMP_SENSOR A5
#define REQUEST_TEMP 2000
#define TEMP_SENSOR_DELAY 94 // (750 / (1 << (12 - resolution))), res = 9
#define REQUEST_TEMP 2000

// light sensor
#define LDR_SENSOR A4
#define LIGHT_THRESHOLD 300

// ultrasound sensor
#define ULTRASOUND_TRIGGER A1
#define ULTRASOUND_ECHO A0
#define MAX_DISTANCE 190
#define DISTANCE_PING_SPEED 40

// menu settings
#define MENU_TIMEOUT 10000

// EEPROM
#define STORED_DATA             4
#define SPRAY_ADDR              0   // integer
#define DEFAULT_SPRAY_VAL       2400
#define TRIGGER_DELAY_ADDR      2   // unsigned long
#define DEFAULT_TRIGGER_DELAY   30000
#define SPRAY_1_ADDR            6   // byte
#define DEFUALT_SPRAY_1         1
#define SPRAY_2_ADDR            7   // byte
#define DEFAULT_SPRAY_2         2

// airwick
#define FRESHNER_INIT  20000
#define FRESHNER_DELAY 3000
#define MOSFET 13

// time-outs 
#define INITIALIZE_TIME 20000 
#define TIMEOUT_DOOR 20000
#define DISTANCE_DOOR 120
#define ONE_TIME 120000
#define TWO_TIME 300000
#define CLEANING_TIME 900000

