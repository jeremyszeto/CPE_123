#include <CPutil.h>

// Define your pins

const int redLedPin = 2;
const int yellowLedPin = 3;
const int greenLedPin = 4;
const int buttonPin = 5;

// Create your hardware

Led redLed(redLedPin);
Led yellowLed(yellowLedPin);
Led greenLed(greenLedPin);
Button myButton(buttonPin);
MSTimer ledTimer;

void setup(){
  
  // Set up serial monitor and print out program info
  Serial.begin(9600);
  setupMessage(__FILE__, "Stoplight");
  delay(500);
  
  // Initialize your hardware
  redLed.on();
  yellowLed.off();
  greenLed.on();

}

void loop(){
  // put your main code here, to run repeatedly:

   light();
 
}

void light(){
  redLed.on();
  if(myButton.wasPushed()){
    Serial.println("Turning on green");
    greenLed.on();
    redLed.off();
    ledTimer.set(3000);
    while(ledTimer.done() != true){}
    Serial.println("Turning on yellow");
    yellowLed.on();
    greenLed.off();
    ledTimer.set(1000);
    while(ledTimer.done() != true){}
    Serial.println("Turning on red");
    redLed.on();
    yellowLed.off();
  }
}
