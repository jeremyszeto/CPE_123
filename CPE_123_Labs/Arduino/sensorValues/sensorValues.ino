#include <CPutil.h>

// Define your pins
const int irSensorPins[] = {A1, A2, A3, A4, A5};

const int buttonPin = 11;

//Define hardware pins
Led irSensorLedPins[] = {47, 48, 49, 50, 51};

Button button(buttonPin);

void setup() 
{
   Serial.begin(9600);
   setupMessage(__FILE__, "IR Sensor testing");
   delay(1000);  
}

void loop() 
{
  MSTimer timer = 0;
  while(button.wasPushed() != true){}
  timer.set(2000);
  while(timer.done() != true)
  {
    printControl();
  }
}

void printControl()
{
  calcAverageValue();
  calcMaxValue();
  calcMinValue();
}

void calcAverageValue()
{
  static int total = 0;
  static int count = 0;
  unsigned long averageValue = 0;
  for(int i = 0; i <= 4; i++)
  {
    total += analogRead(irSensorPins[i]);
    count ++;
    delay(50);
  }
  averageValue = total / count;
  print2("Average Value: ", averageValue);
}
 
void calcMaxValue() 
{
  static unsigned long maxValue = 0;
  int number = 0;
  for(int i = 0; i <= 4; i++)
  {
    number = analogRead(irSensorPins[i]);
    if(number > maxValue)
    {
      maxValue = number;
      delay(50);
    }
  }
  print2("Max Value: ", maxValue);
}

unsigned long calcMinValue()
{
  static unsigned long minValue = 32767;
  int number = 0;
  for(int i = 0; i <= 4; i++)
  {
    number = analogRead(irSensorPins[i]);
    if(number < minValue)
    {
      minValue = number;
      delay(50);
    }
  }
  print2("Min Value: ", minValue);
}
