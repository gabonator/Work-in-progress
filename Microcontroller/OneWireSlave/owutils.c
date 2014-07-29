#include "owutils.h"
#include "owslave.h"

byte ow_error = 0;

// detect reset pulse
// returns 1 if pulse detected
byte OW_reset_pulse (void)
{
  int i;
  byte len;
  for ( len=0; len<50; len++)
  {
    __delay_us(10);
    if ( OW )
      break;
  }

  // vacsinou len=30
  if ( len < 10 )
    return 0;  

	return 1; // reset pulse detected
}

// main function for implementing "match rom" command
// returns 1 if currently compared bit is positively matched
byte OW_match_bits (byte read_bit)
{
	byte read_data;
	byte del_count;

  if ( read_bit )
  {
  	__delay_us(10);//15 
    if ( !OW )
      return 0;
	  __delay_us(35);//35

	  if (OW)
		  return 1;

  	del_count = 50;
	  do
	  {
	  	if (OW) // wait for master to release line
  	 		return 1;
  	} while (del_count--);
    return 0;
  } else
  {
  	__delay_us(10);//15 
    if ( OW )
      return 0;
	  __delay_us(35);//35

	  if (OW)
		  return 1;

  	del_count = 50;
	  do
	  {
	  	if (OW) // wait for master to release line
  	 		return 1;
  	} while (del_count--);
    return 0;
  }
}


// 1-wire slave write bit
// must be run immediately after line is pulled down by master
void OW_write_bit (byte write_bit)
{
  // LSB of write_bit is sent

	if ( (write_bit & 1) == 0 )
	{
		//writing a bit '0'
		drive_OW_low();						// drive the bus low
		__delay_us(28);//15
		drive_OW_high();					// release the bus
		__delay_us(16);//35
	}
	else
	{
		//writing a bit '1'
//		__delay_us(50);//55					// bus is already pulled high by pullup resistor, so just wait
		__delay_us(22);//55					// bus is already pulled high by pullup resistor, so just wait

    if (!OW)
    {
      ow_error = 1;
      return;
    }
		__delay_us(22);//55					// bus is already pulled high by pullup resistor, so just wait
	}
}   

// these functions are for 1-wire serial number checksum generationb
byte C_CRC(byte CRCVal, byte value) 
{
	byte odd, bcnt;
	for (bcnt = 0; bcnt < 8; bcnt++) 
  {
		odd = (value ^ CRCVal) & 0x01;
		CRCVal >>= 1;
		value >>= 1;
		if (odd != 0)
			CRCVal ^= 0x8C;
	}
  return CRCVal;
}

byte OW_calcCrc(byte *code, byte code_len)
{
	byte i, CRCVal = 0;
	for (i = 0; i<code_len; i++)
		CRCVal = C_CRC(CRCVal, code[i]);
	return CRCVal;
}

byte OW_match_search(byte data)
{
  //while(OW); // too late for calling this!
	if (data) 
	{
    // 1
		__delay_us(55);
    // 
		while (OW);
    // 0
		drive_OW_low();
		__delay_us(17);
		drive_OW_high();
		__delay_us(35);
		//        
    while(OW);

		// read bit
    __delay_us(10);
    if ( !OW )
      return 0;
	  __delay_us(35);
	  while (!OW);
	}
	else
	{
    // 0
		drive_OW_low();
		__delay_us(17);
		drive_OW_high();
		__delay_us(35);
    //
    while (OW);
    // 1
		__delay_us(55);
    //
    while(OW);
		// read bit
    __delay_us(10);
    if ( OW )
      return 0;
	  __delay_us(35);
	  while (!OW);
	}
  return 1;
}

byte OW_write_byte(byte write_data)
{
  byte high = 80;
  byte low = 255;

  // do not waste time if OW is already low
  do 
  {
    do 
    {
      if ( !OW )
      {
        // 1
        OW_write_bit(write_data);
        write_data >>= 1;
        if ( ow_error )
          return FALSE;
    		while(OW);

        // 2
        OW_write_bit(write_data);
        write_data >>= 1;
        if ( ow_error )
          return FALSE;
    		while(OW);

        // 3
        OW_write_bit(write_data);
        write_data >>= 1;
        if ( ow_error )
          return FALSE;
    		while(OW);

        // 4
        OW_write_bit(write_data);
        write_data >>= 1;
        if ( ow_error )
          return FALSE;
    		while(OW);

        // 5
        OW_write_bit(write_data);
        write_data >>= 1;
        if ( ow_error )
          return FALSE;
    		while(OW);

        // 6
        OW_write_bit(write_data);
        write_data >>= 1;
        if ( ow_error )
          return FALSE;
    		while(OW);

        // 7
        OW_write_bit(write_data);
        write_data >>= 1;
        if ( ow_error )
          return FALSE;
    		while(OW);

        // 8
        OW_write_bit(write_data); 	

        if ( ow_error )
          return FALSE;

        return TRUE;
      }
    } while (--low > 0);
  } while (--high > 0);

  return FALSE;
}



byte OW_read_byte_lost10 (void)
{
  #define DLY_PRE 20
  #define DLY_POST 15
  #define DLY_LOST 20
  #undef DBG      
  #define DBG(c) c //{GPIO5 = 1; {c} GPIO5 = 0;}
  byte result = 0;
 
  // bit 0
  __delay_us(DLY_PRE - DLY_LOST);
  DBG(if ( OW )
    result |= 1;
  __delay_us(DLY_POST); )
  
  while (!OW);
  // bit 1
  while (OW);

  __delay_us(DLY_PRE);
  DBG( if ( OW )
    result |= 2; 
  __delay_us(DLY_POST);)

  while (!OW);
  // bit 2
  while (OW);

  __delay_us(DLY_PRE);
  DBG( if ( OW )
    result |= 4; 
  __delay_us(DLY_POST); )

  while (!OW);
  // bit 3
  while (OW);

  __delay_us(DLY_PRE);
  DBG( if ( OW )
    result |= 8; 
  __delay_us(DLY_POST); )

  while (!OW);
  // bit 5
  while (OW);

  __delay_us(DLY_PRE);
  DBG( if ( OW )
    result |= 16; 
  __delay_us(DLY_POST); )

  while (!OW);
  // bit 6
  while (OW);

  __delay_us(DLY_PRE);
  DBG( if ( OW )
    result |= 32; 
  __delay_us(DLY_POST); )

  while (!OW);
  // bit 7
  while (OW);

  __delay_us(DLY_PRE);
  DBG( if ( OW )
    result |= 64; 
  __delay_us(DLY_POST); )

  while (!OW);
  // bit 8
  while (OW);

  __delay_us(DLY_PRE);
  if ( OW )
    result |= 128; 
  __delay_us(DLY_POST);

  while (!OW);

  return result;
}

byte OW_read_byte (void)
{
  #undef DLY_LOST
  #define DLY_LOST 0
  byte result = 0;

  // bit 0
  while (OW);
  __delay_us(DLY_PRE - DLY_LOST);
  DBG(if ( OW )
    result |= 1;
  __delay_us(DLY_POST); )
  
  while (!OW);
  // bit 1
  while (OW);

  __delay_us(DLY_PRE);
  DBG( if ( OW )
    result |= 2; 
  __delay_us(DLY_POST);)

  while (!OW);
  // bit 2
  while (OW);

  __delay_us(DLY_PRE);
  DBG( if ( OW )
    result |= 4; 
  __delay_us(DLY_POST); )

  while (!OW);
  // bit 3
  while (OW);

  __delay_us(DLY_PRE);
  DBG( if ( OW )
    result |= 8; 
  __delay_us(DLY_POST); )

  while (!OW);
  // bit 5
  while (OW);

  __delay_us(DLY_PRE);
  DBG( if ( OW )
    result |= 16; 
  __delay_us(DLY_POST); )

  while (!OW);
  // bit 6
  while (OW);

  __delay_us(DLY_PRE);
  DBG( if ( OW )
    result |= 32; 
  __delay_us(DLY_POST); )

  while (!OW);
  // bit 7
  while (OW);

  __delay_us(DLY_PRE);
  DBG( if ( OW )
    result |= 64; 
  __delay_us(DLY_POST); )

  while (!OW);
  // bit 8
  while (OW);

  __delay_us(DLY_PRE);
  if ( OW )
    result |= 128; 
  __delay_us(DLY_POST);

  while (!OW);

  return result;
}
