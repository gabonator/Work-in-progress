#include <Wire.h>
#include <SoftwareSerial.h>
#include "MP3.h"
#include "DS1307new.h"

const byte volumeClock = 0x1F;
const byte volumeClockNight = 0x12;
const byte volumeNoise = 0x1b;

/** define mp3 class */
MP3 mp3;
bool bTest = true;

void VerifyTime()
{
  uint16_t startAddr = 0x0000;            // Start address to store in the NV-RAM
  uint16_t lastAddr;                      // new address for storing in NV-RAM
  uint16_t TimeIsSet = 0;            // Helper that time must not set again
  
  #define CHECK 0x6ab6
  
  RTC.setRAM(0, (uint8_t *)&startAddr, sizeof(uint16_t));// Store startAddr in NV-RAM address 0x08 

  RTC.getRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
  if (TimeIsSet != CHECK)
  {
    RTC.stopClock();
        
    RTC.fillByYMD(2015,31,7);
    RTC.fillByHMS(13,02,00);
    
    RTC.setTime();
    TimeIsSet = CHECK;
    RTC.setRAM(54, (uint8_t *)&TimeIsSet, sizeof(uint16_t));
    RTC.startClock();
  }
  else
  {
    RTC.getTime(false);
  }

}
void WriteTime()
{
  RTC.getTime(false);
  if (RTC.hour < 10)                    // correct hour if necessary
  {
    Serial.print("0");
    Serial.print(RTC.hour, DEC);
  } 
  else
  {
    Serial.print(RTC.hour, DEC);
  }
  Serial.print(":");
  if (RTC.minute < 10)                  // correct minute if necessary
  {
    Serial.print("0");
    Serial.print(RTC.minute, DEC);
  }
  else
  {
    Serial.print(RTC.minute, DEC);
  }
  Serial.print(":");
  if (RTC.second < 10)                  // correct second if necessary
  {
    Serial.print("0");
    Serial.print(RTC.second, DEC);
  }
  else
  {
    Serial.print(RTC.second, DEC);
  }
  Serial.print(" ");
  if (RTC.day < 10)                    // correct date if necessary
  {
    Serial.print("0");
    Serial.print(RTC.day, DEC);
  }
  else
  {
    Serial.print(RTC.day, DEC);
  }
  Serial.print("-");
  if (RTC.month < 10)                   // correct month if necessary
  {
    Serial.print("0");
    Serial.print(RTC.month, DEC);
  }
  else
  {
    Serial.print(RTC.month, DEC);
  }
  Serial.print("-");
  Serial.print(RTC.year, DEC);          // Year need not to be changed
  /*
  Serial.print(" ");
  switch (RTC.dow)                      // Friendly printout the weekday
  {
    case 1:
      Serial.print("MON");
      break;
    case 2:
      Serial.print("TUE");
      break;
    case 3:
      Serial.print("WED");
      break;
    case 4:
      Serial.print("THU");
      break;
    case 5:
      Serial.print("FRI");
      break;
    case 6:
      Serial.print("SAT");
      break;
    case 7:
      Serial.print("SUN");
      break;
  }
  */
  Serial.print("\n");
}
void InitTime()
{
  pinMode(A3, OUTPUT); digitalWrite(A3, 1);
  pinMode(A2, OUTPUT); digitalWrite(A2, 0);
  RTC.ctrl = 0x00;                      // 0x00=disable SQW pin, 0x10=1Hz,
                                       // 0x11=4096Hz, 0x12=8192Hz, 0x13=32768Hz
  RTC.setCTRL();
}


void setup()
{
  InitTime();
  VerifyTime();
  Serial.begin(9600);
  Serial.print("start\n");
  pinMode(13, OUTPUT);
  digitalWrite(13, 0);

  mp3.begin(MP3_SOFTWARE_SERIAL);    // select software serial
  mp3.volume(volumeNoise);

  mp3.stop();
  
  if (0)
  {
      mp3.volume(volumeClock);
      pinMode(13, OUTPUT);
      digitalWrite(13, 1);
      delay(2000);
      for ( int i=4; i<7; i++)
      {
        mp3.set_mode(MP3::SINGLE);
        mp3.play_spi_flash(i);
        delay(4000);
      }    
      mp3.volume(volumeNoise);
      digitalWrite(13, 0);
  }
  
  
  
  mp3.set_mode(MP3::REPEAT);
  mp3.play_sd(1);
  delay(300);
  
  /** play music in USB-disk */ 
  //mp3.play_usb_disk(0x0001);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, 0);
  /** play music in SPI FLASH */ 
  //mp3.play_spi_flash(0x0001);
}

void loop()
{
  static int nLastSecond = -1;
  delay(200);
  RTC.getTime();
  if ( RTC.second != nLastSecond )
  {
    nLastSecond = RTC.second;

    if ( bTest || ((RTC.second == 0) && (RTC.minute == 0) /*&& (RTC.hour >= 6) && (RTC.hour <= 21)*/) )
    {
      bTest = false;
      Serial.print("Bing bang\n");
      
      mp3.stop();
      delay(100);
      if ( RTC.hour < 6 || RTC.hour > 21 )
        mp3.volume(volumeClockNight);
      else
        mp3.volume(volumeClock);
      digitalWrite(13, 1);
      delay(3000);
  
      int nCount = RTC.hour;
      if ( nCount > 12 )
        nCount -= 12;
      for ( int i=0; i<nCount; i++)
      {
        mp3.set_mode(MP3::SINGLE);
        mp3.play_spi_flash(6);
        delay(2200);
      }
      
      mp3.stop();
      digitalWrite(13, 0);
        delay(1000);
      mp3.volume(volumeNoise);      
      mp3.set_mode(MP3::REPEAT);
      mp3.stop();
      mp3.play_sd(1);
      mp3.play_sd(1);
//      mp3.play_sd(0x0001);
      return; 
    }
    if ( (RTC.second == 0) && ((RTC.minute % 5) == 0) && (RTC.hour >= 7) && (RTC.hour < 19) )
    {
      Serial.print("Turning on!\n");

      digitalWrite(13, 1);
//      mp3.set_mode(MP3::SINGLE);
//      mp3.play_sd(0x0001);    
    }
    if ( RTC.second == 25 )
    {
      digitalWrite(13, 0);
    }
    
    WriteTime();

  }
  #if 0
  /*
  return;
	static int i = 0;
	if ( digitalRead(4) == 0 )
	{
		i++;
		Serial.print("Sel tune");
		Serial.print(i);
		Serial.print("\n");
		delay(500);
	}
	if ( digitalRead(5) == 0 )
	{
		i--;
		Serial.print("Sel tune");
		Serial.print(i);
		Serial.print("\n");
		delay(500);
	}
	if ( digitalRead(3) == 0 )
	{
		/*
		Serial.print("Copy!\n");
			mp3.usb_to_flash();
			while (1);
			*/
		Serial.print("Play!\n");
		mp3.play_spi_flash(i);
		//i = (i+1)%12;
		//mp3.play_usb_disk(0x0003);
		delay(500);
	}
	/** function code here */
  //delay(5000);
  //mp3.next();
*/
#endif
}
