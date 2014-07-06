#include "timer.h"

unsigned int TMR_nSeconds = 0; // 1s timer

void TMR_Init(void)
{
  T1CON = 0b00110001;
}

void TMR_Do(void)
{
  unsigned char TmrHigh;
  static unsigned int nCounter = 0;
  TmrHigh = TMR1H;
  nCounter += TmrHigh;
  TMR1H -= TmrHigh;
  
  // nCounter is incremented 8000000/4/8/256 per second (976.5625)
  // 1.024 milli seconds passed
  #define PERIOD (976-60)

  if ( nCounter >= PERIOD )
  {
//    nCounter -= 1000 - 60;// - 24;
    nCounter -= PERIOD;
    TMR_nSeconds++;
  }

  if ( TMR1IF )
  {
    // overflow occured! Some blocking code was executed
    TMR1IF = 0;
  } 
}
