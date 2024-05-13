#define __DEBUG__
#include <ESP32Servo.h>

Servo miServo;

void setup() {
  Serial.begin(9600);

  miServo.attach(14);
}

void loop() {
  for (int pos = 0; pos <= 360; pos += 1) {
    miServo.write(pos);
    delay(5);
    Serial.print("Posicion: ");
    Serial.println(pos);
  }
  delay(1000);

  for (int pos = 360; pos >= 0; pos -= 1) {
    miServo.write(pos);
    delay(5);
    Serial.print("Posicion: ");
    Serial.println(pos);
  }
  delay(1000);
}
