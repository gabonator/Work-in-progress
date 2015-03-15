//#include "crc.h"
#include <TimerOne.h>
#include <EEPROM.h>
#include <OneWire.h>

OneWire ow(A0); 
long g_lTick = 0;

#define POLYNOMIAL 0x47

unsigned short crc16(unsigned short crc, byte data)
{
  static const byte oddparity[16] =
   { 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 };

  // Even though we're just copying a byte from the input,
  // we'll be doing 16-bit computation with it.
  unsigned short cdata = data;
  cdata = (cdata ^ crc) & 0xff;
  crc >>= 8;

  if (oddparity[cdata & 0x0F] ^ oddparity[cdata >> 4])
    crc ^= 0xC001;

  cdata <<= 6;
  crc ^= cdata;
  cdata <<= 1;
  crc ^= cdata;
  return crc;
}

void setup() 
{
  Serial.begin(9600);
  
  while(1)
  {
    sendBufferDbg("on,5s");
    Serial.println("-----");
    delay(1000);
  }
  
  onLoad();
  Serial.print(F("Starting main loop\n"));
  onInit();
}

void onLoad()
{
  Serial.print(F("\n\nValky.eu 2015 - ow test\n"));
  Serial.print(F("Built " __DATE__ " " __TIME__ "\n"));  

  initOw();
 }

void initOw()
{
  pinMode(A0, INPUT);
}

void sendBufferTo(char* data);

int nState = 0;
void update()
{
  byte addr[8];
  char strTemp[8];
  
  Serial.print("Scanning OW network:\n");
  
  ow.reset_search();
  while (ow.search(addr)) 
  {
    Serial.print("ADDR=");
    for( int i = 0; i < 8; i++) 
    {
      sprintf(strTemp, "%02x", addr[i]);
      Serial.print(strTemp);
    }
    Serial.print(":");
    
    if ( addr[0] == 0x2D )
    {
      // DS2480 read
      ow.reset();
      ow.select(addr);
      ow.write(0xf0);
      ow.write(0x10);
      ow.write(0x00);
      
      Serial.print(" \"");    
      for( int i = 0; i < 16; i++) 
      {
        char d = ow.read();
        sprintf(strTemp, "%c", d);
        Serial.print(strTemp);
      }
      /*
      delay(70);
      
      ow.reset();
      ow.select(addr);

      if ( nState )
        sendBufferTo("on");
      else
        sendBufferTo("off");
       delay(30);
      nState = 1-nState;*/
    } else
    {
        Serial.print("error");
    }
    Serial.print("\"\n");    
  }    
  Serial.print("OW scan done\n");  
}

void sendBuffer(char* data)
{
  unsigned short crc = 0;
  unsigned char len = strlen(data);
  crc = crc16(crc, len+2);  
//  crc = crc16(crc, type);  
  for (unsigned char i=0; i<len; i++)
    crc = crc16(crc, data[i]);
  
  ow.reset();
  ow.skip();
  ow.write(0x0f);
  ow.write(0xc0);
  ow.write(0xaa);
  ow.write(len+2);
//  ow.write(type);
  ow.write_bytes((unsigned char*)data, len);
  ow.write(crc & 0xff);
  ow.write(crc >> 8);
  
//   Serial.print("sent = ");
//  Serial.println(crc, HEX);
}

void sendBufferDbg(char* data)
{
  unsigned short crc = 0;
  unsigned char len = strlen(data);
  crc = crc16(crc, len+2);  
//  crc = crc16(crc, type);  
  for (unsigned char i=0; i<len; i++)
    crc = crc16(crc, data[i]);
  
  Serial.println(0x0f, HEX);
  Serial.println(0xc0, HEX);
  Serial.println(0xaa, HEX);
  Serial.println(len+2, HEX);
//  ow.write(type);
Serial.println(data);
//  ow.write_bytes((unsigned char*)data, len);
  Serial.println(crc & 0xff, HEX);
  Serial.println(crc >> 8, HEX);
  
//   Serial.print("sent = ");
//  Serial.println(crc, HEX);
}

void sendBufferTo(char* data)
{
  unsigned short crc = 0;
  unsigned char len = strlen(data);
  crc = crc16(crc, len+2);  
//  crc = crc16(crc, type);  
  for (unsigned char i=0; i<len; i++)
    crc = crc16(crc, data[i]);
  
  ow.write(0x0f);
  ow.write(0xc0);
  ow.write(0xaa);
  ow.write(len+2);
//  ow.write(type);
  ow.write_bytes((unsigned char*)data, len);
  ow.write(crc & 0xff);
  ow.write(crc >> 8);
  
//   Serial.print("sent = ");
//  Serial.println(crc, HEX);
}

void dump(unsigned char*p, int l)
{
   for (int i=0; i<l; i++)
   {
     Serial.print(p[i], HEX);
     Serial.print(" ");
   }
}

void onInit()
{
  delay(20);
  sendBuffer("off");   
  delay(50);
//  sendBuffer("on,5s");   
//  delay(30);
}


void loop() 
{
  
  update();
  delay(100);
  
  return;
  sendBuffer("on,5s");   
  delay(30);
  for ( int i=0; i<15; i++)
  {
    update();
    delay(500);
  }
  
  return;
  
  sendBuffer("on");   
  delay(100);
  sendBuffer("off");   
  delay(100);
  update();
  delay(100);
  return;

  delay(100);
  sendBuffer("on");   
  delay(100);
  sendBuffer("off");   
  return;
  delay(500);
//  sendBuffer("off");   
  delay(500);
  update();
//  delay(500);
  /*
    nCounter++;
    upd();
    
//    chardata[0] = 0x40 + nCounter*8;
//    updateCharData(chardata+1, nCounter);
//    sendBuffer(0xdd, chardata, 9);   
    
    updateCharData2(chardata, nCounter);
    sendBuffer(0xdb, chardata, 4*9);   
    delay(20);


// if (lCur > lLast2 + 200)
 {
     lLast2 = lCur;
     char msg[32];
     sprintf(msg, " Tmr %d ", nTest++);
     msg[0] = 0x80 | 0x47;

     sendBuffer(0xdd, (byte*)msg, strlen(msg));
     delay(15);  // 11 nie!, 15 asi staci     
 } */
};

