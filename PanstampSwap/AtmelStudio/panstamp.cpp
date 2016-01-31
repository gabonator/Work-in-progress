#include "panstamp.h"
#include "hal.h"

//HAL::IO::Read(HAL::IO::D4)
#define enableIRQ_GDO0()          HAL::INT::Attach(HAL::IO::D4, radioISR); // ::attachInterrupt(0, radioISR, FALLING);
#define disableIRQ_GDO0()         HAL::INT::Attach(HAL::IO::D4, nullptr); //::detachInterrupt(0);

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

    // Any packet waiting to be read?
    if (panstamp.radio.receiveData(&ccPacket) > 0)
    {
      // Is CRC OK?
      //if (ccPacket.crc_ok)
      {
        if (panstamp.ccPacketReceived != nullptr)
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
  //Serial.begin(9600);
  //while (1)
//    Serial.print("Reboot!\n");
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
	// TODO: srand!
  //srand(analogRead(0) ^ OSCCAL);
  // Calibrate internal RC oscillator
//  rcOscCalibrate();

  // Setup CC1101
  radio.init(freq, mode);

  HAL_TIME_DelayUs(50);  

  // Enter RX state
  radio.setRxState();

  // Attach callback function for GDO0 (INT0)
  enableIRQ_GDO0();

  // Default values
//  state = RXON;
}

void CPanstamp::sleepSec(int n) 
{ 
  if ( n < 0 || n > 180 )
    n = 5;

  //Serial.print("Sleeping for ");
  //Serial.print(n);
  //Serial.print(" seconds...\n");

  while (n--) 
    HAL_TIME_DelayMs(1000); 
}

uint16_t CPanstamp::getRand(void)
{
  // todo: init, or custom PRNG
  return rand();
}


