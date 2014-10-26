#include "owslave.h"
#include "owutils.h"
#include "ow2431.h"
#include "timer.h"
#include "adc.h"
#include "crc.h"
#include "fastcall.h"
#include "eeprom.h"

__CONFIG(BORDIS & UNPROTECT & MCLRDIS & PWRTEN & WDTEN & INTIO);

// PIC12F683 pinout:
//
// 1. VDD +
// 2. GPIO5 - debug
// 3. GPIO4 - debug                   / AN3
// 4. GPIO3 - MCLR (read only, fixed)
// 5. GPIO2 - one wire (fixed)        / AN2
// 6. GPIO1 - anemometer        / CLK / AN1
// 7. GPIO0 - light sensor      / DAT / AN0
// 8. VSS	GND

extern bank1 byte timeout; 
unsigned int nAdcResult = 0;

unsigned char nPrevWind = 0;
unsigned int nWindCounter = 0;
unsigned int nWindFinal = 0;

byte hex(byte v)
{
  v &= 15;
  if ( v < 10 )
    return '0' + v;
  return 'a' + v - 10;
}

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

void UpdateBuffer(void)
{
    #define ITOA( var, decr, char ) while ( var >= decr ) { var -= decr; char++; }
    unsigned char nTime = TMR_nSeconds;
    unsigned int nWind = nWindFinal;
    signed int nLight = nAdcResult;
    unsigned char i, crc, bDebug;
    unsigned int nZeroAdc; // = 0x338;

    bDebug = eeprom_read(0xD0) == 1;
    nZeroAdc = ( eeprom_read(0xD1) << 8 ) | eeprom_read(0xD2);

    OW_2431_data[15] = ' ';
    // ........--------
    // T00 L111 W123
    OW_2431_data[0]  = 'T';
    OW_2431_data[1]  = '0';
    OW_2431_data[2]  = '0';
    OW_2431_data[3]  = 'L';
    OW_2431_data[4]  = '0';
    OW_2431_data[5]  = '0';
    OW_2431_data[6]  = '.';
    OW_2431_data[7]  = '0';
    OW_2431_data[8]  = 'W';
    OW_2431_data[9]  = '0';
    OW_2431_data[10] = '0';
    OW_2431_data[11] = '0';
    OW_2431_data[12] = '.';
    OW_2431_data[13] = '0';
    OW_2431_data[14] = '#';

    if ( bDebug )
    {
      // debug:                
      OW_2431_data[0] = hex(nLight>>8);
      OW_2431_data[1] = hex((nLight>>4)&15);
      OW_2431_data[2] = hex(nLight&15);
    } else
    {
      // time
      ITOA( nTime, 10, OW_2431_data[1] );
      ITOA( nTime, 1, OW_2431_data[2] );
    }

    // 0x330 .. 0x640
    // 330..730  (73f-74b max)
    nLight -= nZeroAdc;
    // 0x000 .. 0x310
    #define DIVIDER 102

    nLight = nLight*10;

    // 0..2200
    if (nLight < 0)
      nLight = 0;
    if (nLight > (DIVIDER*100)-1)
      nLight = (DIVIDER*100)-1;

    ITOA( nLight, DIVIDER*10, OW_2431_data[4] );
    ITOA( nLight, DIVIDER*1, OW_2431_data[5] );
    nLight = nLight*10;
    ITOA( nLight, DIVIDER*1, OW_2431_data[7] );

    // windspd kmh = frequency, nWind = frequency * 20
    if ( nWind > 20*100*10-1 )
      nWind = 20*100*10-1;
    ITOA( nWind, 20*100, OW_2431_data[9] );
    ITOA( nWind, 20*10, OW_2431_data[10] );
    ITOA( nWind, 20*1, OW_2431_data[11] );
    ITOA( nWind, 2, OW_2431_data[13] );

    crc = 0;
    for (i=0; i<15; i++)
      crc = crcPush(crc, OW_2431_data[i]);

    OW_2431_data[15] = 0x40 + (crc&63);
}

void Wait(unsigned char l)
{
  l <<= 2;
  while (l--)
  {
    FASTCALL();
    DelayUs(245);
  }
}

void APP_Do(void)
{
  static unsigned char lastSecond = 0;
  unsigned int nAdcNewResult = 0;

  FASTCALL();
  if ( TMR_nSeconds == lastSecond )
    return;

  GPIO0 ^= 1;

  if (TMR_nSeconds >= 10)
  {
    TMR_nSeconds -= 10;
    nWindFinal = nWindCounter;
    nWindCounter = 0;
  }

  lastSecond = TMR_nSeconds;  
  // 50Hz : 4 = 5ms, pozor, mohlo byt ovplyvnene prerusenim

  nAdcNewResult = ADC_Get16();
  Wait(5);
  nAdcNewResult += ADC_Get16();
  Wait(5); 
  nAdcNewResult += ADC_Get16();
  Wait(5); 
  nAdcNewResult += ADC_Get16();
  Wait(5);
  nAdcResult = nAdcNewResult;

  UpdateBuffer();
}

void main(void) 
{
  OW_setup();
  TRISIO0 = 0; // debug

  TRISIO5 = 1; // wind 
  GPIO5 = 0;
  WPU5 = 0;
  TRISIO4 = 1; // lout

  GPIO0 = 1;
  DelayMs(250); // @ 4 MHz, -> 500ms
  GPIO0 = 0;
  DelayMs(250);
  GPIO0 = 1;
  DelayMs(250); // @ 4 MHz, -> 500ms
  GPIO0 = 0;

  InitSerial(); 

  TMR_Init();
  OW_start();
  ADC_Init();
  while (TRUE) 
  {
    TMR_Do();
    APP_Do();
    CLRWDT();
  }
}
