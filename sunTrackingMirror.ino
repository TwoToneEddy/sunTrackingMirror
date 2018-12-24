#include "src/sunPosition/sunpos.h"
#include "src/DS3231/DS3231.h"
#include <SoftwareSerial.h>
#include <Servo.h>



//Real time clock 
DS3231  rtc(SDA, SCL);

//Bluetooth comms
SoftwareSerial bluetoothSerial(9, 10);

//Servos
Servo azimuthServo,altServo;

//Structs required for sunpos()
cTime currentTime;
cLocation currentLocation;
cSunCoordinates result;

//Servo related variables
String azimuthServoDemandStr,altServoDemandStr;
int azimuthServoDemandInt,altServoDemandInt;

void setup() {

  //Setup bluetooth comms	
  bluetoothSerial.begin(115200);

  //Setup servos
  azimuthServo.attach(3);
  altServo.attach(5);

  //Initialise rtc
  rtc.begin();
  
  //Get current time and date (for testing)
  currentTime.iYear = rtc.getYearInt();
  currentTime.iMonth = rtc.getMonthInt();
  currentTime.iDay = rtc.getDayInt();
  currentTime.dHours = rtc.getHourD();
  currentTime.dMinutes =rtc.getMinuteD();
  currentTime.dSeconds = rtc.getSecondD();
  
  //Hard coded coordinates, could upgrade to GPS
  currentLocation.dLongitude = -1.485520;
  currentLocation.dLatitude = 51.783710;
  
  sunpos(currentTime,currentLocation,&result);

  /* This is how you set the time on the RTC if needed
  rtc.setDOW(THURSDAY);     //f Set Day-of-Week to SUNDAY
  rtc.setTime(17, 18, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(20, 12, 2018);   // Set the date to January 1st, 2014
  */

}

void loop() {
 	 
  //If manual control has been activated	  
  if (bluetoothSerial.available()) { 
    getManualServoDemand();
  }
  
  
}


/*
 *  Get demand from bluetooth serial and move servos to that point. First character is either
 *  'A' or 'B' for either az or alt. Value from bluetooth will be in the range 0 - 4096 so
 *  map() function is used to map that to the range 500 - 2250 which is roughly 0 - 180 degrees
 */
void getManualServoDemand(){
    switch (bluetoothSerial.read()){
      case 'A':
        while(bluetoothSerial.available()){
          azimuthServoDemandStr=bluetoothSerial.readString();
        }
        azimuthServoDemandInt = azimuthServoDemandStr.toInt();
        bluetoothSerial.print("Azimuth to ");
        bluetoothSerial.println(map(azimuthServoDemandInt,0,4096,500,2250));
        azimuthServo.writeMicroseconds(map(azimuthServoDemandInt,0,4096,500,2250));
      break;
      case 'B':
        while(bluetoothSerial.available()){
          altServoDemandStr=bluetoothSerial.readString();
        }
        altServoDemandInt = altServoDemandStr.toInt();
        bluetoothSerial.print("Altitude to ");
        bluetoothSerial.println(map(altServoDemandInt,0,4096,500,2250));
        altServo.writeMicroseconds(map(altServoDemandInt,0,4096,500,2250));
      break;
      default:
      break;
    }
}
