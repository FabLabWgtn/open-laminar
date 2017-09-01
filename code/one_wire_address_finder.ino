// This sketch looks for 1-wire devices and
// prints their addresses (serial number) to
// the UART, in a format that is useful in Arduino sketches
// Tutorial: 
// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

//http://datasheets.maximintegrated.com/en/ds/DS18S20.pdf
//http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf
#include <OneWire.h>

// Hookup guide
// DS18S20 Pin 1 > GND
// DS18S20 Pin 2 > Arduino Pin 2
// DS18S20 Pin 3 > 5v
// 4.7K resistor between DS18S20 Pin 2 & DS18S20 Pin 3

OneWire  ds(2);  // Connect your 1-wire device to pin 2

void setup(void) {
  Serial.begin(9600);
  discoverOneWireDevices();
}

void discoverOneWireDevices(void) {
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];
  
  Serial.print("Looking for 1-Wire devices...\n\r");
  while(ds.search(addr)) {
    Serial.print("\n\rFound \'1-Wire\' device with address:\n\r");
    for( i = 0; i < 8; i++) {
      Serial.print("0x");
      if (addr[i] < 16) {
        Serial.print('0');
      }
      Serial.print(addr[i], HEX);
      if (i < 7) {
        Serial.print(", ");
      }
    }
    if ( OneWire::crc8( addr, 7) != addr[7]) {
        Serial.print("CRC is not valid!\n");
        return;
    }
  }
  Serial.print("\n\r\n\rThat's it.\r\n");
  ds.reset_search();
  return;
}

void loop(void) {
  // nothing to see here
}


