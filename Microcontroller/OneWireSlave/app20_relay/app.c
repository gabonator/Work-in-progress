#include "app.h"
#include "ow2431.h"
#include "crc.h"
#include "timer.h"
#include <string.h>

byte report_status;
unsigned int g_nTimeout;
byte g_nTimeoutState;
byte g_nState = 0;

byte hex(byte v)
{
  v &= 15;
  if ( v < 10 )
    return '0' + v;
  return 'a' + v - 10;
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

void _ITOA16(unsigned int* var, unsigned char decr, unsigned char* c)
{
  while ( *var >= decr ) 
  { 
    *var -= decr; 
    (*c)++; 
  }
}

byte AppIsRunning(void)
{
  return g_nTimeout > 0; // can go to sleep?
}

void AppUpdateBuffer(void)
{
  unsigned char crc = 0, i;
  unsigned int nTimeout = g_nTimeout;
  // invalidate
  OW_2431_data[15] = ' ';
  // prepare
  OW_2431_data[0] = 'O';
  OW_2431_data[1] = '0' + g_nState;
  OW_2431_data[2] = 'T';
  OW_2431_data[3] = '0';
  OW_2431_data[4] = '0';
  OW_2431_data[5] = '0';

  if ( nTimeout > 999 )
    nTimeout = 999;

  ITOA16( nTimeout, 100, OW_2431_data[3] );
  ITOA16( nTimeout, 10, OW_2431_data[4] );
  ITOA16( nTimeout, 1, OW_2431_data[5] );


  OW_2431_data[6]  = 'S';
  OW_2431_data[7]  = hex(report_status >> 4);
  OW_2431_data[8]  = hex(report_status & 0x0f);
  OW_2431_data[9]  = 'C';
  if ( OW_2431_scratchpad_len > 2 )
  {
    OW_2431_data[10] = hex(OW_2431_scratchpad[OW_2431_scratchpad_len-2] >> 4);
    OW_2431_data[11] = hex(OW_2431_scratchpad[OW_2431_scratchpad_len-2] & 0x0f);
    OW_2431_data[12] = hex(OW_2431_scratchpad[OW_2431_scratchpad_len-1] >> 4);
    OW_2431_data[13] = hex(OW_2431_scratchpad[OW_2431_scratchpad_len-1] & 0x0f);
  } else
  {
    OW_2431_data[10] = '?';
    OW_2431_data[11] = '?';
    OW_2431_data[12] = '?';
    OW_2431_data[13] = '?';
  }

  OW_2431_data[14] = '#';

  for (i=0; i<15; i++)
    crc = crcPush(crc, OW_2431_data[i]);

  // finish & validate
  OW_2431_data[15] = 0x40 + (crc&63);

  // update...
  if ( OW_2431_data_read )
    report_status = 0;  
}

void setState(byte nState)
{
  g_nState = nState;
  GPIO4 = nState;
//  GPIO5 = 0;
}

unsigned int parseTime(char *str)
{
  unsigned int nTemp = 0;
  while (*str >= '0' && *str <= '9')
  {
    if ( nTemp > 0 )
      nTemp *= 10;
    nTemp += *str - '0';
  }
  if (*str == 's')
  {
    return nTemp; // seconds
  }
  if (*str == 'm')
  {
    return nTemp * 60; // minutes
  }
  return 0; // wrong suffix
}

void AppProcessCommand(char *strCommand)
{
  if ( strcmp(strCommand, "on") == 0 )
  {
    setState(1);
    g_nTimeout = 0;
    return;
  }

  if ( strcmp(strCommand, "off") == 0 )
  {
    setState(0);
    g_nTimeout = 0;
    return;
  }

  if ( strncmp(strCommand, "on,", 3) == 0 )
  {
    unsigned int nTimeout = parseTime(strCommand+3);
    if ( nTimeout > 0 )
    {
      g_nTimeout = nTimeout;
      g_nTimeoutState = g_nState;
      TMR_nCounter = 0;
      setState(1);
      return;
    }
  }
  if ( strncmp(strCommand, "off,", 4) == 0 )
  {
    unsigned int nTimeout = parseTime(strCommand+4);
    if ( nTimeout > 0 )
    {
      g_nTimeout = nTimeout;
      g_nTimeoutState = g_nState;
      TMR_nCounter = 0;
      setState(0);
      return;
    }
  }
  OW_2431_scratchpad_status |= 0x20;
}

void AppInit(void)
{
  TRISIO4 = 0;
  TRISIO5 = 0;
  GPIO4 = 0;
  GPIO5 = 0;
}

void AppProcessScratchpad(void)
{
  /*
    '@on'
    '@off'
    '@on,5s'
    '@off,5s'
  */
  unsigned char i;
  if ( (OW_2431_scratchpad_status & 0x0f) == 0x01 )
  {
    OW_2431_scratchpad_status |= 0x80; // mark processing
//    if ( OW_2431_scratchpad[0] == 0x40 )
    {
      char* pCommand = (char*)OW_2431_scratchpad;
      byte nCommandLen = OW_2431_scratchpad_len-2;
      byte bZeroTemp = pCommand[nCommandLen];
      AppProcessCommand(pCommand); // process zero terminated string
      pCommand[nCommandLen] = bZeroTemp;
    }
    OW_2431_scratchpad_status &= ~0x80;
  }

  report_status |= OW_2431_scratchpad_status;
  OW_2431_scratchpad_status = 0;
}

void AppTimer()
{
  // 1 second timer
  if ( g_nTimeout == 0 )
    return;
  if ( --g_nTimeout == 0 )
  {
    setState(g_nTimeoutState);
  }
}
