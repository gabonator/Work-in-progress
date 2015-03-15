#ifndef __APP_H__
#define __APP_H__

#include "compiler.h"

byte AppIsRunning(void);
void AppProcessScratchpad(void);
void AppUpdateBuffer(void);
void AppTimer(void);
void AppInit(void);
#endif