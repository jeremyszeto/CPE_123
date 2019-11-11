#include <CPutil.h>

// Define your pins
const int aLedPin = 3;
const int myButtonPin = 4;
// Create your hardware
Led aLed(aLedPin);
Button myButton(myButtonPin);

void setup() 
{
  
	// Set up serial monitor and print out program info
	Serial.begin(9600);
	setupMessage(__FILE__, "Put a start message here");
	delay(500); 
	
	// Initialize your hardware
	// e.g. redLed.off();

  //aLed.on();
}

void loop() 
{
	// Call your control function(s) here 
	blinker();
}

void blinker(){
  static int buttonPushed = 0;
  int flashes = 0;
  static MSTimer ledTimer;
  if(myButton.wasPushed()){
    buttonPushed = buttonPushed + 1;
    while(buttonPushed != flashes){
      aLed.on();
      ledTimer.set(500);
      while(ledTimer.done() == false){}
      aLed.off();
      ledTimer.set(500);
      while(ledTimer.done() == false){}
      flashes = flashes + 1;
    }
  }
}
