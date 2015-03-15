#include "ow2431.h"
#include "owutils.h"
#include "isreeprom.h"  

volatile byte OW_2431_address = 0;
volatile byte OW_2431_scratchpad_status = 0;
volatile byte OW_2431_scratchpad_len = 0;
volatile byte OW_2431_scratchpad[OW_2431_SCRATCHPAD_LEN];

volatile byte bank1 OW_2431_data[OW_2431_DATA_LEN];
volatile byte bank1 OW_2431_data_read = 0;

void CustomWrite(void);

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
    //OW_2431_address = 0;
    byte addr = OW_read_byte(); // low address byte
    OW_read_byte(); // high address byte
    do {
      byte bData = 0;
      if ( addr >= 16 && addr < 16+16 )
        bData = OW_2431_data[addr - 16];
      else
        bData = _eeprom_read(addr + 128);

      if ( !OW_write_byte(bData) )
        break;

      addr++;
    } while (1);
    OW_2431_data_read = 1;
    return TRUE;
  }
#if 0
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

      if ( addr >= 128 /* && i <= 255 */ )
        _eeprom_write(addr, data);
    }
  }

  // 0F (TA1) (TA2) (D00..08) - Write scratchpad
  if ( ow_buffer == 0x0f )
  {
    unsigned short crc = 0;
    byte i = 0;
    byte addrLow = OW_read_byte();
    byte addrHigh = OW_read_byte();

    if ( addrLow == 0xd1 && addrHigh == 0xaa )
    {
      CustomWrite();
      return TRUE;
    }

    OW_2431_scratchpad[i++] = addrLow; // addr low
    OW_2431_scratchpad[i++] = addrHigh; // addr high
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
  }
#else
  if ( ow_buffer == 0x0f )
  {
    unsigned short crc = 0;
    byte i = 0;
    byte addrLow = OW_read_byte();
    byte addrHigh = OW_read_byte();

    if ( addrLow == 0xc0 && addrHigh == 0xaa )
      CustomWrite();
    return TRUE;
  }
#endif

  return TRUE;
}

// 0F D1 AA ...
void CustomWrite(void)
{
  unsigned short crc = 0;
  unsigned short checkcrc = 0;
  byte i = 0;
  byte len;

  // ignore incoming data
  if ( OW_2431_scratchpad_status & 0x80 )
  {
    // lcd transfer interrupted!
    OW_2431_scratchpad_status |= 0x40;

    // skip all
    len = OW_read_byte();

    do {
      OW_read_byte();
    } while (++i < len && !ow_error);

    return;
  }

// 0x01 - buffer acquired, ready to process
// 0x02 - incorrect buffer length
// 0x04 - ow transmission error
// 0x08 - crc mismatch
// 0x10 - buffer not processed, overwritten with another
// 0x20 - user
// 0x40 - ow transmission during lcd upload, buffer ignored
// 0x80 - internal - lcd upload in progress

  if ( OW_2431_scratchpad_status & 0x01 ) // already valid received buffer, but not processed yet
    OW_2431_scratchpad_status |= 0x10;

  OW_2431_scratchpad_len = OW_read_byte(); 

  if ( OW_2431_scratchpad_len < 2 || OW_2431_scratchpad_len >= OW_2431_SCRATCHPAD_LEN ) 
  {
    OW_2431_scratchpad_status |= 0x02;
    return;
  }

  do {
    OW_2431_scratchpad[i] = OW_read_byte();
  } while (++i < OW_2431_scratchpad_len && !ow_error);

  if (ow_error)
  {
    OW_2431_scratchpad_status |= 0x04;
    return;
  }

  checkcrc = OW_2431_scratchpad[i-2] | ((unsigned short)OW_2431_scratchpad[i-1] << 8);

  crc = crc16(crc, OW_2431_scratchpad_len);
  for (i=0; i<OW_2431_scratchpad_len-2; i++)
    crc = crc16(crc, OW_2431_scratchpad[i]);

  if ( crc != checkcrc )
    OW_2431_scratchpad_status |= 0x08;

  OW_2431_scratchpad_status |= 0x01;
}
