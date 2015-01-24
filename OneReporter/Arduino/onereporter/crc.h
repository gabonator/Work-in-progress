#ifndef _GCRC_H_
#define _GCRC_H_

#include <Arduino.h>

class CRC
{
  public:
  static unsigned long crc_update(unsigned long crc, byte data);
  static unsigned long crc_string(char *s, unsigned long base = ~0L);
  static unsigned long crc_string(const char *s, unsigned long base = ~0L);
};

//extern CRC Crc;

#endif
