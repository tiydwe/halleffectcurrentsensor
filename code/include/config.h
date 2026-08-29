#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// PINS
#define OUT_3V3 A0
#define RAW_OUT_3V3 A1
#define REF_SIG_SCALED A2
#define CTRL_PWR D3
#define CTRL_OLED D10
//#define SDA 5
//#define SCL 6
#define BTN D9

// OLED
#define OLED_SCREEN_WIDTH 128
#define OLED_SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C
#define OLED_RESET_PIN -1

// SENSOR
#define CONVERT_3V3_5V (((long double)5.0) / 3.3)
#define READ_CNT 10

#endif