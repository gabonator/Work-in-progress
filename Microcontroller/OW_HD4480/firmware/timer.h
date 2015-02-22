#include "compiler.h"

volatile extern unsigned char TMR_nSeconds; // 1s timer
volatile extern unsigned int TMR_nCounter;

void TMR_Init(void);
void TMR_Do(void); // call instead of OW_Loop
