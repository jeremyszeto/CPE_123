#include <CPutil.h>

// Jeremy Szeto Team 9
// 3-6 PM section

// Define your pins

const int gLed1Pin = 3;
const int yLed1Pin = 4;
const int rLed1Pin = 5;
const int gLed2Pin = 6;
const int yLed2Pin = 7;
const int rLed2Pin = 8;

const int buttonPin = 9;

// Create your hardware

Led gLED1(gLed1Pin);
Led gLED2(gLed2Pin);
Led yLED1(yLed1Pin);
Led yLED2(yLed2Pin);
Led rLED1(rLed1Pin);
Led rLED2(rLed2Pin);

Button button(buttonPin);

void setup()
{
  Serial.begin(9600);
  setupMessage(__FILE__, "Press the button...");
  delay(500);

  // Initialize your hardware

  gLED1.on();
  gLED2.off();
  yLED1.off();
  yLED2.off();
  rLED1.off();
  rLED2.on();
}

void loop()
{
  bigStreetLight();
}

void bigStreetLight()
{
  enum {GREEN, YELLOW, RED, TRANSITION};
  static int state = GREEN;
  static MSTimer timer = 0;
  switch (state)
  {
    case (GREEN):
      gLED1.on();
      yLED1.off();
      rLED1.off();
      timer.set(4000);
      state = YELLOW;
      break;

    case (YELLOW):
      if (button.wasPushed() && timer.done())
      {
        gLED1.off();
        yLED1.on();
        timer.set(1000);
        state = RED;
      }
      break;
      
    case (RED):
      if (timer.done())
      {
        yLED1.off();
        rLED1.on();
        state = TRANSITION;
      }
      break;
      
    case (TRANSITION):
        if(smallStreetLight() == true)
        {
          state = GREEN;
        }
        break;
  }
}

int smallStreetLight()
{
  enum {GREEN, YELLOW, RED};
  static int state = GREEN;
  static MSTimer timer = 0;
  static int returnValue = false;
  switch (state)
  {
    case (GREEN):
      if (timer.done())
      {
        rLED2.off();
        gLED2.on();
        timer.set(2000);
        state = YELLOW;
        returnValue = false;
      }
      break;

    case (YELLOW):
      if (timer.done())
      {
        gLED2.off();
        yLED2.on();
        timer.set(1000);
        state = RED;
        returnValue = false;
      }
      break;

    case (RED):
      if (timer.done())
      {
        yLED2.off();
        rLED2.on();
        timer.set(1000);
        state = GREEN;
        returnValue = true;
      }
      break;
  }
  return returnValue;
}
