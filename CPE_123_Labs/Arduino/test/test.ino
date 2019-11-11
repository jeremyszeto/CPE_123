#include <CPutil.h>

// Simple sketch to just test a motor

// Define our pins
const int leftMotorPin1 = 4;
const int leftMotorPin2 = 5;
const int rightMotorPin1 = 6;
const int rightMotorPin2 = 7;
const int btn = 11;

Button button(btn);


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  setupMessage(__FILE__, "Simple Motor Test sketch");
  delay(500);
  motorsSetup();
     
}
void motorsSetup(){
  
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



void loop()
{
  //leftMotorBackward(250);
  //rightMotorForward(250);
  //delay(2000);
  //rightMotorStop();
  //delay(2000);
  //rightTurn(250);
  control();
  
}
void control(){
  enum{START, DRIVEF1, TURNR, DRIVEF2, TURNL, DRIVEB, SPIN, STOP};
  static int state = START;
  switch(state){
    case(START):
      if(button.wasPushed()){
        state = DRIVEF1;
      }
    break;
    case(DRIVEF1):
      if(robotForward(250,3000) == true){
          state = TURNR;
        }
    break;
    case(TURNR):
      if(robotRight(250,2000) == true){
          state = DRIVEF2;
        }
    break;
    case(DRIVEF2):
      if(robotForward(250, 5000) == true){
        state = TURNL;
      }
    break;
    case(TURNL):
      if(robotLeft(250,3000) == true){
          state = DRIVEB;
        }
    break;
    case(DRIVEB):
      if(robotBackward(250,1000) == true){
          state = SPIN;
        }
    break;
    case(SPIN):
      if(robotSpin(250,500) == true){
          state = STOP;
      }
    break;
    case(STOP):
      robotStop();
      state = START;
    break;
  }
}

void motorTest()
{
   

   analogWrite(leftMotorPin1, 250);
   analogWrite(leftMotorPin2, 0);
   analogWrite(rightMotorPin1, 250);
   analogWrite(rightMotorPin2, 0);
  
   delay(5000);
 
    // Stop the motor
    robotStop();
  delay(2000);
}
void motorControl(int pin1, int pin2, int aSpeed){
  analogWrite(pin1,0);
  analogWrite(pin2,aSpeed);
  
}
void leftMotorForward(int aSpeed){
  motorControl(leftMotorPin1,leftMotorPin2, aSpeed);
}
void rightMotorForward(int aSpeed){
  motorControl(rightMotorPin1,rightMotorPin2, aSpeed);
}
void leftMotorBackward(int aSpeed){
  motorControl(leftMotorPin2,leftMotorPin1, aSpeed);
}
void rightMotorBackward(int aSpeed){
  motorControl(rightMotorPin2,rightMotorPin1, aSpeed);
}
void leftMotorStop(){
  motorControl(leftMotorPin1,leftMotorPin2, 0);
}
void rightMotorStop(){
  motorControl(rightMotorPin1,rightMotorPin2, 0);
}
void leftTurn(int aSpeed){
  motorControl(rightMotorPin1,rightMotorPin2, aSpeed);
  motorControl(leftMotorPin1,leftMotorPin2, 0);  
}
void rightTurn(int aSpeed){
  motorControl(rightMotorPin1,rightMotorPin2, 0);
  motorControl(leftMotorPin1,leftMotorPin2, aSpeed);  
}
void robotStop(){
  leftMotorStop();
  rightMotorStop(); 
}
int robotForward(int aSpeed, int driveTime){
  enum{STOP,START};
  static int state = STOP;
  int returnvalue = false;
  static MSTimer timer;

  switch(state){
    case(STOP):
      leftMotorForward(aSpeed);
      rightMotorForward(aSpeed);
      state = START;
      timer.set(driveTime);
      returnvalue = false;
    break;
    case(START):
      if(timer.done()){
        robotStop();
        state = STOP;
        returnvalue = true;
      }
    break;
  }
  return returnvalue;
}
int robotBackward(int aSpeed, int driveTime){
  enum{STOP,START};
  static int state = STOP;
  int returnvalue = false;
  static MSTimer timer;

  switch(state){
    case(STOP):
      leftMotorBackward(aSpeed);
      rightMotorBackward(aSpeed);
      state = START;
      timer.set(driveTime);
      returnvalue = false;
    break;
    case(START):
      if(timer.done()){
        robotStop();
        state = STOP;
        returnvalue = true;
      }
    break;
  }
  return returnvalue;
}

int robotLeft(int aSpeed, int turnTime){
  enum{STOP,START};
  static int state = STOP;
  int returnvalue = false;
  static MSTimer timer;

  switch(state){
    case(STOP):
      rightTurn(aSpeed);
      state = START;
      timer.set(turnTime);
      returnvalue = false;
    break;
    case(START):
      if(timer.done()){
        robotStop();
        state = STOP;
        returnvalue = true;
      }
    break;
  }
  return returnvalue;
}
int robotRight(int aSpeed, int turnTime){
  enum{STOP,START};
  static int state = STOP;
  int returnvalue = false;
  static MSTimer timer;

  switch(state){
    case(STOP):
      leftTurn(aSpeed);
      state = START;
      timer.set(turnTime);
      returnvalue = false;
    break;
    case(START):
      if(timer.done()){
        robotStop();
        state = STOP;
        returnvalue = true;
      }
    break;
  }
  return returnvalue;
}
int robotSpin(int aSpeed, int spinTime){
  enum{STOP, START};
  static int state = STOP;
  int returnvalue = false;
  static MSTimer timer;

  switch(state){
    case(STOP):
      rightMotorForward(aSpeed);
      leftMotorBackward(aSpeed);
      state = START;
      timer.set(spinTime);
      returnvalue = false;
    break;
    case(START):
      if(timer.done()){
        robotStop();
        state = STOP;
        returnvalue = true;
      }
    break;
  }
  return returnvalue;
}
