#ifndef _PANSTAMP
#define _PANSTAMP

#include "Arduino.h"
#include "cc1101.h"
#include "ccpacket.h"

// Minimalistic arduino compatible implementation of panstamp class
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
  uint16_t rand(void);
};

extern CPanstamp panstamp;

#endif
