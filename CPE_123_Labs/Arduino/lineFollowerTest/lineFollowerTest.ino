#include <CPutil.h>

const int leftIR = A2;
const int middleIR = A3;
const int rightIR = A4;

const int leftMotorPin2 = 4;
const int leftMotorPin1 = 5;
const int rightMotorPin2 = 6;
const int rightMotorPin1 = 7;

const int buttonPin = 11;

Button button(buttonPin);

void setup()
{
  motorsSetup();
  pinsSetup();
  waitOnButton(button);
}

void loop()
{
  lineFollower();
}

void lineFollower()
{
  int lightValue = 500;
  
  if((analogRead(leftIR) < lightValue) && (analogRead(rightIR) < lightValue))     // forward
  {
    leftMotorForward(100);
    rightMotorForward(100);
  }
  
  if((analogRead(leftIR) > lightValue) && (analogRead(rightIR) < lightValue))     // right
  {
    rightMotorStop();
    leftMotorForward(100);
  }
  
  if((analogRead(leftIR) < lightValue) && (analogRead(rightIR) > lightValue))     // left
  {
    leftMotorStop();
    rightMotorForward(100);
  }
  
  if((analogRead(leftIR) > lightValue) && (analogRead(rightIR) > lightValue  ))     // stop
  {
    robotStop();
  }

  delay(50);
  
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

void waitOnButton(Button & aButton)
{
 Serial.println("Waiting on button push");
 while (aButton.wasPushed() == false)
 { } // note infinite loop until button is pushed
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

   robotStop();
}

void pinsSetup()
{
  pinMode(leftIR, INPUT);
  pinMode(middleIR, INPUT);
  pinMode(rightIR, INPUT); 
}
