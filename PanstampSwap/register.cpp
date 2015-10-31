/**
 * Copyright (c) 2011 panStamp <contact@panstamp.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 06/03/2013
 */

#include "register.h"
#include "swstatus.h"
#include "swap.h"

/*static*/ uint8_t REGISTER::regIndex = 0;
/*static*/ REGISTER* REGISTER::pLast = NULL;
/*static*/ uint16_t REGISTER::ackWaitingNonce = (uint16_t)-1;

/**
 * init
 *
 * Initialize register
 */
void REGISTER::init(void)
{
  // Does the value need to be read from EEPROM?
  load();
}

/**
 * updateData
 * 
 * Update and get register value
 */
REGISTER* REGISTER::updateData(void) 
{
  // Update register value
  if (updateValue != NULL)
    updateValue(this);
  
  return this;
}

/**
 * setData
 * 
 * Set register value
 * 
 * @param data New register value
 */
REGISTER *REGISTER::setData(unsigned char *data) 
{
  // Update register value
  if (setValue != NULL)
    setValue(this, data);

  return this;
}

/**
 * load
 * 
 * ...
 * 
 */
REGISTER *REGISTER::load() 
{
  // Update register value
  if (eepromAddress >= 0)
  {
    STORAGE nvMem;
    
    // Read from info memory
    nvMem.read(value, eepromBank, eepromAddress, length);
  }

  return this;
}

/**
 * save
 * 
 * ...
 */
REGISTER *REGISTER::save() 
{
  if (eepromAddress >= 0)
  {
    STORAGE nvMem;   
    // Write info memory
    nvMem.write(value, eepromBank, eepromAddress, length);
  }
  return this;
}

/**
 * sendSwapStatus
 * 
 * Send SWAP status message
 */
REGISTER *REGISTER::sendSwapStatus(uint16_t targetAddr /* = SWAP_BCAST_ADDR */) 
{
  SWSTATUS packet = SWSTATUS(id, value, length, type, targetAddr);
  packet.send();
  return this;
}

/**
 * sendSwapStatusAck
 * 
 * ...
 */
REGISTER *REGISTER::sendSwapStatusAck(uint16_t targetAddr /* = SWAP_BCAST_ADDR */) 
{
  SWSTATUS packet = SWSTATUS(id, value, length, type, targetAddr);
  packet.function = SWAPFUNCT_REQ;

  // retry 2 times if no response in half second
  for ( uint8_t retry = 0; retry < 3; retry++)
  {  
    packet.send();
    REGISTER::ackWaitingNonce = packet.nonce;

    for ( uint8_t wait = 0; wait < 50; wait++)
    {
      delay(10); 

      // waiting for packet.nonce match, usually takes 85-105ms
      if ( receivedAck() ) 
        return this;
    }

    packet.nonce = ++swap.nonce;
  }

  return this;
}

/**
 * receivedAck
 * 
 * ...
 */
bool REGISTER::receivedAck(void)
{
  return REGISTER::ackWaitingNonce == (uint16_t)-1; 
}

/**
 * replySwapStatusAck
 * 
 * ...
 */
/*static*/ void REGISTER::replySwapStatusAck(SWPACKET* pRcvdPacket)
{
  // acknowledge sender that we received his message
  static uint8_t data;
  data = pRcvdPacket->nonce;
  
  SWSTATUS packet = SWSTATUS(pRcvdPacket->regId, &data, sizeof(data), SWDTYPE_INTEGER);
  packet.destAddr = pRcvdPacket->srcAddr;
  packet.function = SWAPFUNCT_ACK;
  packet.send();
}

/**
 * handleSwapStatusAck
 * 
 * ...
 */
/*static*/ void REGISTER::handleSwapStatusAck(SWPACKET* pRcvdPacket)
{
  // Got some acknowledge message, does it match?
  //REGISTER* reg = getRegisterById(pRcvdPacket->regId);

  if ( pRcvdPacket->value.length == 1 )
  {
    uint8_t ackNonce = pRcvdPacket->value.data[0];

    if ( ackNonce == REGISTER::ackWaitingNonce )
    {
      // this is what we have been waiting for!
      REGISTER::ackWaitingNonce = (uint16_t)-1;
    }
  }
}

/**
 * setValueFromBeBuffer
 *
 * Set curent value from a Big Endian buffer passed as argument
 *
 * @param beBuffer Big Endian buffer
 */
void REGISTER::setValueFromBeBuffer(unsigned char* beBuffer)
{
  unsigned char i;

  for(i=0 ; i<length ; i++)
    value[i] = beBuffer[length-1-i];
}

