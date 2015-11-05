#ifndef _INQUIRY_H
#define _INQUIRY_H

#include "panstamp.h"
#include "swpacket.h"
#include "config.h"
#include "processor.h"

/**
 INQUIRYPROCESS class implements scanning network for devices in RX mode. 
 After issuing INQUIRY_FUNCTION with ResetAndScan command, all devices wich
 receive this message reply with acknowledge command with random delay. 
 Random delay is necessary for preventing network transmission conflicts. 
 When master receives acknowledge command from slave, calls OnDeviceFound
 handler and sends back Silent command to the slave. This informs the slave
 that it should not respond to following Scan commands.

 After some time, when all slaves have already sent their acknowledge 
 messagem while taking into account the time necessary for forwarding
 the packets through repeater , master issues Scan command. This does 
 the same as ResetAndScan, but only slave devices which has not received 
 Silent command from master will respond with acknowledge message (Hello).

 INQUIRY class processes all incomming packets and handles all the inquiry
 stuff for slave devices


 Master: R&S                    | Thanks Slave2, Thanks Slave1, Scan |
 Slave1:           Hello        |                                    |
 Slave2:     Hello              |                                    | 
 Slave3:                 Hello  |                                    |
 Slave4:                  Hello |                                    | ...

 Master:               | Thanks Slave4, Thanks Slave3, Scan |        |  
 Slave1:               |                                    |        |
 Slave2:               |                                    |  2.5s  |
 Slave3:         Hello |                                    |        |
 Slave4:  Hello        |                                    |        | ...

 Master: Scan |        | Scan |        | Done
 Slave1:      |        |      |        |
 Slave2:      |  2.5s  |      |  2.5s  |
 Slave3:      |        |      |        |
 Slave4:      |        |      |        |

 */



/**
 * Class declaration
 */
class INQUIRY : public PROCESSOR
{
  private:
    bool wasPaired;
  
  public:
    enum ECommand
    {
      ResetAndScan,  // master to slave
      Scan,          // master to slave
      Hello,         // slave to master
      Silent         // master to slave
    };

  public:
    INQUIRY()
    {
      wasPaired = false;
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
      // process only INQUIRY function
      if ( packet->function != SWAPFUNCT_INQUIRY )
        return true;

      ECommand command = (ECommand)packet->regId;

      // Broadcasted message by master
      if ( command == ResetAndScan )  
      {
        wasPaired = false;
        command = Scan;
      }

      if ( wasPaired )
        return false;

      // Broadcasted message by master
      if ( command == Scan )
      {
        uint16_t postpone = 100 + (panstamp.rand() & 511);

        // wait 100 .. 600ms to prevent traffic conflicts
        delay(postpone); 

        SWPACKET ackPacket;
        INQUIRY::buildInquiryPacket(&ackPacket, Hello, packet->srcAddr);
        ackPacket.send();
      }

      // Addressed ack from master to slave
      if ( command == Silent && packet->destAddr == swap.devAddress )
      {
        wasPaired = true;
      }

      // Master handling 'hello' from slave
      if ( command == Hello && packet->destAddr == swap.devAddress )
      {
        onDeviceFound(packet->srcAddr);

        // Thank you for indentifyng yourself, please do not respond to following Scan commands
        SWPACKET ackPacket;
        INQUIRY::buildInquiryPacket(&ackPacket, Silent, packet->srcAddr);
        ackPacket.send();
      }

      return false;
    }
  
    static void buildInquiryPacket(SWPACKET* swPacket, ECommand command, uint16_t masterAddr = SWAP_BCAST_ADDR)
    {
      swPacket->destAddr = masterAddr;
      swPacket->srcAddr = swap.devAddress;
      swPacket->hop = 0;
      swPacket->security = swap.security & 0x0F;
      swPacket->nonce = ++swap.nonce;
      swPacket->function = SWAPFUNCT_INQUIRY;
      swPacket->regAddr = swap.devAddress;
      swPacket->regId = command; // shared id
      swPacket->value.length = 0;
      swPacket->value.data = NULL;
      swPacket->value.type = SWDTYPE_INTEGER;
    }

    virtual void onDeviceFound(uint16_t srcAddr)
    {
    }
};

/**
 * Class declaration
 */
class INQUIRYPROCESS : public INQUIRY
{
  public:
    typedef const bool (*TDeviceFoundFunction)(uint16_t srcAddr);

  private:
    int m_nTryCount;
    TDeviceFoundFunction m_fDeviceFound;

  public:
    INQUIRYPROCESS() : INQUIRY()
    {
      m_fDeviceFound = NULL;
    }

    void doInquiry()
    {
      SWPACKET packet;
      m_nTryCount = 3;

      do {
        m_nTryCount--;

        INQUIRY::buildInquiryPacket(&packet, ResetAndScan);
        packet.send();
        delay(2500);

      } while (m_nTryCount > 0);
    }

    virtual void onDeviceFound(uint16_t srcAddr)
    {
      m_nTryCount = 3;
      if ( m_fDeviceFound )
        m_fDeviceFound(srcAddr);
    }

    void setOnDeviceFoundHandler(TDeviceFoundFunction fDeviceFound)
    { 
      m_fDeviceFound = fDeviceFound;
    }
};

#endif
