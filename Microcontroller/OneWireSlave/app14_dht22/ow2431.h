#ifndef __OW2431_H__
#define __OW2431_H__

#include "compiler.h"

#define OW_2431_SCRATCHPAD_LEN 13
extern volatile byte OW_2431_scratchpad[OW_2431_SCRATCHPAD_LEN];
extern volatile bank1 byte OW_2431_data[16];
extern volatile byte OW_2431_scratchpadWrite;

byte Emulate2431(byte ow_buffer);

#endif