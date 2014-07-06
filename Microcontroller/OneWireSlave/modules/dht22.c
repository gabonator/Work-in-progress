//    FILE: dht.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.13
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//     URL: http://arduino.cc/playground/Main/DHTLib

#include "dht22.h"

signed int DHT_humidity = 0;
signed int DHT_temperature = 0;
unsigned char bits[5];

#define OUTPUT 0
#define INPUT 1
#define LOW 0
#define HIGH 1

#define pinMode(pin, tris) TRISIO1 = tris
#define digitalWrite(pin, logic) GPIO1 = logic
#define digitalRead(pin) GPIO1

#define delayMicroseconds DelayUs
#define delay DelayMs
#define word(a, b) (((a)<<8)|(b))

#define DHTLIB_OK               0
#define DHTLIB_ERROR_CHECKSUM   0xe1
#define DHTLIB_ERROR_TIMEOUT    0xe2
#define DHTLIB_INVALID_VALUE    -999

#define DHTLIB_DHT_WAKEUP       1

// 100uS -> (x*5/8)|1 = 62, but reading a IO pin takes some time
#define DHTLIB_TIMEOUT 40

byte DHT_readSensor(void);

byte DHT_read(void)
{
    byte sum, rv;

    // READ VALUES
    rv = DHT_readSensor();
    if (rv != DHTLIB_OK)
    {
        DHT_humidity = DHTLIB_INVALID_VALUE;  // invalid value, or is NaN prefered?
        DHT_humidity = DHTLIB_INVALID_VALUE;  // invalid value
        return rv; // propagate error value
    }

    // CONVERT AND STORE
    DHT_humidity = word(bits[0], bits[1]); // x10
    DHT_temperature = word(bits[2] & 0x7F, bits[3]); // x10
    if (bits[2] & 0x80)  // negative temperature
        DHT_temperature = -DHT_temperature;

    // TEST CHECKSUM
    sum = bits[0] + bits[1] + bits[2] + bits[3];
    if (bits[4] != sum)
        return DHTLIB_ERROR_CHECKSUM;

    return DHTLIB_OK;
}

byte DHT_readSensor(void)
{
    // INIT BUFFERVAR TO RECEIVE DATA
    byte i;
    byte mask = 128;
    byte idx = 0;
    unsigned char loopCnt;

    // EMPTY BUFFER
    for (i = 0; i < 5; i++) 
      bits[i] = 0;

    // REQUEST SAMPLE
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(DHTLIB_DHT_WAKEUP);
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);
    pinMode(pin, INPUT);

    // GET ACKNOWLEDGE or TIMEOUT
    loopCnt = DHTLIB_TIMEOUT;
    while(digitalRead(pin) == LOW)
    {
        if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
    }

    loopCnt = DHTLIB_TIMEOUT;
    while(digitalRead(pin) == HIGH)
    {
        if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
    }

    // READ THE OUTPUT - 40 BITS => 5 BYTES
    for (i = 40; i != 0; i--)
    {
        loopCnt = DHTLIB_TIMEOUT;
        while(digitalRead(pin) == LOW)
        {
            if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
        }

// 100us -> timeout
        loopCnt = DHTLIB_TIMEOUT;
        while(digitalRead(pin) == HIGH)
        {
            if (--loopCnt == 0) return DHTLIB_ERROR_TIMEOUT;
        }

        //if ((micros() - t) > 40)
        if ( loopCnt < DHTLIB_TIMEOUT - 15 )
            bits[idx] |= mask;

        mask >>= 1;
        if (mask == 0)   // next byte?
        {
            mask = 128;
            idx++;
        }
    }
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);

    return DHTLIB_OK;
}

