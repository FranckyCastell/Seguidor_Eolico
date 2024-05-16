// https://bpb-ap-se2.wpmucdn.com/blogs.auckland.ac.nz/dist/9/698/files/2021/08/2_Pinout_D1_R32.png

// PALAS PINES [ 26 / 25 / 17 ] DIGITAL
// ANEMOMETRO PIN [ 4 ] ANALOGICO
// CLEAN BUFFER PIN [ 39 ] ANALOGICO

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

int Clean_Buffer = 39;  // CLEAN BOOFER VALOR "GROUND" = 0

// ANEMOMETRO
int Anemometro = 4;                 // PIN DEL ANEMOMETRO " ANALOGICO "
const float margenError = 0.9;      // Margen de ±0.9 m/s
float velocidadVientoAnterior = 0;  // Almacenar la última velocidad del viento que causó un cambio en las palas
// ANEMOMETRO

// OBJETOS SERVO
Servo SPala1;
Servo SPala2;
Servo SPala3;
// OBJETOS SERVO

void setup() {

// INICIAMOS PANTALLA OLED
#ifdef __DEBUG__
  Serial.begin(9600);

  // SERVOMOTORES / PALAS
  SPala1.attach(26);
  SPala2.attach(25);
  SPala3.attach(17);

  SPala1.write(0);
  SPala2.write(0);
  SPala3.write(0);
  // SERVOMOTORES / PALAS

  Serial.println("~ INICIANDO PANTALLA OLED ~");
#endif

  // INICIAMOS PANTALLA OLED EN LA DIRECCIÓN 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
#ifdef __DEBUG__
    Serial.println("NO SE A ENCONTRADO PANTALLA OLED");
#endif
    while (true)
      ;
  }
  // INICIAMOS PANTALLA OLED
}

void loop() {

  // OLED CONSTANTS
  display.clearDisplay();               // BORRAMOS CONTENIDO DE LA PANTALLA OLED
  display.setTextSize(1);               // DEFINIMOS TAMAÑO DEL TEXTO QUE SE VA A MOSTRAR EL 1 ES EL TAMAÑO MINIMO
  display.setTextColor(SSD1306_WHITE);  // COLOR DEL TEXTO
  // OLED CONSTANTS

  // ANEMOMETRO
  analogRead(Clean_Buffer);  // PONEMOS EL BUFFER A VALOR DE 0
  // TENSION
  int valorAnalogico = analogRead(Anemometro);      // LEE EL VALOR ANALOGICO ( 0 - 4095 )
  float voltaje = (valorAnalogico * 0.43) / 480.0;  // CONVIERTE A VOLTAJE MEDIANTE ESTA FORMULA REFERENTE !! IMPORTANT !!

  Serial.print("Voltaje: ");  // IMPRIMIMOS TEXTO
  Serial.println(voltaje);    // IMPRIMIMOS TEXTO
  // TENSIÓN

  // VELOCIDAD VIENTO
  float velocidadViento = (voltaje / 0.3) * 4.0;  // SI 850 "TENSION" ES IGUAL A 5M/SEG ENTONCES... !! IMPORTANT !!

  Serial.print("Velocidad del viento: ");  // IMPRIMIMOS TEXTO
  Serial.print(velocidadViento);           // IMPRIMIMOS TEXTO
  Serial.println(" m/s");                  // IMPRIMIMOS TEXTO7

  // OLED LOOP
  display.setCursor(25, 10);       // MOVEMOS EL CURSOR EN LA POSICION ( 25, 10 ) DE LA PANTALLA OLED | COLUMNA, FILA
  display.print("~~ KALAMAR ~~");  // IMPRIMIMOS TEXTO

  display.setCursor(10, 30);    // MOVEMOS EL CURSOR EN LA POSICION ( 20, 30 ) DE LA PANTALLA OLED | COLUMNA, FILA
  display.print("Voltaje:  ");  // IMPRIMIMOS TEXTO
  display.print(voltaje);       // IMPRIMIMOS EL ACIMUT A LA QUE SE ENCUENTRA EL SERVO MOTOR EN ESTE MOMENTO
  display.print(" V");

  display.setCursor(10, 50);       // MOVEMOS EL CURSOR EN LA POSICION ( 20, 30 ) DE LA PANTALLA OLED | COLUMNA, FILA
  display.print("Vel Vent:  ");    // IMPRIMIMOS TEXTO
  display.print(velocidadViento);  // IMPRIMIMOS EL ACIMUT A LA QUE SE ENCUENTRA EL SERVO MOTOR EN ESTE MOMENTO
  display.print(" m/s");           // IMPRIMIMOS TEXTO

  display.display();  // ACTUALIZAMOS LA PANTALLA CON LOS DATOS ANTERIORES
  // OLED LOOP

  // ANEMOMETRO

  // PALAS
  if (abs(velocidadViento - velocidadVientoAnterior) > margenError)  // SI LA VELOCIDAD DEL VIENTO ACTUAL - LA VELOCIDAD DEL VIENTO ANTERIOR NO HAY UN MARGEN SUPERIOR A 0.4 QUE NO HAGA NADA
  {
    if (velocidadViento >= 3.1)  // SI LA VELOCIDAD ES IGUAL O SUPERIOR A 3.1 ENTRE EN ESTE CONDICIONAL
    {

      for (int angulo = 0; angulo <= 60; angulo++) {
        SPala1.write(angulo);
        SPala2.write(angulo);
        SPala3.write(angulo);
        delay(50);
      }
    } else if (velocidadViento <= 1.4)  // SI LA VELOCIDAD ES MENOR O IGUAL A 1.4 ENTRE EN ESTE CONDICIONAL
    {

      for (int angulo = 0; angulo <= 60; angulo++) {
        SPala1.write(angulo);
        SPala2.write(angulo);
        SPala3.write(angulo);
        delay(50);
      }
    } else if (velocidadViento > 1.5 && velocidadViento < 3.0)  // SI LA VELOCIDAD ES MAYOR A 1.5 & MENOR A 3.0 ENTRE EN ESTE CONDICIONAL
    {

      for (int angulo = 60; angulo >= 0; angulo--) {
        SPala1.write(angulo);
        SPala2.write(angulo);
        SPala3.write(angulo);
        delay(50);
      }
    }
    velocidadVientoAnterior = velocidadViento;  // DEFINIMOS LA VELOCIDAD ANTERIOR A LA VELOCIDAD DEL VIENTO ACTUAL
  }
  // PALAS
  delay(200);
}
