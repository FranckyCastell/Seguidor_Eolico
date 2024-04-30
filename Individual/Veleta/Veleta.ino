//https://bpb-ap-se2.wpmucdn.com/blogs.auckland.ac.nz/dist/9/698/files/2021/08/2_Pinout_D1_R32.png

// PITCH PIN [ 16 ] DIGITAL
// VELETA PIN [ 34 ] ANALOGICO
// CLEAN BUFFER PIN [ 4 ] ANALOGICO

#define __DEBUG__
#include <ESP32Servo.h>

Servo SPitch;         // SERVOMOTOR PITCH
int Angulo_Servo = 0; // ANGULO DEL SERVOMOTOR

int Clean_Buffer = 39;  // CLEAN BUFFER
const int Veleta = 34;  // PIN VELETA
float Valor_Veleta = 0; // VALOR VELETA ANALOGICO

void setup()
{
  Serial.begin(9600); // INICIAMOS COMUNICACION SERIAL
  SPitch.attach(16);  // DEFINIMOS SERVOMOTOR PIN 25 ( PITCH )
}

void loop()
{
  analogRead(Clean_Buffer);          // PONEMOS EL BUFFER A VALOR DE 0
  Valor_Veleta = analogRead(Veleta); // LEEMOS VALOR DEL POTENCIOMETRO "VELETA" ANALOGICO

  Serial.print("Valor Analogico: ");
  Serial.println(Valor_Veleta);

  Serial.print("DIRECCION VIENTO: ");

  // CALCULAMOS DIRECCION DE DONDE VIENE EL VIENTOS
  if ((Valor_Veleta >= 3839.1) || (Valor_Veleta <= 255.9))
  {
    Serial.println("NORTE");
  }
  else if ((Valor_Veleta >= 256) && (Valor_Veleta <= 767.8))
  {
    Serial.println("NORTE ESTE");
  }
  else if ((Valor_Veleta >= 767.9) && (Valor_Veleta <= 1279.7))
  {
    Serial.println("ESTE");
  }
  else if ((Valor_Veleta >= 1279.8) && (Valor_Veleta <= 1791.5))
  {
    Serial.println("SUD ESTE");
  }
  else if ((Valor_Veleta >= 1791.6) && (Valor_Veleta <= 2303.4))
  {
    Serial.println("SUD");
  }
  else if ((Valor_Veleta >= 2303.5) && (Valor_Veleta <= 2815.3))
  {
    Serial.println("SUD OESTE");
  }
  else if ((Valor_Veleta >= 2815.4) && (Valor_Veleta <= 3327.2))
  {
    Serial.println("OESTE");
  }
  else if ((Valor_Veleta >= 3327.3) && (Valor_Veleta <= 3839.0))
  {
    Serial.println("NORTE OESTE");
  }

  // Mapea el valor analógico a un rango de 0-360 grados para el servomotor
  Angulo_Servo = map(Valor_Veleta, 0, 4095, 0, 360);

  // MOVEMOS SERVOMOTOR AL ANGULO CORRESPONDIENTE
  SPitch.write(Angulo_Servo);

  // IMPRIMIMOS EL ÁNGULO DEL SERVOMOTOR
  Serial.print("ANGULO SERVOMOTOR: ");
  Serial.println(Angulo_Servo);

  delay(500);
}
