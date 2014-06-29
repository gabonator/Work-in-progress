#ifndef __OWSLAVE_H__
#define __OWSLAVE_H__

#include "compiler.h"


// OW pin must match the interrupt enabled pin, cannot be changed!
#define OW       GPIO2	
#define TRIS_OW  TRISIO2

// user defined scratchpad length

#define OW_SCRATCHPAD_LEN 7

extern volatile byte OW_scratchpad[OW_SCRATCHPAD_LEN];
extern volatile byte OW_scratchpad_valid;
extern volatile byte OW_scratchpad_request;
extern volatile byte OW_serial[8];

// internal
void OW_setup(void);
void OW_loop(void);
void OW_start(void);
void OW_stop(void);

#endif