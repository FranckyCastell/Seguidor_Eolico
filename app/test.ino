#include <ESP32Servo.h>

Servo miServo;

void setup()
{
    Serial.begin(9600);
    miServo.attach(9); // PING DIGITAL 
}

void loop()
{
    for (int angulo = 0; angulo <= 180; angulo++)
    {
        miServo.write(angulo);
        delay(30);
        Serial.print("Ángulo: ");
        Serial.println(angulo);
    }

    delay(2000);

    for (int angulo = 180; angulo >= 0; angulo--)
    {
        miServo.write(angulo);
        delay(30);
        Serial.print("Ángulo: ");
        Serial.println(angulo);
    }

    delay(1000);
}
