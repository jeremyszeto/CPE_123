#include "CPutil.h"

int num = 0;
int maxNum = 0;
int count = 0;

void setup(){
  
  // Set up serial monitor and print out program info
  Serial.begin(9600);
  setupMessage(__FILE__, "Finds maximum value from 5 numbers");
  delay(500);
  
}

void loop(){
   findMaxNumber();
 
}

void findMax(){
  static int maxNumber = 1;
  static int numberCount = 0;
  int nextNumber = 0;
  if(Serial.available()){
    nextNumber = Serial.parseInt();
    numberCount = numberCount + 1;
    if(nextNumber > maxNumber){
      maxNumber = nextNumber;
      if(numberCount == 5){
       print2("The max is: ", maxNumber);
      }
    }
  }
}

void findMaxNumber(){
  while(count <= 5){
    if(Serial.available()){
      num = Serial.parseInt();
      if (num > maxNum){
        maxNum = num;
      }
      count = count + 1;
    }
  }
  Serial.println(maxNum);
  count = 0;
  maxNum = 0;
}
