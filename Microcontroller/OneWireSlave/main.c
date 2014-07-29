#include "owslave.h"
#include "owutils.h"
#include "ow1820.h"
#include "ow2431.h"

__CONFIG(BORDIS & UNPROTECT & MCLRDIS & PWRTEN & WDTEN & INTIO);

// PIC12F683 pinout:
//
// 1. VDD +
// 2. GPIO5 - debug
// 3. GPIO4 - debug
// 4. GPIO3 - MCLR (read only, fixed)
// 5. GPIO2 - one wire (fixed)
// 6. GPIO1 - anemometer        / CLK
// 7. GPIO0 - light sensor      / DAT
// 8. VSS	GND


void InitSerial(void) 
{
  byte i;
  for (i=0; i<16; i++)
    OW_2431_data[i] = 0xa0 | i;

  // family code: 0x2D - ds2431, 0x28 - ds18b20
  OW_serial[0] = 0x2D;
  OW_serial[1] = 0x54;
  OW_serial[2] = 0x59;
  OW_serial[3] = 0x4D;
  OW_serial[4] = 0x45;
  OW_serial[5] = 0x4B;
  OW_serial[6] = 0x00;
  OW_serial[7] = OW_calcCrc((byte*)OW_serial, 7);

  OW_1820_scratchpad[0] = 0x90; // LSB temp - 25 deg
  OW_1820_scratchpad[1] = 0x01; // MSB temp
  OW_1820_scratchpad[2] = 0x4b; // user byte 1
  OW_1820_scratchpad[3] = 0x46; // user byte 2
  OW_1820_scratchpad[4] = 0x7f; // config register
  OW_1820_scratchpad[5] = 0xff; // reserved
  OW_1820_scratchpad[6] = 0x10; // reserved
  OW_1820_scratchpad[7] = 0x10; // reserved
  OW_1820_scratchpad[8] = OW_calcCrc((byte*)OW_1820_scratchpad, 8);
}

void main(void) 
{
  OW_setup();
  DBGINIT();

  DBG(1, 0);
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
    if ( OW_1820_scratchpad_request )
    {
      unsigned int* pTemp = (unsigned int*)OW_1820_scratchpad;

      OW_stop();
      DBG(1, 0);
      DelayMs(10);
      DBG(0, 0);

      *pTemp += 0x10;

      OW_1820_scratchpad[8] = OW_calcCrc((byte*)OW_1820_scratchpad, 8);

      OW_1820_scratchpad_valid = 1;
      OW_1820_scratchpad_request = 0;
      OW_start();
    }

    OW_loop(); // 10ms delay or sleep
  }
}
