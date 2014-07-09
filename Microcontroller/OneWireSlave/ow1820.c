#include "ow1820.h"
#include "owutils.h"

volatile byte OW_1820_scratchpad[OW_1820_SCRATCHPAD_LEN];
volatile byte OW_1820_scratchpad_valid = 0;
volatile byte OW_1820_scratchpad_request = 0;

#define OW_2431_SCRATCHPAD_LEN 13
volatile byte OW_2431_address = 0;
volatile byte OW_2431_data[16];
volatile byte OW_2431_scratchpad[OW_2431_SCRATCHPAD_LEN];

byte Emulate1820(void)
{
  byte i;

  // Function command
  byte ow_buffer = OW_read_byte();
 
  if (ow_error)
    return FALSE;

  // DS1820
  if ( ow_buffer == 0xBE && OW_1820_scratchpad_valid ) // read scratchpad
  {
    i = 0;
    do {
      if ( !OW_write_byte(OW_1820_scratchpad[i]) )
        break;
    } while (++i < OW_1820_SCRATCHPAD_LEN);
  } 

  if ( ow_buffer == 0x44 ) // start conversion
  {
    OW_1820_scratchpad_valid = 0;
    OW_1820_scratchpad_request = 1;
  }

  // DS2431
  // AA (R:D00..D12) - Read scratchpad
  if ( ow_buffer == 0xaa )
  {
    i = 0;
    do {
      if ( !OW_write_byte(OW_2431_scratchpad[i]) )
        break;
    } while (++i < OW_2431_SCRATCHPAD_LEN);
  }

  // F0 (TA1-low_addr) (TA2-high_addr) (R:D00...) - read eeprom
  if ( ow_buffer == 0xf0 )
  {
    OW_2431_address = OW_read_byte(); // low address byte
    OW_read_byte(); // high address byte
    do {
      OW_2431_address &= 15;
      if ( !OW_write_byte(OW_2431_data[OW_2431_address]) )
        break;
      OW_2431_address++;
    } while (1);
  }

  // 55 (TA1) (TA2) (ES) - Copy scratchpad
  if ( ow_buffer == 0x55 )
  {
    byte bWriteAddr = OW_read_byte(); // low address byte
    OW_read_byte(); // high address
    OW_read_byte(); // protection code - ES
    // finish writing scratchpad to addr OW_2431_address
  }

  // 0F (TA1) (TA2) (D00..08) - Write scratchpad
  if ( ow_buffer == 0x0f )
  {
    OW_read_byte(); // low address byte
    OW_read_byte(); // high address
    i = 0;
    do {
      OW_2431_scratchpad[i] = OW_read_byte();
    } while (++i < OW_2431_SCRATCHPAD_LEN && !ow_error);
  }

  return TRUE;
}
