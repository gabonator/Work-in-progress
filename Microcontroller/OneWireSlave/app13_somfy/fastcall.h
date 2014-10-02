#ifndef __FASTCALL__
#define __FASTCALL__

void TMR_Do_isr(void);
void User_Do_isr(void);
void User_Do_fast(void);

#define FASTCALL() { TMR_Do_isr(); User_Do_isr(); }
#define UFASTCALL() { User_Do_fast(); }

#endif