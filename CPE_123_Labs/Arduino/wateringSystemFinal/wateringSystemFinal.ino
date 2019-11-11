// Define pins
const int moistureSensorPin = A0;
const int moistureSensorPowerPin = 7;
const int solenoidPin = 8;

/*
 * Send:
 *  0 - Need water
 *  1 - Sufficient water
 *  ------------------
 * Receive:
 *  3 - Open solenoid
 *  4 - Close solenoid
 */

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  
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
  if(Serial1.available())
  {
    state = Serial1.parseInt();
    switch(state)
    {
      case(3):
        digitalWrite(solenoidPin, HIGH);
        Serial.println("Turning on system...");
      break;
      case(4):
        digitalWrite(solenoidPin, LOW);
        Serial.println("Turning off system...");
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
    Serial1.println(0);
  }
  else
  {
    Serial.println(1);
    Serial1.println(1);
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
