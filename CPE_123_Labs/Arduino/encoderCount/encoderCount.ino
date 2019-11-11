#include <CPutil.h>

// Encoder State Machine testing


// Put your pins here 
const int encoderPin1 = 2;
const int encoderPin2 = 3;


void setup() {
  // put your setup code here, to run once:

  // Setup serial monitor
  Serial.begin(9600);
  setupMessage(__FILE__, "Encoder Count Test");
  
  // configure the encoder pin 
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);
}

void loop() 
{
	processEncoder(); 
}

void processEncoder()
{
	static MSTimer aTimer(1500);
	unsigned long count = 0;
  unsigned long count2 = 0;
	
	count = encoderCount(count);
  count2 = encoderCount2(count);
		
	if (aTimer.done())
	{
		aTimer.set(1500);
		print2("Current Count: ", count + count2);
	}
}

unsigned long encoderCount(int resetFlag)
{ 
  int pinValue = 0;
 
  pinValue = digitalRead(encoderPin1);
  
  // Put your encoder state machine here
  enum{EHIGH, ELOW};
  static int state = EHIGH;
  static int count = 0;
  if(resetFlag == false)
  {
    switch(state)
    {
      case(EHIGH):
        if(pinValue == ELOW)
        {
          count++;
          state = ELOW;
        }
      break;
      case(ELOW):
        if(pinValue == EHIGH)
        {
          count++;
          state = EHIGH;
        }
      break;
    }
  }
  
  // put your return here
  return count;
}

unsigned long encoderCount2(int resetFlag)
{ 
  int pinValue = 0;
 
  pinValue = digitalRead(encoderPin2);
  
  // Put your encoder state machine here
  enum{EHIGH, ELOW};
  static int state = EHIGH;
  static int count = 0;
  if(resetFlag == false)
  {
    switch(state)
    {
      case(EHIGH):
        if(pinValue == ELOW)
        {
          count++;
          state = ELOW;
        }
      break;
      case(ELOW):
        if(pinValue == EHIGH)
        {
          count++;
          state = EHIGH;
        }
      break;
    }
  }
  
  // put your return here
  return count;
}
