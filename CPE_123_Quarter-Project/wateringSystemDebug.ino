#include <CPutil.h>

// Define pins
const int moistureSensorPin = A0;
const int moistureSensorPowerPin = 7;
const int solenoidPin = 8;

void setup()
{
  Serial.begin(9600);
  
  moistureSensorPowerPinSetup();
  solenoidPinSetup();

  delay(1000);
}

void loop()
{
  controlWateringSystem();
}

void controlWateringSystem()
{
  printMoistureSensor();
  controlSolenoid();
  delay(1000);
}

void controlSolenoid()
{
  static int state = 0;
  if(Serial.available())
  {
    state = Serial.parseInt();
    switch(state)
    {
      case(1):
        digitalWrite(solenoidPin, LOW);
        Serial.println("Enough water. Turning off system...");
      case(3):
        digitalWrite(solenoidPin, HIGH);
        Serial.println("Turning on system...");
      break;
      case(4):
        digitalWrite(solenoidPin, LOW);
        Serial.println("Turning off system...");
      break;
      default:
        digitalWrite(solenoidPin, LOW);
        Serial.println("No signal detected. Turning off system...");
      break;
    }
  }
}

void printMoistureSensor()
{
  int moistureThreshold = 500;
  if(readMoistureSensor() < moistureThreshold)
  {
    Serial.println(0);
  }
  else
  {
    Serial.println(1);
  }
}

int readMoistureSensor()
{
  int moistureValue = 0;
  digitalWrite(moistureSensorPowerPin, HIGH);
  delay(10);
  moistureValue = analogRead(moistureSensorPin);
  digitalWrite(moistureSensorPowerPin, LOW);
  return moistureValue;
}

void moistureSensorPowerPinSetup()
{
  pinMode(moistureSensorPowerPin, OUTPUT);
  digitalWrite(moistureSensorPowerPin, LOW);
}

void solenoidPinSetup()
{
  pinMode(solenoidPin, OUTPUT);
  digitalWrite(solenoidPin, LOW);
}
