//#include <ESP8266WiFi.h>        //esp8266
//#include <WiFiClient.h>         //esp8266
//#include <ESP8266WebServer.h>   //esp8266

#include <WiFi.h>        //esp32
#include <WebServer.h>   //esp32

#include "page.h"
#include "SettingPage.h"
#include "styles.h"

//const char* ssid = "Led";  
//const char* password = "12345678"; 

//ESP8266WebServer server (80);     //esp8266
WebServer server(80);           // esp32

void ApInit () 
{
  String ip = WiFi.gatewayIP ().toString ();
  char *str = strdup (ip.c_str());
  char *token = strtok (str, ".");

  int ip1 = atoi (token);
  token = strtok (NULL, ".");
  int ip2 = atoi (token);
  token = strtok (NULL, ".");
  int ip3 = atoi (token);
  int ip4 = 92;
  free(str);

  IPAddress local_ip (ip1,ip2,ip3,ip4);
  IPAddress subnet (255,255,255,0);

  (WiFi.config (local_ip, WiFi.gatewayIP (), subnet));

  WiFi.setAutoReconnect (true);
  WiFi.persistent (true);

  //WiFi.setSleepMode (WIFI_NONE_SLEEP);

  
  /*WiFi.softAP(ssid, password);
  IPAddress local_ip(192,168,2,1);
  IPAddress gateway(192,168,2,1);
  IPAddress subnet(255,255,255,0);
  WiFi.softAPConfig(local_ip, gateway, subnet);*/
  //WiFi.setSleepMode(WIFI_NONE_SLEEP);
}

void handleStartPage (void) {
  String page = mypage;
  server.send (200, "text/html", page);
}

void handleSettingPage (void) {
  String page = SettingPage;
  server.send (200, "text/html", page);
}

void handlecss (void) {
  String page = mystyle;
  server.send (200, "text/css", page);
}

void handlemode (void) {

  server.send (200, "text/plane", "OK");
  delay (1);

  String R = server.arg ("R");
  String G = server.arg ("G");
  String B = server.arg ("B");

  Ws2812SetMode ("0");
  Ws2812SetColor (R.toInt (), G.toInt (), B.toInt ());

  /*EEPROM.put (6, R.toInt());
  EEPROM.put (8, G.toInt());
  EEPROM.put (10, B.toInt());

  EEPROM.commit ();*/
}

void handleoff (void) {
  server.send (200, "text/plane", "OK");
  delay (1);
  
  String Tag = server.arg ("Mode");
  Ws2812SetMode (Tag);
}

void handlespeed (void) {
  server.send (200, "text/plane", "OK");
  delay (1);
  String Tag = server.arg ("Speed");
  Ws2812SetSpeed (Tag.toInt ());
}

void handleblind (void) {
  server.send (200, "text/plane", "OK");
  delay (1);

  String Tag = server.arg ("Blind");
  uint8_t Blinds = Tag.toInt ();
  strip.setBrightness (Blinds * 1.9);
  uint8_t Blind = Blinds * 1.9;
  strip.show (); 
  
  /*EEPROM.put (4, Blind);
  EEPROM.commit ();*/
}

void handlereset (void) {
  String page = SettingPage;
  server.send (200, "text/html", page);
}

void handleSetCount (void) {
  server.send (200, "text/plane", "OK");
  String Tag = server.arg ("CountLed");

  int CountLed = Tag.toInt();

  if (CountLed > 500) CountLed = 500;
  if (CountLed < 0)   CountLed = 0;

  EEPROM.put (0, CountLed);
  EEPROM.commit ();

  Ws2812SetColor (0, 0, 0); 

  delay (100);
  ESP.restart(); 
}

void handleResetWifi (void) {
  server.send (200, "text/plane", "OK");

  FlagResetWifi = 1;

  EEPROM.put (2, FlagResetWifi);
  EEPROM.commit ();

  delay (100);
  ESP.restart();
  
}

void handleeffects (void) {
  server.send (200, "text/plane", "OK");
  delay (1);

  String Tag = server.arg ("Effects");

  if (Tag == "2" || Tag == "7") {
    String R = server.arg ("R");
    String G = server.arg ("G");
    String B = server.arg ("B");
    if (R == "0" && G == "0" && B == "0") {

    } 
    else {
      /*EEPROM.put (12, R.toInt());
      EEPROM.put (14, G.toInt());
      EEPROM.put (16, B.toInt());
      EEPROM.commit ();*/
    }
    r1 = R.toInt ();
    g1 = G.toInt ();
    b1 = B.toInt ();
  } 
  Ws2812SetMode (Tag);
}

void handleGetState (void) {

  if (stateOnOff) server.send (200, "text/plane", "true");
  else            server.send (200, "text/plane", "false");

}

void SetTime (String time, String state) {

  if (time) {
    Serial.println (time);
    char *str = strdup (time.c_str());
    char delimiters[] = ":";

    char *token = strtok (str, delimiters);
    String HourT = token;

    token = strtok(NULL, delimiters);
    String MinuteT = token;

    if (HourT.charAt(0) == '0') {
      String H = String (HourT.charAt(1));
      Hour = H.toInt();
    }
    else Hour = HourT.toInt();

    if (MinuteT.charAt(0) == '0') {
      String T = String (MinuteT.charAt(1));
      Minute = T.toInt();
    }
    else Minute = MinuteT.toInt();
  }

  if (state == "true")   server.send (200, "text/plane", "OK");
  if (state == "false")  server.send (200, "text/plane", "OKwithoutSheld");
  if (state == "Non")    server.send (200, "text/plane", "false");
}

void handleLedOffTime (void) {

  String State = server.arg ("state");

  if (State == "true") {
    stateOnOff = true;

    String Time = server.arg ("T");

    SetTime (Time, State);

    OldTime = Time;
  }

  else {
    stateOnOff = false;

    String Time = server.arg ("T");

    if (OldTime == Time) SetTime (Time, "Non");
    else                 SetTime (Time, State);

    OldTime = Time;
  }                
}


void handleGetTime (void) {

  String HourT;
  String MinuteT;

  HourT = String(Hour);
  MinuteT = String(Minute);

  String TimeAll = HourT + ":" + MinuteT;

  server.send (200, "text/plane", TimeAll);
}


void ServerStart (void) {
  if (FlagLed) server.on ("/", handleSettingPage);                     // Страница при первом запуске
  else         server.on ("/", handleStartPage);                     // Страница при первом запуске
  server.on ("/styles.css", handlecss);
  server.on ("/mode", handlemode); 
  server.on ("/ledoff", handleoff);                    
  server.on ("/blind", handleblind);
  server.on ("/effects", handleeffects);    
  server.on ("/speed", handlespeed);
  server.on ("/page.html", handlereset);
  server.on ("/setcount", handleSetCount);
  server.on ("/resetWifi", handleResetWifi);

  server.on ("/getState", handleGetState);
  server.on ("/ledofftime", handleLedOffTime);  
  server.on ("/getTime", handleGetTime);                    
  server.begin ();
}