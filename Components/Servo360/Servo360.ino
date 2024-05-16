#include <Servo.h>

Servo miServo;  // Crea un objeto servo para controlar un servomotor

void setup() {
  miServo.attach(9);  // El servomotor está conectado al pin 9
  // No es necesario inicializar el ángulo aquí, se asume que el servomotor ya está en la posición deseada
}

void loop() {
  for (int angulo = miServo.read(); angulo >= 0; angulo--) {  // Bucle desde la posición actual a 0 grados
    miServo.write(angulo);  // Mueve el servomotor al ángulo especificado
    delay(50);              // Espera 50 milisegundos antes del próximo grado
  }
  delay(1000);  // Espera un segundo cuando alcanza 0 grados
  // Aquí puedes agregar más código si necesitas que el servomotor haga algo después
}
