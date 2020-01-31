# WS-Z Library
Arduino library for Dart WZ-S Formaldehyde module. https://www.dart-sensors.com/product/wz-s-formaldehyde-module/
Heavly based on https://github.com/fu-hsi/PMS

## Basic Usage
Example using (Arduino Uno's) software serial at pin D8 and D9 connects to sensor, serial use for output. Sensor working at passive mode.

```cpp
#include "WS_Z.h"
#include <SoftwareSerial.h> 

//HCHO 5V
//Pin D9 TX
//Pin D8 RX
SoftwareSerial ws_z_Serial(8, 9);
WS_Z ws_z(ws_z_Serial);
WS_Z::DATA hcho_data;

void setup()
{
 Serial.begin(9600);
 ws_z_Serial.begin(9600); 
 ws_z.passiveMode();
}

void loop()
{
  // if using multiple software serial, you might want listen() before sending command!
  // ws_z_Serial.listen(); 
  ws_z.requestData(); // passive mode require you to request data, active mode dont.
  if(ws_z.dataRead(hcho_data))
  {
	Serial.print("HCHO PPB:");
	Serial.println(hcho_data.HCHO_ppb);
	Serial.print("HCHO ug:");
	Serial.println(hcho_data.HCHO_ug);
  }
  
}
