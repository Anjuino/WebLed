#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

String OldTimeOff;
String OldTimeOn;
uint64_t TimerOff = 0;
uint64_t TimerOn = 0;
bool stateOff = false;
bool stateOn  = false;

int HourOff = 0;
int MinuteOff = 0;

int HourOn = 0;
int MinuteOn = 0;

void TimeInit ()
{
  timeClient.begin();
  timeClient.setTimeOffset(25200); // +7 Часовой пояс 
}

void loopSheldure ()
{
  if (stateOff) {
    if (millis () > TimerOff) {
      timeClient.update();
      TimerOff = millis () + 20000;
      if (HourOff == timeClient.getHours()) {
        if (MinuteOff == timeClient.getMinutes()) {
          Ws2812SetMode ("250");
          Serial.println ("Off");
          TimerOff = millis () + 60000;
        }
      }
    }
  }

  if (stateOn) {
    if (millis () > TimerOn) {
      timeClient.update();
      TimerOn = millis () + 20000;
      if (HourOn == timeClient.getHours()) {
        if (MinuteOn == timeClient.getMinutes()) {
          Serial.println (String (stepOld));
          Ws2812SetMode (String (stepOld));
          Serial.println ("On");
          TimerOn = millis () + 60000;
        }
      }
    }
  }
}