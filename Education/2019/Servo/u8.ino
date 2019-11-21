#include <Servo.h>

Servo servoX;
Servo servoY;

void setup()
{
  servoX.attach(A0);
  servoY.attach(A1);
}

void loop()
{
  for (int i=0; i<=100; i++)
  {
    // i = 0, 1, 2, 3 ... 98, 99, 100
    
    int x = ??? + i*???/???;
    int y = ??? + i*???/???;
    
    servoX.write(x);
    servoY.write(y);
    delay(10); // 100*10ms = 1s
  }
}