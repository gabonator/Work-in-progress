#include "ow1820.h"
#include "owutils.h"

volatile byte OW_1820_scratchpad[OW_1820_SCRATCHPAD_LEN];
volatile byte OW_1820_scratchpad_valid = 0;
volatile byte OW_1820_scratchpad_request = 0;

byte Emulate1820(byte ow_buffer)
{
  // DS1820
  if ( ow_buffer == 0xBE && OW_1820_scratchpad_valid ) // read scratchpad
  {
    byte i = 0;
    do {
      if ( !OW_write_byte(OW_1820_scratchpad[i]) )
        break;
    } while (++i < OW_1820_SCRATCHPAD_LEN);
  } else

  if ( ow_buffer == 0x44 ) // start conversion
  {
    OW_1820_scratchpad_valid = 0;
    OW_1820_scratchpad_request = 1;
  }

  return TRUE;
}
