#ifndef _1wire_H
#define _1wire_H
#include "config.h"

#define ROM_CMD				1		// ROM Command

#define FUNCTION_CMD				2    	// Function Command

// macros
// I turned some functions into macros to avoid losing time on jumps
#define drive_OW_low() { TRIS_OW = OUTPUT; OW = LOW; }
#define drive_OW_high() { TRIS_OW = INPUT;}
#define OW_presence_pulse() {\
  	drive_OW_low(); \
	__delay_us(120); \
 	drive_OW_high(); \
}

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
byte C_CRC(byte CRCVal, byte value);
byte CalcCRC(byte code_len, byte *code);
byte OW_search_bit(byte data);

extern byte ow_error;

#endif
