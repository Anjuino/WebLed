//#include <ESP8266WiFi.h>        //esp8266
//#include <WiFiClient.h>         //esp8266
//#include <ESP8266WebServer.h>   //esp8266

#include <WiFi.h>        //esp32
#include <WebServer.h>   //esp32
#include <ESPmDNS.h>

#include "page.h"
#include "SettingPage.h"
#include "styles.h"

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

  WiFi.config (local_ip, WiFi.gatewayIP (), subnet, WiFi.gatewayIP ());

  WiFi.setAutoReconnect (true);
  WiFi.persistent (true);

  MDNS.begin("WebLed");

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
  BlindLed = Tag.toInt ();
  strip.setBrightness (BlindLed * 1.9);
  strip.show (); 
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

    r1 = R.toInt ();
    g1 = G.toInt ();
    b1 = B.toInt ();
  } 
  Ws2812SetMode (Tag);
}

void handleGetState (void) 
{

  String On = server.arg ("On");
  String Off = server.arg ("Off");

  if (Off) {
    if (stateOff)   server.send (200, "text/plane", "true");
    else            server.send (200, "text/plane", "false");
  }

  if (On) {
    if (stateOn)   server.send (200, "text/plane", "true");
    else            server.send (200, "text/plane", "false");
  }

}

void handleGetBlind (void) 
{
  server.send (200, "text/plane", String (BlindLed));
}

void handleGetSpeed (void) 
{
  server.send (200, "text/plane", String(Speed));
}

void SetTime (String time, String state, bool IsOnOff) 
{
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

      if (IsOnOff) HourOff = H.toInt();
      else         HourOn  = H.toInt();
    }
    else {
      if (IsOnOff) HourOff = HourT.toInt();
      else         HourOn  = HourT.toInt();
    }

    if (MinuteT.charAt(0) == '0') {
      String T = String (MinuteT.charAt(1));
      
      if (IsOnOff) MinuteOff = T.toInt();
      else         MinuteOn  = T.toInt();
    }
    else {
      if (IsOnOff) MinuteOff = MinuteT.toInt();
      else         MinuteOn  = MinuteT.toInt();
    }
  }

  if (state == "true")   server.send (200, "text/plane", "OK");
  if (state == "Non")    server.send (200, "text/plane", "false");
}

void handleLedOffTime (void) {

  String State = server.arg ("state");

  if (State == "true") {
    stateOff = true;

    String Time = server.arg ("T");

    SetTime (Time, State, true);

    OldTimeOff = Time;
  }

  else {
    stateOff = false;

    String Time = server.arg ("T");

    if (OldTimeOff == Time) SetTime (Time, "Non", true);
    else                    SetTime (Time, State, true);

    OldTimeOff = Time;
  }                
}

void handleLedOnTime (void) {

  String State = server.arg ("state");

  if (State == "true") {
    stateOn = true;

    String Time = server.arg ("T");

    SetTime (Time, State, false);

    OldTimeOn = Time;
  }

  else {
    stateOn = false;

    String Time = server.arg ("T");

    if (OldTimeOn == Time)  SetTime (Time, "Non", false);
    else                    SetTime (Time, State, false);

    OldTimeOn = Time;
  }                
}


void handleGetTimeOnOff (void) {

  String HourT;
  String MinuteT;
  String TimeAll;

  String On = server.arg ("On");
  String Off = server.arg ("Off");

  if (Off) {
    HourT = String(HourOff);
    MinuteT = String(MinuteOff);

    TimeAll = HourT + ":" + MinuteT;
  }

  if (On) {
    HourT = String(HourOn);
    MinuteT = String(MinuteOn);

    TimeAll = HourT + ":" + MinuteT;
  }

  server.send (200, "text/plane", TimeAll);
}


void ServerStart (void) {
  if (FlagLed) server.on ("/", handleSettingPage);                     // Страница при первом запуске
  else         server.on ("/", handleStartPage);                       // Страница при первом запуске

  server.on ("/styles.css", handlecss);
  server.on ("/mode", handlemode); 
  server.on ("/ledoff", handleoff);                    
  server.on ("/blind", handleblind);
  server.on ("/effects", handleeffects);    
  server.on ("/speed", handlespeed);
  server.on ("/page.html", handlereset);
  server.on ("/setcount", handleSetCount);
  server.on ("/resetWifi", handleResetWifi);

  server.on ("/getBlind", handleGetBlind);
  server.on ("/getSpeed", handleGetSpeed);

  server.on ("/getState", handleGetState);
  server.on ("/ledofftime", handleLedOffTime);
  server.on ("/ledontime", handleLedOnTime);    
  server.on ("/getTime", handleGetTimeOnOff);    

  server.begin ();

}