## rota Device
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Please edit `YourPacifier.ino` and use.
sample is a collection of other publicly available source code.

## Hardware Environment
#### Arduino
We tested on Genuino 101（Arduino 101 in US）
https://www.switch-science.com/catalog/2670/

#### Sensor
Operation in DHT11 sensor as a Humidity Sensor, we have seen.
http://playground.arduino.cc//Main/DHTLib

## Adjustment of variables for communication
#### BLEService
When specifying UUIDs as `181B` on the iOS side

https://github.com/RotaPlusPlus/rota_iOS/blob/master/rota/Controller/HumidityViewController.swift#L93

```swift
let serviceUUIDs:[AnyObject] = [CBUUID(string: "181B")]
let lastPeripherals = centralManager.retrieveConnectedPeripherals(withServices: serviceUUIDs as! [CBUUID] )
```

https://github.com/RotaPlusPlus/rota_iOS/blob/master/rota/Controller/HumidityViewController.swift#L118

```swift
func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
    print("Connect success!")
    let serviceUUIDs:[AnyObject] = [CBUUID(string: "181B")]
    connectingPeripheral.discoverServices(serviceUUIDs as! [CBUUID])
}
```

then, It is necessary to unify the following to `181B` on Arduino.

https://github.com/RotaPlusPlus/rota_Device/blob/master/YourPacifier.ino#L30

```Arduino
#include <CurieBLE.h>

BLEPeripheral blePeripheral;
BLEService humidService("181B"); // BLE LED Service
```

#### BLECharacteristic
When specifying UUIDs as `2A3B` on the iOS side
https://github.com/RotaPlusPlus/rota_iOS/blob/master/rota/Controller/HumidityViewController.swift#L134

```swift
let characteristicUUIDs: [AnyObject] = [CBUUID(string: "2A3B")]
connectingPeripheral.discoverCharacteristics(characteristicUUIDs as! [CBUUID],
                                   for: (peripheral.services?.first)!)
```

then, It is necessary to unify the following to `2A3B` on Arduino.

https://github.com/RotaPlusPlus/rota_Device/blob/master/YourPacifier.ino#L31

```Arduino
BLECharacteristic humidCharacteristic("2A3B", BLERead | BLENotify, 2);
```

## Run
Arduino IDE on OSX
https://www.arduino.cc/en/Main/Software

## LISENSE
Copyright 2018 Hiroki11x(Hiroki Naganuma)
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
