#include <Servo.h>
Servo servoX, servoY;

/*
 *    40,110        75,110
 * 
 * 
 * 
 *    10,70         67,120
 */

void setup()
{
  servoX.attach(A1);
  servoY.attach(A0);
}

void ciara(int x1, int y1, int x2, int y2)
{
  int dlzka = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
  for (int i=0; i<dlzka; i++)
  {
     int x = x1 + (x2-x1)*i/dlzka;
     int y = y1 + (y2-y1)*i/dlzka;
     servoX.write(x);
     servoY.write(y);
     delay(20);
  }
}

 /*
  *  pismeno A
  *           .  57,110
  *  
  *  33,90  /   \   88,88
  *        . ___  .
  *      /          \ 
  *    .              .
  *   10,70          120,67
  * 
  */

void loop()
{
  ciara(10, 70, 33, 90);
  ciara(33, 90, 57, 110);
  ciara(57, 110, 88, 88);
  ciara(88, 88, 120, 67);
  ciara(120, 67, 88, 88);
  ciara(88, 88, 33, 90);
  ciara(33, 90, 10, 70);
  delay(100);
}
