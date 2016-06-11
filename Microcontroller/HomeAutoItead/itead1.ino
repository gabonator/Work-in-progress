#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "dht.h"
#include "oregon.h"
#include <Dns.h>
#include "Adafruit_BMP085.h"

#define MAC {0x43, 0x07, 0xA3, 0xD0, 0x6A, 0x9A };
#define REQ_SERVER "api.valky.eu"
//#define REQ_SCRIPT "/test/"
#define REQ_SCRIPT "/onereporter/"

byte mac[] = MAC; //{ 0x00, 0x6A, 0xB0, 0x17, 0xEA, 0xD0 };
byte ip[] = { 192, 168, 1, 254 };

IPAddress UdpAddress;
IPAddress ServerAddress;
unsigned int UdpPort = 2000;
const bool bUseInternet = true;
const long lUploadInterval = bUseInternet ? 60000 : 5000;

dht sensor;
Adafruit_BMP085 bmp;

EthernetServer server(80);
EthernetUDP Udp;
COregon Oregon;

const int nOregonMax = 8;
byte arrOregon[nOregonMax*COregon::PacketLength];
byte nOregonCount = 0;


void InitSensor()
{
  pinMode(A0, OUTPUT); // 1 VCC
  digitalWrite(A0, 1);

  pinMode(A1, INPUT);  // 2 DATA
  pinMode(A2, INPUT);  // 3 NC
  pinMode(A3, OUTPUT);  // 4 GND
  digitalWrite(A3, 0);
}

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

void InitBmp()
{
  /*
  pinMode(A7, OUTPUT); // 7 GND
  digitalWrite(A7, 0);

  pinMode(A6, OUTPUT); // 6 VCC
  digitalWrite(A6, 1);
*/
  pinMode(A5, INPUT);  // 5 SCL
  pinMode(A4, INPUT);  // 4 SDA
}
/*
void GetBmp()
{
  Serial.print("[BMP Sensor:");

	if (bmp.begin())
	{	
		float fPressure = bmp.readPressure() / 1000.0f;
		float fTemp = bmp.readTemperature();

    if ( fPressure > 0.0f && fPressure < 10000.0f &&
         fTemp > -50.0f && fTemp < 200.0f )
    {
      char report[8];

  		FloatToString(report, fTemp, 2);
      Serial.print(" temp = ");
      Serial.print(report);

  		FloatToString(report, fPressure, 2);
      Serial.print(" pres = ");  
      Serial.print(sensor.humidity);  
      Serial.print("]");
      return;
    }
  }

  Serial.print(" Error] ");
}
*/
/*
void GetSensor()
{
  Serial.print("[DHT Sensor:");
  if ( sensor.read(A1) == DHTLIB_OK )
  {
    Serial.print(" temp = ");
    Serial.print(sensor.temperature);
    Serial.print(" hum = ");  
    Serial.print(sensor.humidity);  
    Serial.print("]");
  } else
  {
    Serial.print(" Error] ");
  }
}
*/
void SensorReport(EthernetClient& client)
{
  char report[8];  
  byte valid = 0;

  // DHT22
  Serial.print("[DHT:");

  if ( sensor.read(A1) == DHTLIB_OK )
  {
    valid |= 1;

    FloatToString(report, sensor.temperature, 1);
    client.print("&temp=");
    client.print(report);
    Serial.print(" temp = ");
    Serial.print(report);
    
    FloatToString(report, sensor.humidity, 1);
    client.print("&hum=");  
    client.print(report);
    Serial.print(" hum = ");  
    Serial.print(report);
         
    Serial.print("] ");  
  } else
  {
    Serial.print("error] ");    
  }

  // BMP085
  Serial.print("[BMP Sensor:");

	if (bmp.begin())
	{	      
		float fPressure = bmp.readPressure() / 10.0f;
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
    } else
    {
      Serial.print(" Error] ");
    }
  } else
  {
    Serial.print(" Error] ");
  }

  // status

  client.print("&status=");
  client.print(valid);  
}

/*
void Reboot()
{
  // not working!
  wdt_enable(WDTO_15MS);
  while(1)
  {
  }
}
*/

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

  InitSensor();
  Restart();
}

void Restart()
{
  Serial.print("Booting...\n");

  InitOregon();
  
  if ( bUseInternet )
  {   
    InitEthernet();
    GetServerIp();
    
    Serial.print("Starting TCP server\n");
    server.begin();    
  
    UdpAddress = Ethernet.localIP();
    UdpAddress[3] = 255;
    Udp.begin(UdpPort);
    Serial.print("Starting UDP server ");
    Serial.print(UdpAddress);
    Serial.print(":");
    Serial.print(UdpPort);
    Serial.print("\n");  
  }
  
  Serial.print("Starting main loop\n");
}

void InitOregon()
{
  while (!Receiver.Init())
  {
    Serial.print("Cannot initialize receiver!\n");
    delay(1000);
  }
  Serial.print("Oregon scientific ready.\n");
}

void InitEthernet()
{
  const long lDhcpTimeout = 30*1000;
  
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

void GetServerIp()
{
  int nDnsOk = 0;
  do 
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

    if ( ServerAddress[0] == 0 )
      nDnsOk = 0;

  } while (nDnsOk != 1);
}

void loop()
{
  DoOregon();
  DoEthernetClient();

  static unsigned char nErrors = 0;
  static unsigned long lLast = 0;
  unsigned long lTick = millis();
  if ( lTick - lLast > lUploadInterval )
  {
    if ( DoEthernetServer() )
      nErrors = 0;
    else
    {
      if ( ++nErrors == 3 )
      {
        nErrors = 0;
        Serial.print(F("Restarting ethernet module\n\n\n"));
        Restart();
      }
    }
    lLast = lTick;
  }
}

int DoEthernetServer()
{  
  EthernetClient client;
  Serial.print( F("Connecting to server... ") );

    if ( !bUseInternet || client.connect( ServerAddress, 80 ) )
    {
      Serial.print( F("Sending... ") );
      client.print( F("POST ") );
      client.print( F(REQ_SCRIPT) );
      client.println( F(" HTTP/1.1") );
      client.print( F("Host: ") );
      client.println( F(REQ_SERVER) );
      client.println( F("User-Agent: Wiznet W5100 (Itead Iboard 1.1) SensorBoard Collector2016a") );
      client.println( F("Connection: close") );
      client.print( F("Cookie: _boardVersion=16.5; _boardPlatform=Iboard11; _boardType=Collector2016a; _boardId=") );
      {
        byte mac[] = MAC;
        for ( int j = 0; j < 6; j++)
          client.print( tohex(mac[j]) );
      }
      client.println( F(";") );
      client.println( F("Content-Type: application/x-www-form-urlencoded") );
      client.println( F("Content-Length: 512") ); // !!!!
      client.println();
      SensorReport(client);
      OregonReport(client);
      //client.println( F("measure=1234") );
      client.println( F("&dummy=") ); // !!!!
      client.println();
      client.println();
      client.stop();
      Serial.print( F("Done.\n") );
      return 1;
    }
    Serial.print( F("Error!\n") );
    return 0;
}

void DoEthernetClient()
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
          OregonReport(client);
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
        if ( bUseInternet )
        {
          Udp.beginPacket(UdpAddress, UdpPort);
          Udp.write("(");
        }
        
        for( int i=0; i < received; i++)
        {     
          Serial.print(hex[pBuffer[i] >> 4]);
          Serial.print(hex[pBuffer[i] & 15]);
          if ( bUseInternet )
          {
            Udp.write(hex[pBuffer[i] >> 4]);
            Udp.write(hex[pBuffer[i] & 15]);
          }
        }
        if ( bUseInternet )
        {
          Udp.write(")");
          Udp.endPacket();
        }
        Serial.print("\n");
      } else
        Serial.print("Receive error\n");
    }
  }  
}

void OregonReport(EthernetClient& client)
{
  const char hex[] = "0123456789abcdef";
  
  client.print("&oregon=");
  
  int nOfs = 0;
  for (byte i = 0; i < nOregonCount; i++)
  {
    if (i>0)
      client.print(',');
    for (byte j = 0; j < COregon::PacketLength; j++)
    {
      client.print(hex[arrOregon[nOfs] >> 4]);
      client.print(hex[arrOregon[nOfs++] & 15]);
    }
  }
  nOregonCount = 0;
}


