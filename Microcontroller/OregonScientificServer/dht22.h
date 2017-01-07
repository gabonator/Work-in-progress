#include <arduino.h>

#define DHT_INVALID    -9999

extern signed int DHT_humidity;
extern signed int DHT_temperature;

byte DHT_read(byte pin);

