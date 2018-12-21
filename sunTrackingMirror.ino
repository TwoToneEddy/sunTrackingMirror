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
  
  currentTime.iYear = rtc.getYearInt();
  currentTime.iMonth = rtc.getMonthInt();
  currentTime.iDay = rtc.getDayInt();
  currentTime.dHours = rtc.getHourD();
  currentTime.dMinutes =rtc.getMinuteD();
  currentTime.dSeconds = rtc.getSecondD();
  
  currentLocation.dLongitude = -1.485520;
  currentLocation.dLatitude = 51.783710;
  
  sunpos(currentTime,currentLocation,&result);
  //rtc.setDOW(THURSDAY);     //f Set Day-of-Week to SUNDAY
  //rtc.setTime(17, 18, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(20, 12, 2018);   // Set the date to January 1st, 2014


}

void loop() {
  
  Serial.println(result.dInclinationAngle);
  Serial.println(result.dAzimuth);
  delay(1000);
  
}
