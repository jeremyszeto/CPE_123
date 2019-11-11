#include <CPE123_Fall17.h>

// Simple sketch to just test a motor

// Define our pins
const int motorPinA = 4;
const int motorPinB = 5;


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  setupMessage(__FILE__, "Simple Motor Test sketch");
  delay(500);

   // Initalize the pins for output 
   pinMode(motorPinA, OUTPUT);
   pinMode(motorPinB, OUTPUT);

    // Stop the motor
   analogWrite(motorPinA, 0);
   analogWrite(motorPinB, 0);
     
}



void loop()
{
  motorTest();

}

void motorTest()
{
   
   analogWrite(motorPinA, 250);
   analogWrite(motorPinB, 0);
  
   delay(5000);
 
  analogWrite(motorPinA, 0);
  analogWrite(motorPinB, 0);
 
  delay(2000);
}
