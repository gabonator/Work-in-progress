#ifndef __OW1820_H__
#define __OW1820_H__

#include "compiler.h"

// user defined scratchpad length

#define OW_1820_SCRATCHPAD_LEN 7

extern volatile byte OW_1820_scratchpad[OW_1820_SCRATCHPAD_LEN];
extern volatile byte OW_1820_scratchpad_valid;
extern volatile byte OW_1820_scratchpad_request;

extern volatile byte OW_2431_data[16];

byte Emulate1820(void);

#endif