#ifndef _PANSTAMP
#define _PANSTAMP

#include "Arduino.h"
#include "cc1101.h"
#include "ccpacket.h"

typedef unsigned char uint8_t;

class CPanstamp
{
public:
  CC1101 radio;
  void init(uint8_t freq, uint8_t mode);

  void reset();
  void goToWirelessBoot();
  void (*ccPacketReceived)(CCPACKET *packet);
     
  void attachInterrupt(void (*funct)(CCPACKET*));
  void sleepSec(int n);
     inline uint16_t GET_RANDOM(void)
     {
       return OSCCAL;
     }

};

extern CPanstamp panstamp;

#endif
