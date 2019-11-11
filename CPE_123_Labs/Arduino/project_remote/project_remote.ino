#include <CPutil.h>

// Define your pins
int ledPin = 49;
Led waterLight(ledPin);
const int abutton = 8;
Button b1(abutton);

void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(500);      
}

void loop() 
{
  control();
}

void control()
{
  static int serial=0;
  
  if(Serial1.available()==true){
    serial=Serial1.parseInt();
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
  static int water=0;
  enum {OFF, ON};
  
  switch (water){
    case (OFF):
      if(serial==0 && b1.wasPushed()==true){
        Serial1.println("3");
        water=ON;
      }
    break;
  
    case (ON):
      if(serial==0 && b1.wasPushed()==true){
        Serial1.println("4");
        water=OFF;
      }
      else if(serial==1){
        Serial1.println("4");
        water=OFF;
      }
    break;
  }
}

void light(int serial){
  if(serial==0){
    waterLight.on();
  }
  else{
    waterLight.off();
  }
} 
