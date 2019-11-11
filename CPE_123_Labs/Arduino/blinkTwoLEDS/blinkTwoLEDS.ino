#include <CPutil.h>

// Define your pins

const int led1Pin = 3;
const int led2Pin = 4;
const int button1Pin = 5;

// Create your hardware

Led bLED(led1Pin);
Led gLED(led2Pin);
Button button1(button1Pin);

void setup() 
{
  
  // Set up serial monitor and print out program info
  Serial.begin(9600);
  setupMessage(__FILE__, "Blinks an LED");
  delay(500);
  
  // Initialize your hardware
  bLED.off();
  gLED.off();
}

void loop() 
{
   control();
}

void control()
{
  enum{START, BOTH_OFF, BLINK_BLUE, BLINK_GREEN};
  static int state = START;
  switch(state)
  {
    case(START):
    bLED.off();
    gLED.off();
    state = BOTH_OFF;
      break;
    case(BOTH_OFF):
    if(button1.wasPushed())
    {
      blueBlink();
      state = BLINK_BLUE;
    }
      break;
    case(BLINK_BLUE):
    blueBlink();
    if(button1.wasPushed())
    {
      greenBlink();
      bLED.off();
      state = BLINK_GREEN;
    }
      break;
    case(BLINK_GREEN):
    greenBlink();
    if(button1.wasPushed())
    {
      gLED.off();
      blueBlink();
      state = BLINK_BLUE;
    }
      break;
    default:
      break;
  }
}

void blueBlink()
{
  enum{BON, BOFF};
  static int state = BOFF;
  static MSTimer timer = 0;
  switch(state)
  {
    case(BOFF):
    if(timer.done())
    {
      bLED.on();
      timer.set(500);
      state = BON;
    }
      break;
    case(BON):
    if(timer.done())
    {
      bLED.off();
      timer.set(500);
      state = BOFF;
    }
      break;
  }
}

void greenBlink()
{
  enum{GON, GOFF};
  static int state = GOFF;
  static MSTimer timer = 0;
  switch(state)
  {
    case(GOFF):
    if(timer.done())
    {
      gLED.on();
      timer.set(1000);
      state = GON;
    }
      break;
    case(GON):
    if(timer.done())
    {
      gLED.off();
      timer.set(1000);
      state = GOFF;
    }
      break;
  }
}
