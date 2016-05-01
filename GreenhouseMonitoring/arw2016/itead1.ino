#include <SPI.h>
#include <Ethernet.h>
//#include <avr/wdt.h>
#include "dht.h"

byte mac[] = { 0x00, 0x6A, 0xB0, 0x17, 0xEA, 0xD0 };
byte ip[] = { 192, 168, 1, 254 };

dht sensor;
EthernetServer server(80);

void InitSensor()
{
  pinMode(A0, OUTPUT); // 1 VCC
  digitalWrite(A0, 1);

  pinMode(A1, INPUT);  // 2 DATA
  pinMode(A2, INPUT);  // 3 NC
  pinMode(A3, OUTPUT);  // 4 GND
  digitalWrite(A3, 0);
}

void GetSensor()
{
  Serial.print("Sensor:");
  if ( sensor.read(A1) == DHTLIB_OK )
  {
    Serial.print(" temp = ");
    Serial.print(sensor.temperature);
    Serial.print(" hum = ");  
    Serial.print(sensor.humidity);  
    Serial.print("\n");
  } else
  {
    Serial.print("Error\n");
  }
}

void DhtReport(EthernetClient& client)
{
  Serial.print("Sensor:");
  
  if ( sensor.read(A1) == DHTLIB_OK )
  {
    client.print("status=ok&temp=");
    client.print(sensor.temperature);
    client.print("&hum=");  
    client.print(sensor.humidity);  

    Serial.print(" temp = ");
    Serial.print(sensor.temperature);
    Serial.print(" hum = ");  
    Serial.print(sensor.humidity);  
    Serial.print("\n");
    
  } else
  {
    Serial.print("status=error");

    Serial.print("Error\n");    
  }
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
  InitSensor();
  Restart();
}

void Restart()
{
  Serial.begin(9600);
  Serial.print("Starting board\n"); 
  Serial.print("Built " __DATE__ " " __TIME__ "\n");

  InitEthernet();
  server.begin();
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
      Serial.print("Ok.\n");
      
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

void loop()
{
  DoEthernetClient();

  static unsigned char nErrors = 0;
  static unsigned long lLast = 0;
  unsigned long lTick = millis();
  if ( lTick - lLast > 10000 )
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
  #define MAC {0x00, 0x01, 0xA3, 0xD0, 0x6A, 0xB0 };
  //#define LOCAL_ADDR "192.168.1.50"
  #define REQ_SERVER "api.valky.eu"
  #define REQ_SCRIPT "/test/test.php"

//  GetSensor();
  
  EthernetClient client;
    Serial.print( F("Connecting to server... ") );
    if ( client.connect( REQ_SERVER, 80 ) )
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
      client.println( F("Content-Length: 256") ); // !!!!
      client.println();
      DhtReport(client);
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
          DhtReport(client);
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

