/*
 * Itead iboard 1.1
 * 
 * Programmer: Parallel progarmmer
 * Processor: Atmel328 (328P)
 * Board: Arduino Duemilanove or Diecimila
 * 
 * Pinout on board: DTR, GND, TX, RX, VDD 3.3, GND, NC
 */

 
//#define USE_OREGON  // flash:11% mem:12%
//#define USE_OREGON_UDP
//#define USE_ONEWIRE // flash:5% mem:1%
#define USE_DHT22   // flash:3% mem:2%
//#define USE_BMP085  // flash:9% mem:2%
#define USE_PIR

#include <SPI.h>
#include <Ethernet.h>
#include <Dns.h>

#ifdef USE_OREGON
#endif

#ifdef USE_BMP085
#include <Wire.h>
#endif

#ifdef USE_DHT22
#include "dht.h"
#endif

#ifdef USE_BMP085
#include "Adafruit_BMP085.h"
#endif

#ifdef USE_ONEWIRE
#include "OneWire.h"
#endif


#define MAC {0x00, 0x11, 0x11, 0x11, 0x22, 0x23 }; // Sklad

#define REQ_SERVER "****"
#define REQ_SCRIPT "/***/"


/*
#define MAC {0x01, 0x01, 0x02, 0x34, 0x56, 0x78 };

#define REQ_SERVER "server.com"
#define REQ_SCRIPT "/script/"
*/
byte mac[] = MAC;
byte ip[] = { 192, 168, 1, 254 };

IPAddress ServerAddress;
unsigned int UdpPort = 2000;
const bool bUseInternet = 1;
const long lUploadInterval = 60000; //bUseInternet ? 60000 : 5000;

#ifdef USE_DHT22
dht sensor;
#endif

#ifdef USE_BMP085
Adafruit_BMP085 bmp;
#endif

EthernetServer server(80);

#ifdef USE_ONEWIRE
OneWire wire(A2); 
#endif 

#ifdef USE_PIR
int nPirCounterL = 0;
int nPirCounterR = 0;
int nPirCounter = 0;

void PirInit()
{
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}

void PirDo()
{
  static unsigned long lLast = 0;
  unsigned long lTick = millis();
  
  if ( lTick - lLast < 200 )
    return;
  lLast = lTick;

  nPirCounter++;  
  if ( digitalRead(A4) )
    nPirCounterL++;
  if ( digitalRead(A5) )
    nPirCounterR++;
}

void PirReset()
{
  nPirCounter = 0;
  nPirCounterL = 0;
  nPirCounterR = 0;
}
#endif

#ifdef USE_DHT22
void InitDHT22()
{
  pinMode(A0, OUTPUT); // 1 VCC
  digitalWrite(A0, 1);

  pinMode(A1, INPUT);  // 2 DATA
  pinMode(A2, INPUT);  // 3 NC
  pinMode(A3, OUTPUT);  // 4 GND
  digitalWrite(A3, 0);
}
#endif

void FloatToString(char* out, float f, int decimals)
{
	if ( f < 0 )
	{
		f = -f;
		*out++ = '-';
	}
	int nDec = (int)f;
	itoa(nDec, out, 10);
	out += strlen(out);
	*out++ = '.';
	f -= nDec;
	for (int i=0; i<decimals; i++)
	{
		f *= 10;
		nDec = (int)f;
		*out++ = '0' + nDec;
		f -= nDec;
	}
	*out = 0;
}

int SensorReport(EthernetClient& client)
{
  char report[32];  
  byte valid = 0;

  int nBytes = 0;
  sprintf(report, "&uptime=%d", millis()/1000);

  nBytes += strlen(report);
  client.print(report);
  
#ifdef USE_DHT22
  // DHT22
  Serial.print("[DHT:");

  if ( sensor.read(A1) == DHTLIB_OK )
  {
    valid |= 1;

    FloatToString(report, sensor.temperature, 1);

    nBytes += 6 + strlen(report);
    client.print("&temp=");
    client.print(report);
    Serial.print(" temp = ");
    Serial.print(report);
    
    FloatToString(report, sensor.humidity, 1);
    nBytes += 5 + strlen(report);    
    client.print("&hum=");  
    client.print(report);
    Serial.print(" hum = ");  
    Serial.print(report);
         
    Serial.print("] ");  
  } else
  {
    Serial.print(" error] ");    
  }
#endif

#ifdef USE_PIR
  Serial.print("[PIR:");
  Serial.print("l=");
  Serial.print(nPirCounterL);
  Serial.print(" r=");
  Serial.print(nPirCounterR);
  Serial.print(" c=");
  Serial.print(nPirCounter);
  Serial.print("] ");

  sprintf(report, "&pir_l=%d", nPirCounterL);
  nBytes += strlen(report);
  client.print(report);  
  sprintf(report, "&pir_r=%d", nPirCounterR);
  nBytes += strlen(report);
  client.print(report);  
  sprintf(report, "&pir_c=%d", nPirCounter);
  nBytes += strlen(report);
  client.print(report);  

  PirReset();
#endif

#ifdef USE_BMP085
  // BMP085
  Serial.print("[BMP Sensor:");

  if (bmp.begin())
  {	      
    float fPressure = bmp.readPressure() / 100.0f; // QFE/hPa
    float fTemp = bmp.readTemperature();

    if ( fPressure > 0.0f && fPressure < 20000.0f &&
    fTemp > -50.0f && fTemp < 200.0f )
    {
      valid |= 2;

      FloatToString(report, fTemp, 1);
      Serial.print(" temp = ");
      Serial.print(report);

      FloatToString(report, fPressure, 1);
      Serial.print(" baro = ");  
      Serial.print(report);  
      Serial.print("] ");

      client.print("&baro=");
      client.print(report);  
      nBytes += 6 + strlen(report);
    } else
    {
      Serial.print(" Error] ");
    }
  } else
  {
    Serial.print(" Error] ");
  }
#endif

#ifdef USE_OREGON
  Serial.print("[Oregon:");
  nBytes += OregonReport(client);
  Serial.print("] ");
#endif

#ifdef USE_ONEWIRE
  // One wire
  Serial.print("[Onewire:");
  
  // request temperature
  if ( !wire.reset() )
  {
    Serial.print(" Error] ");
  } else
  {
    typedef uint8_t DeviceAddress[8];
    enum {
      STARTCONVO = 0x44,  // Tells device to take a temperature reading and put it on the scratchpad
      READSCRATCH = 0xBE,  // Read EEPROM
    };
  
    wire.skip();
    wire.write(STARTCONVO);
  
    // wait
    delay(750);
    
    // scan bus
    DeviceAddress deviceAddress;
    wire.reset_search();
    while (wire.search(deviceAddress))
    {
      if (wire.crc8(deviceAddress, 7) == deviceAddress[7]) // valid address
      {        
        valid |= 4;

        nBytes += 4 + sizeof(DeviceAddress)*2 + 1 + 9*2;
        client.print("&ow_");
        for (byte i=0; i<sizeof(DeviceAddress); i++)
        {
          char* p = tohex(deviceAddress[i]); //wire.read());
          client.print(p);
          Serial.print(p);
        }
        client.print('=');
        Serial.print('=');
        
        wire.reset();
        wire.select(deviceAddress);
        wire.write(READSCRATCH);
        for (byte i=0; i<9; i++)
        {
          char* p = tohex(wire.read());
          client.print(p);
          Serial.print(p);
        }
        wire.reset();
      }
    }
    Serial.print("] ");    
  }
#endif
  
  // status
  nBytes += 8 + 1;
  client.print("&status=");
  client.print(valid);  
  return nBytes;
}

char* tohex(byte n)
{
  const char hex[] = "0123456789abcdef";
  static char str[3];
  str[0] = hex[n>>4];
  str[1] = hex[n&15];
  str[2] = 0;
  return str;
}

void setup() 
{
  Serial.begin(9600);
  Serial.print("Starting board\n"); 
  Serial.print("Built " __DATE__ " " __TIME__ "\n");

  Restart();
}

void Restart()
{
  Serial.print("Booting...\n");

#ifdef USE_DHT22
  InitDHT22();
#endif

#ifdef USE_PIR
  PirInit();
#endif

#ifdef USE_OREGON
  InitOregon();
#endif

  if ( bUseInternet )
  { 
    do 
    {  
      InitEthernet();
      if (!GetServerIp())
        continue;
    } while(0);
    
    Serial.print("Starting TCP server\n");
    server.begin();    

#ifdef USE_OREGON
    InitEthOregon();
#endif
  }
  
  Serial.print("Starting main loop\n");
}

void InitEthernet()
{
  const long lDhcpTimeout = 15*60*1000;
  
  Serial.print(F("Requesting IP from DHCP server... "));

  pinMode(10, OUTPUT);     // set the SS pin as an output (necessary!)
  digitalWrite(10, HIGH);  // but turn off the W5100 chip!

  unsigned long lTick = millis();

  while (millis() - lTick < lDhcpTimeout)
  {
    if ( Ethernet.begin(mac) )
    {
      if ( Ethernet.localIP()[0] == 0 )
      {
        Serial.print(F("Invalid address.\n"));
        continue;
      }
      Serial.print(F("Ok.\n"));
      
      Serial.print(F("Server running at "));
      Serial.println(Ethernet.localIP());
      return;
    } 
    Serial.print(F("Error!\nRetrying... "));
    delay(1000);
  }
  Serial.print(F("\nSetting default IP\n"));

  Ethernet.begin(mac, ip);
  Serial.print(F("Server running at "));
  Serial.println(Ethernet.localIP());
}

byte GetServerIp()
{
  int nDnsOk = 0;

  for(byte nRetry=0; nRetry<20; nRetry++) 
  {
    DNSClient dns;    
    Serial.print("DNS search: ");

    dns.begin(Ethernet.dnsServerIP());
    nDnsOk = dns.getHostByName(REQ_SERVER, ServerAddress);

    Serial.print(REQ_SERVER);
    Serial.print(" -> ");
    Serial.print(ServerAddress);
    Serial.print(" (");
    Serial.print(nDnsOk);
    Serial.print(")\n");

    if ( nDnsOk == 1 && ServerAddress[0] != 0 )
      return 1;
  }

  return 0;
}

unsigned char nErrors = 0;

void OnDone()
{
  nErrors = 0;  
}

void OnFailure()
{
  nErrors++;
}


void loop()
{
#ifdef USE_OREGON
  DoOregon();
#endif

  EthWebserver();
  EthDo();
#ifdef USE_PIR
  PirDo();
#endif
  
  static unsigned long lLast = 0;
  unsigned long lTick = millis();
  
  if ( lLast == 0 || lTick - lLast > lUploadInterval )
  {
    EthMakeRequest();
    lLast = lTick;
  }
  
  if ( nErrors == 3 )
  {
    nErrors = 0;
    Serial.print(F("Restarting ethernet module\n\n\n"));
    Restart();
  }
}

EthernetClient clientReq;
enum {
  _0_WAIT,
  _1_0D,
  _2_0A,
  _3_0D,
  _4_0A,
  _5_BEGIN,
  _6_END,
  _7_CLOSED
} clientStatus = _7_CLOSED;

bool bEthOpened = false;

void EthDo()
{
  if ( clientReq.connected() )
  {
    bEthOpened = true;

    while (clientReq.available()) 
    {
      char c = clientReq.read();
      if ( clientStatus == _0_WAIT && c == 0x0d )
        clientStatus = _1_0D;
      else
      if ( clientStatus == _1_0D && c == 0x0a )
        clientStatus = _2_0A;
      else
      if ( clientStatus == _2_0A && c == 0x0d )
        clientStatus = _3_0D;
      else
      if ( clientStatus == _3_0D && c == 0x0a )
        clientStatus = _4_0A;
      else
      if ( clientStatus == _4_0A && c == '{' )
        clientStatus = _5_BEGIN;
      else
      if ( clientStatus == _5_BEGIN && c == '}' )
        clientStatus = _6_END;
      else
      if ( clientStatus == _6_END )
        clientStatus = _7_CLOSED;

      if ( clientStatus == _5_BEGIN )
        Serial.print( F("Server reply: '") );
        
      if ( clientStatus == _5_BEGIN || clientStatus == _6_END )
        Serial.print(c);

      if ( clientStatus == _6_END )
      {
        Serial.print("\' ");
        OnDone();
      }
    }
  } else
  {
    if ( bEthOpened  )
    {
      Serial.print( F("Client disconnected.\n") );
      clientStatus = _7_CLOSED;  
      bEthOpened = false;
    }
  }
}

void EthMakeRequest()
{  
  Serial.print( F("Connecting to server... ") );
  clientStatus = _0_WAIT;
  clientReq.stop();

  if ( !bUseInternet || clientReq.connect( ServerAddress, 80 ) )
  {
    Serial.print( F("Sending... ") );
    clientReq.print( F("POST ") );
    clientReq.print( F(REQ_SCRIPT) );
    clientReq.println( F(" HTTP/1.1") );
    clientReq.print( F("Host: ") );
    clientReq.println( F(REQ_SERVER) );
    clientReq.println( F("Server: rio-gabo-guru 2017a") );
    clientReq.print( F("User-Agent: Itead Iboard 1.1 (") );
    //clientReq.print( F("Cookie: _boardVersion=16.5; _boardPlatform=Iboard11; _boardType=Collector2016a; "));
    clientReq.print( F("#") );
    {
      byte mac[] = MAC;
      for ( int j = 0; j < 6; j++)
        clientReq.print( tohex(mac[j]) );
    }    
    #ifdef USE_OREGON
      clientReq.print(F(",oregon"));
    #endif
    #ifdef USE_DHT22
      clientReq.print(F(",dht22"));
    #endif
    #ifdef USE_BMP085
      clientReq.print(F(",bmp085"));
    #endif
    #ifdef USE_ONEWIRE
      clientReq.print(F(",onewire"));
    #endif      
    #ifdef USE_PIR
      clientReq.print(F(",pir"));
    #endif
    clientReq.println( F(")") );
    clientReq.println( F("Content-Type: application/x-www-form-urlencoded") );
    clientReq.println( F("Content-Length: 256") ); // !!!!
    clientReq.println( F("Connection: close") );    
    clientReq.println();

    int nLen = SensorReport(clientReq);

    clientReq.print( F("&dummy=") ); // !!!!
    nLen += 7;

    char temp[4];
    itoa(nLen, temp, 0);

    clientReq.print( temp ); // !!!!
    nLen += strlen(temp);

    Serial.print( F("Done. ") );
    Serial.print(nLen);
    
    nLen = 256-nLen;
    if (nLen > 0)
    {
      while (nLen--)
        clientReq.print(' ');
    }
    clientReq.print( F("\r\n\r\n") );
    Serial.print( F(" bytes sent.\n") );
    return;
  }

  Serial.print( F("Error!\n") );
  OnFailure();
}

void EthWebserver()
{
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean current_line_is_blank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if we've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so we can send a reply
        if (c == '\n' && current_line_is_blank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          
          client.println("Server working");          
          client.print("Built " __DATE__ " " __TIME__ "\n");
          SensorReport(client);
          break;
        }
        if (c == '\n') {
          // we're starting a new line
          current_line_is_blank = true;
        } else if (c != '\r') {
          // we've gotten a character on the current line
          current_line_is_blank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
}


#ifdef USE_OREGON
#include <SPI.h>
#ifdef USE_OREGON_UDP
#include <EthernetUdp.h>
#endif
#include "oregon.h"

#ifdef USE_OREGON_UDP
EthernetUDP Udp;
IPAddress UdpAddress;
#endif

COregon Oregon;

const int nOregonMax = 8;
byte arrOregon[nOregonMax*COregon::PacketLength];
byte nOregonCount = 0;

void InitOregon()
{
  while (!Receiver.Init())
  {
    Serial.print("Cannot initialize receiver!\n");
    delay(1000);
  }
  Serial.print("Oregon scientific ready.\n");
}

void InitEthOregon()
{
#ifdef USE_OREGON_UDP
    UdpAddress = Ethernet.localIP();
    UdpAddress[3] = 255;
    Udp.begin(UdpPort);
    Serial.print("Starting UDP server ");
    Serial.print(UdpAddress);
    Serial.print(":");
    Serial.print(UdpPort);
    Serial.print("\n");  
#endif
}

void DoOregon()
{
  if ( nOregonCount >= nOregonMax )
    return;
  
  if ( Oregon.WaitHeader() )
  {
    if ( Oregon.GetHeader() )
    {
      //byte buffer[COregon::PacketLength] = {0};
      byte* pBuffer = arrOregon + nOregonCount * COregon::PacketLength;
      byte received = Oregon.ReceivePacket(pBuffer);
      if ( received )
      {
        nOregonCount++;
        const char hex[] = "0123456789abcdef";
        Serial.print("Received buffer: ");
#ifdef USE_OREGON_UDP
        if ( bUseInternet )
        {
          Udp.beginPacket(UdpAddress, UdpPort);
          Udp.write("(");
        }
#endif        
        for( int i=0; i < received; i++)
        {     
          Serial.print(hex[pBuffer[i] >> 4]);
          Serial.print(hex[pBuffer[i] & 15]);
#ifdef USE_OREGON_UDP
          if ( bUseInternet )
          {
            Udp.write(hex[pBuffer[i] >> 4]);
            Udp.write(hex[pBuffer[i] & 15]);
          }
#endif
        }
#ifdef USE_OREGON_UDP
        if ( bUseInternet )
        {
          Udp.write(")");
          Udp.endPacket();
        }
#endif
        Serial.print("\n");
      } else
        Serial.print("Receive error\n");
    }
  }  
}

int OregonReport(EthernetClient& client)
{
  const char hex[] = "0123456789abcdef";

  Serial.print(nOregonCount);
  Serial.print(" records");
 
  int nBytes = 8;
  client.print("&oregon=");
  
  int nOfs = 0;
  for (byte i = 0; i < nOregonCount; i++)
  {
    if (i>0)
    {
      client.print(',');
      nBytes++;
    }
    for (byte j = 0; j < COregon::PacketLength; j++)
    {
      client.print(hex[arrOregon[nOfs] >> 4]);
      client.print(hex[arrOregon[nOfs++] & 15]);
      nBytes += 2;
    }
  }
  nOregonCount = 0;
  return nBytes;
}
#endif

