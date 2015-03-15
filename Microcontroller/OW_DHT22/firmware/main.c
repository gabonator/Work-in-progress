#include "owslave.h"
#include "owutils.h"
#include "ow2431.h"
#include "timer.h"
//#include "adc.h"
#include "crc.h"
#include "dht22.h"
#include "eeprom.h"

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

int nValueHumidity = DHT_INVALID;
int nValueTemperature = DHT_INVALID;
extern bank1 byte ow_status;
//unsigned char nFailures = 0;

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

//  const unsigned char addrbuf[8] = {0x2D, 'G', 'A', 'B',  '#', '0', '1', 0};//'1', 0x00};
 
  for (i=0; i<16; i++)
    OW_2431_data[i] = ' '; //0xa0 | i;

/*
  // default ID
  if ( eeprom_read(0xC0) == 0xFF )  
  {
    for (i=0; i<8; i++)
      eeprom_write(0xC0 | i, addrbuf[i]);
  }
*/
  // family code: 0x2D - ds2431, 0x28 - ds18b20
  for (i=0; i<7; i++)
    OW_serial[i] = eeprom_read(0xC0 | i);

  OW_serial[7] = OW_calcCrc((byte*)OW_serial, 7);
}

#define ITOA8(var, decr, c) _ITOA8(&var, decr, (unsigned char*)&(c))
#define ITOA16(var, decr, c) _ITOA16(&var, decr, (unsigned char*)&(c))

void _ITOA8(unsigned char* var, unsigned char decr, unsigned char* c)
{
  while ( *var >= decr ) 
  { 
    *var -= decr; 
    (*c)++; 
  }
}

void _ITOA16(int* var, unsigned char decr, unsigned char* c)
{
  while ( *var >= decr ) 
  { 
    *var -= decr; 
    (*c)++; 
  }
}

void UpdateBuffer(void)
{
    unsigned char nTime = TMR_nSeconds;
    int nTemp = nValueTemperature;
    int nHum = nValueHumidity;
    unsigned char i, crc;
    char tempBuffer[15];

    tempBuffer[0]  = 'S';
    tempBuffer[1]  = hex(TMR_nSeconds & 15);//'0'; // timer

    tempBuffer[2]  = 'T';
    tempBuffer[3]  = '+';
    tempBuffer[4]  = '0';
    tempBuffer[5]  = '0';
    tempBuffer[6]  = '.';
    tempBuffer[7]  = '0';

    tempBuffer[8]  = 'H';
    tempBuffer[9]  = '0';
    tempBuffer[10] = '0';
    tempBuffer[11] = '.';
    tempBuffer[12] = '0';
    tempBuffer[13] = ' ';
    tempBuffer[14] = '#';

    // time
    //ITOA8( nTime, 1, OW_2431_data[1] );

    // temp
    if ( nTemp == DHT_INVALID )
    {
      tempBuffer[3] = '?';
      tempBuffer[4] = '?';
      tempBuffer[5] = '?';
      tempBuffer[6] = '?';  
      tempBuffer[7] = '?';  
    } else 
    if ( nTemp >= 0 )
    {
      if ( nTemp > 999 )
        nTemp = 999;

      tempBuffer[3] = '+';
      ITOA16( nTemp, 100, tempBuffer[4] );
      ITOA16( nTemp, 10, tempBuffer[5] );
      ITOA16( nTemp, 1, tempBuffer[7] );
    } else
    if ( nTemp < 0 )
    {
      nTemp = -nTemp;
      if ( nTemp > 999 )
        nTemp = 999;

      tempBuffer[3] = '-';
      ITOA16( nTemp, 100, tempBuffer[4] );
      ITOA16( nTemp, 10, tempBuffer[5] );
      ITOA16( nTemp, 1, tempBuffer[7] );
    }

    // humidity
    if ( nHum == DHT_INVALID )
    {
      tempBuffer[9] = '?';
      tempBuffer[10] = '?';
      tempBuffer[11] = '?';
      tempBuffer[12] = '?';
    } else
    {
      ITOA16( nHum, 100, tempBuffer[9] );
      ITOA16( nHum, 10, tempBuffer[10] );
      ITOA16( nHum, 1, tempBuffer[12] );
    }

    crc = 0;
    for (i=0; i<15; i++)
      crc = crcPush(crc, tempBuffer[i]);

    // this function can be interrupted by OW at any point!
    // invalidate buffer contents
    OW_2431_data[15] = '?';

    // previosly, there was '?' indicating that the buffer wasn't filled yet,
    // this is also a workaround for situations where UpdateBuffer was
    // interrupted by OW routines
    for (i=0; i<15; i++)
      OW_2431_data[i] = tempBuffer[i];

    OW_2431_data[15] = 0x40 + (crc&63);
    // and now the buffer contents is valid!
}

void APP_Do(void)
{
  static unsigned char lastSecond = 0;
  static unsigned char inhibit = 0;
  static unsigned char wrongReads = 0;
  unsigned char convStatus;

  if ( ow_status == CMD_NOMATCH )
  {
    if ( wrongReads > 5 && inhibit == 0 )
    {
      // panic! Traffic on OW bus is so heavy, we cannot reliably read from DHT22
      // block isr for few ms
      OW_stop();    

      inhibit = 4; // next measurement in 5 seconds
      convStatus = DHT_read();
      if ( convStatus == 0 )
      {
        nValueHumidity = DHT_humidity;
        nValueTemperature = DHT_temperature;
        wrongReads = 0;                                                            
      }

      // useless: isr could be fired before calling OW_stop !
      if ( ow_status == CMD_NOMATCH )
        OW_start();
      else
        GIE = 1;
      return;
    }
  }

  if ( (unsigned char)TMR_nSeconds == lastSecond )
    return;    

  if ( TMR_nSeconds >= 10 )
    TMR_nSeconds = 0;

  lastSecond = (unsigned char)TMR_nSeconds;  

  // every 1s
  GPIO0 ^= 1;

  if ( inhibit == 0 )
  {
    inhibit = 4; // next measurement in 5 seconds
    convStatus = DHT_read();

    if ( /*!OW_interrupted() &&*/ convStatus == 0 )
    {
      nValueHumidity = DHT_humidity;
      nValueTemperature = DHT_temperature;
      wrongReads = 0;                                                            
    } else {
      if ( wrongReads < 10 )
        wrongReads++;
      else
      {
        // sensor cannot be read for longer than 30 seconds
        nValueHumidity = DHT_INVALID;
        nValueTemperature = DHT_INVALID;
      }
    }
  } else
  {
    inhibit--;
  }

  UpdateBuffer();
}

void main(void) 
{
  OW_setup();
  TRISIO0 = 0; // debug

  GPIO0 = 1;
  DelayMs(250); // @ 4 MHz, -> 500ms
  GPIO0 = 0;
  DelayMs(250);

  CLRWDT();
  GPIO0 = 1;
  DelayMs(250); // @ 4 MHz, -> 500ms
  GPIO0 = 0;
  DelayMs(250);

  CLRWDT();
  GPIO0 = 1;
  DelayMs(125); // @ 4 MHz, -> 500ms
  GPIO0 = 0;
  DelayMs(125);

  InitSerial(); 

  TMR_Init();
  OW_start();
  while (TRUE) 
  {
    APP_Do();
    TMR_Do();
    CLRWDT();
  }
}
