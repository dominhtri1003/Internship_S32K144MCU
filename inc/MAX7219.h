#pragma once
#ifndef MAX7219_H
#define MAX7219_H

#include <stdint.h>

#define NO_OP 0x00
#define DIGIT0 0x01
#define DIGIT1 0x02
#define DIGIT2 0x03
#define DIGIT3 0x04
#define DIGIT4 0x05
#define DIGIT5 0x06
#define DIGIT6 0x07
#define DIGIT7 0x08
#define DECODE_MODE 0x09
#define INTENSITY 0x0A
#define SCAN_LIMIT 0x0B
#define SHUTDOWN 0x0C
#define DISPLAY_TEST 0x0F

#define DASH_LED_CODE 0x0A
#define DOT_LED_CODE 0x80

void MAX7219_Innit(void);
void MAX7219_Display(uint8_t Address, uint8_t Data);
void MAX7219_TimeDisplay(unsigned int p_hour, unsigned int p_minute, unsigned int p_second);
void MAX7219_DateDisplay(unsigned int p_day, unsigned int p_month, unsigned int p_year);
void MAX7219_Intensity(int p_level);
void MAX7219_TurnOffAllLED(void);


#endif