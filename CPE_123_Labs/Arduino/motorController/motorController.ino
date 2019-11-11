#include <CPutil.h>

// Jeremy Szeto Group 9 3-6 Section

// Define our pins
const int leftMotorPin2 = 4;
const int leftMotorPin1 = 5;
const int rightMotorPin2 = 6;
const int rightMotorPin1 = 7;
const int buttonPin = 11;

// Define hardware
Button button(buttonPin);

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupMessage(__FILE__, "Motor Controller");
  delay(500);
  motorsSetup();
}

void loop()
{
  drivingControl();
}

void drivingControl()
{
  enum{START, FORWARD_1, RIGHT, FORWARD_2, LEFT, BACKWARD, SPIN, STOP};
  static int state = START;
  switch(state)
  {
    case(START):
      if(button.wasPushed())
      {
        state = FORWARD_1;
      }
    break;
    case(FORWARD_1):
      if(robotForward(250,3000))
      {
        state = RIGHT;
      }
    break;
    case(RIGHT):
      if(robotRight(250,2000))
      {
        state = FORWARD_2;
      }
    break;
    case(FORWARD_2):
      if(robotForward(250, 5000))
      {
        state = LEFT;
      }
    break;
    case(LEFT):
      if(robotLeft(250,3000))
      {
        state = BACKWARD;
      }
    break;
    case(BACKWARD):
      if(robotBackward(250,1000))
      {
        state = SPIN;
      }
    break;
    case(SPIN):
      if(robotSpin(250,500))
      {
        state = STOP;
      }
    break;
    case(STOP):
      robotStop();
      state = START;
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

int robotRight(int aSpeed, int turnTime)
{
  enum {START, STOP};
  static int state = START;
  static MSTimer timer = 0;
  int returnValue = false;
  switch(state)
  {
    case(START):
      leftTurn(aSpeed);
      timer.set(turnTime);
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

int robotLeft(int aSpeed, int turnTime)
{
  enum {START, STOP};
  static int state = START;
  static MSTimer timer = 0;
  int returnValue = false;
  switch(state)
  {
    case(START):
      rightTurn(aSpeed);
      timer.set(turnTime);
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

int robotBackward(int aSpeed, int driveTime)
{
  enum {START, STOP};
  static int state = START;
  static MSTimer timer = 0;
  int returnValue = false;
  switch(state)
  {
    case(START):
      leftMotorBackward(aSpeed);
      rightMotorBackward(aSpeed);
      timer.set(driveTime);
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

int robotForward(int aSpeed, int driveTime)
{
  enum {START, STOP};
  static int state = START;
  static MSTimer timer = 0;
  int returnValue = false;
  switch(state)
  {
    case(START):
      leftMotorForward(aSpeed);
      rightMotorForward(aSpeed);
      timer.set(driveTime);
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

   robotStop();
}
