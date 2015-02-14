#include "owslave.h"
#include "owutils.h"
#include "ow2431.h"
#include "crc.h"
#include "lcd.h"
#include "eeprom.h"

__CONFIG(DEBUGDIS & BORDIS & UNPROTECT & MCLRDIS & PWRTDIS & WDTDIS & INTIO & LVPDIS);

//__CONFIG(BORDIS & UNPROTECT & MCLRDIS & PWRTEN & WDTEN & INTIO);

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

//extern bank1 byte timeout; 

unsigned char report_status = 0;

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
  for (i=0; i<7; i++)
    OW_serial[i] = eeprom_read(0xd0 | i);

  OW_serial[7] = OW_calcCrc((byte*)OW_serial, 7);
}

void APP_Init(void)
{
  unsigned char i;
  LCD_GOTO(0x00);
  for (i = 0; i<16; i++)
    LCD_PUTCH(eeprom_read(0xe0 | i));

  LCD_GOTO(0x40);
  for (i = 0; i<16; i++)
    LCD_PUTCH(eeprom_read(0xf0 | i));

  TRISB3 = 0;
  RB3 = 0;
}
extern bank1 byte ow_status; // 0 - waiting for reset, ROM_CMD - waiting for rom command, FUNCTION_CMD - waiting for function command


void UpdateBuffer(void)
{
  unsigned char crc = 0, i;

  OW_2431_data[15] = ' ';
  // ........--------
  // T00 L111 W123
  OW_2431_data[0]  = 'S';
  OW_2431_data[1]  = hex(report_status & 0x0f);
  OW_2431_data[2]  = hex(report_status >> 4);
  OW_2431_data[3]  = ' ';
  OW_2431_data[4]  = 'A';
  OW_2431_data[5]  = hex(OW_2431_scratchpad_addr & 0x0f);
  OW_2431_data[6]  = hex(OW_2431_scratchpad_addr >> 4);
  OW_2431_data[7]  = ' ';
  OW_2431_data[8]  = 'L';
  OW_2431_data[9]  = hex(OW_2431_scratchpad_len & 0x0f);
  OW_2431_data[10] = hex(OW_2431_scratchpad_len >> 4);
  OW_2431_data[11] = ' ';
  OW_2431_data[12] = ' ';
  OW_2431_data[13] = ' ';
  OW_2431_data[14] = '#';

  for (i=0; i<15; i++)
    crc = crcPush(crc, OW_2431_data[i]);

  OW_2431_data[15] = 0x40 + (crc&63);

  // update...
  if ( OW_2431_data_read )
    report_status = 0;  
}

void ProcessScratchpad(void)
{
  unsigned char i;
  if ( (OW_2431_scratchpad_status & 0x0f) == 0x01 )
  {
    if ( OW_2431_scratchpad_addr == 0xF0 )
    {
      for (i = 0; i < OW_2431_scratchpad_len; i++)
        LCD_PUTCH( OW_2431_scratchpad[i] );
    }
    if ( OW_2431_scratchpad_addr == 0xF1 )
    {
      LCD_GOTO(0x00);
      for (i = 0; i < OW_2431_scratchpad_len; i++)
        LCD_PUTCH( OW_2431_scratchpad[i] );
    }
    if ( OW_2431_scratchpad_addr == 0xF2 )
    {
      LCD_GOTO(0x40);
      for (i = 0; i < OW_2431_scratchpad_len; i++)
        LCD_PUTCH( OW_2431_scratchpad[i] );
    }
    if ( OW_2431_scratchpad_addr == 0xF3 )
    {
      for (i = 0; i < OW_2431_scratchpad_len; i+=2)
      {
        if ( OW_2431_scratchpad[i] == 'i' )
          LCD_INIT();
        else if ( OW_2431_scratchpad[i] == 'x' )
          LCD_CLEAR();
        else if ( OW_2431_scratchpad[i] == 'd' )
          __LCD_SEND(OW_2431_scratchpad[i+1], 1);
        else if ( OW_2431_scratchpad[i] == 'c' )
          __LCD_SEND(OW_2431_scratchpad[i+1], 0);
        else
          break;
      }
    }
    if ( OW_2431_scratchpad_addr == 0xF4 )
    {
      __LCD_SEND(OW_2431_scratchpad[0], 0);
      _ASSUME( OW_2431_scratchpad_len == 8+1 );
      for (i = 1; i < OW_2431_scratchpad_len; i++)
        __LCD_SEND( OW_2431_scratchpad[i], 1 );
    }
  }

  report_status |= OW_2431_scratchpad_status;
  OW_2431_scratchpad_status = 0;
}

void APP_Do(void)
{
  unsigned char i;
  static unsigned char id;

  ProcessScratchpad();
  UpdateBuffer();

/*
  LCD_GOTO(0x00);
  for (i = 0; i < 16; i++)
    LCD_PUTCH( OW_2431_scratchpad[i] );
*/
/*
  LCD_GOTO(0x40);
  LCD_PRINT("ss=");
  LCD_PUTHEX(OW_2431_scratchpad_status);
  LCD_PRINT("/");
  LCD_PUTHEX(OW_2431_scratchpad_addr);
  LCD_PRINT("/");
  LCD_PUTHEX(OW_2431_scratchpad_len);
  LCD_PRINT(" ");
  LCD_PUTHEX('a' + (id++ &15));
*/
}

void OW_EnterSleep(void)
{
  RB3 = 1;
}

void OW_LeaveSleep(void)
{
  RB3 = 0;
}

void main(void) 
{
  OSCCON = 0b01110001;  /// 8 MHz

  LCD_INIT();
  OW_setup();
  InitSerial(); 
  APP_Init();
  OW_start();
  while (TRUE) 
  {
    APP_Do();
    OW_loop();
    //CLRWDT();
  }
}
