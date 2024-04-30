// MAX 7 m/s BANDERA
// MIN 3 m/s BANDERA
// PINES ANALOGICOS -> CLEAN BUFFER [39] / VELETA [34] / ANEMOMETRO [4]  ((POR SI FALLA ALGUNO MAS [2] )

#define __DEBUG__
#include <ESP32Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// CLEAN BUFFER
int Clean_Buffer = 39; // CLEAN BOOFER VALOR "GROUND" = 0
// CLEAN BUFFER

// DECLARACIONES PARA LA PANTALLA OLED
#define ANCHO_PANTALLA 128
#define ALTO_PANTALLA 64
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);
// DECLARACIONES PARA LA PANTALLA OLED

// CREACION DE LOS SERVO MOTORES PARA CADA UNA DE LAS PALAS
Servo SPala1; // SERVO PARA LA PALA 1
Servo SPala2; // SERVO PARA LA PALA 2
Servo SPala3; // SERVO PARA LA PALA 3
// CREACION DE LOS SERVO MOTORES PARA CADA UNA DE LAS PALAS

// VARIABLES DEL ANEMOMETRO
int Anemometro = 4; // PIN DEL ANEMOMETRO " ANALOGICO "
// VARIABLES PARA EL ANEMOMETRO

// VARIABLES DE LA VELETA
Servo SPitch;           // SERVO PARA MOVER EL MOLINO HACIA EL VIENTO
int Potenciometro = 34; // PIN DEL POTENCIOMETRO " ANALOGICO "
int ValorPotenciometro; // VALOR DEL POTENCIOMETRO
int PosicionSPitch;     // POSICION DEL PITCH
// VARIABLES DE LA VELETA

void setup()
{
    SPitch.attach(25); // DEFINIMOS SERVOMOTOR PIN 25 ( PITCH )
    SPala1.attach(26); // DEFINIMOS SERVOMOTOR PIN 26 ( PALA1 )
    SPala2.attach(27); // DEFINIMOS SERVOMOTOR PIN 25 ( PALA2 )
    SPala3.attach(28); // DEFINIMOS SERVOMOTOR PIN 26 ( PALA3 )

// INICIAMOS PANTALLA OLED
#ifdef __DEBUG__
    Serial.begin(9600);
    delay(100);
    Serial.println("~ INICIANDO PANTALLA OLED ~");
#endif

    // INICIAMOS PANTALLA OLED EN LA DIRECCIÓN 0x3C
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
#ifdef __DEBUG__
        Serial.println("~ NO SE A ENCONTRADO PANTALLA OLED ~");
#endif
        while (true)
            ;
    }
    // INICIAMOS PANTALLA OLED
}

void loop()
{
    // OLED CONSTANTS
    display.clearDisplay();              // BORRAMOS CONTENIDO DE LA PANTALLA OLED
    display.setTextSize(1);              // DEFINIMOS TAMAÑO DEL TEXTO QUE SE VA A MOSTRAR EL 1 ES EL TAMAÑO MINIMO
    display.setTextColor(SSD1306_WHITE); // COLOR DEL TEXTO
    // OLED CONSTANTS

    // CLEAN BUFFER
    analogRead(Clean_Buffer); // PONEMOS EL BUFFER A VALOR DE 0
    // CLEAN BUFFER

    // SECCION ANEMOMETRO
    // TENSION
    int valorAnalogico = analogRead(Anemometro);     // LEE EL VALOR ANALOGICO ( 0 - 4095 )
    float voltaje = (valorAnalogico * 5.0) / 4095.0; // CONVIERTE A VOLTAJE MEDIANTE ESTA FORMULA REFERENTE (0 - 5V) - ( 0 - 4095 )

    Serial.print("Voltaje: "); // IMPRIMIMOS TEXTO
    Serial.println(voltaje);   // IMPRIMIMOS TEXTO
    // TENSIÓN

    // VELOCIDAD VIENTO
    float VelocidadViento = (valorAnalogico / 850.0) * 5.0; // SI 850 "TENSION" ES IGUAL A 5M/SEG ENTONCES...

    Serial.print("Velocidad del viento: "); // IMPRIMIMOS TEXTO
    Serial.print(VelocidadViento);          // IMPRIMIMOS TEXTO
    Serial.println(" m/s");                 // IMPRIMIMOS TEXTO
    // VELOCIDAD VIENTO
    //  SECCION ANEMOMETRO

    // SECCION VELETA
    ValorPotenciometro = analogRead(Potenciometro); // LEE EL VALOR DEL POTENCIOMETRO (VELETA)
 
    PosicionSPitch = map(ValorPotenciometro, 0, 4095, 0, 360); // MAPEA EL VALOR DEL POTENCIOMETRO AL RANGO DE ANGULOS DEL SERVO

    SPitch.write(PosicionSPitch); //  MUEVE EL SERVO A LA POSICION CALCULADA

    // IMPRIMIMOS LA POSICION ORDINAL
    if (PosicionSPitch >= 0 && PosicionSPitch < 45)
    {
        Serial.println("Norte");

        display.setCursor(20, 40);       // MOVEMOS EL CURSOR EN LA POSICION ( 20, 40 ) DE LA PANTALLA OLED | COLUMNA, FILA
        display.print("- DIRECCIO: NORTE"); // IMPRIMIMOS TEXTO
    }
    else if (PosicionSPitch >= 45 && PosicionSPitch < 135)
    {
        Serial.println("Este");

        display.setCursor(20, 40);       // MOVEMOS EL CURSOR EN LA POSICION ( 20, 40 ) DE LA PANTALLA OLED | COLUMNA, FILA
        display.print("- DIRECCIO: ESTE"); // IMPRIMIMOS TEXTO
    }
    else if (PosicionSPitch >= 135 && PosicionSPitch < 225)
    {
        Serial.println("Sur");

        display.setCursor(20, 40);       // MOVEMOS EL CURSOR EN LA POSICION ( 20, 40 ) DE LA PANTALLA OLED | COLUMNA, FILA
        display.print("- DIRECCIO: SUR"); // IMPRIMIMOS TEXTO
    }
    else if (PosicionSPitch >= 225 && PosicionSPitch < 315)
    {
        Serial.println("Oeste");

        display.setCursor(20, 40);       // MOVEMOS EL CURSOR EN LA POSICION ( 20, 40 ) DE LA PANTALLA OLED | COLUMNA, FILA
        display.print("- DIRECCIO: OESTE"); // IMPRIMIMOS TEXTO
    }
    else
    {
        Serial.println("Noroeste");

        display.setCursor(20, 40);       // MOVEMOS EL CURSOR EN LA POSICION ( 20, 40 ) DE LA PANTALLA OLED | COLUMNA, FILA
        display.print("- DIRECCIO: NOROESTE"); // IMPRIMIMOS TEXTO
    }
    // SECCION VELETA

    // SECCION PALAS
    if (VelocidadViento > 7) // SUPONEMOS QUE 25 ES UMBRAL VIENTO FUERTE
    {
        SPala1.write(0); // ANGULO MODO BANDERA
        SPala2.write(0);
        SPala3.write(0);
    }
    else if (VelocidadViento < 3)
    {                    // SUPONEMOS QUE 5 ES UMBRAL VIENTO FLOJO
        SPala1.write(0); // ANGULO MODO BANDERA
        SPala2.write(0);
        SPala3.write(0);
    }
    else
    {
        // VIENTO NORMAL
        SPala1.write(90); // ANGULO MODO NORMAL
        SPala2.write(90);
        SPala3.write(90);
    }
    // SECCION PALAS

    // OLED LOOP
    display.setCursor(25, 10);       // MOVEMOS EL CURSOR EN LA POSICION ( 25, 10 ) DE LA PANTALLA OLED | COLUMNA, FILA
    display.print("~~~ KALAMAR ~~~"); // IMPRIMIMOS TEXTO

    display.setCursor(20, 30);   // MOVEMOS EL CURSOR EN LA POSICION ( 20, 30 ) DE LA PANTALLA OLED | COLUMNA, FILA
    display.print("- VELOCITAT VENT:  "); // IMPRIMIMOS TEXTO
    display.print(VelocidadViento);       // IMPRIMIMOS EL ACIMUT A LA QUE SE ENCUENTRA EL SERVO MOTOR EN ESTE MOMENTO
    display.print(" m/seg"); // IMPRIMIMOS TEXTO

    display.display(); // ACTUALIZAMOS LA PANTALLA CON LOS DATOS ANTERIORES
    // OLED LOOP
}