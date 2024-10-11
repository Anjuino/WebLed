#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
String OldTime;
uint64_t Timer = 0;
bool stateOnOff = false;
int Hour = 0;
int Minute = 0;

void TimeInit ()
{
  timeClient.begin();
  timeClient.setTimeOffset(25200); // +7 Часовой пояс 
}


void loopSheldure ()
{
  if (stateOnOff) {
    if (millis () > Timer) {
      timeClient.update();
      Timer = millis () + 20000;
      if (timeClient.getHours() == Hour) {
        if (timeClient.getMinutes() == Minute) {
          Ws2812SetMode ("250");
          Timer = millis () + 60000;
        }
      }
    }
  }
}