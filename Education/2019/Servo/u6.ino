#include <Servo.h>
Servo servo;

void setup()
{
  servo.attach(A0);
}

void loop()
{
  servo.write(80); // 0..180
}
