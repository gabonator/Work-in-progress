#include <Servo.h>
Servo servoX, servoY;

void setup()
{
  servoX.attach(A1); // 10..75, stred 55
  servoY.attach(A0); // 70..120, stred 90
  pinMode(A2, OUTPUT);
}

void loop()
{
  for (int uhol=0; uhol<360; uhol++)
  {
    float uholRad = uhol*PI/180.0f;
    int x = 50 + cos(uholRad)*30;
    int y = 90 + sin(uholRad)*30;

    if (uhol > 30 && uhol < 360-30)
    {
      digitalWrite(A2, HIGH);
    }
    else
    {
      digitalWrite(A2, LOW);
    }
    
    servoX.write(x);
    servoY.write(y);
    delay(10);
  }
}
