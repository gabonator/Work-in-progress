#include "timer.h"

#define PERIOD 976

volatile unsigned int TMR_nCounter = 0;
volatile unsigned char TMR_nSeconds = 0; // 1s timer
volatile unsigned char prev1H = 0;

void TMR_Init(void)
{
  T1CON = 0b00110001;
}


// http://www.pcbheaven.com/picpages/The_Timer_Modules_Timer1/
void TMR_Do(void)
{
  unsigned char new1H = TMR1H;
  unsigned char nPassed = new1H - prev1H;
  prev1H = new1H;
  if ( nPassed < 200 )
    TMR_nCounter += nPassed;
  else 
    TMR_nCounter += 255-nPassed;

  if ( TMR_nCounter >= PERIOD )
  {
    TMR_nCounter -= PERIOD;
    TMR_nSeconds++;
//    GPIO0 = TMR_nSeconds & 1;
  }
}
