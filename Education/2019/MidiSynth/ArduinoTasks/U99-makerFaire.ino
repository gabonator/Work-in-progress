#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs[12] = {
CapacitiveSensor(2,3), CapacitiveSensor(2,A5), CapacitiveSensor(2,5),
CapacitiveSensor(2,7), CapacitiveSensor(2,8), CapacitiveSensor(2,A3),
CapacitiveSensor(2,10), CapacitiveSensor(2,11), CapacitiveSensor(2,12),
CapacitiveSensor(2,A0),CapacitiveSensor(2,A1), CapacitiveSensor(2,A2)};

int was[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int freq[12] = {524, 554, 587, 622, 659, 698, 739, 783, 830, 880, 932, 987};
//int base[12] = {23, 14, 10, 26, 173, 170, 73, 116, 10, 7, 6};
//int base[12] = {4, 5, 3, 6, 19, 3, 10, 20, 3, 5, 4, 18};
//int base[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//int base[12] = {187, 165, 154, 126, 187, 187, 97, 145, 102, 144, 93, 167};
int base[12] = {203, 163, 161, 130, 192, 193, 103, 160, 107, 155, 102, 178 };
long since[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void NoteOn(int i)
{
  int note = 60+i;
  int channel = 0;
  int velocity = 127;
  
  Serial1.write(0x90 + channel);
  Serial1.write(note);
  Serial1.write(velocity);  

}

void NoteOff(int i)
{
  int note = 60+i;
  int channel = 0;
  int velocity = 127;

  Serial1.write(0x80 + channel);
  Serial1.write(note);
  Serial1.write(velocity);  
}

void SetInstrument(byte channel, byte i) 
{
  Serial1.write(0xC0 | channel);
  Serial1.write(i);
}

void DreamControl(word command, byte value)
{
  Serial1.write(0xb0);
  Serial1.write(0x63); 
  Serial1.write(command >> 8); // NRPN high = 0x37
  Serial1.write(0xb0);
  Serial1.write(0x62); 
  Serial1.write(command & 0xff); // NRPN low = 0x07
  Serial1.write(0xb0);
  Serial1.write(0x06); 
  Serial1.write(value); // NRPN value = 127  
}

void setup()                    
{
  Serial1.begin(31250);  
  delay(200);
  DreamControl(0x3707, 100);
  SetInstrument(0, 0);

  for (int i=0; i<12; i++)
    cs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
    
  Serial.begin(9600);
}

void loop()                    
{
    long start = millis();
    long total[12];
    for (int i=0; i<12; i++)
      total[i] = cs[i].capacitiveSensorRaw(5);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

    
    int threshold = 20;
    int is[12];
    for (int i=0; i<12; i++)
      is[i] = total[i] - base[i] > threshold;
/*
    for (int i=0; i<12; i++)
    {
      Serial.print(total[i]);
      Serial.print("\t");
    }
  */  
    for (int i=0; i<12; i++)
    {
      Serial.print(is[i]);    
    }
    Serial.print("\n");

    for (int i=0; i<12; i++)
    {
      if (is[i]==1 && was[i]==0)
      {
        NoteOn(i);
        was[i] = 1;
        since[i] = start;
      }
  
      if (is[i]==0 && was[i]==1)
      {
        NoteOff(i);
        was[i] = 0;
        since[i] = 0;
      }
    }

    int trigger = -1;
    for (int i=0; i<12; i++)
    {
      if (since[i] != 0 && start - since[i] > 5000)
      {
        if (trigger == -1)
          trigger = i;
        else
        {
          trigger = -1;
          break;
        }
      }
    }


    if (trigger != -1)
    {
      NoteOff(trigger);
      switch (trigger)
      {
        case 0: SetInstrument(0, 1-1); break;
        case 1: SetInstrument(0, 5-1); break;
        case 2: SetInstrument(0, 17-1); break;
        case 3: SetInstrument(0, 19-1); break;
        case 4: SetInstrument(0, 26-1); break;
        case 5: SetInstrument(0, 41-1); break;
        case 6: SetInstrument(0, 46-1); break;
        case 7: SetInstrument(0, 65-1); break;
        case 8: SetInstrument(0, 74-1); break;
        case 9: SetInstrument(0, 82-1); break;
        case 10: SetInstrument(0, 89-1); break;
        case 11: SetInstrument(0, 100-1); break;
        //case 9: SetInstrument(0, 128-1); break;
      }
      since[trigger] = -1;
      NoteOn(trigger);
      delay(100);
      NoteOff(trigger);
    }
    
    //delay(10);                             // arbitrary delay to limit data to serial port 
}