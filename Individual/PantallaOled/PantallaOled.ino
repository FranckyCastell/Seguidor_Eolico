// #include <Servo.h>
#include <ESP32Servo.h>
#define __DEBUG__
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// DECLARACIONES PARA LA PANTALLA OLED
#define ANCHO_PANTALLA 128
#define ALTO_PANTALLA 64
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);
// DECLARACIONES PARA LA PANTALLA OLED

void setup()
{

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
        Serial.println("NO SE A ENCONTRADO PANTALLA OLED");
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

    // OLED LOOP
    display.setCursor(25, 10);              // MOVEMOS EL CURSOR EN LA POSICION ( 25, 10 ) DE LA PANTALLA OLED | COLUMNA, FILA
    display.print("~~~ PANTALLA OLED ~~~"); // IMPRIMIMOS TEXTO

    display.display(); // ACTUALIZAMOS LA PANTALLA CON LOS DATOS ANTERIORES
    // OLED LOOP
}