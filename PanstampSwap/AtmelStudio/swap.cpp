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

#include "panstamp.h"
#include "swap.h"
#include "swpacket.h"
#include "nvolat.h"
#include "inquiry.h"
#include "mediator.h"
#include "logger.h"
#include "repeater.h"

extern REGISTER regSecuNonce;
extern REGISTER regProductCode;

INQUIRY procInquiry;
MEDIATOR procMediator;
LOGGER procLogger;
REPEATER procRepeater;

/*static*/ void SWAP::tick()
{
  // Repeater enabled?
  PROCESSOR* p = swap.processor;
  while (p)
  {
    p->tick();
    p = p->pNext;
  }
}

/**
 * pacKetReceived
 *
 * CCPACKET received
 *
 * @param packet CCPACKET received
 */
/*static*/ void SWAP::onPacketReceived(CCPACKET *packet)
{
  if (packet->length <= SWAP_DATA_HEAD_LEN)
    return;
  
  SWPACKET swPacket = SWPACKET(packet);
  REGISTER *reg;

  #ifdef SWAP_EXTENDED_ADDRESS
  if (swPacket.addrType != SWAPADDR_EXTENDED)
    return;
  #else
  if (swPacket.addrType != SWAPADDR_SIMPLE)
    return;
  #endif
  
  // Repeater enabled?
  PROCESSOR* p = swap.processor;
  while (p)
  {
    if ( !p->packetHandler(&swPacket) )
      return;

    p = p->pNext;
  }

  // Smart encryption locally enabled?
  if (swap.security & 0x02)
  {
    // OK, then incoming packets must be encrypted too
    if (!(swPacket.security & 0x02))
      return;
  }

  // Function
  switch(swPacket.function)
  {
    case SWAPFUNCT_CMD:
      // Command not addressed to us?
      if (swPacket.destAddr != swap.devAddress)
        break;
      // Current version does not support data recording mode
      // so destination address and register address must be the same
      if (swPacket.destAddr != swPacket.regAddr)
        break;
      // Valid register?
      if ((reg = swap.getRegister(swPacket.regId)) == NULL)
        break;
      // Anti-playback security enabled?
      if (swap.security & 0x01)
      {
        // Check received nonce
        if (swap.nonce != swPacket.nonce)
        {
          // Nonce missmatch. Transmit correct nonce.
          reg = swap.getRegister(regSecuNonce.id);
          reg->getStatusPacket()->prepare()->send();
          break;
        }
      }
      // handle write protection reg->access == Public

      // Filter incorrect data lengths
      if (swPacket.value.length == reg->length)
      {
        reg = reg->setData(swPacket.value.data);
        if (reg)
          reg->save()->getStatusPacket()->prepare()->send();
      }
      else
        reg->getStatusPacket()->prepare()->send();
      break;

    case SWAPFUNCT_QRY:
      // Only Product Code can be broadcasted
      if (swPacket.destAddr == SWAP_BCAST_ADDR)
      {
        if (swPacket.regId != regProductCode.id)
          break;
      }
      // Query not addressed to us?
      else if (swPacket.destAddr != swap.devAddress)
        break;
      // Current version does not support data recording mode
      // so destination address and register address must be the same
      if (swPacket.destAddr != swPacket.regAddr)
        break;
      // Valid register?
      if ((reg = swap.getRegister(swPacket.regId)) == NULL)
        break;
      
      // handle write protection reg->access == Public, Readonly
      reg = reg->updateData();
      if (reg)
        reg->getStatusPacket(swPacket.srcAddr)->prepare()->send();
      break;

    case SWAPFUNCT_STA:
      // User callback function declared?
      if (swap.statusReceived != NULL)
        swap.statusReceived(&swPacket);
      break;

// todo: move into separate processor!
    case SWAPFUNCT_REQ:
      if (swPacket.destAddr != SWAP_BCAST_ADDR && swPacket.destAddr != swap.devAddress )
        break;

      if (swap.statusReceived != NULL)
        swap.statusReceived(&swPacket);

      // Behaves same as SWAPFUNC_STA but requests the receiver to acknowledge reception
      SWPACKET::replySwapStatusAck(&swPacket); 
      break;

    case SWAPFUNCT_ACK:
      if (swPacket.destAddr != SWAP_BCAST_ADDR && swPacket.destAddr != swap.devAddress )
        break;

      // receiver notifies us back about successfull reception
      SWPACKET::handleSwapStatusAck(&swPacket);
      break;

    default:
      break;
  }
}

/**
 * SWAP
 *
 * Class constructor
 */
SWAP::SWAP(void)
{  
  statusReceived = NULL;
  processor = NULL;
  encryptPwd = NULL;
  security = 0;
}

/**
 * init
 *
 * Initialize SWAP registers and stack
 */
void SWAP::init(void)
{
  uint8_t i;
  STORAGE nvMem;

  // Read signature from info/eeprom memory
  uint8_t signature[2];
  nvMem.read(signature, DEFAULT_NVOLAT_SECTION, NVOLAT_SIGNATURE, sizeof(signature));

  // Correct signature in non-volatile memory?
  if ((signature[0] != NVOLAT_SIGNATURE_HIGH) || (signature[1] != NVOLAT_SIGNATURE_LOW))
    nvolatToFactoryDefaults(); // Copy default settings in non-volatile memory  

  // Intialize registers
  REGISTER::initAll();
  
  // Config radio settings
  panstamp.radio.devAddress = devAddress & 0xFF; 
  panstamp.radio.setCCregs();
  
  // Attach RF ISR
  panstamp.attachInterrupt(SWAP::onPacketReceived);  

  // processors
  addProcessor(&procMediator);
  addProcessor(&procInquiry);
  addProcessor(&procLogger);
}

/**
 * enableRepeater
 *
 * Enable repeater mode
 *
 * @param maxHop Maximum repeater count. Zero if omitted
 */
void SWAP::enableRepeater(unsigned char maxHop)
{
  if ( maxHop )
  {
    procRepeater.init(maxHop);
    addProcessor(&procRepeater);
  }
  else
  {
    procRepeater.stop();
    removeProcessor(&procRepeater);
  }
}

void SWAP::addProcessor(PROCESSOR* pAddProcessor)
{
  // don't add the sam processor twice
  PROCESSOR* p = processor;
  while (p)
  {
    if ( p == pAddProcessor )
      return;
    p = p->pNext;
  }

  // add as first
  p = processor;
  processor = pAddProcessor;
  processor->pNext = p;
}

void SWAP::removeProcessor(PROCESSOR* pRemoveProcessor)
{
  PROCESSOR* p = processor;
  if ( p == pRemoveProcessor )
  {
    processor = pRemoveProcessor->pNext;
    return;
  }

  while (p)
  {
    if ( p->pNext == pRemoveProcessor )
    {
      p->pNext = pRemoveProcessor->pNext;
    }
    p = p->pNext;
  }
}

/**
 * goToSleep
 *
 * put the MCU in sleep mode during txInterval seconds
 */
void SWAP::goToSleep(void)
{
  int n = txInterval;
  if ( n < 0 || n > 180 )
    n = 5;

//  Serial.print("Sleeping for ");
//  Serial.print(n);
//  Serial.print(" seconds...\n");

  n *= 8;

  while (n--) 
  {
    HAL_TIME_DelayMs(125);
    tick();
  }
  
  /*
  systemState = SYSTATE_RXOFF;
  panstamp.sleepSec(txInterval);
  systemState = SYSTATE_RXON;
  */
}

/**
 * nvolatToFactoryDefaults
 * 
 * Write default config values in non-volatile memory
 */
void SWAP::nvolatToFactoryDefaults(void)
{
  STORAGE nvMem;

  // Signature
  uint8_t signature[] = {NVOLAT_SIGNATURE_HIGH, NVOLAT_SIGNATURE_LOW};
  nvMem.write(signature, DEFAULT_NVOLAT_SECTION, NVOLAT_SIGNATURE, sizeof(signature));
  
  // Frequency channel
  uint8_t channel[] = {CCDEF_CHANNR};
  nvMem.write(channel, DEFAULT_NVOLAT_SECTION, NVOLAT_FREQ_CHANNEL, sizeof(channel));
  
  // Sync word
  uint8_t syncW[] = {CCDEF_SYNC1, CCDEF_SYNC0};
  nvMem.write(syncW, DEFAULT_NVOLAT_SECTION, NVOLAT_SYNC_WORD, sizeof(syncW));

  // SWAP address (pseudo-random number)
  uint16_t random = panstamp.getRand();
  uint8_t addr[] = {(random >> 8) & 0xFF, random & 0xFF};
  nvMem.write(addr, DEFAULT_NVOLAT_SECTION, NVOLAT_DEVICE_ADDR, sizeof(addr));
  
  // TX interval: 15 seconds
  uint8_t txInt[] = {15, 0};
  nvMem.write(txInt, DEFAULT_NVOLAT_SECTION, NVOLAT_TX_INTERVAL, sizeof(txInt));
}

/**
 * Pre-instantiate SWAP object
 */
SWAP swap;
