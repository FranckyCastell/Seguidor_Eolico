// Conexión: Potenciómetro conectado al pin analógico A0
int Clean_Buffer = 4; // CLEAN BOOFER VALOR "GROUND" = 0

void setup() {
  Serial.begin(9600); // Inicializar la comunicación serial
}

void loop() {
  analogRead(Clean_Buffer); // PONEMOS EL BUFFER A VALOR DE 0

  int pin_39 = analogRead(39); // Leer el valor del potenciómetro
  Serial.print("VALOR DEL PIN 39: ");
  Serial.println(pin_39); // Mostrar el valor por pantalla

  analogRead(Clean_Buffer); // PONEMOS EL BUFFER A VALOR DE 0
  int pin_38 = analogRead(38); // Leer el valor del potenciómetro
  Serial.print("VALOR DEL PIN 38: ");
  Serial.println(pin_38); // Mostrar el valor por pantalla

  analogRead(Clean_Buffer); // PONEMOS EL BUFFER A VALOR DE 0
  int pin_34 = analogRead(34); // Leer el valor del potenciómetro
  Serial.print("VALOR DEL PIN 34: ");
  Serial.println(pin_34); // Mostrar el valor por pantalla

  analogRead(Clean_Buffer); // PONEMOS EL BUFFER A VALOR DE 0
  int pin_36 = analogRead(36); // Leer el valor del potenciómetro
  Serial.print("VALOR DEL PIN 36: ");
  Serial.println(pin_36); // Mostrar el valor por pantalla

  // analogRead(Clean_Buffer); // PONEMOS EL BUFFER A VALOR DE 0
  // int pin_4 = analogRead(4); // Leer el valor del potenciómetro
  // Serial.print("VALOR DEL PIN 4: ");
  // Serial.println(pin_4); // Mostrar el valor por pantalla

  analogRead(Clean_Buffer); // PONEMOS EL BUFFER A VALOR DE 0
  int pin_2 = analogRead(2); // Leer el valor del potenciómetro
  Serial.print("VALOR DEL PIN 2: ");
  Serial.println(pin_2); // Mostrar el valor por pantalla

  delay(500); // Esperar 1 segundo antes de leer nuevamente
}
