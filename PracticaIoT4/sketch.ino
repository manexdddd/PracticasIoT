#define BOTON 4
int valor;

void setup() {
  // Manuel Vergara:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(BOTON,INPUT);

}

void loop() {
  
  valor = digitalRead(BOTON);
  Serial.println(valor);
  delay(500);
}
