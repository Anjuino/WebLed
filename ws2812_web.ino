bool FlagLed;
uint8_t FlagResetWifi = 0;

TaskHandle_t Task1;

#include <EEPROM.h>
#include <WiFiManager.h>
#include "Ws2812.h"
#include "TimeNTP.h"
#include "Web.h"

SET_LOOP_TASK_STACK_SIZE(40*1024); // Задаем размер стека для Loop

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
  res = wm.autoConnect ("ESPLed","password");

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

    Ws2812Init ();
    delay (100);
    ApInit (); 
    delay (100);
    ServerStart ();
    delay (200);
    TimeInit ();

    xTaskCreatePinnedToCore (
      TaskSheldure, 
      "Task1",      
      10000,        
      NULL,         
      1,            
      &Task1,       
      0);                            
    delay(500); 
  }
}

void TaskSheldure( void * pvParameters ){
  for(;;) {
    loopSheldure ();
  } 
}

void loop() {	
  Ws2812Loop ();
  server.handleClient ();
  loopSheldure ();
}



