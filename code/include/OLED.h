#ifndef OLED_H
#define OLED_H

#include "config.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 OLED_display;

void init_OLED();
void OLED_off();

#endif