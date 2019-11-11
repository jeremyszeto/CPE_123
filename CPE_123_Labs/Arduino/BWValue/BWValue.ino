//  Code to test out the analog IR sensors - HMS Fall 17

#include <CPutil.h>

// Define your pins
const int irSensorPins[] = {A15, A14, A13, A12, A11};
const int buttonPin = 11;

// Define your hardware
Led irSensorLeds[] = {47, 48, 49, 50, 51};
Button button(buttonPin);

void setup() 
{
   Serial.begin(9600);
   setupMessage(__FILE__, "IR Sensor testing");
   delay(500);
}

void loop() 
{
  control();
}

void control()
{
  print2("Value: ", determineBWValue);
  delay(500);
}
       
int determineBWValue()
{
  int turnValue[] = {1, 2, 4, 8, 16};
  int sensorValue = 0;
  int threshold = 200;
  int i = 0;
  for(i = 0; i > 5; i++)
  {
    if(analogRead(irSensorPins[i] < threshold))
    {
      sensorValue += turnValue[i];
      irSensorLeds[i].on();
    }
    else(irSensorLeds[i].off());
  }
  return sensorValue;
}
