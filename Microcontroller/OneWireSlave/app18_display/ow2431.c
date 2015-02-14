#include "ow2431.h"
#include "owutils.h"
#include "isreeprom.h"

volatile byte OW_2431_address = 0;
volatile byte OW_2431_scratchpad_status = 0;
volatile byte OW_2431_scratchpad_len = 0;
volatile byte OW_2431_scratchpad_addr = 0;
volatile byte OW_2431_scratchpad[OW_2431_SCRATCHPAD_LEN];

volatile byte bank1 OW_2431_data[16];
volatile byte bank1 OW_2431_data_read = 0;

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
  // F0 (TA1-low_addr) (TA2-high_addr) (R:D00...) - read eeprom
  if ( ow_buffer == 0xf0 )
  {
//	status = 0xf0;
    //OW_2431_address = 0;
    OW_2431_address = OW_read_byte(); // low address byte
    OW_read_byte(); // high address byte
    do {
      byte bData = 0;
      if ( OW_2431_address >= 16 && OW_2431_address < 16+16 )
        bData = OW_2431_data[OW_2431_address - 16];
      else if ( OW_2431_address < 64 )
        bData = _eeprom_read(OW_2431_address + 128);
      else 
        bData = 0;

      if ( !OW_write_byte(bData) )
        break;

      OW_2431_address++;
    } while (1);
    OW_2431_data_read = 1;
    return TRUE;
  }

  // 0F (TA1) (TA2) (D00..08) - Write scratchpad
  // 0F (addr F0/F1/F2) (D00..0F) (CRC) (CRC)
  if ( ow_buffer == 0x0f )
  {
    unsigned short crc = 0;
    unsigned short checkcrc = 0;
    unsigned char len = 0;
    byte i = 0;

    if ( OW_2431_scratchpad_status & 0x01 ) // already valid received buffer, but not processed yet
      OW_2431_scratchpad_status |= 0x10;

    OW_2431_scratchpad_addr = OW_read_byte(); // F0 - first row, F1 - second row, F2 - raw
    OW_2431_scratchpad_len = OW_read_byte();
    _ASSUME( OW_2431_scratchpad_len <= 16 );

    if ( OW_2431_scratchpad_len > 16 ) 
    {
      OW_2431_scratchpad_status |= 0x02;
      return FALSE;
    }

    do {
      OW_2431_scratchpad[i] = OW_read_byte();
    } while (++i < OW_2431_scratchpad_len && !ow_error);

    if (ow_error)
    {
      OW_2431_scratchpad_status |= 0x04;
      return FALSE;
    }

    checkcrc = OW_read_byte();
    checkcrc |= ((unsigned short)OW_read_byte() << 8);

    crc = crc16(crc, OW_2431_scratchpad_addr);
    crc = crc16(crc, OW_2431_scratchpad_len);
    for (i=0; i<OW_2431_scratchpad_len; i++)
      crc = crc16(crc, OW_2431_scratchpad[i]);

    if ( crc != checkcrc )
      OW_2431_scratchpad_status |= 0x08;

    OW_2431_scratchpad_status |= 0x01;
    return TRUE;
  }
  return TRUE;
}
