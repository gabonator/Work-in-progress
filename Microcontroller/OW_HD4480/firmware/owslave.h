#ifndef __OWSLAVE_H__
#define __OWSLAVE_H__

#include "compiler.h"


// OW pin must match the interrupt enabled pin, cannot be changed!
#define OW        RB0
#define TRIS_OW   TRISB0
//#define PULLUP_OW WPU2

extern volatile bank1 byte OW_serial[8];

// internal
void OW_setup(void);
void OW_loop(void);
void OW_start(void);
void OW_stop(void);

// extern
void OW_EnterSleep(void);
void OW_LeaveSleep(void);

#endif