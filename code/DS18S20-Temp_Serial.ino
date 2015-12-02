// This Arduino sketch reads DS18B20 family of "1-Wire" digital temperature sensors.
// Tutorial:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-tutorial.html

//http://datasheets.maximintegrated.com/en/ds/DS18S20.pdf
//http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf

#include <OneWire.h>
#include <DallasTemperature.h>

// Assign the addresses of your 1-Wire temp sensors.
// See the tutorial on how to obtain these addresses:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

DeviceAddress insideThermometer = { 0x10, 0x44, 0x6A, 0x16, 0x03, 0x08, 0x00, 0x5D };

// Hookup guide
// DS18S20 Pin 1 > GND
// DS18S20 Pin 2 > Arduino Pin 2
// DS18S20 Pin 3 > 5v
// 4.7K resistor between DS18S20 Pin 2 & DS18S20 Pin 3


// Data wire is plugged into pin 3 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);



void setup(void)
{
  // start serial port
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
  // set the resolution to 10 bit (good enough?)
  sensors.setResolution(insideThermometer, 10);
}

void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == -127.00) {
    Serial.print("Error getting temperature");
  } else {
    Serial.print("C: ");
    Serial.print(tempC);
  }
}

void loop(void)
{ 
  delay(2000);
  Serial.print("Getting temperatures...\n\r");
  sensors.requestTemperatures();
  
  Serial.print("Inside temperature is: ");
  printTemperature(insideThermometer);
  Serial.print("\n\r");

}

