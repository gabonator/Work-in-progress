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
#include "swap.h"
#include "../panstamp/panstamp.h"

/*static*/ uint8_t REGISTER::regIndex = 0;
/*static*/ REGISTER* REGISTER::pLast = NULL;

extern REGISTER regSecuNonce;
static SWPACKET commonPacket; // TODO

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
    return updateValue(this) ? this : NULL;
  
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
  {
    return setValue(this, data) ? this : NULL;
  } else
  {
    if ( /*access == EPublic &&*/ type == SWDTYPE_INTEGER )
      setValueFromBeBuffer(data);
  }

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

SWPACKET* REGISTER::getStatusPacket()
{
  commonPacket.destAddr = SWAP_BCAST_ADDR;
  commonPacket.srcAddr = panstamp.m_swap.devAddress;
  commonPacket.hop = 0;
  commonPacket.security = panstamp.m_swap.security & 0x0F;
  commonPacket.nonce = ++panstamp.m_swap.nonce;
  commonPacket.function = SWAPFUNCT_STA;
  commonPacket.regAddr = panstamp.m_swap.devAddress;
  commonPacket.regId = id;
  commonPacket.value.length = length;
  commonPacket.value.data = value;
  commonPacket.value.type = type;

  return &commonPacket;
}


SWPACKET* REGISTER::getCommandPacket()
{
	commonPacket.destAddr = SWAP_BCAST_ADDR;
	commonPacket.srcAddr = panstamp.m_swap.devAddress;
	commonPacket.hop = 0;
	commonPacket.security = panstamp.m_swap.security & 0x0F;
	commonPacket.nonce = ++panstamp.m_swap.nonce;
	commonPacket.function = SWAPFUNCT_CMD;
	commonPacket.regAddr = panstamp.m_swap.devAddress;
	commonPacket.regId = id;
	commonPacket.value.length = length;
	commonPacket.value.data = value;
	commonPacket.value.type = type;

	return &commonPacket;
}

