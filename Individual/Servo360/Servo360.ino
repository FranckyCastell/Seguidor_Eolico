// https://bpb-ap-se2.wpmucdn.com/blogs.auckland.ac.nz/dist/9/698/files/2021/08/2_Pinout_D1_R32.png

// #include <Servo.h>
#include <ESP32Servo.h>
#define __DEBUG__

Servo myservo;  // crea un objeto servo para controlar un servomotor

int pos = 0;    // variable para almacenar la posición del servo

void setup() {
  myservo.attach(14);  // el servo está conectado al pin 9
}

void loop() {
  // gira el servomotor en una dirección a velocidad completa
  myservo.writeMicroseconds(2000); // 2000 microsegundos para rotación completa en una dirección
  delay(1000);                      // espera un segundo
  // detiene el movimiento del servomotor
  myservo.writeMicroseconds(1500); // 1500 microsegundos para detener
  delay(1000);                      // espera un segundo
  // gira el servomotor en la dirección opuesta a velocidad completa
  myservo.writeMicroseconds(1000); // 1000 microsegundos para rotación completa en la dirección opuesta
  delay(1000);                      // espera un segundo
  // detiene el movimiento del servomotor
  myservo.writeMicroseconds(1500); // 1500 microsegundos para detener
  delay(1000);                      // espera un segundo
}
