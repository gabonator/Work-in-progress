# DIY klavir

## U0: Prvy ton

 ![Pinout](ArduinoMicro.png)

 - pouzit vstavanu ukazku blink (Arduino -> File -> Examples -> 01. Basics -> Blink)
 - pouzit pin 12 alebo 13 (interna LED)
 - perioda obdlznikoveho signalu T = Ton + Toff
 - perioda T [s, sekundy], frekvencia f [Hz, hertz, kmity za sekundu], f = 1/T, T = 1/f


## U1: A440 

  ![Tabulka frkvencii](FrequencyTable.jpg)

  - upravit program z U0 aby zahral ton 440 Hz
  - pouzit delayMicroseconds(n) namiesto (n)
  - 1 s = 1000 ms = 1000000 us

    ```arduino
    void setup() 
    {
      pinMode(12, OUTPUT);
    }

    /*
     *  A4
     *  f = 440Hz
     *  T = ? s
     *  T = ? ms
     *  T = ? us
     *  Ton = Toff = ? us
     */

    void loop() 
    {
      digitalWrite(12, HIGH);
      delayMicroseconds(?);
      digitalWrite(12, LOW);
      delayMicroseconds(?);
    }
    ```

## U2: Funkcia tone a noTone

  - pouzit funkciu tone(pin, frekvencia), a noTone(pin)

## U3: Akord

  - zahrat akord

    ```arduino
    void setup()
    {
    }

    /*
     *  C dur = ? ? ?
     *  
     *  ?6 = ? Hz
     *  ?6 = ? Hz
     *  ?6 = ? Hz
     */

    void loop() 
    {  
      tone(12, ?);
      delay(200);
      tone(12, ?);
      delay(200);
      tone(12, ?);
      delay(200);
      noTone(12);
      delay(5000);
    }
    ```

## U4: Melodia

  ![Tabulka tonov](PitchTable.png)

  - http://L.valky.eu/klavirgen

## U5: Midi melodia

  - upravit predosly program aby namiesto pieza pouzival MIDI

    ```arduino
    void setup()
    {
      Serial1.begin(31250);
    }

    void NoteOn(int note)
    {
      Serial.write(?);
      Serial.write(?);
      Serial.write(?);
    }

    void NoteOff(int note)
    {
      Serial.write(?);
      Serial.write(?);
      Serial.write(?);
    }
    ```

  ![Tabulka nastrojov](MidiInstruments.png)
  
  - riesenie [predoslej ulohy](ArduinoTasks/U04-melodyPiezo.ino)

## U6: USB Midi melodia

    ```arduino
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
    ```

  - [online multiplayer piano](http://www.multiplayerpiano.com)

## U7: Knizinca CapacitiveSensor

    ```arduino
    #include <CapacitiveSensor.h>

    // 4 - send pin, 2 - sensor pin
    CapacitiveSensor cs = CapacitiveSensor(4, 2);

    void setup()
    {
       cs.set_CS_AutocaL_Millis(0xFFFFFFFF);
       Serial.begin(9600);
    }

    void loop()
    {
        long start = millis();
        long measure = cs.capacitiveSensor(30);

        Serial.print(millis() - start); // kolko ms trvalo meranie?
        Serial.print("\t"); // tabulator
        Serial.print(measure); // vysledok
        Serial.print("\n"); // novy riadok
        delay(100);
    }
    ```

## U8: Trigger

  - globalna premenna

    ```c
    int bolZapnuty = 0;
    
    void update()
    {
      int jeZapnuty = ...;

      if (bolZapnuty == 0 && jeZapnuty == 1)
      {
        Serial.print("On\n");
        jeZapnuty = 1;
      }
      if (bolZapnuty == 1 && jeZapnuty == 0)
      {
        Serial.print("Off\n");
        jeZapnuty = 0;
      }
    }
    ```

## U09: Styri klavesy C, D, E, F

  - rozsirit program na styri nezavisle senzory
  - zahrat kohutik jarabi

## U10: Cela oktava

  - rozsirit program na celu oktavu
  - hrat tony s piezom

## U11: MIDI Klavesy

  - cez uart ako v ulohe U5

## U12: USB MIDI klavesy

  - midi usb

## U13: Piano	
 
    ```c
    void Preposli()
    {
      while (Serial.available())
        Serial.write(Serial.read());
    }
    ```
