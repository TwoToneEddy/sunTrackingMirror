#include "src/sunPosition/sunpos.h"
#include "src/DS3231/DS3231.h"


cTime currentTime;
cLocation currentLocation;
cSunCoordinates result;

DS3231  rtc(SDA, SCL);

void setup() {

  Serial.begin(9600);
  // Initialize the rtc object
  rtc.begin();
  
  currentTime.iYear = 2018;
  currentTime.iMonth = 12;
  currentTime.iDay = 19;
  currentTime.dHours = 13.0;
  currentTime.dMinutes =4.0;
  currentTime.dSeconds = 0.0;
  
  currentLocation.dLongitude = -1.485520;
  currentLocation.dLatitude = 51.783710;
  
  sunpos(currentTime,currentLocation,&result);
  //rtc.setDOW(THURSDAY);     //f Set Day-of-Week to SUNDAY
  //rtc.setTime(17, 18, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(20, 12, 2018);   // Set the date to January 1st, 2014


}

void loop() {
  /*
  Serial.println(result.dInclinationAngle);
  Serial.println(result.dAzimuth);
  delay(1000);*/
  
  
  // Send date
  Serial.print(rtc.getDayStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());
  
  // Wait one second before repeating :)
  delay (1000);
}
