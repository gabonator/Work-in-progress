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

#include "config.h"
#include "register.h"
#include "commonregs.h"
#include "inquiry.h"
#include "DHT.h"

enum {
  DHT_DATA = A4,
  DHT_POWER = A5,
  DHT_GROUND = A2
};

DHT dht(DHT_DATA, DHT22);

const bool updtSensor(REGISTER* pRegister);

/*
 * Definition of custom registers
 */

// Dummy register to maintain their order
REGISTER regVoltSupply(NULL, 0, NULL, NULL, REGISTER::NoAccess);

// Sensor value register
byte dtSensor[4];
REGISTER regSensor(dtSensor, sizeof(dtSensor), &updtSensor, NULL, REGISTER::Public);

byte dtTargetAddr[1] = {0};
REGISTER regTargetAddr(dtTargetAddr, sizeof(dtTargetAddr), NULL, NULL, REGISTER::Private);

byte dtMediateAddr[1] = {0};
REGISTER regMediateAddr(dtMediateAddr, sizeof(dtMediateAddr), NULL, NULL, REGISTER::Private);

/**
 * Definition of custom getter/setter callback functions
 */
 
/**
 * updtSensor
 *
 * Measure sensor data and update register
 *
 * 'rId'  Register ID
 */
const bool updtSensor(REGISTER* pRegister)
{
  // Power sensor
  pinMode(DHT_DATA, INPUT);

  pinMode(DHT_GROUND, OUTPUT);
  digitalWrite(DHT_POWER, LOW);

  pinMode(DHT_POWER, OUTPUT);
  digitalWrite(DHT_POWER, HIGH);

  delay(1500);

  // Read humidity
  float h = dht.readHumidity();
  // Read temperature
  float t = dht.readTemperature();

  // Unpower sensor
  digitalWrite(DHT_POWER, LOW);
  // TODO: shoud set dht_data as output to reduce consumption

  if ( isnan(h) || isnan(t) ) 
  {
    // set invalid value
    Serial.print("sensor error!\n");
    pRegister->value[0] = 0xEE;
    pRegister->value[1] = 0xEE;
    pRegister->value[2] = 0xEE;
    pRegister->value[3] = 0xEE;
    return true;
  }

  uint16_t humidity = h * 10;
  uint16_t temperature = t * 10;

  Serial.print("read temp=");
  Serial.print(temperature);
  Serial.print(" read hum=");
  Serial.print(humidity);
  Serial.print("\n");

  pRegister->value[0] = (temperature >> 8) & 0xFF;
  pRegister->value[1] = temperature & 0xFF;
  pRegister->value[2] = (humidity >> 8) & 0xFF;
  pRegister->value[3] = humidity & 0xFF;

  return true;
}
