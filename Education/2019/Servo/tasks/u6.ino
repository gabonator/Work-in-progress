#include <Servo.h>

Servo servo;

void setup() 
{
  Serial.begin(9600);

  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  pinMode(A3, INPUT);
  pinMode(A5, OUTPUT);
  digitalWrite(A5, HIGH);

  servo.attach(A0);
}

void loop() 
{
  int hodnota = analogRead(A3);
  servo.write((long)hodnota*180/1024);
}
