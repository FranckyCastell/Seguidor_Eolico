// PITCH PIN [ 16 ] DIGITAL
// VELETA PIN [ 34 ] ANALOGICO
// CLEAN BUFFER PIN [ 4 ] ANALOGICO

#define __DEBUG__
#include <ESP32Servo.h>

<<<<<<< HEAD
Servo SPitch;         // SERVOMOTOR PITCH
int Angulo_Servo = 0; // ANGULO DEL SERVOMOTOR

int Clean_Buffer = 39;  // CLEAN BUFFER
const int Veleta = 34;  // PIN VELETA
float Valor_Veleta = 0; // VALOR VELETA ANALOGICO

void setup()
{
  Serial.begin(9600); // INICIAMOS COMUNICACION SERIAL
  SPitch.attach(16);  // DEFINIMOS SERVOMOTOR PIN 25 ( PITCH )
=======
Servo SPitch;
int Angulo_Servo = 0; // Variable para el ángulo del servomotor

int Clean_Buffer = 39;
const int Veleta = 34;
float Valor_Veleta = 0;

void setup()
{
  Serial.begin(9600); // Inicia la comunicación serial
  SPitch.attach(25); // DEFINIMOS SERVOMOTOR PIN 25 ( HORIZONTAL )
>>>>>>> cb39953b08645c85c6166ed1623923767d0af232
}

void loop()
{
  analogRead(Clean_Buffer);          // PONEMOS EL BUFFER A VALOR DE 0
<<<<<<< HEAD
  Valor_Veleta = analogRead(Veleta); // LEEMOS VALOR DEL POTENCIOMETRO "VELETA" ANALOGICO
=======
  Valor_Veleta = analogRead(Veleta); // Lee el valor del potenciómetro
>>>>>>> cb39953b08645c85c6166ed1623923767d0af232

  Serial.print("Valor Analogico: ");
  Serial.println(Valor_Veleta);

  Serial.print("DIRECCION VIENTO: ");

<<<<<<< HEAD
  // CALCULAMOS DIRECCION DE DONDE VIENE EL VIENTOS
=======
  // Calcula la dirección basándose en el valor del potenciómetro
>>>>>>> cb39953b08645c85c6166ed1623923767d0af232
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

<<<<<<< HEAD
  // MOVEMOS SERVOMOTOR AL ANGULO CORRESPONDIENTE
  SPitch.write(Angulo_Servo);

  delay(500);
=======
  // Mueve el servomotor al ángulo correspondiente
  SPitch.write(Angulo_Servo);

  delay(500); // Espera un segundo antes de leer de nuevo
>>>>>>> cb39953b08645c85c6166ed1623923767d0af232
}
