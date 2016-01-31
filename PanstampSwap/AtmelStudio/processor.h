#ifndef _PROCESSOR_H
#define _PROCESSOR_H

#include "swpacket.h"

class PROCESSOR 
{
public:
  PROCESSOR* pNext;

public:
  PROCESSOR() : pNext(NULL)
  {
  }

  virtual bool packetHandler(SWPACKET *packet) = 0;
  virtual void tick() {}
};

#endif
