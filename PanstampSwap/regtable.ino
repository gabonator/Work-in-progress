/**
 * regtable
 *
 * Copyright (c) 2011 Daniel Berenguer <dberenguer@usapiens.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 03/31/2011
 */

#include "product.h"
#include "register.h"
#include "commonregs.h"

const void updtVoltSupply(REGISTER* pRegister);
const void updtSensor(REGISTER* pRegister);

/*
 * Definition of custom registers
 */
// Voltage supply
static unsigned long voltageSupply = 3300;
static byte dtVoltSupply[2];
REGISTER regVoltSupply(dtVoltSupply, sizeof(dtVoltSupply), &updtVoltSupply, NULL);

// Sensor value register
byte dtSensor[4];
REGISTER regSensor(dtSensor, sizeof(dtSensor), &updtSensor, NULL);


////const SWDTYPE _type=SWDTYPE_OTHER, EAccess _access=Public

/**
 * Definition of custom getter/setter callback functions
 */
 
/**
 * updtVoltSupply
 *
 * Measure voltage supply and update register
 *
 * 'rId'  Register ID
 */
const void updtVoltSupply(REGISTER* pRegister)
{  
  unsigned long result;
  
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  voltageSupply = result;     // Update global variable Vcc
  
  #ifdef VOLT_SUPPLY_A7
  
  // Read voltage supply from A7
  unsigned short ref = voltageSupply;
  result = analogRead(7);
  result *= ref;
  result /= 1024;
  #endif

  /**
   * register[eId]->member can be replaced by regVoltSupply in this case since
   * no other register is going to use "updtVoltSupply" as "updater" function
   */

  // Update register value
  pRegister->value[0] = (result >> 8) & 0xFF;
  pRegister->value[1] = result & 0xFF;
}

/**
 * updtSensor
 *
 * Measure sensor data and update register
 *
 * 'rId'  Register ID
 */
const void updtSensor(REGISTER* pRegister)
{
  dtSensor[0] = 0x12; //(temperature >> 8) & 0xFF;
  dtSensor[1] = 0x34; //temperature & 0xFF;
  dtSensor[2] = 0x56; //(humidity >> 8) & 0xFF;
  dtSensor[3] = 0x78; //humidity & 0xFF;
}
