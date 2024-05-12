#define LED 2


void setup() {
  // Manuel Vergara:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED,LOW);
  delay(1000);

}
