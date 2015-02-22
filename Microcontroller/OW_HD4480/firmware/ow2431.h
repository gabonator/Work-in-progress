#ifndef __OW2431_H__
#define __OW2431_H__

#include "compiler.h"

#define OW_2431_SCRATCHPAD_LEN 40
#define OW_2431_DATA_LEN 16

extern volatile byte OW_2431_scratchpad_len;
extern volatile byte OW_2431_scratchpad_status; 
extern volatile byte bank1 OW_2431_scratchpad[OW_2431_SCRATCHPAD_LEN];

extern volatile bank1 byte OW_2431_data[OW_2431_DATA_LEN];
extern volatile bank1 byte OW_2431_data_read;

byte Emulate2431(byte ow_buffer);

#endif