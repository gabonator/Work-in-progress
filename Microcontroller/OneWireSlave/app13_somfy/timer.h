#include "compiler.h"

extern unsigned int TMR_nSeconds; // 1s timer

void TMR_Init(void);
void TMR_Do(void); // call instead of OW_Loop
