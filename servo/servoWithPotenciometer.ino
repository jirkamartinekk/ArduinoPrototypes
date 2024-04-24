#include <Servo.h>

Servo rotor;
int servoPin = 3;
int analogPotenciometer = 0;
int servoPosition, servoPositionConverted;

void setup() {
  Serial.begin(9600);
  rotor.attach(servoPin);
  rotor.write(0);
  delay(1000);
  rotor.write(90);
  delay(1000);
  rotor.write(180);
  delay(1000);
  rotor.write(90);
  delay(1000);
  rotor.write(0);
}

void loop() {
  servoPosition = analogRead(analogPotenciometer);

  servoPositionConverted = map(servoPosition, 0, 1023, 0,160);  
  rotor.write(servoPositionConverted);

    Serial.print("Analog:");
    Serial.print(servoPosition);
    Serial.println();
    Serial.print("Angle:");
    Serial.print(servoPositionConverted);
    Serial.println();

  delay(10);
}
