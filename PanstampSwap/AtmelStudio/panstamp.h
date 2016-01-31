#ifndef _PANSTAMP
#define _PANSTAMP

#include "common.h"
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
  uint16_t getRand(void); // freezes when function is called 'rand'!
};

extern CPanstamp panstamp;

#endif
