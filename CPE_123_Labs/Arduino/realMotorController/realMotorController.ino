#include <CPutil.h>
#include <CPE123_EncoderLib.h>

// Jeremy Szeto Group 9 3-6 Section

// Define our pins
const int leftMotorPin2 = 4;
const int leftMotorPin1 = 5;
const int rightMotorPin2 = 6;
const int rightMotorPin1 = 7;
const int buttonPin = 11;

// Encoder Pins for Mega board
const int rightEncoderPin1 = 20;
const int rightEncoderPin2 = 21;
const int leftEncoderPin1 = 2;
const int leftEncoderPin2 = 3;

// Define hardware
Button button(buttonPin);

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupMessage(__FILE__, "Motor Controller");
  delay(500);
  motorsSetup();
  encoderSetup(rightEncoderPin1, rightEncoderPin2, leftEncoderPin1, leftEncoderPin2);
  waitOnButton(button);
}

void loop()
{
  drivingControl();
}

void drivingControl()
{
  enum{FORWARD_1, LEFT, FORWARD_2, RIGHT_1, FORWARD_3, RIGHT_2, FORWARD_4, STOP};
  static int state = FORWARD_1;
  switch(state)
  {
    case(FORWARD_1):
      if(robotForward(60,250))
      {
          state = LEFT;
      }
    break;
    case(LEFT):
      if(robotLeft(45,250))
      {
          state = FORWARD_2;
      }
    break;
    case(FORWARD_2):
      if(robotForward(40, 250))
      {
        state = RIGHT_1;
      }
    break;
    case(RIGHT_1):
      if(robotRight(90,250))
      {
          state = FORWARD_3;
      }
    break;
    case(FORWARD_3):
      if(robotForward(50,250))
      {
          state = RIGHT_2;
      }
    break;
    case(RIGHT_2):
      if(robotRight(45,250))
      {
          state = FORWARD_4;
      }
    break;
    case(FORWARD_4):
      if(robotForward(50,250))
      {
          state = STOP;
      }
    break;
    case(STOP):
      robotStop();
    break;
  }
}

int robotSpin(int aSpeed, int spinTime)
{
  enum {START, STOP};
  static int state = START;
  static MSTimer timer = 0;
  int returnValue = false;
  switch(state)
  {
    case(START):
      rightMotorForward(aSpeed);
      leftMotorBackward(aSpeed);
      timer.set(spinTime);
      state = STOP;
      returnValue = false;
    break;
    case(STOP):
      if(timer.done())
      {
        robotStop();
        state = START;
        returnValue = true;
      }
    break;
  }
  return returnValue;
}

int robotRight(int turnAngle, int aSpeed)
 {
  enum {START, STOP};
  static int state = START;
  int returnValue = false;
  unsigned long clicks = 0;
  clicks = calcAngle(turnAngle);
  switch(state)
  {
    case(START):
      leftTurn(aSpeed);
      if(clicks == leftEncoderCount())
      {
        state = STOP;
      }
    break;
    case(STOP):
        robotStop();
        resetEncoders();
        state = START;
        returnValue = true;
    break;
  }
  return returnValue;
}

int robotLeft(int turnAngle, int aSpeed)
{
  enum {START, STOP};
  static int state = START;
  int returnValue = false;
  unsigned long clicks = 0;
  clicks = calcAngle(turnAngle);
  switch(state)
  {
    case(START):
      rightTurn(aSpeed);
      if(clicks == rightEncoderCount())
        {
          state = STOP;
        }
    break;
    case(STOP):
        robotStop();
        resetEncoders();
        state = START;
        returnValue = true;
    break;
  }
  return returnValue;
}

int robotBackward(int distanceInCm, int aSpeed)
{
  enum {START, STOP};
  static int state = START;
  int returnValue = false;
  unsigned long clicks = 0;
  clicks = calcDistance(distanceInCm);
  switch(state)
  {
    case(START):
      leftMotorBackward(aSpeed);
      rightMotorBackward(aSpeed);
      if(leftEncoderCount() == clicks || rightEncoderCount() == clicks)
      {
      state = STOP;
      }
    break;
    case(STOP):
      robotStop();
      resetEncoders();
      state = START;
      returnValue = true;
    break;
  }
  return returnValue;
}

int robotForward(int distanceInCm, int aSpeed)
{
  enum {START, STOP};
  static int state = START;
  int returnValue = false;
  unsigned long clicks = 0;
  clicks = calcDistance(distanceInCm);
  switch(state)
  {
    case(START):
      leftMotorForward(aSpeed);
      rightMotorForward(aSpeed);
      if(leftEncoderCount() == clicks || rightEncoderCount() == clicks)
      {
      state = STOP;
      }
    break;
    case(STOP):
      robotStop();
      resetEncoders();
      state = START;
      returnValue = true;
    break;
  }
  return returnValue;
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

unsigned long calcAngle(int aAngle)
{
  unsigned long encoderCount = 0;
  encoderCount = (3431/90) * aAngle;
  return encoderCount;
}

unsigned long calcDistance(int aDistance)
{
  unsigned long encoderCount = 0;
  encoderCount = 2214.25 * (aDistance / 20.42035224833366);
  return encoderCount;
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
