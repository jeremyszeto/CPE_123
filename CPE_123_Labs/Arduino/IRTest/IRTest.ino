#include <CPutil.h>

const int leftIR = A2;
const int rightIR = A4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  
}

void loop() {
  Serial.println(analogRead(leftIR));
  delay(500);
  //Serial.println(analogRead(rightIR));
  //delay(500);
}
