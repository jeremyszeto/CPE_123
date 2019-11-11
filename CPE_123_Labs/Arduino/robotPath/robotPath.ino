#include <CPutil.h>

// Define your pins
// e.g. const int redLedPin = 38;
const int bLedPin = 5;
const int yLedPin = 3;
// Create your hardware
// e.g. Led redLed(redLedPin);
Led bLed(bLedPin);
Led yLed(yLedPin);
void setup() 
{
  
	// Set up serial monitor and print out program info
	Serial.begin(9600);
	setupMessage(__FILE__, "Put a start message here");
	delay(500); 
	
	// Initialize your hardware
	// e.g. redLed.off();

 
}

void loop() 
{
	// Call your control function(s) here 
  path();
	
}

void path(){
  static MSTimer aTimer;
  static int state = 1;
  if(aTimer.done()){
    if(state == 1){
      Serial.println("first straight");
      bLed.on();
      yLed.on();
      aTimer.set(3000);
      state = 2;
    }
    else if(state == 2){
      Serial.println("first right turn");
      yLed.off();
      aTimer.set(1000);
      state = 3;
    }
    else if(state == 3){
      Serial.println("second straight");
      yLed.on();
      aTimer.set(3000);
      state = 4;
    }
    else if(state == 4){
      Serial.println("first left turn");
      bLed.off();
      aTimer.set(1000);
      state = 5;
    }
    else if(state == 5){
      Serial.println("third straight");
      bLed.on();
      aTimer.set(3000);
      state = 6;
    }
    else if(state == 6){
      Serial.println("second left");
      bLed.off();
      aTimer.set(1000);
      state = 7;
    }
    else if(state == 7){
      Serial.println("fourth straight");
      bLed.on();
      aTimer.set(3000);
      state = 8;
    }
    else if(state == 8){
      Serial.println("second right");
      yLed.off();
      aTimer.set(1000);
      state = 9;
    }
    else if(state == 9){
      Serial.println("last straight");
      yLed.on();
      aTimer.set(3000);
      yLed.off();
      bLed.off();
    }
  }
}
