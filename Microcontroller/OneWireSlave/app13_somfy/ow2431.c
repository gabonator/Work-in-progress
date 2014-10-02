#include "ow2431.h"
#include "owutils.h"
#include "fastcall.h"

volatile byte OW_2431_address = 0;
volatile byte bank1 OW_2431_data[16];
volatile byte OW_2431_scratchpadWrite = 0;
volatile byte OW_2431_scratchpad[OW_2431_SCRATCHPAD_LEN];

extern void onScratchadWrite(void);

unsigned short crc16(unsigned short crc, byte data)
{
  static const byte oddparity[16] =
   { 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 };

  // Even though we're just copying a byte from the input,
  // we'll be doing 16-bit computation with it.
  unsigned short cdata = data;
  cdata = (cdata ^ crc) & 0xff;
  crc >>= 8;

  if (oddparity[cdata & 0x0F] ^ oddparity[cdata >> 4])
    crc ^= 0xC001;

  cdata <<= 6;
  crc ^= cdata;
  cdata <<= 1;
  crc ^= cdata;
  return crc;
}

byte Emulate2431(byte ow_buffer)
{
  FASTCALL();
  // F0 (TA1-low_addr) (TA2-high_addr) (R:D00...) - read eeprom
  if ( ow_buffer == 0xf0 )
  {
    //OW_2431_address = 0;
    OW_2431_address = OW_read_byte(); // low address byte
    FASTCALL();
    OW_read_byte(); // high address byte
    do {
      byte bData = 0;
      if ( OW_2431_address < 16 )
        bData = eeprom_read(OW_2431_address + 128);
      else 
      if ( OW_2431_address < 16+16 )
        bData = OW_2431_data[OW_2431_address - 16];
      else
      if ( OW_2431_address < 32+32 )
        bData = eeprom_read(OW_2431_address - 32 + 128 + 16);
      else
      if ( OW_2431_address >= 128 /*&& OW_2431_address <= 255*/ )
        bData = eeprom_read(OW_2431_address);

      if ( !OW_write_byte(bData) )
        break;

      OW_2431_address++;
    } while (1);
  }

  // AA (R:D00..D12) - Read scratchpad
  if ( ow_buffer == 0xaa )
  {
    byte i = 0;
    do {
      if ( !OW_write_byte(OW_2431_scratchpad[i]) )
        break;
    } while (++i < OW_2431_SCRATCHPAD_LEN);
  }

  // 55 (TA1) (TA2) (ES) - Copy scratchpad
  if ( ow_buffer == 0x55 )
  {
    byte i;

    if ( OW_2431_scratchpad[0] != OW_read_byte() ) // low address byte
      return FALSE;
    if ( OW_2431_scratchpad[1] != OW_read_byte() ) // high address byte
      return FALSE;
    if ( OW_2431_scratchpad[2] != OW_read_byte() ) // ES
      return FALSE;

    // finish writing scratchpad to addr OW_2431_address
    for (i=0; i<8; i++)
    {
      byte addr = OW_2431_scratchpad[0] + i;
      byte data = OW_2431_scratchpad[3+i];

      if ( /*i >= 0 && */ addr <= 15 )
        OW_2431_data[addr] = data; 
      if ( addr >= 128 /* && i <= 255 */ )
        eeprom_write(addr, data);
    }
  }

  // 0F (TA1) (TA2) (D00..08) - Write scratchpad
  if ( ow_buffer == 0x0f )
  {
    unsigned short crc = 0;
    byte i = 0;

    OW_2431_scratchpad[i++] = OW_read_byte(); // addr low
    OW_2431_scratchpad[i++] = OW_read_byte(); // addr high
    OW_2431_scratchpad[i++] = 0x01; // ES
    
    do {
      OW_2431_scratchpad[i] = OW_read_byte();
    } while (++i < 8+3 && !ow_error);

    if (ow_error)
      return FALSE;

    for (i=0; i<8; i++)
      crc = crc16(crc, OW_2431_scratchpad[3+i]);

    OW_2431_scratchpad[11] = crc & 0xff;
    OW_2431_scratchpad[12] = crc >> 8;

    if ( !OW_write_byte(OW_2431_scratchpad[11]) )
      return FALSE;
    if ( !OW_write_byte(OW_2431_scratchpad[12]) )
      return FALSE;

    OW_2431_scratchpadWrite = 1;
  }

  return TRUE;
}
