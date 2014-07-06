#include "owslave.h"
#include "owutils.h"

__CONFIG(BORDIS & UNPROTECT & MCLRDIS & PWRTEN & WDTEN & INTIO);

void InitSerial(void) 
{
  OW_serial[0] = 0xBF;
  OW_serial[1] = 0x54;
  OW_serial[2] = 0x59;
  OW_serial[3] = 0x4D;
  OW_serial[4] = 0x45;
  OW_serial[5] = 0x4B;
  OW_serial[6] = 0x00;
  OW_serial[7] = OW_calcCrc((byte*)OW_serial, 7);
}

void main(void) 
{
  OW_setup();
  DBGINIT();

  DBG(0, 1);
  DelayMs(250); // @ 4 MHz, -> 500ms
  DBG(0, 0);
  DelayMs(250);
  DBG(0, 1);
  DelayMs(250);
  DBG(0, 0);

  InitSerial(); 

  OW_start();
  while (TRUE) 
  {
    if ( OW_scratchpad_request )
    {
      OW_stop();
      DBG(1, 0);
      DelayMs(10);
      DBG(0, 0);

      OW_scratchpad[0] = 0x12;
      OW_scratchpad[1] = 0x34;
      OW_scratchpad[2] = 0x56;
      OW_scratchpad[3] = 0x78;
      OW_scratchpad[4] = 0x9a;
      OW_scratchpad[5]++;

      OW_scratchpad[6] = OW_calcCrc((byte*)OW_scratchpad, 6);
      OW_scratchpad_valid = 1;
      OW_scratchpad_request = 0;
      OW_start();
    }

    OW_loop(); // 10ms delay or sleep
  }
}
