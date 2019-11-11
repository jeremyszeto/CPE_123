//  Code to test out the analog IR sensors - HMS Fall 17

#include <CPutil.h>

// Define your pins
const int irRightPin = A1;
const int irCenterRightPin = A2;
const int irCenterPin = A3;
const int irCenterLeftPin = A4;
const int irLeftPin = A5;

void setup() 
{
   Serial.begin(9600);
   setupMessage(__FILE__, "IR Sensor testing");
   delay(500);
       
}

void loop() 
{
	testIRSensors();
}
       
void testIRSensors()
{
	static MSTimer aDelay(1000);
	if (aDelay.done())
	{
    int sensorPins[] = {irRightPin, irCenterRightPin, irCenterPin, irCenterLeftPin, irLeftPin};
		for(int i = 0; i <= 4; i++)
    {
		  aDelay.set(1000);
		  printIR(sensorPins[i]);
    }
    Serial.print("\n\n");
	}
}
  
void printIR(int aIRPin) 
{
  int irValue = analogRead(aIRPin);   
  
  print4("Pin #: ", aIRPin, " IR value: ", irValue);

}          
