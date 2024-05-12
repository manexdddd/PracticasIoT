#define TRIG  19
#define ECHO  18

int tiempo, distancia;
void setup() {
  //Manuel Vergara
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);
}

void loop() {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  tiempo = pulseIn(ECHO, HIGH);

  distancia = tiempo / 58.2; 
  Serial.println("d = " + 
  String(distancia) + ", t = " + 
  String(tiempo) );
  delay(1000);
}