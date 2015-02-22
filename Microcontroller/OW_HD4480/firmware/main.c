#include "owslave.h"
#include "owutils.h"
#include "ow2431.h"
#include "crc.h"
#include "lcd.h"
#include "eeprom.h"
#include "timer.h"

__CONFIG(DEBUGDIS & BORDIS & UNPROTECT & MCLRDIS & PWRTDIS & WDTDIS & INTIO & LVPDIS);

/*
  PIC16F88

  RB0 - one wire bus
  RB1 - HD44780.strobe
  RB2 - HD44780.rs
  RB3 - sleep indicator

  RB4 - HD44780.d4
  RB5 - HD44780.d5
  RB6 - HD44780.d6
  RB7 - HD44780.d7

  (HD44780: 1,5: GND, 2: 5V, 3: contrast, 10k pot)
*/

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

struct anim
{
  byte automatic;
  //
  byte enabled;   // 1-anim enabled
  signed char position;  // current position
  signed char target;		// char x offset
  byte wait;      // in seconds for next anim to start
  //
  byte cfg_interval;
  byte cfg_wait;
} g_Anim = {0, 0, 0, 0, 0, 40, 10};

void StartAnim(void);
void StopAnim(void);
void GoAnim(byte pos);


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

  InitSerial();

  LCD_GOTO(0x00);
  for (i = 0; i<16; i++)
    LCD_PUTCH(eeprom_read(0xe0 | i));

  LCD_PRINT("Ver 1.0, built:");

  LCD_GOTO(0x40);
  for (i = 0; i<16; i++)
    LCD_PUTCH(eeprom_read(0xf0 | i));

  LCD_PRINT(__DATE__);

}

void UpdateBuffer(void)
{
  unsigned char crc = 0, i;

  OW_2431_data[15] = ' ';
  // ........--------
  // T00 L111 W123
  OW_2431_data[0]  = 'S';
  OW_2431_data[1]  = hex(report_status >> 4);
  OW_2431_data[2]  = hex(report_status & 0x0f);
  OW_2431_data[3]  = ' ';
  OW_2431_data[4]  = 'C';
  if ( OW_2431_scratchpad_len > 2 )
  {
    OW_2431_data[5] = hex(OW_2431_scratchpad[OW_2431_scratchpad_len-2] >> 4);
    OW_2431_data[6] = hex(OW_2431_scratchpad[OW_2431_scratchpad_len-2] & 0x0f);
    OW_2431_data[7] = hex(OW_2431_scratchpad[OW_2431_scratchpad_len-1] >> 4);
    OW_2431_data[8] = hex(OW_2431_scratchpad[OW_2431_scratchpad_len-1] & 0x0f);
  } else
  {
    OW_2431_data[5] = '?';
    OW_2431_data[6] = '?';
    OW_2431_data[7] = '?';
    OW_2431_data[8] = '?';
  }

  OW_2431_data[9] = ' ';
  OW_2431_data[10] = ' ';
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
    OW_2431_scratchpad_status |= 0x80; // mark processing
    if ( OW_2431_scratchpad[0] == 0xD0 )
    {
      for (i = 1; i < OW_2431_scratchpad_len-2; i++)
      {
        if ( OW_2431_scratchpad[i] == '\r' || OW_2431_scratchpad[i] == '\n' ) 
	        LCD_GOTO(0x40);
        else
  	      LCD_PUTCH( OW_2431_scratchpad[i] );
      }
    }
    if ( OW_2431_scratchpad[0] == 0xD1 )
    {
      LCD_GOTO(0x00);
      for (i = 1; i < OW_2431_scratchpad_len-2; i++)
        LCD_PUTCH( OW_2431_scratchpad[i] );
    }
    if ( OW_2431_scratchpad[0] == 0xD2 )
    {
      LCD_GOTO(0x40);
      for (i = 1; i < OW_2431_scratchpad_len-2; i++)
        LCD_PUTCH( OW_2431_scratchpad[i] );
    }
    if ( OW_2431_scratchpad[0] == 0xD3 )
    {
      LCD_GOTO(0x10);
      for (i = 1; i < OW_2431_scratchpad_len-2; i++)
        LCD_PUTCH( OW_2431_scratchpad[i] );
    }
    if ( OW_2431_scratchpad[0] == 0xD4 )
    {
      LCD_GOTO(0x50);
      for (i = 1; i < OW_2431_scratchpad_len-2; i++)
        LCD_PUTCH( OW_2431_scratchpad[i] );
    }
    if ( OW_2431_scratchpad[0] == 0xDA )
    {
      for (i = 1; i < OW_2431_scratchpad_len-2; i+=2)
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
    if ( OW_2431_scratchpad[0] == 0xDB )
    {
      //          <scratchpad begins...
      // F0 AA AA ?? DB 00  b0 b1 b2 b3 b4 b5 b6 b7 
      //                01  b0 b1 b2 b3 b4 b5 b6 b7
      //                02  b0 b1 b2 b3 b4 b5 b6 b7
      //                03  b0 b1 b2 b3 b4 b5 b6 b7
      //                                             crc crc
      // 2 + 4*9 + 2 = 40 bytes
    
      for (i = 1; i < OW_2431_scratchpad_len-2; i+=9)
      {
        __LCD_SEND( OW_2431_scratchpad[i], 0 );
        __LCD_SEND( OW_2431_scratchpad[i+1], 1 );
        __LCD_SEND( OW_2431_scratchpad[i+2], 1 );
        __LCD_SEND( OW_2431_scratchpad[i+3], 1 );
        __LCD_SEND( OW_2431_scratchpad[i+4], 1 );
        __LCD_SEND( OW_2431_scratchpad[i+5], 1 );
        __LCD_SEND( OW_2431_scratchpad[i+6], 1 );
        __LCD_SEND( OW_2431_scratchpad[i+7], 1 );
        __LCD_SEND( OW_2431_scratchpad[i+8], 1 );
      }
    }
    if ( OW_2431_scratchpad[0] == 0xDC )
    {
      switch ( OW_2431_scratchpad[1] )
      {
        case 0x80: StopAnim(); break;
        case 0x81: StartAnim(); break;
        case 0x8A: g_Anim.cfg_interval = OW_2431_scratchpad[2]; break;
        case 0x8B: g_Anim.cfg_wait = OW_2431_scratchpad[2]; break;
        default:
          GoAnim(OW_2431_scratchpad[1]);
          g_Anim.wait = 0;
      }
    }
    if ( OW_2431_scratchpad[0] == 0xDD )
    {
      __LCD_SEND(OW_2431_scratchpad[1], 0);
      //_ASSUME( OW_2431_scratchpad_len == 8+1 );
      for (i = 2; i < OW_2431_scratchpad_len-2; i++)
        __LCD_SEND( OW_2431_scratchpad[i], 1 );
    }
    OW_2431_scratchpad_status &= ~0x80;
  }

  report_status |= OW_2431_scratchpad_status;
  OW_2431_scratchpad_status = 0;
}

void StartAnim(void)
{
  g_Anim.automatic = TRUE;
  GoAnim(16);
}

void StopAnim(void)
{
  g_Anim.automatic = FALSE;
  GoAnim(0);
}

void GoAnim(byte pos)
{
  g_Anim.enabled = TRUE;
  g_Anim.wait = g_Anim.cfg_wait;
  g_Anim.target = pos;
}

void UpdateAnim(void)
{
  const byte LCD_moveLeft = 0x10 /* CURSORSHIFT */ | 0x08 /* DISPLAYMOVE */ | 0x00 /* MOVELEFT */;
  const byte LCD_moveRight = 0x10 /* CURSORSHIFT */ | 0x08 /* DISPLAYMOVE */ | 0x04 /* MOVERIGHT */;

  // every 40ms
  if ( TMR_nCounter < g_Anim.cfg_interval )
    return;
  TMR_nCounter = 0;

  if ( !g_Anim.enabled )
  {
    if ( g_Anim.automatic )
    {
      if ( g_Anim.position > 0 )
      {
        g_Anim.position--;
        __LCD_SEND( LCD_moveLeft, 0 );
      }
    }
    return;
  }

  // wait?
  if ( g_Anim.wait > 0 )
  {
    if ( TMR_nSeconds )
    {
      TMR_nSeconds = 0;
      g_Anim.wait--;
    }
    return;
  }

  if ( g_Anim.target > g_Anim.position )
  {
    g_Anim.position++;
    __LCD_SEND( LCD_moveLeft, 0 );
    return;
  }

  if ( g_Anim.target < g_Anim.position )
  {
    g_Anim.position--;
    __LCD_SEND( LCD_moveRight, 0 );
    return;
  }

  // finished transition
  if ( g_Anim.automatic )
  {
    if ( g_Anim.target == 0 )
      GoAnim(16);
    else
      GoAnim(0);
  } else
  {
    g_Anim.enabled = FALSE;
  }
}

void APP_Do(void)
{
  unsigned char i;
  static unsigned char id;

  ProcessScratchpad();
  UpdateBuffer();
  UpdateAnim();
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
  OSCCON = 0b01110001;  /// 8 MHz

  LCD_INIT();
  OW_setup();
  APP_Init();
  OW_start();
  TMR_Init();
  //StartAnim();
  while (TRUE) 
  {
    TMR_Do();
    APP_Do();
    if ( g_Anim.enabled )
	    CLRWDT();
    else
	    OW_loop();
  }
}
