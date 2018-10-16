#pragma once

#include <stdint.h>

extern "C" 
{
  void Set_Posi(uint16_t x, uint16_t y);
  void Set_Pixel(uint16_t Color);
  void ExtFlash_CS_LOW(void);
  void ExtFlash_CS_HIGH(void);
}