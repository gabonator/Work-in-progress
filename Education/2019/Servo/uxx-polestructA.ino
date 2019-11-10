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
  *          C.  57,110
  *  
  *  33,90  /   \   88,88        - 40, 100, 80, 100
  *       B. ___ D.
  *      /          \ 
  *   A.             E.
  *   10,70          120,67
  * 
  */

struct bod {
  int x, y;
};

bod A{10, 70}, B{50, 95}, C{65, 110}, D{80, 95}, E{120, 67};
bod ciary[] = {A, B, C, D, E, D, B, A};
  
void loop()
{
  int pocet = sizeof(ciary)/sizeof(ciary[0]);
  for (int i=0; i<pocet-1; i++)
  {
    ciara(ciary[i].x, ciary[i].y, ciary[i+1].x, ciary[i+1].y);
  }
  delay(1000);
}
