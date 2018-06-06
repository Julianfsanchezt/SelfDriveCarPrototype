#include <Servo.h>

Servo miServo;

const int pinServo = 10;
const int pulsoMin = 680;
const int pulsoMax = 2550;
int tiempo = 20;
int valor, angulo;

void setup() {
  Serial.begin(115200);
  miServo.attach(pinServo, pulsoMin, pulsoMax);
  miServo.write(86);
  delay(2000);

}

void loop() {
//  while (Serial.available() > 0) {
//    valor = Serial.parseInt();
//    angulo = map(valor, 65, 105, 65, 105);

    for(int x = 60; x <106; x++ ){
     
    miServo.write(x);
    delay(tiempo); 
    }
    delay(2000);
    for(int x = 105; x >59; x-- ){
     
    miServo.write(x);
    delay(tiempo); 
    }
    delay(2000);
    //delay(20);
   // }

}
