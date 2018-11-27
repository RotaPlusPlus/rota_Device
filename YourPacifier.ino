/*
 * Copyright (c) 2018 Hiroki Naganuma.  All rights reserved.
 * See the bottom of this file for the license terms.
 */

/*
 * Sketch: led.ino
 *
 * Description:
 *   This is a Peripheral sketch that works with a connected Central.
 *   It allows the Central to write a value and set/reset the led
 *   accordingly.
 */

 // - : CND(right)
// + : 3.3v
// S : 4 (DIGITAL)

#include <dht.h>

dht DHT;

#define DHT11_PIN 4
#define DHT21_PIN 5
#define DHT22_PIN 6

#include <CurieBLE.h>

BLEPeripheral blePeripheral; 
BLEService humidService("181B"); // BLE LED Service
BLECharacteristic humidCharacteristic("2A3B", BLERead | BLENotify, 2);

const int ledPin = 13; // pin to use for the LED
int oldHumidity = 0;  // 
long previousMillis = 0;  // last time the heart rate was checked, in ms

void setup() {
  Serial.begin(9600);

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);

  blePeripheral.setLocalName("HumidBlueTooth");
  blePeripheral.setAdvertisedServiceUuid(humidService.uuid());  // add the service UUID
  blePeripheral.addAttribute(humidService);   // Add the BLE Heart Rate service
  blePeripheral.addAttribute(humidCharacteristic); // add the Heart Rate Measurement characteristic

  /* Now activate the BLE device.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection */
  blePeripheral.begin();

  Serial.println("BLE LED Peripheral");
  setupHumidity();
}

void setupHumidity(){
  Serial.begin(115200);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

void loop() {
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());
    digitalWrite(ledPin, HIGH);

    // while the central is still connected to peripheral:
    while (central.connected()) {
      long currentMillis = millis();
      // if 200ms have passed, check the heart rate measurement:
      if (currentMillis - previousMillis >= 200) {
        previousMillis = currentMillis;
        updateHumidity();
      }      
    }

    digitalWrite(ledPin, LOW);
    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}

void updateHumidity(){
  // READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;
  }
  
 // DISPLAY DATA
  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.println(DHT.temperature,1);

//  delay(1000);

  int nowHumidity = DHT.humidity;
  
  if (nowHumidity != oldHumidity) {      // if the heart rate has changed
    const unsigned char humidityCharArray[2] = { 0, (char)nowHumidity};
    humidCharacteristic.setValue(humidityCharArray, 2);  // and update the heart rate measurement characteristic
    oldHumidity = nowHumidity;           // save the level for next comparison
  }
}
/*
   Copyright (c) 2018 Hiroki Naganuma.  All rights reserved.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
*/
