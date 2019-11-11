#include<CPutil.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupMessage(__FILE__, "Motor Controller");
  delay(500);
  
  //print2("20cm:", calcDistance(20));
  //print2("10cm:", calcDistance(10));

  print2("90 deg:", calcAngle(90));
  print2("45 deg:", calcAngle(1));
}

void loop() {
  // put your main code here, to run repeatedly:

}

unsigned long calcAngle(int aAngle)
{
  unsigned long distance = 0;
  
  distance = 6.1507 * aAngle;

  return distance;
}

unsigned long calcDistance(int aDistance)
{
  unsigned long encoderCount = 0;
  
  encoderCount = (6.1507 * 360) * (aDistance / 20.42035224833366);
  
  return encoderCount;
}
