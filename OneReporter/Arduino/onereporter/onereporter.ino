#include <SoftwareSerial.h>
//#include "SIM900.h"
#include "inetGSM.h"
#include "crc.h"
#include <TimerOne.h>
#include <EEPROM.h>
#include <OneWire.h>
//#include "License.h"

#ifndef _LICENSE
#	define LICENSE_BASE 0x8971A134
#	define LICENSE_KEY "GAB28y4\\2013"
#endif

#define VERSION "1.4"
#define APN_NAME "o2internet"

InetGSM inet;
char g_imei[16] = "Unknown";
long g_lTick = -99999;
long g_lUptime = 0;
long v_nWatchdog = 0;

#define CHECK_VALUE 'GAB!'

  static OneWire ow(A1); 

void reset()
{
  pinMode(A5, OUTPUT);    
  digitalWrite( A5, 0 );
  while(1);
}

void timerIsr()
{
    // Toggle LED
    //digitalWrite( 13, digitalRead( 13 ) ^ 1 );
//	ProcessSample( analogRead(A3) );

	if ( v_nWatchdog++ > 70000 / 30 ) // 70 seconds interval
	{
                onRestart();
		reset();
		while (1);
	}
}
// }}}

void calchash(char *url)
{
	unsigned long crc = LICENSE_BASE;
	static const char* secret = LICENSE_KEY;
	crc = CRC::crc_string( secret, crc );
	crc = CRC::crc_string( url, crc );

	unsigned long lDigest = crc;
	static PROGMEM const char hexits[16] = {'0', '1', '2', '3', '4', 
		'5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	char *hash32 = url + strlen(url) - 8;
	for ( int i=0; i<8; i++ )
		hash32[7-i] = pgm_read_byte_near(hexits + ((lDigest>>(i*4)) & 15));
}

/*
void buildurl(char* url)
{
  char single[32];
  strcpy(url, "/onereporter/add.php?");
  int nSkipBytes = strlen(url);
  strcat(url, "v=" VERSION "&");
  sprintf( single, "imei=%s&", g_imei ); strcat( url, single );
  sprintf( single, "uptime=%lu&", g_lUptime ); strcat( url, single );
  sprintf( single, "hash=00000000" ); strcat( url, single );
  calchash(url+nSkipBytes);
}
*/

int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

bool allnumeric(char* str)
{
	while (*str)
	{
		if ( *str < '0' || *str > '9' )
			return false;
		str++;
	}
	return true;
}

void setup() 
{
	Serial.begin(9600);
        onLoad();
	Serial.print(F("GSM Init..."));
	while ( !gsm.begin(2400) )
	{
                onRestart();
		reset();
		//delay(5000);
	}
	Serial.print(F(" Ok.\n"));
	delay(500);

	Serial.print(F("IMEI: ")); 
	do {
		gsm.getIMEI(g_imei);
		if ( !allnumeric(g_imei) )
		{
			Serial.print(".");
			continue;
		}
	} while(0);

	Serial.print(F("'")); 
	Serial.print(g_imei); 
	Serial.print(F("'\n")); 

        Serial.print( F("Free memory: ") );
        Serial.println( freeRam() );
        
	Serial.print(F("Initializing GPRS... ")); 
	//GPRS attach, put in order APN, username and password.
	//If no needed auth let them blank.
	while ( !inet.attachGPRS(APN_NAME, "", "") )
	{
		Serial.print(F("Error\n"));
		delay(5000);
	}
	Serial.print(F(" Ok.\n"));

	char ip[16] = "Unknown";
	gsm.getIP(ip);

	Serial.print(F("Local IP Address='"));
	Serial.print(ip);
	Serial.print(F("'\n"));

	Serial.print(F("Starting main loop\n"));
}

void onLoad()
{
  Serial.print(F("\n\nValky.eu 2015 - gprs shield v" VERSION "\n"));
  Serial.print(F("Built " __DATE__ " " __TIME__ "\n"));  

  initOw();
  
  int nFreq = 30;
  Timer1.initialize(1000000UL / nFreq); // [us]
  Timer1.attachInterrupt( timerIsr );   
}

void onRestart()
{
  Serial.print(F("onRestart\n"));
  delay(5000);
}

void initOw()
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  digitalWrite(A3, 0);
  pinMode(A3, OUTPUT);

  digitalWrite(A2, 1);
  pinMode(A2, OUTPUT);
}

void owStartConversion()
{
  ow.reset();
  ow.skip();
  ow.write(0x44);  
//  ow.write(0x41);
  Serial.print("Conversion in progress...\n");
}

boolean anyTemperature = false;
 
void owScan()
{
  byte addr[8];
  char strTemp[8];
  
  Serial.print("Scanning OW network:\n");
  
  anyTemperature = false;
  
  ow.reset_search();
  while (ow.search(addr)) 
  {
    gsm.SimpleWrite("&dev_");
    Serial.print("ADDR=");
    for( int i = 0; i < 8; i++) 
    {
      sprintf(strTemp, "%02x", addr[i]);
      Serial.print(strTemp);
      gsm.SimpleWrite(strTemp);
    }
    Serial.print(":");
    gsm.SimpleWrite("=");
    
    if ( addr[0] == 0x10 || addr[0] == 0x28 || addr[0] == 0x22 )
    {
      ow.reset();
      ow.select(addr);
      ow.write(0xbe);
      Serial.print(" \"");    
      for( int i = 0; i < 9; i++) 
      {
        unsigned char d = ow.read();
        sprintf(strTemp, "%%%02x", d);
        Serial.print(strTemp);
        gsm.SimpleWrite(strTemp);
      }      
      Serial.print("\"\n");    
      anyTemperature = true;
    } else
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
        unsigned char d = ow.read();
        sprintf(strTemp, "%%%02x", d);
        Serial.print(strTemp);
        gsm.SimpleWrite(strTemp);
      }
    } else
    {
        Serial.print("error");
        gsm.SimpleWrite("error");     
    }
    Serial.print("\"\n");    
  }    
  Serial.print("OW scan done\n");  

  // todo: conversion done too late! Should be called 1000ms before calling owScan
  /*
  if ( anyTemperature )
  {
    owStartConversion();
  }*/
}
/*
boolean processResponse(char *strLine)
{
  unsigned char sum1 = 0, sum2 = 0;;
  for ( int i=0; i<strlen(strLine); i++ )
    sum1 += (unsigned char) strLine[i];
  
  boolean aux = jsonParse(strLine);

  for ( int i=0; i<strlen(strLine); i++ )
    sum2 += (unsigned char) strLine[i];

  if ( sum1 != sum2 )
  {
    Serial.print("===\nMemory fail!\n===\n");
  }
  return aux;
  return jsonParse(strLine);
}
*/

byte asc2hex(char ch)
{
  if ( ch >= '0' && ch <= '9' )
    return ch - '0';
  if ( ch >= 'a' && ch <= 'f' )
    return ch - 'a' + 10;
  if ( ch >= 'A' && ch <= 'F' )
    return ch - 'A' + 10;
  return 0;
}

// JSON {{{
char jsonKey[22]; // 4 + 8*2 = 20M
char jsonValue[64];
byte jsonKeyI;
byte jsonValueI;

void jsonPushKey(char ch)
{
  if ( jsonKeyI < sizeof(jsonKey)-2 )
    jsonKey[jsonKeyI++] = ch;
}

void jsonPushValue(char ch)
{
  if ( jsonValueI < sizeof(jsonValue)-2 )
    jsonValue[jsonValueI++] = ch;
}

void jsonResetPair()
{
  jsonKeyI = 0;
  jsonValueI = 0;
}

void jsonFinalizePair()
{
  jsonKey[jsonKeyI] = 0;  
  jsonValue[jsonValueI] = 0;  

  Serial.print("  ");
  Serial.print(jsonKey);
  Serial.print("=");
  Serial.print(jsonValue);
  Serial.print("\n");

  if ( strcmp(jsonKey, "delay") == 0 )
  {
    delay(atoi(jsonValue));
  } else
  if ( strncmp(jsonKey, "dev_", 4) == 0 )
  {
    if ( strlen(jsonKey) == 4+2*8 )
    {
      byte devid[8];
      for (byte i=0; i<8; i++)
      {
        devid[i] = (asc2hex(jsonKey[4+i*2])<<4) | asc2hex(jsonKey[4+i*2+1]);
      }
      ow.reset();
      ow.select(devid);
    } else if ( strcmp(jsonKey, "dev_*") == 0 )
    {
      ow.reset();
      ow.skip();
    } else 
    {
      Serial.print("unknown!");
    }
    
    for (byte i=0; i<jsonValueI; i++)
    {
      if (jsonValue[i] == '\\' && jsonValue[i+1] == 'u')
      {
        //  \u1234
        ow.write( (asc2hex(jsonValue[i+4])<<4) | asc2hex(jsonValue[i+5]) );
        i += 5;
        continue;
      }
      if (jsonValue[i] == '\\' && jsonValue[i+1] == 'x')
      {
        //  \x12
        ow.write( (asc2hex(jsonValue[i+2])<<4) | asc2hex(jsonValue[i+3]) );
        i += 3;
        continue;
      }
      if (jsonValue[i] == '%' && jsonValue[i+1] == '%')
      {
        ow.write( '%' );
        i++;
        continue;
      }
      if (jsonValue[i] == '%' )
      {
        //  %12
        ow.write( (asc2hex(jsonValue[i+1])<<4) | asc2hex(jsonValue[i+2]) );
        i += 2;
        continue;
      }
      ow.write( jsonValue[i] );
    }
  } else
  {
    Serial.print("Unknown command!\n");
  }
}

void jsonBegin()
{
  Serial.print("Json {\n");
}

void jsonFinish()
{
  Serial.print("}\n");
}

  enum EJsonState {
    WaitParentLeft,
    WaitQuoteBegin,
    WaitQuote,
    KeyBegin,
    Key,
    KeyEnd,
    WaitColon,
    WaitQuote2,
    ValueBegin,
    Value,
    ValueEnd,  // 10
    WaitComma, 
    End,       // 12
    Error };   // 13

static EJsonState eState = WaitParentLeft;

void jsonReset()
{
  eState = WaitParentLeft;
}

int jsonState()
{
  return eState;
}

boolean jsonParse(char ch)
{   
//  for ( ; *strLine; strLine++ )
//  {
//    char ch = *strLine;
    switch ( eState )
    {
      case WaitParentLeft:
        if ( ch == '{' ) eState = WaitQuoteBegin;
        else if ( ch != ' ' ) { eState = Error; return false; }
      break;
      case WaitQuoteBegin:
        jsonBegin();
        eState = WaitQuote;
      case WaitQuote:
        if ( ch == '"' ) eState = KeyBegin;
        else if ( ch != ' ' ) { eState = Error; return false; }
      break;
      // key
      case KeyBegin:
        eState = Key;
        jsonResetPair();
//        Serial.print("Key = '");
      case Key:
        if ( ch == '"' ) eState = KeyEnd;
        else jsonPushKey(ch); //Serial.print(ch);
        break;
      case KeyEnd:
//        Serial.print("' ");
        eState = WaitColon;
      //
      case WaitColon:
        if ( ch == ':' ) eState = WaitQuote2;
        else if ( ch != ' ' ) { eState = Error; return false; }
      break;
      case WaitQuote2:
        if ( ch == '"' ) eState = ValueBegin;
        else if ( ch != ' ' ) { eState = Error; return false; }
      break;
      // value
      case ValueBegin:
        eState = Value;
//        Serial.print("Value = '");
      case Value:
        if ( ch == '"' ) eState = ValueEnd;
        else jsonPushValue(ch); //Serial.print(ch);
        break;
      case ValueEnd:
//        Serial.print("'\n");
        jsonFinalizePair();
        eState = WaitComma;
      //
      case WaitComma:
        if ( ch == ',' ) eState = WaitQuote; 
        else if ( ch == '}' ) { jsonFinish(); eState = End; }
        else if ( ch != ' ' ) { eState = Error; return false; }
      break;
      case End:
        if ( ch != ' ' && ch != '\n' )
        {
          eState = Error;
          return false;
        }
        break;
      case Error:
        return false;
    }
//  }
  return true;
}

// }}} JSON

bool sendRequest()
{
  char single[20];
  if ( anyTemperature )
  {
    owStartConversion(); // needs 1000ms!
  }
  
  // httpOpen takes 9000 ms
  if ( !inet.httpOpen("api.valky.eu", 80) )
  {
    Serial.print("HTTPOPEN ERR");
    return false;
  }
//  Serial.print("connection took ");
//  Serial.println(millis()-l0);
  
  gsm.SimpleWrite("GET ");
  gsm.SimpleWrite("/onereporter/?");
  // url {{{
  gsm.SimpleWrite("v=" VERSION "&");
  gsm.SimpleWrite("imei=");
  gsm.SimpleWrite( g_imei ); 
  sprintf( single, "&uptime=%lu", g_lUptime ); 
  gsm.SimpleWrite( single );
  
  owScan();
  // }}}
  gsm.SimpleWrite(" HTTP/1.0\nHost: ");

  gsm.SimpleWrite("api.valky.eu");
  gsm.SimpleWrite("\n");
  gsm.SimpleWrite("User-Agent: Arduino");
  gsm.SimpleWrite("\n\n");

  if (!inet.httpClose())
  {
    Serial.print("Error sending request\n");
    return false;
  }
  
  char strLine[256+32];
  enum { First, Header, Body, Closed } eSection = First;
  bool bLineSplit = false;
  long lJsonTimeout;
    
  do {
#if 0
    if ( eSection == Body && (jsonState() != Error && jsonState() != End ) && millis() < lJsonTimeout )
    {
//      int nPrev = jsonState();
       // JSON or CLOSED\n
       if (gsm.available())
         jsonParse(gsm.read());
       /*
       if ( jsonState() == End )
       {
         Serial.print("Json parse finished!\n");
       }
       if ( jsonState() == Error )
       {
         Serial.print("Json error!\n");
         Serial.print("Prev state ");
         Serial.println(nPrev);
       }*/
       continue;
    }
#endif    
    if ( !inet.ReadLine(strLine, sizeof(strLine)-1, 8000 ) )
      break;
      
    if ( eSection == First )
      eSection = Header;
      
    if ( !bLineSplit && eSection == Header && strcmp(strLine, "\n") == 0 )
    {
      lJsonTimeout = millis() + 15000;
      jsonReset();      
      eSection = Body;
      continue;
    }
    
    bLineSplit = strLine[strlen(strLine)-1] != '\n';

    if ( !bLineSplit )
      Serial.print(eSection != Body ? "HDR: " : "BODY: ");
    Serial.print(strLine);    

    if ( eSection == Body && strcmp(strLine, "CLOSED\n") == 0 ) // 4000 ms after last data
    {
      Serial.print("Connection closed.\n");
      eSection = Closed;
    }
    
    if ( eSection == Body ) 
    {
      for ( int i=0; i<strlen(strLine); i++)
         jsonParse(strLine[i]);      
    }
  } while (eSection == Body || eSection == Header);

  return true;
}

void loop() 
{
  const long lUploadInterval = 60000;
  static int nFailedCounter = 0;
  
	v_nWatchdog = 0; // reset WDT
	long lCur = millis();
	if ( lCur >= 0x10000000 )
	{
                onRestart();
		reset();
	}

	if ( lCur - g_lTick >= lUploadInterval )
	{
		g_lTick = lCur;
  
		Serial.print(F("Sending request..."));
		if ( !sendRequest() )
		{
			Serial.print(F(" Error!\n"));
			if ( ++nFailedCounter >= 3 )
			{
                                onRestart();
				reset();
			}
		} else
		{
			nFailedCounter = 0;
//			Serial.print(F(" Ok.\n"));
		}
		g_lUptime += lUploadInterval/1000;
	}

  if ( gsm.available() )
  {
    Serial.print("Unhandled reply at ");
    Serial.print(millis());
    Serial.print(" <");
    while ( gsm.available() )
    {
      char ch = gsm.read();
      Serial.print(ch);
    }
    Serial.println(">");
  }
};

