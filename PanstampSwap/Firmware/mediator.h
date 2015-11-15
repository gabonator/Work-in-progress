#ifndef _MEDIATOR_H
#define _MEDIATOR_H

#include "panstamp.h"
#include "swpacket.h"
#include "config.h"

/**
 This processor allows master to communicate with distant nodes without repeater.
 For talking to distant node we will use third node called Mediator to forward
 our query:
  
   MASTER ------ MEDIATOR ---- SLAVE

 Using ::MediateRequest function we wrap regular request into FORWARD_REQ request
 wich is sent to Mediator node. Mediator unwraps FORWARD_REQ and sends the request
 to slave node. Slave processes this query and sends status back to mediator.
 Mediator remembers that he is waiting for response for forwarded request, if it
 receives reponse from slave, it wraps it into FORWARD_ACK function and sends this
 response to Master with RSSI and LQI identifiers:

   Master -> Mediator: FORWARD_REQ{QUERY ProductCode}
   Mediator -> Slave: QUERY ProductCode
   Slave -> Mediator: STATE ProductCode
   Mediator -> Master: FORWARD_ACK{STATE ProductCode, RSSI}

 By doing this, we can query distant nodes by knowing the topology of our network,
 next benefit of this approach is the ability to obtain RSSI values of any two
 nodes. From RSSI value we can guess the distance of nodes and by knowing 
 distances of all pairs of nodes, it is possible to calculate the network topology 
 layout.

 */

/**
 * Class declaration
 */
class MEDIATOR : public PROCESSOR
{
  private:
    uint16_t masterAddr;
    uint16_t checkAddr;
    uint16_t checkRegAddr;
    uint8_t checkRegId;
    bool waiting;

  public:
    /**
     * packetHandler
     *
     * ...
     *
     * @param packet Pointer to the SWAP packet received
     */
    virtual bool packetHandler(SWPACKET *packet) 
    {
      // from master
      if (packet->destAddr != swap.devAddress)
        return true;

      // master to mediator
      if ( packet->function == SWAPFUNCT_FORWARD_REQ )
      {
        masterAddr = packet->srcAddr;

        // tuto by sme mali aplikovat nase adresy a vsetko, iba function, payload
        UnmediateRequest(packet);

        waiting = true;
        checkAddr = packet->destAddr;   // !!! dstAddr !
        checkRegAddr = packet->regAddr;
        checkRegId = packet->regId;

        packet->prepare()->_send();
        // do not proces this packet by swap
        return false;
      }


      // from slave to mediator - INQUIRY
      if ( waiting )
      {
        waiting = true; // we must implement some mechanism to stop waiting
      }
      // from slave to mediator
      
      if ( waiting )
      {
        // do register matching, or broadcasted ?
        // in case of broadcasted INQUIRY function, we forward first ours packet to the master
        if ( (checkAddr == 0x00 && packet->srcAddr != masterAddr) || (packet->srcAddr == checkAddr && packet->regAddr == checkRegAddr && packet->regId == checkRegId) )
        {
          MediateAnswer(packet, masterAddr);
          packet->prepare()->_send();

          waiting = false;

          // do not process this packet by swap
          return false;
        }
      }

      // from mediator to master
      if ( packet->function == SWAPFUNCT_FORWARD_ACK )
      {        
        UnmediateAnswer(packet);

        // process this packet as if it was received in normal way
        return true;
      }

      return true;
    }

    static void MediateRequest(SWPACKET* swPacket, uint16_t mediatorAddr)
    {
      // todo check packet size!
      swPacket->srcAddr = swap.devAddress;
      swPacket->hop = 0;
      swPacket->security = swap.security & 0x0F;
      swPacket->nonce = ++swap.nonce;

      swPacket->value.data[swPacket->value.length++] = swPacket->function;
      swPacket->value.data[swPacket->value.length++] = swPacket->destAddr & 0xff;
      swPacket->value.data[swPacket->value.length++] = swPacket->destAddr >> 8;

      swPacket->function = SWAPFUNCT_FORWARD_ACK;
      swPacket->destAddr = mediatorAddr;
      swPacket->regAddr = swPacket->destAddr;
    }

    static void UnmediateRequest(SWPACKET* swPacket)
    {
      // todo check size!
      uint8_t* pMediatorHead = swPacket->value.data + swPacket->value.length;
      swPacket->value.length -= 3;

      swPacket->destAddr = pMediatorHead[-2] | (pMediatorHead[-1] << 8);
      swPacket->srcAddr = swap.devAddress;
      swPacket->hop = 0;
      swPacket->security = swap.security & 0x0F;
      swPacket->nonce = ++swap.nonce;
      swPacket->regAddr = swPacket->destAddr;

      swPacket->function = pMediatorHead[-3];
    }

    static void MediateAnswer(SWPACKET* swPacket, uint16_t destAddr)
    {
      swPacket->value.data[swPacket->value.length++] = swPacket->function;
      swPacket->value.data[swPacket->value.length++] = swPacket->getPacket().rssi;
      swPacket->value.data[swPacket->value.length++] = swPacket->getPacket().lqi;
      swPacket->function = SWAPFUNCT_FORWARD_ACK;
      swPacket->destAddr = destAddr;
//      swPacket->regAddr = swPacket->destAddr; // ?

      swPacket->srcAddr = swap.devAddress;
      swPacket->hop = 0;
      swPacket->security = swap.security & 0x0F;
      swPacket->nonce = ++swap.nonce;
    }

    static void UnmediateAnswer(SWPACKET* packet)
    { 
      // todo check size!
      uint8_t* pMediatorHead = packet->value.data + packet->value.length;
      // mark this packet, lqi&rssi are not from mediator!
      packet->hop = (uint8_t)-1; 
      packet->function = pMediatorHead[-3]; 
      packet->getPacket().rssi = pMediatorHead[-2];
      packet->getPacket().lqi = pMediatorHead[-1];

      packet->value.length -= 3;
    }

};

#endif

