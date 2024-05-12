#define LED 12
void setup() {
  pinMode(LED,OUTPUT);

}

void loop() {
  // Manuel Vergara:
 digitalWrite(LED,HIGH);
 delay(1000);
 digitalWrite(LED,LOW);
  delay(1000);
}
