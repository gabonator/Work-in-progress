
#include <SoftwareSerial.h>

// NOTE: Reads on Software serial are blocking!
SoftwareSerial mySerial(2, 3); //rx, tx

#define PIN_RX_LIN 7
#define PIN_TX_LIN 8
#define LIN digitalRead(PIN_RX_LIN)
#define HALF 23

unsigned char ReadBit()
{
  unsigned char b;
  delayMicroseconds(HALF);
  b = LIN;
  delayMicroseconds(HALF);
  return b;  
}

int ReadByte(byte bContinuous = 0)
{
  int nSync = 0;
  // start bit
  if ( ReadBit() != 0 )
     return -3;

  // data
  unsigned char data = 0;
  for (int i=0; i<8; i++)
  {
    data >>= 1;
    if ( ReadBit() )
      data |= 128;
  }

  // stop bit
  if ( bContinuous ) 
  {
    delayMicroseconds(HALF);
    while (LIN);
    return data;
  }
  
  if ( ReadBit() != 1 )
    return -4;    
    
  return data;
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Lin monitor");
  mySerial.begin(9600);
  mySerial.println("Hello BT!");
  pinMode(PIN_RX_LIN, INPUT);
  pinMode(PIN_TX_LIN, OUTPUT);
  digitalWrite(PIN_TX_LIN, 1);
}

void WriteBit(unsigned char b)
{
  digitalWrite(PIN_TX_LIN, b);
  // 20khz -> 50uS pulse
  delayMicroseconds(50-2);
}

void SendSync()
{
   delayMicroseconds(28);
   for (int i=0; i<9; i++)
     WriteBit(0);
   WriteBit(1); // preamble
}

void SendByte(byte b)
{
   WriteBit(0); // start bit
   for (int i=0; i<8; i++)
   {
     WriteBit(b&1);
     b >>= 1;
   }
   WriteBit(1); // stop bit
}

// App
int nPosition = 0;
int nSpeed = 0;
long lLastUpdate = 0;
char nMove = 0;
char nLastMove = 0;
int nTarget = -1;

void doLin()
{
  if (LIN)
    return;
//  while (LIN);
  while (!LIN);
  while (LIN);
  
  int data = ReadByte();
  
  if ( data == 0x64 )
  {
    // keep alive
    SendSync();
    SendByte(0x9b);
  }
  
  // position / speed info
  if ( data == 0x80 )
  {
    int arr[5];
    arr[0] = ReadByte(1);
    arr[1] = ReadByte(1);
    arr[2] = ReadByte(1);
    arr[3] = ReadByte(1);
    arr[4] = ReadByte();
    
    int nSum = data + arr[0] + arr[1] + arr[2] + arr[3] + arr[4];
    nSum = (nSum + (nSum >> 8)) & 0xff;
    if ( nSum != 0xff )
    {
      Serial.print("CRC error - ");
      Serial.println(nSum, HEX);
    } else
    {
      nPosition = (arr[1] << 8) | arr[0];
      nSpeed = arr[2] == 0x80 ? -arr[3] : arr[3];
      //pos: min 0 (79cm)
      //     max 6600 (145cm)
      //int poscm = (pos/100)+79;
      lLastUpdate = millis();
    }
  }
  
  // move request
  if ( data == 0xCA )
  {
    int nSendMove = 0;
    if (nMove < 0)
       nSendMove = -1;
    else 
    if (nMove > 0)
      nSendMove = +1;
    else
    if (nLastMove != 0)
      nSendMove = -nLastMove;

    nLastMove = nMove;

    if (nSendMove < 0)
    {
      SendSync();
      SendByte(0x00);
      SendByte(0x35);
    } 
    if (nSendMove > 0)
    {
      SendSync();
      SendByte(0x80);
      SendByte(0xb4);
    } 
  }
}

void Execute (char* command)
{
  Serial.print("exec '");
  Serial.print(command);  
  Serial.println("'");
  mySerial.print("exec '");
  mySerial.print(command);  
  mySerial.println("'");

  if ( strcmp(command, "up") == 0 )
  {
    nMove = +1;  
    nTarget = -1;    
  }
  if ( strcmp(command, "down") == 0 )
  {
    nMove = -1;  
    nTarget = -1;    
  }
  if ( strcmp(command, "stop") == 0 )
  {
    nMove = 0;  
    nTarget = -1;
  }

  if ( memcmp(command, "go ", 3) == 0 )
  {
    nMove = 0;  
    nTarget = atoi(command+3);
    Serial.print("Setting target to ");
    Serial.print(nTarget);
    Serial.print("cm\n");
  }
}

void doComm()
{
  static char buffer[16];
  static byte nPos = 0;
  char ch = 0;
  
  if ( Serial.available() )
    ch = Serial.read();

  if ( mySerial.available() )
    ch = mySerial.read();
  
  if ( ch )
  {
    if ( ch == 0x0d || ch == 0x0a )
    {
      if ( nPos > 0 )
      {
        buffer[nPos] = 0;
        // execute buffer
        Execute(buffer);
      }
      nPos = 0;
    } else
    {
      if ( ch >= 0x20  && ch < 0x80 )
      {
        if (nPos < 16-2)
          buffer[nPos++] = ch;
      }
    }
  }
}

void doTarget()
{
  if ( nTarget == -1 )
    return;
    
  int nTargetPos = (nTarget - 79)*100+50;
  if ( nTargetPos < nPosition + nSpeed/2 - 25)
    nMove = -1;
  else if ( nTargetPos > nPosition + nSpeed/2 + 25 )
    nMove = +1;
  else
  {
    nMove = 0;
    nTarget = -1;
    Serial.println("Target achieved!");
  }
}

void doReport()
{
  static long lLast = 0;
  long lCur = millis();
  if (lCur - lLast < 1000)
    return;
  lLast = lCur;

  long lPassed = lCur - lLastUpdate;
  if ( lPassed > 1000 )
  {
    Serial.println("Connection lost");
    mySerial.println("Connection lost");
  }
  else
  {
    float fPos = (nPosition/100.0f)+79.0f;
    int nDec = (int)fPos;
    int nSub = (int)((fPos-nDec)*10.0f);

    Serial.print("pos=");
    Serial.print(nPosition, HEX);
    Serial.print(" (");
    Serial.print(nDec);
    Serial.print('.');
    Serial.print(nSub);
    Serial.print("cm), spd=");
    Serial.println(nSpeed);

    mySerial.print("pos=");
    mySerial.print(nPosition, HEX);
    mySerial.print(" (");
    mySerial.print(nDec);
    mySerial.print('.');
    mySerial.print(nSub);
    mySerial.print("cm), spd=");
    mySerial.println(nSpeed);
  }
}

void loop()
{
  doLin();
  doComm();
  doTarget();
  doReport();
}
