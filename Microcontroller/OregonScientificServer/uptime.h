//https://gist.github.com/AndiSHFR/1f8b71dbeae6ee9073e0

#include <Arduino.h>

/**
 * CalculateUptimeSeconds()
 * 
 * Handle millis() rollover and calculate the total uptime in seconds.
 * This function must be called at least once for every 50 days to be
 * able to see the rollover.
 */ 
unsigned long CalculateUptimeSeconds(void) {
  static unsigned int  _rolloverCount   = 0;    // Number of 0xFFFFFFFF rollover we had in millis()
  static unsigned long _lastMillis      = 0;    // Value of the last millis() 

  // Get the current milliseconds uptime from the system.
  // Note: This only works as long as no one else did hook up with timer0
  //       because the arduino system uses timer0 to manage delay() and millis().
  unsigned long currentMilliSeconds = millis();

  // If we had a rollover we count that.
  if (currentMilliSeconds < _lastMillis) {
    _rolloverCount++;
  }

  // Now store the current number of milliseconds for the next round.
  _lastMillis = currentMilliSeconds;    

  // Based on the current milliseconds and the number of rollovers
  // we had in total we calculate here the uptime in seconds since 
  // poweron or reset.
  // Caution: Because we shorten millis to seconds we may miss one 
  // second for every rollover (1 second every 50 days).
  return (0xFFFFFFFF / 1000 ) * _rolloverCount + (_lastMillis / 1000);  
}
