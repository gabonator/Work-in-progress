#include "owslave.h"
#include "owutils.h"
#include "ow2431.h"
#include "timer.h"
#include "adc.h"

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
extern unsigned char TMR_overflow;

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

unsigned char
_eeprom_read(unsigned char addr)
{
	while (WR) continue;
	return EEPROM_READ(addr);
}

void InitSerial(void) 
{
  byte i;
  for (i=0; i<16; i++)
    OW_2431_data[i] = ' '; //0xa0 | i;

  // family code: 0x2D - ds2431, 0x28 - ds18b20
  for (i=0; i<7; i++)
    OW_serial[i] = _eeprom_read(0xC0 | i);
//  OW_serial[0] = 0x2D;
//  OW_serial[1] = 0x54;
//  OW_serial[2] = 0x59;
//  OW_serial[3] = 0x4D;
//  OW_serial[4] = 0x45;
//  OW_serial[5] = 0x4B;
//  OW_serial[6] = 0x00;
  OW_serial[7] = OW_calcCrc((byte*)OW_serial, 7);
}


void UpdateBuffer(void)
{
    #define ITOA( var, decr, char ) while ( var >= decr ) { var -= decr; char++; }
    unsigned int nTime = TMR_nSeconds;
    unsigned int nWind = nWindFinal;
    signed int nLight = nAdcResult;
    unsigned char i, sum;

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
    OW_2431_data[15] = ' ';

    // time
    ITOA( nTime, 10, OW_2431_data[1] );
    ITOA( nTime, 1, OW_2431_data[2] );

    // 800..3000 
    nLight -= 800;
    // 0..2200
    if (nLight < 0)
      nLight = 0;
    if (nLight > 2200-1)
      nLight = 2200-1;

//    ITOA( nLight, 22*100, OW_2431_data[5] );
    ITOA( nLight, 22*10, OW_2431_data[4] );
    ITOA( nLight, 22*1, OW_2431_data[5] );
    nLight = (nLight*29) >> 6; //*10/22;
    ITOA( nLight, 1, OW_2431_data[7] );


    // windspd kmh = frequency, nWind = frequency * 20
    ITOA( nWind, 20*100, OW_2431_data[9] );
    ITOA( nWind, 20*10, OW_2431_data[10] );
    ITOA( nWind, 20*1, OW_2431_data[11] );
    ITOA( nWind, 2, OW_2431_data[13] );

    sum = 0;
    for (i=0; i<15; i++)
    { 
      sum ^= sum<<1;
      sum += OW_2431_data[i];
    }
    OW_2431_data[15] = 0x40 + (sum&63);
     
#if 0
    OW_2431_data[0] = 'T';
    OW_2431_data[1] = '0';
    OW_2431_data[2] = '0';
    OW_2431_data[3] = ' ';

    #define ITOA( var, decr, char ) while ( var >= decr ) { var -= decr; char++; }
//    ITOA( nTime, 100, OW_2431_data[1] );
    ITOA( nTime, 10, OW_2431_data[1] );
    ITOA( nTime, 1, OW_2431_data[2] );

    OW_2431_data[4] = 'L';
    OW_2431_data[5] = hex(nAdcResult >> 12);
    OW_2431_data[6] = hex(nAdcResult >> 8);
    OW_2431_data[7] = hex(nAdcResult >> 4);
    OW_2431_data[8] = hex(nAdcResult >> 0);
    OW_2431_data[9] = ' ';

    OW_2431_data[10] = 'W';
    OW_2431_data[11] = '0';
    OW_2431_data[12] = '0';
    OW_2431_data[13] = '0';
    OW_2431_data[14] = '0';
    OW_2431_data[15] = 0;

    ITOA( nWind, 1000, OW_2431_data[11] );
    ITOA( nWind, 100, OW_2431_data[12] );
    ITOA( nWind, 10, OW_2431_data[13] );
    ITOA( nWind, 1, OW_2431_data[14] );
#endif
}

static unsigned int lastSecond = 0;
unsigned char doProc = 0;

void User_Do_fast(void)
{
  unsigned char nNewWind = GPIO5;
  if ( nPrevWind != nNewWind )
  {  
    nPrevWind = nNewWind;
    nWindCounter++;
  }
}

void User_Do_isr(void)
{
  unsigned char nNewWind = GPIO5;
  if ( nPrevWind != nNewWind )
  {  
    nPrevWind = nNewWind;
    nWindCounter++;
  }

  if ( TMR_nSeconds == lastSecond )
    return;

  GPIO0 ^= 1;

  if (TMR_nSeconds >= 10)
  {
    TMR_nSeconds = 0;
    nWindFinal = nWindCounter;
    nWindCounter = 0;
  }

  lastSecond = TMR_nSeconds;  
  doProc = 1;
}

void User_Do(void)
{
  unsigned char nNewWind = GPIO5;
  if ( nPrevWind != nNewWind )
  {  
    nPrevWind = nNewWind;
    nWindCounter++;
  }

  if ( TMR_nSeconds == lastSecond )
    return;

  GPIO0 ^= 1;

  if (TMR_nSeconds >= 10)
  {
    TMR_nSeconds = 0;
    nWindFinal = nWindCounter;
    nWindCounter = 0;
  }

  lastSecond = TMR_nSeconds;  
  doProc = 1;
}

void APP_Do(void)
{
  unsigned int nAdcNewResult = 0;

  User_Do();

  if ( !doProc )
    return;
  doProc = 0;

  // 50Hz : 4 = 5ms, pozor, mohlo byt ovplyvnene prerusenim

  nAdcNewResult = ADC_Get16();
  /*User_Do();*/ DelayMs(5);
  nAdcNewResult += ADC_Get16();
  /*User_Do();*/ DelayMs(5);
  nAdcNewResult += ADC_Get16();
  /*User_Do();*/ DelayMs(5);
  nAdcNewResult += ADC_Get16();

  nAdcResult = nAdcNewResult;
  //User_Do();
  UpdateBuffer();
  //User_Do();
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
  DelayMs(250);

  InitSerial(); 

  TMR_Init();
  OW_start();
  ADC_Init();
  while (TRUE) 
  {
    APP_Do();
    TMR_Do();
    CLRWDT();
  }
}
