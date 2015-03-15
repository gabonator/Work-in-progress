#include "owslave.h"
#include "owutils.h"
#include "ow2431.h"
#include "timer.h"
#include "eeprom.h"
#include "app.h"

__CONFIG(BORDIS & UNPROTECT & MCLRDIS & PWRTEN & WDTEN & INTIO );

// PIC12F683 pinout:
//
// 1. VDD +
// 2. GPIO5 -     
// 3. GPIO4 - DHT22                   / AN3
// 4. GPIO3 - MCLR (read only, fixed)
// 5. GPIO2 - one wire (fixed)        / AN2
// 6. GPIO1 - (GPOI2)           / CLK / AN1
// 7. GPIO0 - dbg tick          / DAT / AN0
// 8. VSS	GND

void InitSerial(void) 
{
  unsigned int i;

  for (i=0; i<16; i++)
    OW_2431_data[i] = ' '; //0xa0 | i;

  // family code: 0x2D - ds2431, 0x28 - ds18b20
  for (i=0; i<7; i++)
    OW_serial[i] = eeprom_read(0xC0 | i);

  OW_serial[7] = OW_calcCrc((byte*)OW_serial, 7);
}

void APP_Do(void)
{
  static byte nPrevSeconds = 0;
  if ( TMR_nSeconds != nPrevSeconds )
  {
    nPrevSeconds = TMR_nSeconds;
    AppTimer();
    AppUpdateBuffer();
  }

  AppProcessScratchpad();
}

void OW_EnterSleep(void)
{
//  RB3 = 1;
}

void OW_LeaveSleep(void)
{
//  RB3 = 0;
}

void main(void) 
{
  OW_setup();

  DelayMs(100);
  InitSerial(); 

  TMR_Init();
  OW_start();
  AppInit();

  while (TRUE) 
  {
    TMR_Do();
    APP_Do();
    if ( AppIsRunning() )
	    CLRWDT();
    else
	    OW_loop();
  }
}
