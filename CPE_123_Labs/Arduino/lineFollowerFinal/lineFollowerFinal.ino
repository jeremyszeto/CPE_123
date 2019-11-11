//  Code to test out the analog IR sensors - HMS Fall 17

#include <CPutil.h>

// Define your pins
const int irSensorPins[] = {A15, A14, A13, A12, A11};
const int buttonPin = 8;

const int leftMotorPin2 = 4;
const int leftMotorPin1 = 5;
const int rightMotorPin2 = 6;
const int rightMotorPin1 = 7;

// Define your hardware
Led irSensorLeds[] = {47, 48, 49, 50, 51};
Button button(buttonPin);

void setup() 
{
   Serial.begin(9600);
   setupMessage(__FILE__, "Line Follower");
   delay(500);

   motorsSetup();

   while(button.wasPushed() != true){}
}

void loop() 
{
	control();
  delay(50);
  determineBWValue();
  serialLog();
}

void control()
{
  static int state = determineBWValue();
  
  switch(state)
  {
    case(2):
      leftMotorForward(100);
      rightMotorStop();
    break;

    case(6):
      leftMotorForward(100);
      rightMotorForward(50);
    break;

    case(4):
      leftMotorForward(100);
      rightMotorForward(100);
    break;

    case(12):
      rightMotorForward(100);
      leftMotorForward(50);
    break;

    case(8):
      rightMotorForward(100);
      leftMotorStop();
    break;

//    default:
//      leftMotorForward(100);
//      rightMotorForward(100);
//    break;
  }
}

void serialLog()
{
  print2("Value: ", determineBWValue());
  delay(500);
}
       
int determineBWValue()
{
  int turnValue[] = {0, 8, 4, 2, 0};
  int sensorValue = 0;
  int threshold = 200;
  int i = 0;
  for(i = 0; i < 5; i++)
  {
    if(analogRead(irSensorPins[i]) > threshold)
    {
      sensorValue = sensorValue + turnValue[i];
      irSensorLeds[i].on();
    }
    else
    {
    irSensorLeds[i].off();
    }
  }
  return sensorValue;
}

void robotStop()
{
  leftMotorStop();
  rightMotorStop();
}

void rightTurn(int aSpeed)
{
  motorControl(leftMotorPin1, leftMotorPin2, aSpeed);
  motorControl(rightMotorPin1, rightMotorPin2, 0);
}

void leftTurn(int aSpeed)
{
  motorControl(leftMotorPin1, leftMotorPin2, 0);
  motorControl(rightMotorPin1, rightMotorPin2, aSpeed);
}

void leftMotorStop()
{
  motorControl(leftMotorPin1, leftMotorPin2, 0);
}

void rightMotorStop()
{
  motorControl(rightMotorPin1, rightMotorPin2, 0);
}

void rightMotorBackward(int aSpeed)
{
  motorControl(rightMotorPin2, rightMotorPin1, aSpeed);
}

void leftMotorBackward(int aSpeed)
{
  motorControl(leftMotorPin2, leftMotorPin1, aSpeed);
}

void rightMotorForward(int aSpeed)
{
  motorControl(rightMotorPin1, rightMotorPin2, aSpeed);
}

void leftMotorForward(int aSpeed)
{
  motorControl(leftMotorPin1, leftMotorPin2, aSpeed);
}

void motorControl(int pin1, int pin2, int aSpeed)
{
  analogWrite(pin1, aSpeed);
  analogWrite(pin2, 0);
}

void motorsSetup()
{
   // Initalize the pins for output 
   pinMode(leftMotorPin1, OUTPUT);
   pinMode(leftMotorPin2, OUTPUT);
   pinMode(rightMotorPin1, OUTPUT);
   pinMode(rightMotorPin2, OUTPUT);

    // Stop the motor
   analogWrite(leftMotorPin1, 0);
   analogWrite(leftMotorPin2, 0);
   analogWrite(rightMotorPin1, 0);
   analogWrite(rightMotorPin2, 0);
}
