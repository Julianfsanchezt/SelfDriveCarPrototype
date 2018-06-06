/*
  Ultrasonic Sensor HC-SR04 and Arduino Tutorial

  Crated by Dejan Nedelkovski,
  www.HowToMechatronics.com

*/
// defines pins numbers
const int trigPinR = 2;
const int echoPinR = 3;
const int trigPinF = 4;
const int echoPinF = 5;
const int trigPinL = 6;
const int echoPinL = 7;
const int tiempoGiro = 3500;
const int timepoEvasion = 2000;
long duration, distance, RightSensor, BackSensor, FrontSensor, LeftSensor;

void setup()
{
  Serial.begin (9600);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  pinMode(trigPinF, OUTPUT);
  pinMode(echoPinF, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
}

void loop() {
  SonarSensor(trigPinF, echoPinF);
  FrontSensor = distance;
  if (FrontSensor < 55 ) {

    SonarSensor(trigPinR, echoPinR);
    RightSensor = distance;

    SonarSensor(trigPinL, echoPinL);
    LeftSensor = distance;
  } else {
    RightSensor = 0;
    LeftSensor = 0;
  }


  Serial.print(RightSensor);
  Serial.print(" - ");
  Serial.print(FrontSensor);
  Serial.print(" - ");
  Serial.println(LeftSensor);
}

void SonarSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

}
