bool FlagLed;
uint8_t FlagResetWifi = 0;

#include <EEPROM.h>
#include <WiFiManager.h>
#include "Ws2812.h"
#include "TimeNTP.h"
#include "Web.h"

SET_LOOP_TASK_STACK_SIZE(40*1024); // Задаем размер стека для Loop. Для esp32

unsigned long timer = 30000;

void setup() {
  Serial.begin (115200);
  WiFiManager wm;

  EEPROM.begin (10);

  EEPROM.get (2, FlagResetWifi);
  if (FlagResetWifi) {
    FlagResetWifi = 0;
    EEPROM.put (2, FlagResetWifi);
    EEPROM.commit ();
    wm.resetSettings();
  }

  bool res;
  res = wm.autoConnect ("ESPLed","password"); // password protected ap

  if(!res) {
    Serial.println ("Failed to connect");
  } 
  else {

    EEPROM.get (0, CountLed);
    EEPROM.get (0, posDown);

    delay (1);
    if (CountLed == 65535) {
      FlagLed = true;
    }
    else {
      strip.updateLength (CountLed);
      FlagLed = false;
    }

    Serial.println (CountLed);

    /*EEPROM.get (0, Speed);
    EEPROM.get (2, step);
    EEPROM.get (4, BlindLed);
    EEPROM.get (12, r1);
    EEPROM.get (14, g1);
    EEPROM.get (16, b1);*/
   
    Ws2812Init ();
    delay (1000);
    ApInit (); 
    delay (1000);
    ServerStart ();
    delay (2000);
    TimeInit ();
  }
}

void loop() {	
  Ws2812Loop ();
  server.handleClient ();
  loopSheldure ();
  delay (1);
}



