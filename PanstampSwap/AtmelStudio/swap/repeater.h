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

#ifndef _REPEATER_H
#define _REPEATER_H

//#include "panstamp.h"
#include "swpacket.h"
//#include "config.h"
#include "processor.h"

enum CONFIG {
/**
 * Repeater options
 */

  // Amount of transactions to be saved for evaluation before repeating a packet
  // Maximum depth = 255
  REPEATER_TABLE_DEPTH = 20,

  // Expiration time (in ms) for any transaction
  REPEATER_EXPIRATION_TIME = 2000
};

/**
 * Class declaration
 */
class REPEATER : public PROCESSOR
{
  private:
    /**
     * Transaction
     */
    typedef struct
    {
      unsigned long timeStamp;  // Transmission time stamp (ms)
      unsigned char function;   // SWAP function
      unsigned char srcAddr;    // Source address
      unsigned char nonce;      // Cyclic nonce
      unsigned char regAddr;    // Register address
    } Transaction;

  private:
    /**
     * Maximum hop
     */
    uint8_t maxHopCount;

    /**
     * Array of latest transactions
     */
    Transaction transactions[REPEATER_TABLE_DEPTH];

    /**
     * saveTransaction
     *
     * Save transaction in array
     *
     * @param packet SWAP packet being repeated
     */
    void saveTransaction(SWPACKET *packet);

  public:
    /**
     * Enable flag
     */
    bool enabled;

    /**
     * init
     *
     * Initialize repeater
     *
     * @param maxHop maximum hop count
     */
    void init(uint8_t maxHop);

    /**
     * packetHandler
     *
     * Handle incoming packet. Repeat if necessary
     *
     * @param packet Pointer to the SWAP packet received
     */
    virtual bool packetHandler(SWPACKET *packet);

    /**
     * Class constructor
     */
    REPEATER(void);

    /**
     * start
     *
     * Start repeater
     */
    void start(void);

    /**
     * stop
     *
     * Stop repeater
     */
    void stop(void);
};

#endif

