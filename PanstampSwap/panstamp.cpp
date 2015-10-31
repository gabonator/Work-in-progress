#include "panstamp.h"

#define enableIRQ_GDO0()          ::attachInterrupt(0, radioISR, FALLING);
#define disableIRQ_GDO0()         ::detachInterrupt(0);

CPanstamp panstamp;

/**
 * radioISR
 *
 * Radio interrupt routine
 */
void radioISR(void)
{
  // Disable interrupt
  disableIRQ_GDO0();

  if (panstamp.radio.rfState == RFSTATE_RX)
  {
    static CCPACKET ccPacket;
    bool eval = true;

    // Any packet waiting to be read?
    if (panstamp.radio.receiveData(&ccPacket) > 0)
    {
      // Is CRC OK?
      if (ccPacket.crc_ok)
      {
        if (panstamp.ccPacketReceived != NULL)
          panstamp.ccPacketReceived(&ccPacket);
      }
    }
  }
  
  // Enable interrupt
  enableIRQ_GDO0();
}

void CPanstamp::reset()
{
  //wdt_disable();  
  //wdt_enable(WDTO_15MS);
  //while (1) {}  
  Serial.begin(9600);
  while (1)
    Serial.print("Reboot!\n");
}

void CPanstamp::goToWirelessBoot()
{
  
}

void CPanstamp::attachInterrupt(void (*funct)(CCPACKET*))
{
  ccPacketReceived = funct;
}


//attachInterrupt(0, cc1101signalsInterrupt, FALLING);

void CPanstamp::init(uint8_t freq, uint8_t mode)
{
  // Calibrate internal RC oscillator
//  rcOscCalibrate();

  // Setup CC1101
  radio.init(freq, mode);

  delayMicroseconds(50);  

  // Enter RX state
  radio.setRxState();

  // Attach callback function for GDO0 (INT0)
  enableIRQ_GDO0();

  // Default values
//  state = RXON;
}

void CPanstamp::sleepSec(int n) 
{ 
  Serial.print("Should sleep for ");
  Serial.print(n);
  Serial.print("seconds...\n");
  delay(5000);
  //while (n--) delay(1000); 
}

uint16_t CPanstamp::GET_RANDOM(void)
{
  return OSCCAL;
}
