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

#define VERSION "1.3"
#define APN_NAME "o2internet"

InetGSM inet;
char g_imei[16] = "Unknown";
long g_lTick = -99999;
long g_lUptime = 0;
long v_nWatchdog = 0;

#define CHECK_VALUE 'GAB!'

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

void scanOw()
{
  static OneWire ow(A1); 
  byte addr[8];
  char strTemp[8];
  
  Serial.print("Scanning OW network:\n");
  
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
}

bool sendRequest()
{
  char single[32];
  
  if ( !inet.httpOpen("api.valky.eu", 80) )
  {
    Serial.print("HTTPOPEN ERR");
    return false;  \\\
  }
  
  gsm.SimpleWrite("GET ");
  gsm.SimpleWrite("/onereporter/add.php?");
  // url {{{
  gsm.SimpleWrite("v=" VERSION "&");
  gsm.SimpleWrite("imei=");
  gsm.SimpleWrite( g_imei ); 
  sprintf( single, "&uptime=%lu", g_lUptime ); 
  gsm.SimpleWrite( single );
  scanOw();
  // }}}
  gsm.SimpleWrite(" HTTP/1.0\nHost: ");

  gsm.SimpleWrite("api.valky.eu");
    gsm.SimpleWrite("\n");
  gsm.SimpleWrite("User-Agent: Arduino");
  gsm.SimpleWrite("\n\n");

  if (!inet.httpClose())
  {
    Serial.print("HTTPCLOSR ERR");
    return false;
  }
  return true;
//  return inet.httpClose();
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

	if ( lCur - g_lTick > lUploadInterval )
	{
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
			Serial.print(F(" Ok.\n"));
		}
		g_lUptime += lUploadInterval/1000;
		g_lTick = lCur;
	}
	gsm.SimpleRead();
//	gsm.SimpleSkip();
};

