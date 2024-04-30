// https://bpb-ap-se2.wpmucdn.com/blogs.auckland.ac.nz/dist/9/698/files/2021/08/2_Pinout_D1_R32.png

// PITCH PIN [ 16 ] DIGITAL
// VELETA PIN [ 34 ] ANALOGICO
// CLEAN BUFFER PIN [ 4 ] ANALOGICO

#define __DEBUG__
#include <ESP32Servo.h>

Servo SPitch; // SERVOMOTOR PITCH

int Clean_Buffer = 39;  // CLEAN BUFFER
const int Veleta = 34;  // PIN VELETA
float Valor_Veleta = 0; // VALOR VELETA ANALOGICO

void setup()
{
    Serial.begin(9600); // INICIAMOS COMUNICACION SERIAL
    SPitch.attach(16);  // DEFINIMOS SERVOMOTOR PIN 16 ( PITCH )
}

void loop()
{
    analogRead(Clean_Buffer);          // PONEMOS EL BUFFER A VALOR DE 0
    Valor_Veleta = analogRead(Veleta); // LEEMOS VALOR DEL POTENCIOMETRO "VELETA" ANALOGICO

    Serial.print("Valor Analogico: ");
    Serial.println(Valor_Veleta);

    Serial.print("DIRECCION VIENTO: ");

    // CALCULAMOS DIRECCION DE DONDE VIENE EL VIENTO
    if ((Valor_Veleta >= 3839.1) || (Valor_Veleta <= 255.9))
    {
        Serial.println("NORTE");
        SPitch.writeMicroseconds(1500); // Detenemos el servomotor
    }
    else if ((Valor_Veleta >= 256) && (Valor_Veleta <= 767.8))
    {
        Serial.println("NORTE ESTE");
        SPitch.writeMicroseconds(1600); // Movemos el servomotor lentamente en una dirección
    }
    else if ((Valor_Veleta >= 767.9) && (Valor_Veleta <= 1279.7))
    {
        Serial.println("ESTE");
        SPitch.writeMicroseconds(1700); // Movemos el servomotor más rápido en una dirección
    }
    else if ((Valor_Veleta >= 1279.8) && (Valor_Veleta <= 1791.5))
    {
        Serial.println("SUD ESTE");
        SPitch.writeMicroseconds(1800); // Movemos el servomotor aún más rápido en una dirección
    }
    else if ((Valor_Veleta >= 1791.6) && (Valor_Veleta <= 2303.4))
    {
        Serial.println("SUD");
        SPitch.writeMicroseconds(1900); // Movemos el servomotor a casi la máxima velocidad en una dirección
    }
    else if ((Valor_Veleta >= 2303.5) && (Valor_Veleta <= 2815.3))
    {
        Serial.println("SUD OESTE");
        SPitch.writeMicroseconds(1400); // Movemos el servomotor lentamente en la dirección opuesta
    }
    else if ((Valor_Veleta >= 2815.4) && (Valor_Veleta <= 3327.2))
    {
        Serial.println("OESTE");
        SPitch.writeMicroseconds(1300); // Movemos el servomotor más rápido en la dirección opuesta
    }
    else if ((Valor_Veleta >= 3327.3) && (Valor_Veleta <= 3839.0))
    {
        Serial.println("NORTE OESTE");
        SPitch.writeMicroseconds(1200); // Movemos el servomotor aún más rápido en la dirección opuesta
    }

    delay(500);
}
