// https://bpb-ap-se2.wpmucdn.com/blogs.auckland.ac.nz/dist/9/698/files/2021/08/2_Pinout_D1_R32.png

// PALAS PINES [ 26 / 25 / 17 ] DIGITAL
// ANEMOMETRO PIN [ 4 ] ANALOGICO
// CLEAN BUFFER PIN [ 39 ] ANALOGICO

// #include <Servo.h>
#include <ESP32Servo.h>
#define __DEBUG__

int Clean_Buffer = 39; // CLEAN BOOFER VALOR "GROUND" = 0

// ANEMOMETRO
int Anemometro = 4; // PIN DEL ANEMOMETRO " ANALOGICO "
// ANEMOMETRO

// OBJETOS SERVO
Servo SPala1;
Servo SPala2;
Servo SPala3;
// OBJETOS SERVO

void setup()
{
  Serial.begin(9600);

  // SERVOMOTORES / PALAS
  SPala1.attach(26);
  SPala2.attach(25);
  SPala3.attach(17);
  // SERVOMOTORES / PALAS
}

void loop()
{
  // ANEMOMETRO
  analogRead(Clean_Buffer); // PONEMOS EL BUFFER A VALOR DE 0
  // TENSION
  int valorAnalogico = analogRead(Anemometro);     // LEE EL VALOR ANALOGICO ( 0 - 4095 )
  float voltaje = (valorAnalogico * 0.43) / 480.0; // CONVIERTE A VOLTAJE MEDIANTE ESTA FORMULA REFERENTE !! IMPORTANT !!

  Serial.print("Voltaje: "); // IMPRIMIMOS TEXTO
  Serial.println(voltaje);   // IMPRIMIMOS TEXTO
  // TENSIÓN

  // VELOCIDAD VIENTO
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
    SPala1.write(90);
    SPala2.write(90);
    SPala3.write(90);
  }
  else if (velocidadViento <= 3.1)
  {
    // VELOCIDAD DEL VIENTO INFERIOR A LOS 3 m/seg PONER A 90 GRADOS
    SPala1.write(90);
    SPala2.write(90);
    SPala3.write(90);
  }
  else if (velocidadViento > 3.0 && velocidadViento < 7.0)
  {
    // VELOCIDAD DEL VIENTO ENTRE 3 m/seg & 7 m/seg PONER A 45 GRADOS
    SPala1.write(45);
    SPala2.write(45);
    SPala3.write(45);
  }
  // PALAS

  delay(200);
}
