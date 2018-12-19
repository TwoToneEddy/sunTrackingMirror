#include "src/sunPosition/sunpos.h"


cTime currentTime;
cLocation currentLocation;
cSunCoordinates result;


void setup() {

  Serial.begin(9600);
  currentTime.iYear = 2018;
  currentTime.iMonth = 12;
  currentTime.iDay = 19;
  currentTime.dHours = 13.0;
  currentTime.dMinutes =4.0;
  currentTime.dSeconds = 0.0;
  
  currentLocation.dLongitude = -1.485520;
  currentLocation.dLatitude = 51.783710;
  
  sunpos(currentTime,currentLocation,&result);
  


}

void loop() {
  
  Serial.println(result.dInclinationAngle);
  Serial.println(result.dAzimuth);
  delay(1000);

}
