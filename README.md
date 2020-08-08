# WZ-S Library
Arduino library for Dart WZ-S Formaldehyde module. https://www.dart-sensors.com/product/wz-s-formaldehyde-module/
Heavly based on https://github.com/fu-hsi/PMS

## Basic Usage
Example using (Arduino Uno's) software serial at pin D8 and D9 connects to sensor, serial use for output. Sensor working at passive mode.

```cpp
#include "WZ_S.h"
#include <SoftwareSerial.h> 

//HCHO 5V
//Pin D9 TX
//Pin D8 RX
SoftwareSerial wz_s_Serial(8, 9);
WZ_S wz_s(wz_s_Serial);
WZ_S::DATA hcho_data;

void setup()
{
 Serial.begin(9600);
 wz_s_Serial.begin(9600); 
 wz_s.passiveMode();
}

void loop()
{
  // if using multiple software serial, you might want listen() before sending command!
  // wz_s_Serial.listen(); 
  wz_s.requestData(); // passive mode require you to request data, active mode dont.
  if(wz_s.dataRead(hcho_data))
  {
	Serial.print("HCHO PPB:");
	Serial.println(hcho_data.HCHO_ppb);
	Serial.print("HCHO ug:");
	Serial.println(hcho_data.HCHO_ug);
  }
  delay(5000); //don't request data too frequent :P 
}
