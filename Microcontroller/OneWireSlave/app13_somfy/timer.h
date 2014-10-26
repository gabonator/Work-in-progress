#include "compiler.h"

volatile extern unsigned char TMR_nSeconds; // 1s timer

void TMR_Init(void);
void TMR_Do(void); // call instead of OW_Loop
