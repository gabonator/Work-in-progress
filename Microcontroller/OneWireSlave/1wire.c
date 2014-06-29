/* 1wire.c
 * basic 1-wire slave functions
 *
 * Copyright (C) 2011 Bartek Fabiszewski (www.fabiszewski.net)
 *
 * This is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "config.h"

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
/*
// main function for implementing "search rom" command
// returns 1 if currently compared bit is positively matched
byte OW_match_search (byte write_bit)
{
	byte result=0;
	OW_write_bit(write_bit); 		    // send bit
	while(OW);
	OW_write_bit(write_bit ^ 0x01);		// sent complement bit
	while(OW);
	if (OW_read_bit() == write_bit)		// read bit and compare with sent one
		result = 1;						// match
	if(ow_error)
		result = 0;						// error during reading 1-wire line
	return result;
}
*/
// main function for implementing "match rom" command
// returns 1 if currently compared bit is positively matched
byte OW_match_bits (byte read_bit)
{
	byte result=0;
	if (OW_read_bit() == read_bit)		// read bit on 1-wire line and compare with current one
		result = 1;						// match
	if(ow_error)
		result = 0;
	return result;
}
// 1-wire slave write bit
// must be run immediately after line is pulled down by master
void OW_write_bit (byte write_bit)
{
	if (write_bit)
	{
		//writing a bit '1'
		__delay_us(55);//55					// bus is already pulled high by pullup resistor, so just wait
	}
	else
	{
		//writing a bit '0'
		drive_OW_low();						// drive the bus low
		__delay_us(17);//15
		drive_OW_high();					// release the bus
		__delay_us(35);//35
	}
}

// 1-wire slave write byte
// must be initiated immediately after line is pulled down by master
// unfolded for increased speed
void OW_write_byte (byte write_data)
{
		OW_write_bit(write_data & 0x01); 	// sending LS-bit first
		while(OW);							// wait for master set bus low
		write_data >>= 1;					// shift the data byte for the next bit to send
		OW_write_bit(write_data & 0x01); 	
		while(OW);
		write_data >>= 1;				
		OW_write_bit(write_data & 0x01); 	
		while(OW);
		write_data >>= 1;					
		OW_write_bit(write_data & 0x01); 	
		while(OW);
		write_data >>= 1;					
		OW_write_bit(write_data & 0x01); 	
		while(OW);
		write_data >>= 1;		
		OW_write_bit(write_data & 0x01);
		while(OW);
		write_data >>= 1;					
		OW_write_bit(write_data & 0x01); 	
		while(OW);
		write_data >>= 1;					
		OW_write_bit(write_data & 0x01); 	
}

// 1-wire slave read bit
// must be run immediately after line is pulled down by master
byte OW_read_bit (void)
{
	byte read_data;
	byte del_count;

	__delay_us(10);//15
	read_data = OW;					// read the status of 1-wire line
	__delay_us(35);//35

	if (OW)
	{
		return read_data;			// return data when line is released
	}

	del_count = 40;
	do
	{
		if (OW)						// wait for master to release line
		{
			return read_data;
		}
	} while (del_count--);
	ow_error = 1;					// bus is held low for too long, probably unpredicted reset
									// FIXME: here we need immediate jump to reset detection and response with pulse
									// currently unpredicted resets are not handled properly because
									// we return to reset detection too late (too many nested functions to return from)
	return 0;

}
// 1-wire slave read byte
// must be run immediately after line is pulled down by master
byte OW_read_byte (void)
{
	// I unfold this and some other loops to meet very strict time limits
	byte result=0;
	if (OW_read_bit())
		result |= 0x80;				// if result is one, then set MS-bit
	while(OW);
	result >>= 1; 				    // shift the result to get it ready for the next bit to receive
	if (OW_read_bit())
		result |= 0x80;	
	while(OW);
	result >>= 1; 		
	if (OW_read_bit())
		result |= 0x80;		
	while(OW);
	result >>= 1; 	
	if (OW_read_bit())
		result |= 0x80;		
	while(OW);
	result >>= 1; 			
	if (OW_read_bit())
		result |= 0x80;			
	while(OW);
	result >>= 1; 		
	if (OW_read_bit())
		result |= 0x80;
	while(OW);
	result >>= 1;
	if (OW_read_bit())
		result |= 0x80;
	while(OW);
	result >>= 1; 
	if (OW_read_bit())
		result |= 0x80;
	if(ow_error)
		return 0;
	return result;
}

// these functions are for 1-wire serial number checksum generation
void C_CRC(byte *CRCVal, byte value) {
	byte odd, bcnt;
	for (bcnt = 0; bcnt < 8; bcnt++) {
		odd = (value ^ *CRCVal) & 0x01;
		*CRCVal >>= 1;
		value >>= 1;
		if (odd != 0)
			*CRCVal ^= 0x8C;
	}
}
byte CalcCRC(byte code_len, byte *code) {
	byte i, CRCVal = 0;
	for (i = code_len; i > 0; i--)
		C_CRC(&CRCVal, code[i]);
	return CRCVal;
}


//byte OW_search_bit(byte data)
byte OW_match_search(byte data)
{
  //while(OW);
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
/*
byte OW_match_search (byte write_bit)
{
	byte result=0;
	OW_write_bit(write_bit); 		    // send bit
	while(OW);
	OW_write_bit(write_bit ^ 0x01);		// sent complement bit
	while(OW);
	if (OW_read_bit() == write_bit)		// read bit and compare with sent one
		result = 1;						// match
	if(ow_error)
		result = 0;						// error during reading 1-wire line
	return result;
}
*/

