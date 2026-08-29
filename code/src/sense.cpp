#include "sense.h"

#include <Arduino.h>

#include "config.h"

void init_sensors() {
  // turn sensors on
  pinMode(CTRL_PWR, OUTPUT);
  pinMode(CTRL_OLED, OUTPUT);
  digitalWrite(CTRL_PWR, HIGH);
  digitalWrite(CTRL_OLED, HIGH);
}

void sensors_off() {
  // save power
  digitalWrite(CTRL_PWR, LOW);
  digitalWrite(CTRL_OLED, HIGH);
}

long double read_pin(int pin) {
  long double res = 0;
  // sometimes this helps improve accuracy
  analogRead(OUT_3V3);
  delay(10);
  for(int i = 0; i < READ_CNT; ++i){
    res += analogRead(OUT_3V3);
    delay(5);
  }
  return res / READ_CNT * 3.3 / 4096;
}

long double read_OUT() {
  return read_pin(OUT_3V3) * CONVERT_3V3_5V;
}

long double read_RAW_OUT() {
  return read_pin(OUT_3V3) * CONVERT_3V3_5V;
}

long double read_REF_SIG() {
  return read_pin(REF_SIG_SCALED);
}
