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
  int x1 = 50;
  int x2 = 80;
  int y1 = 30;
  int y2 = 90;

  servoX.write(x1);
  servoY.write(y1);
  delay(1000);
  
  for (int i=0; i<=1000; i++)
  {
    // i = 0, 1, 2, 3 ... 998, 999, 1000
    
    int x = x1 + (long)i*(x2-x1)/1000;
    int y = y1 + (long)i*(y2-y1)/1000;
    
    servoX.write(x);
    servoY.write(y);
    delay(1); // 1000*1ms = 1s
  }
  delay(1000);
}