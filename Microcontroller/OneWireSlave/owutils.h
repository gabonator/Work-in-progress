#ifndef __OWUTILS_H__
#define __OWUTILS_H__

#include "owslave.h"

#define CMD_INIT 0
#define CMD_ROM 1
#define CMD_FUNCTION 2

// macros
// I turned some functions into macros to avoid losing time on jumps
#define drive_OW_low() { TRIS_OW = OUTPUT; OW = LOW; }
#define drive_OW_high() { TRIS_OW = INPUT;}
#define OW_presence_pulse() \
  { \
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
byte OW_reset_pulse (void);
byte OW_read_byte (void);
byte OW_read_byte_lost10(void);
byte OW_match_search (byte write_bit);
byte OW_match_bits (byte read_bit);
byte OW_search_bit(byte data);
byte OW_write_byte(byte data);
byte OW_calcCrc(byte *code, byte code_len);

extern byte ow_error;

#endif
