#include "OLED.h"

#include <Arduino.h>
#include <Wire.h>

#include "utility.h"

Adafruit_SSD1306 OLED_display(OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT, &Wire,
                              OLED_RESET_PIN);

void init_OLED() {
  pinMode(CTRL_OLED, OUTPUT);
  digitalWrite(CTRL_OLED, HIGH);
  delay(100);
  if (!OLED_display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    hang();
  }
  OLED_display.clearDisplay();
  OLED_display.setCursor(0,0);
}

void OLED_off() {
  digitalWrite(CTRL_OLED, LOW);
}
