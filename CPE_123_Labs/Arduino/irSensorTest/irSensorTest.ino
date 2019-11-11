//  Code to test out the analog IR sensors - HMS Fall 17

#include <CPutil.h>

// Define your pins
const int irSensorPins[] = {A15, A14, A13, A12, A11};

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
		aDelay.set(1000);
		Serial.print("\n\n");
    for(int i = 0; i < 5; i++)
    {
      printIR(irSensorPins[i]);
    }
	}
}
 
     
void printIR(int aIRPin) 
{
  int irValue = analogRead(aIRPin);   
  
  print4("Pin #: ", aIRPin, " IR value: ", irValue);

}          
