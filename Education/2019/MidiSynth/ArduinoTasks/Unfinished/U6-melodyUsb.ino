#include "MIDIUSB.h"

void setup()
{
}

void NoteOn(int note)
{
  int channel = 0;
  int velocity = 127;

  midiEventPacket_t noteOn = {0x09, 0x90 | channel, note, velocity};
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

void NoteOff(int note)
{
  int channel = 0;
  int velocity = 127;

  midiEventPacket_t noteOff = {0x08, 0x80 | channel, note, velocity};
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();
}

int C=0, Cis=1, D=2, Dis=3, E=4, F=5, Fis=6, G=7, Gis=8, A=9, Ais=10, B=11, None=12;
int BPM = 120;

// 120 beatov za minutu, kolko milisekund trva jeden beat?
int Beat = 60000L / BPM;
int Whole = Beat*4;
int Half = Whole/2;
int Quarter = Whole/4;
int Eigth = Whole/8;
int Sixteenth = Whole/16;
int Thirtysecond = Whole/32;
int WholeDot = Whole*1.5;
int HalfDot = Half*1.5;
int QuarterDot = Quarter*1.5;
int EigthDot = Eigth*1.5;
int SixteenthDot = Sixteenth*1.5;
int ThirtysecondDot = Thirtysecond*1.5;

int Frequency(int note)
{
  // A3 - 440 Hz (69)
  float semitonesDelta = note-69.0+12;
  float octavesDelta = semitonesDelta/12.0;
  float freq = 440.0*pow(2, octavesDelta);
  Serial.println(freq);
  return freq;
}

void Play(int note, int octave, int length)
{
  int noteIndex = 24 + octave*12 + note;
  if (note != None) 
  {
    NoteOn(noteIndex);
    delay(length);
    NoteOff(noteIndex);
  } else
  {
    delay(length);
  }
}

void loop() 
{  
  Serial.println("Hram!\n");
  Play(G, 2, Quarter);
  Play(Ais, 2, EigthDot);
  Play(G, 2, Sixteenth);
  Play(None, 0, Sixteenth);
  Play(G, 2, Sixteenth);
  Play(C, 3, Eigth);
  Play(G, 2, Eigth);
  Play(F, 2, Eigth);
  Play(G, 2, Quarter);
  Play(D, 3, EigthDot);
  Play(G, 2, Sixteenth);
  Play(None, 0, Sixteenth);
  Play(G, 2, Sixteenth);
  Play(Dis, 3, Eigth);
  Play(D, 3, Eigth);
  Play(Ais, 2, Eigth);
  Play(G, 2, Eigth);
  Play(D, 3, Eigth);
  Play(G, 3, Eigth);
  Play(G, 2, Sixteenth);
  Play(F, 2, Sixteenth);
  Play(None, 0, Sixteenth);
  Play(F, 2, Sixteenth);
  Play(D, 2, Eigth);
  Play(A, 2, Eigth);
  Play(G, 2, Half);
  delay(5000);
}