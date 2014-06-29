/* 1wire.h
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

#ifndef _1wire_H
#define _1wire_H
#include "config.h"

// macros
// I turned some functions into macros to avoid losing time on jumps
#define drive_OW_low() { TRIS_OW = OUTPUT; OW = LOW; }
#define drive_OW_high() { TRIS_OW = INPUT;}
#define OW_presence_pulse() {\
  	drive_OW_low(); \
	__delay_us(120); \
 	drive_OW_high(); \
}

#define ROM_CMD				1		// ROM Command
#define FUNCTION_CMD				2    	// Function Command

#if 0
	#define SEARCH_SEND_BIT() \
	if (current_byte & 1)     \
	{                         \
    // 1                    \
		__delay_us(55);         \
    //                      \
		while (OW);             \
    // 0                    \
		drive_OW_low();         \
		__delay_us(17);         \
		drive_OW_high();        \
		__delay_us(35);         \
		//                      \
    while(OW);              \
		// read bit             \
    __delay_us(10);         \
    if ( !OW )              \
      break;                \
	  __delay_us(35);         \
	  while (!OW);            \
	}                         \
	else                      \
	{                         \
    // 0                    \
		drive_OW_low();         \
		__delay_us(17);         \
		drive_OW_high();        \
		__delay_us(35);         \
    //                      \
    while (OW);             \
    // 1                    \
		__delay_us(55);         \
    //                      \
    while(OW);              \
		// read bit             \
    __delay_us(10);         \
    if ( OW )               \
      break;                \
	  __delay_us(35);         \
	  while (!OW);            \
	}                         


			#define SEARCH_SEND_BYTE( data )     \
				current_byte = data;               \
				SEARCH_SEND_BIT();                 \	
				current_byte >>= 1;                \
				SEARCH_SEND_BIT();                 \ 	
				current_byte >>= 1;                \
				SEARCH_SEND_BIT();                 \	
				current_byte >>= 1;                \
				SEARCH_SEND_BIT();                 \
				current_byte >>= 1;                \
				SEARCH_SEND_BIT();                 \
				current_byte >>= 1;                \
				SEARCH_SEND_BIT();                 \	
				current_byte >>= 1;                \
				SEARCH_SEND_BIT();                 \ 	
				current_byte >>= 1;                \
				SEARCH_SEND_BIT();                 \


#endif

//#define SEARCH_SEND_BIT() OW_search_bit(current_byte)

#define SEARCH_SEND_BIT() while(OW); if (!OW_match_search(current_byte & 1)) break;

#define SEARCH_SEND_BYTE( data )  \
  current_byte = data;            \
  SEARCH_SEND_BIT();              \
  current_byte >>= 1;             \
  SEARCH_SEND_BIT();              \
  current_byte >>= 1;             \
  SEARCH_SEND_BIT();              \
  current_byte >>= 1;             \
  SEARCH_SEND_BIT();              \
  current_byte >>= 1;             \
  SEARCH_SEND_BIT();              \
  current_byte >>= 1;             \
  SEARCH_SEND_BIT();              \
  current_byte >>= 1;             \
  SEARCH_SEND_BIT();              \
  current_byte >>= 1;             \
  SEARCH_SEND_BIT();              

#define SEARCH_MATCH_BIT() while(OW); if(!OW_match_bits(current_byte & 1)) break;

#define SEARCH_MATCH_BYTE( data )  \
  current_byte = data;            \
  SEARCH_MATCH_BIT();              \
  current_byte >>= 1;             \
  SEARCH_MATCH_BIT();              \
  current_byte >>= 1;             \
  SEARCH_MATCH_BIT();              \
  current_byte >>= 1;             \
  SEARCH_MATCH_BIT();              \
  current_byte >>= 1;             \
  SEARCH_MATCH_BIT();              \
  current_byte >>= 1;             \
  SEARCH_MATCH_BIT();              \
  current_byte >>= 1;             \
  SEARCH_MATCH_BIT();              \
  current_byte >>= 1;             \
  SEARCH_MATCH_BIT();              

// prototypes
void OW_write_bit (byte write_data);
byte OW_read_bit (void);
byte OW_reset_pulse (void);
void OW_write_byte (byte write_data);
byte OW_read_byte (void);
byte OW_match_search (byte write_bit);
byte OW_match_bits (byte read_bit);
void C_CRC(byte *CRCVal, byte value);
byte CalcCRC(byte code_len, byte *code);
byte OW_search_bit(byte data);

#endif
