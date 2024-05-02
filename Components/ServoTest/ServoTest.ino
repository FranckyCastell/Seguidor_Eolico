#define __DEBUG__
#include <ESP32Servo.h>

Servo miServo;

void setup()
{
    miServo.attach(14);
}

void loop()
{
    for (int pos = 0; pos <= 180; pos += 1)
    {
        miServo.write(pos);
        delay(150);
    }
    delay(1000);

    for (int pos = 180; pos >= 0; pos -= 1)
    {
        miServo.write(pos);
        delay(150);
    }
    delay(1000);
}
