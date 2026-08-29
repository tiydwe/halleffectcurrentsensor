#include <Arduino.h>


#include "config.h"
#include "OLED.h"
#include "sense.h"
#include "utility.h"

long pushStart = 0;
bool wasPushed = false;

void go_to_sleep();

void setup() {
 init_sensors();
 init_OLED();
 pinMode(BTN, INPUT);
}

void loop() {
  auto out = read_OUT();
  auto raw_out = read_RAW_OUT();
  auto ref_sig = read_REF_SIG();
  OLED_display.clearDisplay();
  OLED_display.setCursor(0, 0);
  OLED_display.printf("Current: %.2fA*factor\n", out);
  OLED_display.printf("Reference V: %.2f A\n", ref_sig);
  OLED_display.printf("Raw voltage: %.2f V\n", raw_out);
  if(out > 4.5){
    OLED_display.println("WARNING! Current may be");
    OLED_display.println("wrong! High current!");
  }
  else{
    OLED_display.println("");
    OLED_display.println("");
  }
  OLED_display.println("To power off, hold the");
  OLED_display.println("power button for 5 s");
  
  if(digitalRead(INPUT) == HIGH){
    if(wasPushed){
      if(millis() - pushStart > 5000){
        
      }
    }
  }

}


void go_to_sleep(){
  sensors_off();
  OLED_off();
}