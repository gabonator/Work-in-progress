#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_3 = CapacitiveSensor(2,3);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4 = CapacitiveSensor(2,4);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_5 = CapacitiveSensor(2,5);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_6 = CapacitiveSensor(2,7);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil

int wasC = 0;
int wasD = 0;
int wasE = 0;
int wasF = 0;

void setup()                    
{
   cs_3.set_CS_AutocaL_Millis(0xFFFFFFFF);
   cs_4.set_CS_AutocaL_Millis(0xFFFFFFFF);
   cs_5.set_CS_AutocaL_Millis(0xFFFFFFFF);
   cs_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
   Serial.begin(9600);
}

void loop()                    
{
    long start = millis();
    long total1 =  cs_3.capacitiveSensor(5);
    long total2 =  cs_4.capacitiveSensor(5);
    long total3 =  cs_5.capacitiveSensor(5);
    long total4 =  cs_6.capacitiveSensor(5);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing


    int threshold = 80;
    int isC = total1 > threshold;
    int isD = total2 > threshold;
    int isE = total3 > threshold;
    int isF = total4 > threshold;

    Serial.print(total1);                  // print sensor output 1
    Serial.print("\t");
    Serial.print(total2);                  // print sensor output 2
    Serial.print("\t");
    Serial.print(total3);                // print sensor output 3
    Serial.print("\t");
    Serial.print(total4);                // print sensor output 3
    Serial.print("\t");    
    Serial.print(isC);    
    Serial.print(isD);
    Serial.print(isE);
    Serial.print(isF);
    Serial.print("\n");


    // C
    if (isC==1 && wasC==0)
    {
      tone(12, 523);
      wasC = 1;
    }

    if (isC==0 && wasC==1)
    {
      noTone(12);
      wasC = 0;
    }
    // D
    if (isD==1 && wasD==0)
    {
      tone(12, 587);
      wasD = 1;
    }

    if (isD==0 && wasD==1)
    {
      noTone(12);
      wasD = 0;
    }
    // E
    if (isE==1 && wasE==0)
    {
      tone(12, 659);
      wasE = 1;
    }

    if (isE==0 && wasE==1)
    {
      noTone(12);
      wasE = 0;
    }
    // F
    if (isF==1 && wasF==0)
    {
      tone(12, 698);
      wasF = 1;
    }

    if (isF==0 && wasF==1)
    {
      noTone(12);
      wasF = 0;
    }
    
    delay(10);                             // arbitrary delay to limit data to serial port 
}