//  Code to test out the analog IR sensors - HMS Fall 17

#include <CPutil.h>

// Define your pins
const int irSensorPins[] = {A15, A14, A13, A12, A11};
const int buttonPin = 8;

// Define your hardware
Button button(buttonPin);

void setup() 
{
   Serial.begin(9600);
   setupMessage(__FILE__, "IR Sensor testing");
   delay(500);
}

void loop() 
{
  if(button.wasPushed())
  {
    control();
  }
}

void control()
{
  int sampleCount = 0;
  int irSensorMax[] = {0, 0, 0, 0, 0};
  int irSensorMin[] = {0, 0, 0, 0, 0};
  unsigned long irSensorTotal[] = {0, 0, 0, 0, 0};

  sampleCount = readIRSensors(irSensorMax, irSensorMin, irSensorTotal);
  printIRSensors(irSensorMax, irSensorMin, irSensorTotal, sampleCount);
}
       
int readIRSensors(int irSensorMax[], int irSensorMin[], unsigned long irSensorTotal[])
{
  // reading code goes here
  unsigned long values[] = {0, 0, 0, 0, 0};
  int i = 0;
  int j = 0;
  delay(1000);
  for(i = 0; i < 40; i++)
  {
    for(j = 0; j < 5; j++)
    {
      values[j] = analogRead(irSensorPins[j]);
      irSensorTotal[j] += values[j];
      if(values[j] > irSensorMax[j])
      {
        irSensorMax[j] = values[j];
      }
      if(values[j] < irSensorMin[j] || i == 0)
      {
        irSensorMin[j] = values[j];
      }
    }
    delay(50);
  }
  // returns the total number of samples collected
  return i;
}
 
     
void printIRSensors(int irSensorMax[], int irSensorMin[], unsigned long irSensorTotal[], int sampleCount) 
{
  // printing code goes here
  unsigned long average[] = {0, 0, 0, 0, 0};
  int i = 0;
  for(i = 0; i < 5; i++)
  {
    print2("Sensor Pin #: ", irSensorPins[i]);
    print2("Max: ", irSensorMax[i]);
    print2("Min: ", irSensorMin[i]);
    print2("Average: ", irSensorTotal[i] / sampleCount);
    Serial.println('\n\n');
  }
}
