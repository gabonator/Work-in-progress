#include "timer.h"

unsigned int TMR_nSeconds = 0; // 1s timer
unsigned char TMR_overflow = 0;
void TMR_Init(void)
{
  T1CON = 0b00110001;
}

volatile unsigned int nCounter = 0;


//  #define PERIOD (420+22) // 4.967
//  #define PERIOD (420+23) // 4.979
//  #define PERIOD (420+24) // 4.990
//  #define PERIOD (420+25) // 5.001
//  #define PERIOD (445*2) // 5.001


//  #define PERIOD (445*2) // 1.827
  #define PERIOD (976) // 1.827

void TMR_Do_isr(void)
{
  unsigned char TmrHigh;
  TmrHigh = TMR1H;
  if ( !TmrHigh )
    return;

  TMR1H -= TmrHigh;
  nCounter += TmrHigh;
  
  // nCounter is incremented 8000000/4/8/256 per second (976.5625)
  // 1.024 milli seconds passed


  if ( nCounter >= PERIOD )
  {
    nCounter -= PERIOD;
    TMR_nSeconds++;
  }

  if ( TMR1IF )
  {
    // overflow occured! Some blocking code was executed
    TMR1IF = 0;
    TMR_overflow++;
  } 
}

void TMR_Do(void)
{
  unsigned char TmrHigh;
  TmrHigh = TMR1H;
  if ( !TmrHigh )
    return;

  TMR1H -= TmrHigh;
  nCounter += TmrHigh;
  
  // nCounter is incremented 8000000/4/8/256 per second (976.5625)
  // 1.024 milli seconds passed

  if ( nCounter >= PERIOD )
  {
    nCounter -= PERIOD;
    TMR_nSeconds++;
  }

  if ( TMR1IF )
  {
    // overflow occured! Some blocking code was executed
    TMR1IF = 0;
    TMR_overflow++;
  } 
}
