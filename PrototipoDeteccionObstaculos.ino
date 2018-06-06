#include <Servo.h>

const int EchoPin = 5;
const int TriggerPin = 6;
const int LedPin = 13;
const int pinServo = 10;
const int pulsoMin = 680;
const int pulsoMax = 2550;
const int enableH = 3;
const int in1H = 8;
const int in2H = 7;
int tiempo = 20;
int valor, angulo;
int i = 1;
Servo miServo;

void setup() {
  miServo.attach(pinServo, pulsoMin, pulsoMax);
  miServo.write(83);
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(enableH, OUTPUT);
  pinMode(in1H, OUTPUT);
  pinMode(in2H, OUTPUT);

}

void loop() {
  adelante(255);
  int cm = ping(TriggerPin, EchoPin);                  //Llamar a la función ping para hacer lectura del sensor de ultrasonido
  Serial.print("Distancia: ");
  Serial.println(cm);


  if (cm < 70) {
    adelante(150);
    miServo.write(110);
    delay(1600);
    int cm = ping(TriggerPin, EchoPin);
    if (cm < 15) {
      parar();
      miServo.write(60);
      delay(1200);
      digitalWrite(2, HIGH);
      atras(210);
      delay(2500);
    }
  }
  miServo.write(82);          // Alineado al centro
  digitalWrite(2, LOW);
}

void adelante(int a) {

  analogWrite(enableH, a);
  digitalWrite(in1H, HIGH);
  digitalWrite(in2H, LOW);
}

void atras(int a) {

  analogWrite(enableH, a);
  digitalWrite(in1H, LOW);
  digitalWrite(in2H, HIGH);
  
}

void parar() {

  analogWrite(enableH, 0);
  digitalWrite(in1H, LOW);
  digitalWrite(in2H, LOW);
  
}


int ping(int TriggerPin, int EchoPin) {
  long duration, distanceCm;
  digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  distanceCm = duration * 10 / 292 / 2;  //convertimos a distancia, en cm
  return distanceCm;
}
