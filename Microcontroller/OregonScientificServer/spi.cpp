/**
 * Copyright (c) 2011 Daniel Berenguer <dberenguer@usapiens.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * panLoader is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with panLoader; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 03/03/2011
 */

#include "spi.h"


#include "tinysoftwarespi.h"


void CSPI::init() 
{
/*
  sck = D7 = PD7  7
  ss = d8 = PB0   8
  mi = d6 = PD6   6
  mo = d5 = PD5   5
*/
	//begin(byte SCK_, byte MOSI_, byte MISO_, byte SS_);
  softSPI.begin(7, 5, 6, 8);
}

byte CSPI::send(byte value) 
{
	return softSPI.transfer(value);
}

#if 0
/**
 * init
 * 
 * SPI initialization
 */
void CSPI::init() 
{
  digitalWrite(SPI_SS, HIGH);
  
  // Configure SPI pins
  pinMode(SPI_SS, OUTPUT);
  pinMode(SPI_MOSI, OUTPUT);
  pinMode(SPI_MISO, INPUT);
  pinMode(SPI_SCK, OUTPUT);

  digitalWrite(SPI_SCK, HIGH);
  digitalWrite(SPI_MOSI, LOW);

  // SPI speed = clk/4
  SPCR = _BV(SPE) | _BV(MSTR);
}

/**
 * send
 * 
 * Send byte via SPI
 * 
 * 'value'	Value to be sent
 * 
 * Return:
 * 	Response received from SPI slave
 */
byte CSPI::send(byte value) 
{
  SPDR = value;                          // Transfer byte via SPI
  wait_Spi();                            // Wait until SPI operation is terminated

  return SPDR;
}

#endif