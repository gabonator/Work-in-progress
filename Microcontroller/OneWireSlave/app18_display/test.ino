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
    } else
    {
        Serial.print("error");
    }
    Serial.print("\"\n");    
  }    
  Serial.print("OW scan done\n");  
}

void sendBuffer(unsigned char type, unsigned char* data, int len)
{
  unsigned short crc = 0;
  crc = crc16(crc, type);  
  crc = crc16(crc, len);  
  for (unsigned char i=0; i<len; i++)
    crc = crc16(crc, data[i]);
  
  ow.reset();
  ow.skip();
  ow.write(0x0f);
  ow.write(type);
  ow.write(len);
  ow.write_bytes(data, len);
  ow.write(crc & 0xff);
  ow.write(crc >> 8);
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
  unsigned char custom1[] = {' ', ' ', 0, 1, 2, 3, ' ', ' '};
  unsigned char custom2[] = {' ', ' ', 4, 5, 6, 7, ' ', ' '};
  delay(100);
  sendBuffer(0xf1, custom1, sizeof(custom1));      
  delay(100);
  sendBuffer(0xf2, custom2, sizeof(custom2));      
  upd();
  delay(100);
}

// 4x2  5x8 = 20x16pixels

unsigned char pix[40];  // 40x8
byte getPixel(byte x, byte y)
{
  if ( y >= 8 )
  {
    x += 20;
    y -= 8;
  }
  return pix[x] & (1<<y);
}

void setPixel(byte x, byte y, byte c)
{
  if ( y >= 8 )
  {
    x += 20;
    y -= 8;
  }
  if ( c )
    pix[x] |= (1<<y);
  else
    pix[x] &= ~(1<<y);
}

void upd()
{
  int r = (millis()>>4 )+1000;
  for (int x=0; x<20; x++)
    for (int y=0; y<16; y++)
    {
      int nDif = (x-10)*(x-10) + (y-8)*(y-8);

      if ( ((r-nDif) & 0x7f) < 0x40 )
        setPixel(x, y, 1);
      else
        setPixel(x, y, 0);
    }
}

void updateCharData(byte*p, int q)
{
  for (byte b=0; b<8; b++)
  {
    int r = 0;
    for (byte n=0; n<5; n++)
    {
      if (getPixel((q&3)*5+4-n, (q/4)*8+b))
        r |= 1<<n;
    }
    p[b] = r;
  }
}

// 6x 8x5 
void loop() 
{
//  const long lUploadInterval = 50;
//  long lCur = millis();
  static int nCounter = 0;
  unsigned char chardata[9];

//  if ( lCur - g_lTick > lUploadInterval )
//  {
//    g_lTick = lCur;   
    
//    update(); 
//    char test[32];
//    sprintf(test, "Test %d ", nCounter++);
//    sendBuffer(0xf0, (unsigned char*)test, strlen(test));
//    chardata[0] = 0x40 + (nCounter++%6)*8;

    nCounter++;
    if (nCounter > 7) 
    {
      nCounter = 0;
      upd();
    }
    chardata[0] = 0x40 + nCounter*8;
    updateCharData(chardata+1, nCounter);
    sendBuffer(0xf4, chardata, sizeof(chardata));   
    delay(15);
//  }
};

