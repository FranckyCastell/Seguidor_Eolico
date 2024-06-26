// https://bpb-ap-se2.wpmucdn.com/blogs.auckland.ac.nz/dist/9/698/files/2021/08/2_Pinout_D1_R32.png

// MAX 3.1 m/s BANDERA
// MIN 1.4 m/s BANDERA

// PALAS PINES [ 26 / 25 / 17 ] DIGITAL
// ANEMOMETRO PIN [ 4 ] ANALOGICO

// PITCH PIN [ 16 ] DIGITAL
// VELETA PIN [ 34 ] ANALOGICO

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

// ANEMOMETRO
int Anemometro = 4;                // PIN DEL ANEMOMETRO " ANALOGICO "
const float margenError = 0.9;     // Margen de ±0.9 m/s
float velocidadVientoAnterior = 0; // Almacenar la última velocidad del viento que causó un cambio en las palas
// ANEMOMETRO

// VARIABLES DE LA VELETA
Servo SPitch;         // SERVO PARA MOVER EL MOLINO HACIA EL VIENTO
int Angulo_Servo = 0; // ANGULO DEL SERVOMOTOR

int Veleta = 34;  // PIN DEL POTENCIOMETRO " ANALOGICO "
int Valor_Veleta; // VALOR DEL POTENCIOMETRO
// VARIABLES DE LA VELETA

void setup()
{
    SPitch.attach(16); // DEFINIMOS SERVOMOTOR PIN 25 ( PITCH )

    // SERVOMOTORES / PALAS
    SPala1.attach(26);
    SPala2.attach(25);
    SPala3.attach(17);

    SPala1.write(0);
    SPala2.write(0);
    SPala3.write(0);
    // SERVOMOTORES / PALAS

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

    // SECCION ANEMOMETRO
    // ANEMOMETRO
    analogRead(Clean_Buffer); // PONEMOS EL BUFFER A VALOR DE 0
    // TENSION
    int valorAnalogico = analogRead(Anemometro);     // LEE EL VALOR ANALOGICO ( 0 - 4095 )
    float voltaje = (valorAnalogico * 0.43) / 480.0; // CONVIERTE A VOLTAJE MEDIANTE ESTA FORMULA REFERENTE !! IMPORTANT !!

    Serial.print("Voltaje: "); // IMPRIMIMOS TEXTO
    Serial.println(voltaje);   // IMPRIMIMOS TEXTO
    // TENSIÓN

    // VELOCIDAD VIENTO
    float VelocidadViento = (voltaje / 0.3) * 4.0; // SI 850 "TENSION" ES IGUAL A 5M/SEG ENTONCES... !! IMPORTANT !!

    Serial.print("Velocidad del viento: "); // IMPRIMIMOS TEXTO
    Serial.print(VelocidadViento);          // IMPRIMIMOS TEXTO
    Serial.println(" m/s");                 // IMPRIMIMOS TEXTO
                                            // VELOCIDAD VIENTO

    const float margenError = 0.4;     // Margen de ±0.4 m/s
    float velocidadVientoAnterior = 0; // Almacenar la última velocidad del viento que causó un cambio en las palas

    // ANEMOMETRO
    // PALAS
    if (abs(VelocidadViento - velocidadVientoAnterior) > margenError) // SI LA VELOCIDAD DEL VIENTO ACTUAL - LA VELOCIDAD DEL VIENTO ANTERIOR NO HAY UN MARGEN SUPERIOR A 0.4 QUE NO HAGA NADA
    {
        if (VelocidadViento >= 3.1) // SI LA VELOCIDAD ES IGUAL O SUPERIOR A 3.1 ENTRE EN ESTE CONDICIONAL
        {

            for (int angulo = 0; angulo <= 60; angulo++)
            {
                SPala1.write(angulo);
                SPala2.write(angulo);
                SPala3.write(angulo);
                delay(50);
            }
        }
        else if (VelocidadViento <= 1.4) // SI LA VELOCIDAD ES MENOR O IGUAL A 1.4 ENTRE EN ESTE CONDICIONAL
        {

            for (int angulo = 0; angulo <= 60; angulo++)
            {
                SPala1.write(angulo);
                SPala2.write(angulo);
                SPala3.write(angulo);
                delay(50);
            }
        }
        else if (VelocidadViento > 1.5 && VelocidadViento < 3.0) // SI LA VELOCIDAD ES MAYOR A 1.5 & MENOR A 3.0 ENTRE EN ESTE CONDICIONAL
        {

            for (int angulo = 60; angulo >= 0; angulo--)
            {
                SPala1.write(angulo);
                SPala2.write(angulo);
                SPala3.write(angulo);
                delay(50);
            }
        }
        velocidadVientoAnterior = VelocidadViento; // DEFINIMOS LA VELOCIDAD ANTERIOR A LA VELOCIDAD DEL VIENTO ACTUAL
    }
    // PALAS
    // SECCION ANEMOMETRO

    // SECCION VELETA
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
    Angulo_Servo = map(Valor_Veleta, 0, 4095, 0, 255);

    // MOVEMOS SERVOMOTOR AL ANGULO CORRESPONDIENTE
    SPitch.write(Angulo_Servo);

    // IMPRIMIMOS EL ÁNGULO DEL SERVOMOTOR
    Serial.print("ANGULO SERVOMOTOR: ");
    Serial.println(Angulo_Servo);
    // SECCION VELETA

    // OLED LOOP
    display.setCursor(25, 10);        // MOVEMOS EL CURSOR EN LA POSICION ( 25, 10 ) DE LA PANTALLA OLED | COLUMNA, FILA
    display.print("~~~ KALAMAR ~~~"); // IMPRIMIMOS TEXTO

    display.setCursor(20, 30);            // MOVEMOS EL CURSOR EN LA POSICION ( 20, 30 ) DE LA PANTALLA OLED | COLUMNA, FILA
    display.print("- VELOCITAT VENT:  "); // IMPRIMIMOS TEXTO
    display.print(VelocidadViento);       // IMPRIMIMOS EL ACIMUT A LA QUE SE ENCUENTRA EL SERVO MOTOR EN ESTE MOMENTO
    display.print(" m/seg");              // IMPRIMIMOS TEXTO

    display.display(); // ACTUALIZAMOS LA PANTALLA CON LOS DATOS ANTERIORES
    // OLED LOOP
}