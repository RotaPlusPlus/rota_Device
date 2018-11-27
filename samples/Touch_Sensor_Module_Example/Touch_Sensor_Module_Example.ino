/*

OSEPP Touch Sensor Module Example

Serial monitor prints values output from touch sensor
when body conductivity applied. 

ref : 
http://www.musashinodenpa.com/arduino/ref/index.php?f=0&pos=2113

int sensorPin = A0; ?
int sensorPin = 0; ?
 */

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin,INPUT);
  // declare the ledPin as an OUTPUT:
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  Serial.println("Touch Sensor Value = " + sensorValue);

}
