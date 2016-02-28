#ifndef _LOGGER_H
#define _LOGGER_H

#include "panstamp.h"
#include "swpacket.h"
#include "config.h"
#include "processor.h"

/**
 * Class declaration
 */
class LOGGER : public PROCESSOR
{
  private:
    bool enabled;

  public:
    LOGGER()
    {
      enabled = false;
    }

    /**
     * packetHandler
     *
     * ...
     *
     * @param packet Pointer to the SWAP packet received
     */
    virtual bool packetHandler(SWPACKET *packet) 
    {
      if ( !enabled )
        return true;

      CCPACKET& ccPacket = packet->getPacket();

      Serial.print("RX: ");
      dumpPacket(ccPacket);

      return true;
    }

    static void dumpPacket(CCPACKET& ccPacket, bool bExtra = true)
    {
      for ( uint8_t i = 0; i < ccPacket.length; i++ )
      {
        uint8_t data = ccPacket.data[i];
        if ( i > 0 )
          Serial.print(',');

        if ( data < 0x10 )
          Serial.print('0');
        Serial.print(data, CSerial::HEX);
      }

      if ( bExtra )
      {
        Serial.print(" crc=");
        Serial.print(ccPacket.crc_ok, CSerial::DEC);
        Serial.print(",rssi=");
        Serial.print(ccPacket.rssi, CSerial::DEC);
        Serial.print(",lqi=");
        Serial.print(ccPacket.lqi, CSerial::DEC);
      }
      
      Serial.print("\r\n");
    }

    void setEnabled(bool enable)
    {
      enabled = enable;
    }

    bool isEnabled()
    {
      return enabled;
    }
};

#endif

