#include <Servo.h>
Servo servoX, servoY;

void setup()
{
  servoX.attach(A1);
  servoY.attach(A0);
}

void loop()
{
  servoX.write(40);
  servoY.write(110);

  delay(1000);

  servoX.write(75);
  servoY.write(110);

  delay(1000);

  servoX.write(120);
  servoY.write(67);

  delay(1000);

  servoX.write(10);
  servoY.write(70);

  delay(5000);
}
