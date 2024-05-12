#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <ESP32Servo.h>

#define TRIG 19
#define ECHO 18
#define s1 23
#define LED 2

double tiempo, distancia;
Servo servo;
WiFiMulti wm;
String jwt;
bool sesion = false;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(TRIG, LOW);
  servo.attach(s1);
  servo.write(0);
  digitalWrite(LED, LOW);
  sesion = false;
  //Conexion a wifi
  Serial.println("MAC:" + WiFi.macAddress());
  wm.addAP("IOT", "A3o6HhLw");


}

void loop() {
  /*Servo*/
  if(wm.run() == WL_CONNECTED){
    digitalWrite(LED, HIGH);
    Serial.println("IP:");
    Serial.print(WiFi.localIP());

    if(!sesion){
      login();
    }else{
      //Enviar datos de sensores
      ultrasonico();
      registrar();
      
    }
  }else{
    digitalWrite(LED, LOW);
  }

  delay(1000);

}

void ultrasonico(){
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  tiempo=pulseIn(ECHO, HIGH);
  distancia = tiempo/58.4;
  Serial.println(distancia);
  /*Serial.println("d =  " + String(distancia)+ ", t = " + String(tiempo) );
  s.write(0);
  delay(500);
  s.write(90);
  delay(500);
  s.write(180);*/
}

void login(){
  HTTPClient http;
  http.begin("https://iotrest.itsch.kyared.com/login");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST("username=admin&password=123");
  if(httpCode == HTTP_CODE_OK){
    jwt = http.getString();
    Serial.println(jwt);
    sesion = true;
  }else{
    Serial.println("Error de conexion. Codigo: " + httpCode);
  }
  http.end();
}

void registrar(){
  HTTPClient http;
  http.begin("https://iotrest.itsch.kyared.com/sensors");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.addHeader("Authorization", "Bearer " + jwt);

  int httpCode = http.POST("name=mustangsTeam&type=ultrasonic&value=" + String(distancia));
  if(httpCode == HTTP_CODE_OK){
    String result = http.getString();
    Serial.println(result);
  }else{
    Serial.println("Error de conexion. Codigo: " + httpCode);
  }
  http.end();
}

void actualizar(int id){
  HTTPClient http;
  http.begin("https://iotrest.itsch.kyared.com/sensors" + String(id));
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.addHeader("Authorization", "Bearer " + jwt);

  int httpCode = http.PUT("name=mustangsTeam&type=ultrasonic&value=" + String(distancia));
  if(httpCode == HTTP_CODE_OK){
    String result = http.getString();
    Serial.println(result);
  }else{
    Serial.println("Error de conexion. Codigo: " + httpCode);
  }
  http.end();
}