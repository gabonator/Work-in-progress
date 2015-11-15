/**
 * Copyright (c) 2014 panStamp <contact@panstamp.com>
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
 * Creation date: 07/06/2011
 */

#ifndef _COMMONREGS_H
#define _COMMONREGS_H

#include "nvolat.h"
#include "register.h"
#include "swap.h"
#include "config.h"

const bool setSysState(REGISTER* pRegister, uint8_t *state);
const bool setFreqChannel(REGISTER* pRegister, uint8_t *channel);
const bool setDevAddress(REGISTER* pRegister, uint8_t *addr);
const bool setNetworkId(REGISTER* pRegister, uint8_t *nId);
const bool setTxInterval(REGISTER* pRegister, uint8_t *interval);

/**
 * Macro for the definition of registers common to all SWAP devices
 */
/* Product code */                                                                                                           
static uint8_t dtProductCode[8] = {(uint8_t)(SWAP_MANUFACT_ID >> 24), (uint8_t)(SWAP_MANUFACT_ID >> 16) , (uint8_t)(SWAP_MANUFACT_ID >> 8), (uint8_t)(SWAP_MANUFACT_ID),    
        (uint8_t)(SWAP_PRODUCT_ID >> 24), (uint8_t)(SWAP_PRODUCT_ID >> 16) , (uint8_t)(SWAP_PRODUCT_ID >> 8), (uint8_t)(SWAP_PRODUCT_ID)};                
REGISTER regProductCode(dtProductCode, sizeof(dtProductCode), NULL, NULL, REGISTER::Public);

/* Hardware version */                                                                                                       
static uint8_t dtHwVersion[4] = {(uint8_t)(HARDWARE_VERSION >> 24), (uint8_t)(HARDWARE_VERSION >> 16) , (uint8_t)(HARDWARE_VERSION >> 8), (uint8_t)(HARDWARE_VERSION)};     
REGISTER regHwVersion(dtHwVersion, sizeof(dtHwVersion), NULL, NULL, REGISTER::Public);

/* Firmware version */                                                                                                       
static uint8_t dtFwVersion[4] = {(uint8_t)(FIRMWARE_VERSION >> 24), (uint8_t)(FIRMWARE_VERSION >> 16) , (uint8_t)(FIRMWARE_VERSION >> 8), (uint8_t)(FIRMWARE_VERSION)};     
REGISTER regFwVersion(dtFwVersion, sizeof(dtFwVersion), NULL, NULL, REGISTER::Public);

/* System state */                                                                                                           
REGISTER regSysState(&swap.systemState, sizeof(swap.systemState), NULL, &setSysState, REGISTER::Public);

/* Frequency channel */                                                                                                      
REGISTER regFreqChannel(&panstamp.radio.channel, sizeof(panstamp.radio.channel), NULL, &setFreqChannel, REGISTER::ReadOnly, SWDTYPE_INTEGER, NVOLAT_FREQ_CHANNEL);  

/* Security option */                                                                                                        
REGISTER regSecuOption(&swap.security, sizeof(swap.security), NULL, NULL, REGISTER::Private);

/* Security password (not implemented yet) */                                                                                
static uint8_t dtPassword[1];                                                                                                   

REGISTER regPassword(dtPassword, sizeof(dtPassword), NULL, NULL, REGISTER::Private);

/* Security nonce */                                                                                                         
REGISTER regSecuNonce(&swap.nonce, sizeof(swap.nonce), NULL, NULL, REGISTER::Private);

/* Network Id */                                                                                                             
REGISTER regNetworkId(panstamp.radio.syncWord, sizeof(panstamp.radio.syncWord), NULL, &setNetworkId, REGISTER::ReadOnly, SWDTYPE_OTHER, NVOLAT_SYNC_WORD);  

/* Device address */                                                                                                         
REGISTER regDevAddress((uint8_t*)&swap.devAddress, sizeof(swap.devAddress), NULL, &setDevAddress, REGISTER::ReadOnly, SWDTYPE_INTEGER, NVOLAT_DEVICE_ADDRESS);  

/* Periodic Tx interval */                                                                                                   
REGISTER regTxInterval((uint8_t*)&swap.txInterval, sizeof(swap.txInterval), NULL, &setTxInterval, REGISTER::ReadOnly, SWDTYPE_INTEGER, NVOLAT_TX_INTERVAL);

/**
 * Macros for the declaration of global table of registers
 */

/**                                                         
 * setSysState                                              
 *                                                          
 * Set system state                                         
 *                                                          
 * 'id'     Register ID                                     
 * 'state'  New system state                                
 */                                                         
const bool setSysState(REGISTER* pRegister, uint8_t *state)       
{                                                           
  swap.systemState = state[0];                              
  switch(state[0])                                         
  {                                                         
    case SYSTATE_RESTART:                                  
      /* Send status message before restarting the mote */  
      swap.getRegister(regSysState.id)->getStatusPacket()->prepare()->_send();    
      panstamp.reset();                                     
      break;                                                
    case SYSTATE_UPGRADE:                                   
      panstamp.goToWirelessBoot();                          
      break;                                                
    default:                                                
      break;                                                
  }                                                         
  return true;
}                                                           
                                                            
/**                                                         
 * setFreqChannel                                           
 *                                                          
 * Set frequency channel                                    
 *                                                          
 * 'id'       Register ID                                   
 * 'channel'  New channel                                   
 */                                                         
const bool setFreqChannel(REGISTER* pRegister, uint8_t *channel)           
{                                                           
  if (channel[0] != regFreqChannel.value[0])                
  {                                                         
    /* Send status message before entering the new          
    frequency channel */    

    SWPACKET* packet = pRegister->getStatusPacket();
    packet->value.data = channel;
    packet->prepare()->_send();                                          
                                    
    /* Update register value */                             
    panstamp.radio.setChannel(channel[0]);                  
    /* Restart device */                                    
    panstamp.reset();                                       
  }       
  return true;                                                  
}                                                           
                                                            
                                                            
/**                                                         
 * setDevAddress                                            
 *                                                          
 * Set device address                                       
 *                                                          
 * 'id'    Register ID                                      
 * 'addr'  New device address                               
 */                                                         
const bool setDevAddress(REGISTER* pRegister, uint8_t *addr)               
{                                                           
  /* Send status before setting the new address */          
  SWPACKET* packet = pRegister->getStatusPacket();
  packet->value.data = addr;
  packet->prepare()->_send();                                          
  
  /* Set new SWAP address. BE to LE conversion */           
  regDevAddress.setValueFromBeBuffer(addr);                 
  /* Update register value */                               
  panstamp.radio.setDevAddress(addr[regDevAddress.length-1]); 
  return true;
}                                                           
                                                            
/**                                                         
 * setNetworkId                                             
 *                                                          
 * Set network id                                           
 *                                                          
 * 'rId' Register ID                                        
 * 'nId' New network id                                     
 */                                                         
const bool setNetworkId(REGISTER* pRegister, uint8_t *nId)       
{                                                           
  if ((nId[0] != regNetworkId.value[0]) ||                  
      (nId[1] != regNetworkId.value[1]))                    
  {                                                         
    /* Send status before taking the new network ID */      
    SWPACKET* packet = pRegister->getStatusPacket();
    packet->value.data = nId;
    packet->prepare()->_send();                                          
    /* Update register value */                             
    panstamp.radio.setSyncWord(nId);                        
  }                                                         
  return true;
}                                                           

/**                                                         
 * setTxInterval                                            
 *                                                          
 * Set periodic Tx interval                                 
 *                                                          
 * 'id'        Register ID                                  
 * 'interval'  New interval (in seconds)                    
 */                                                         
const bool setTxInterval(REGISTER* pRegister, uint8_t *interval)  
{                                                           
  /* Set new Tx interval. BE to LE conversion */            
  regTxInterval.setValueFromBeBuffer(interval);             
  return true;
}
#endif

