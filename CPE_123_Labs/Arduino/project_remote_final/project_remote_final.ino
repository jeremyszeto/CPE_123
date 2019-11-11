#include <CPutil.h>

// Define pins
const int ledPin = 7;
const int buttonPin = 8;

// Define hardware
Led waterLight(ledPin);
Button b1(buttonPin);

void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(500);      
}

void loop() 
{
  controlRemote();
}

void controlRemote()
{
  static int serial = 0;
  
  if(Serial1.available())
  {
    serial = Serial1.parseInt();
  }
  light(serial);
  button(serial);
}
//0 is need water
//1 is sufficiently watered

//3 is button push for on
//4 is button push for off
void button(int serial)
{
  static int water = 0;
  enum {OFF, ON};
  
  switch (water){
    case (OFF):
      if(serial == 0 && b1.wasPushed())
      {
        Serial1.println(3);
        water = ON;
      }
    break;
  
    case (ON):
      if(serial == 0 && b1.wasPushed())
      {
        Serial1.println(4);
        water = OFF;
      }
      else if(serial == 1)
      {
        Serial1.println(4);
        water = OFF;
      }
    break;
  }
}

void light(int serial)
{
  if(serial == 0)
  {
    waterLight.on();
  }
  else
  {
    waterLight.off();
  }
} 
