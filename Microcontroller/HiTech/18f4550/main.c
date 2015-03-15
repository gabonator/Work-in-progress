#include <htc.h>

#define XTAL_FREQ  20000000

#include "delay.h"

__CONFIG(1,HSPLL & USBPLL	& PLLDIV5 & CPUDIV1 & FCMDIS & IESODIS);
__CONFIG(2,VREGEN & PWRTDIS & BOREN & BORV20 & WDTDIS & WDTPS32K);
__CONFIG(3,CCP2RC1 & PBADDIS & LPT1DIS & MCLRDIS);
__CONFIG(4,STVREN & LVPDIS /*& ICPORT */& XINSTDIS & DEBUGDIS);
__CONFIG(5,UNPROTECT);
__CONFIG(6,UNPROTECT);
__CONFIG(7,UNPROTECT);

void main(void) 
{
  unsigned char c = 0;
  ADCON1 = 0x0F;
    
  LATD &= 0xF0; 
  TRISD &= 0xF0;
  PORTD = 0xFF;

  while (1)
  {
    RD0 = c & 1;
    RD1 = (c >> 1) & 1;
    RD2 = (c >> 2) & 1;
    RD3 = (c >> 3) & 1;

    c++;
    DelayMs(200);
    DelayMs(200);
    DelayMs(200);
    DelayMs(200);
    DelayMs(200);
  }
}
