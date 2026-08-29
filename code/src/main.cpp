#include <Arduino.h>
#include <bluefruit.h>
#include <Adafruit_SPIFlash.h>

#include "config.h"
#include "OLED.h"
#include "sense.h"
#include "utility.h"

#if defined(CUSTOM_CS) && defined(CUSTOM_SPI)
  Adafruit_FlashTransport_SPI flashTransport(CUSTOM_CS, CUSTOM_SPI);

#elif defined(ARDUINO_ARCH_ESP32)
  Adafruit_FlashTransport_ESP32 flashTransport;

#else
  #if defined(EXTERNAL_FLASH_USE_QSPI)
    Adafruit_FlashTransport_QSPI flashTransport;

  #elif defined(EXTERNAL_FLASH_USE_SPI)
    Adafruit_FlashTransport_SPI flashTransport(EXTERNAL_FLASH_USE_CS, EXTERNAL_FLASH_USE_SPI);

  #else
    #error No QSPI/SPI flash are defined on your board variant.h !
  #endif
#endif

Adafruit_SPIFlash flash(&flashTransport);

long pushStart = 0;
bool wasPushed = false;

void go_to_sleep();

void setup() {
 init_sensors();
 init_OLED();
 pinMode(BTN, INPUT);
 nrf_gpio_cfg_sense_input(
    g_ADigitalPinMap[BTN],
    NRF_GPIO_PIN_NOPULL,
    NRF_GPIO_PIN_SENSE_HIGH
  );
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
        go_to_sleep();
      }
    }
    else{ 
      wasPushed = true;
      pushStart = millis();
    }
  }
  else{
    wasPushed = false;
  }
  delay(50);
}

// HOW TO WAKE UP FROM SLEEP FROM GPIO PIN???
// ANYONE?
void go_to_sleep(){
  sensors_off();
  OLED_off();
  flash.begin();
  flashTransport.begin();
  if(flashTransport.runCommand(0xB9) == false){
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    while(true){
      yield();
    }
  }
  flashTransport.end();
  flash.end();
}