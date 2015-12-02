/* Example sketch for Maxim Integrated DS18B20 temperature sensor
   Written by cactus.io, and requires the cactus_io_DS18B20 library.
   This sketch was tested using the Adafruit Prewired DS18B20 Sensor.
   For hookup details using this sensor then visit
   http://cactus.io/hookups/sensors/temperature-humidity/ds18b20/hookup-arduino-to-ds18b20-temperature-sensor
*/

#include "cactus_io_DS18B20.h" 

int DS18S20_Pin = 2; //DS18S20 Signal pin on digital 2

// Create DS18B20 object
DS18B20 ds(DS18S20_Pin);  // on digital pin 2

void setup(void) {
  
    ds.readSensor();
  
    Serial.begin(9600);
    Serial.println("Maxim Integrated DS18B20 Temperature Sensor | cactus.io");
    Serial.print("DS18B20 Serial Number: ");
  
    // we pass the serial number byte array into the printSerialNumber function
    printSerialNumber(ds.getSerialNumber());
  
    Serial.println("");
    Serial.println("");
    Serial.println("Temp (C)\tTemp (F)");
}

void loop(void) {
  
    ds.readSensor();
  
    Serial.print(ds.getTemperature_C()); Serial.print(" *C\t");
    Serial.print(ds.getTemperature_F()); Serial.println(" *F");
  
    // Add a 2 second delay.
    delay(2000); //just here to slow down the output.
}

// We call this function to display the DS18B20 serial number. 
// It takes an array of bytes for printing
void printSerialNumber(byte *addr) {
    byte i;
  
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
}  
