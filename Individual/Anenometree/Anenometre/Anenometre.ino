// PALAS PINES [ 26 / 25 / 17 ] DIGITAL
// ANEMOMETRO PIN [ 4 ] ANALOGICO
// CLEAN BUFFER PIN [ 39 ] ANALOGICO

// #include <Servo.h>
#include <ESP32Servo.h>
#define __DEBUG__

int Clean_Buffer = 39; // CLEAN BOOFER VALOR "GROUND" = 0

// ANEMOMETRO
int anemometro = 4; // PIN DEL ANEMOMETRO " ANALOGICO "
// ANEMOMETRO

// OBJETOS SERVO
Servo servo1;
Servo servo2;
Servo servo3;
// OBJETOS SERVO

void setup()
{
  Serial.begin(9600);

  // SERVOMOTORES / PALAS
  servo1.attach(26);
  servo2.attach(25);
  servo3.attach(17);
  // SERVOMOTORES / PALAS
}

void loop()
{
  // ANEMOMETRO
  analogRead(Clean_Buffer); // PONEMOS EL BUFFER A VALOR DE 0
  // TENSION
  int valorAnalogico = analogRead(anemometro);     // LEE EL VALOR ANALOGICO ( 0 - 4095 )
  float voltaje = (valorAnalogico * 0.43) / 480.0; // CONVIERTE A VOLTAJE MEDIANTE ESTA FORMULA REFERENTE !! IMPORTANT !!

  Serial.print("Voltaje: "); // IMPRIMIMOS TEXTO
  Serial.println(voltaje);   // IMPRIMIMOS TEXTO
  // TENSIÓN

<<<<<<< HEAD
  // VELOCIDAD VIENTO
=======
  //VELOCIDAD VIENTO  
>>>>>>> cb39953b08645c85c6166ed1623923767d0af232
  float velocidadViento = (voltaje / 0.3) * 4.0; // SI 850 "TENSION" ES IGUAL A 5M/SEG ENTONCES... !! IMPORTANT !!

  Serial.print("Velocidad del viento: "); // IMPRIMIMOS TEXTO
  Serial.print(velocidadViento);          // IMPRIMIMOS TEXTO
  Serial.println(" m/s");                 // IMPRIMIMOS TEXTO
  // VELOCIDAD VIENTO
  // ANEMOMETRO

  // PALAS
  if (velocidadViento >= 7.1)
  {
    // VELOCIDAD DEL VIENTO SUPERA LOS 7 m/seg PONER A 90 GRADOS
    servo1.write(90);
    servo2.write(90);
    servo3.write(90);
  }
  else if (velocidadViento <= 3.1)
  {
    // VELOCIDAD DEL VIENTO INFERIOR A LOS 3 m/seg PONER A 90 GRADOS
    servo1.write(90);
    servo2.write(90);
    servo3.write(90);
  }
  else if (velocidadViento > 3.0 && velocidadViento < 7.0)
  {
    // VELOCIDAD DEL VIENTO ENTRE 3 m/seg & 7 m/seg PONER A 45 GRADOS
    servo1.write(45);
    servo2.write(45);
    servo3.write(45);
  }
  // PALAS

  delay(200);
}
