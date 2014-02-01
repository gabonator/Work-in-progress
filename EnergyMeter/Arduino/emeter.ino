//#include "SoftReset.h"
#include "SIM900.h"
#include "inetGSM.h"
#include <TimerOne.h>
#include <EEPROM.h>
//#include "License.h"

#ifndef _LICENSE
#	define LICENSE_BASE 0x8971A134
#	define LICENSE_KEY "GAB28y4\\2013"
#endif
#define VERSION "1.2"
#define APN_NAME "o2internet"


unsigned long g_lPowerCount;

InetGSM inet;
char g_imei[16] = "Unknown";
long g_lTick = -99999;
long g_lUptime = 0;

#define CHECK_VALUE 'GAB!'
#define EE_CHECK 7
#define EE_TOTAL 8
#define EE_PWR 9

void reset()
{
  pinMode(A5, OUTPUT);    
  digitalWrite( A5, 0 );
  while(1);
}

// ee {{{

unsigned long readEE(unsigned char pos)
{
	int nBase = pos*4;
	unsigned long lValue = 0;
	lValue |= EEPROM.read( nBase+0 );
	lValue <<= 8;
	lValue |= EEPROM.read( nBase+1 );
	lValue <<= 8;
	lValue |= EEPROM.read( nBase+2 );
	lValue <<= 8;
	lValue |= EEPROM.read( nBase+3 );
	return lValue;
}

void writeEE( unsigned char pos, unsigned long l )
{
	int nBase = pos*4;
	EEPROM.write( nBase+3, l & 0xff );
	l >>= 8;
	EEPROM.write( nBase+2, l & 0xff );
	l >>= 8;
	EEPROM.write( nBase+1, l & 0xff );
	l >>= 8;
	EEPROM.write( nBase+0, l & 0xff );
}
// }}}

// emeter {{{
volatile bool v_bSignal = false;
volatile long v_nTotal = 0;
volatile long v_nTicks = 0;
volatile long v_nDbgLastLen = 0;
volatile long v_nDbgSnr = 0;
volatile long v_nErrors = 0;
volatile long v_nWatchdog = 0;
volatile long v_nDbgSum = 0;

char v_strInfo[32] = "";
volatile int v_bInfo = false;
int nFailedCounter = 0;

void ProcessSample( long nValue )
{
	#define TOFIXED(a) ((a)<<10)
	#define FROMFIXED(a) ((a)>>10)
	#define ADCDEPTH(a) ((a)<<2) // 8->10 bits
	
	static long nLastVal = 0;
	static long x=0;
	static long nFloatAvg = 0;
	static long nFloatMin = 0;
	const long nFactor = 240;
	const long nFactorMin = 240;
	const long nFactorCharge = 240;
	const long nFactorDischarge = 252;
	static long nCounter = -1;
//	static long nTotal = 0;

	static long nSnr = 0;
	static long nRising = 0;
	
	v_nTicks++;
	v_nDbgSum += nValue;
	// ---

	if ( nFloatAvg == 0 )
		nFloatAvg = TOFIXED(nValue);
	else
	{
		if ( nValue > TOFIXED(nFloatAvg) )
			nFloatAvg = ( nFloatAvg * nFactorCharge + TOFIXED(nValue) * (256-nFactorCharge) ) / 256;
		else
			nFloatAvg = ( nFloatAvg * nFactorDischarge + TOFIXED(nValue) * (256-nFactorDischarge) ) / 256;
	}

	bool bSignal = FROMFIXED(nFloatAvg) > nValue + ADCDEPTH(15);
	//tmp_nFloatAvg = nFloatAvg;
	digitalWrite( 13, bSignal );

	v_bSignal = bSignal;

	static bool bLastSignal = false;

	if ( bSignal )
	{
		if (nFloatMin == 0 )
			nFloatMin = TOFIXED(nValue);
		else 
			nFloatMin = ( nFloatMin * nFactorMin + TOFIXED(nValue) * (256-nFactorMin) ) / 256;
	} 

	if ( !bSignal && nFloatMin != 0 )
	{
		long nCurSnr = nValue - FROMFIXED(nFloatMin);
		if ( nSnr == 0 )
			nSnr = TOFIXED(nCurSnr);
		else
			nSnr = ( nSnr * nFactor + TOFIXED(nCurSnr) * (256-nFactor) ) / 256;
		v_nDbgSnr = FROMFIXED(nSnr);
	}

	if ( nCounter != -1 )
		nCounter++;

	if ( bSignal && !bLastSignal )
	{
		nRising = millis();
		nCounter = 0;
	}

	if ( !bSignal && bLastSignal )
	{
		v_nDbgLastLen = millis() - nRising;
		if ( nCounter >= 4 && nCounter < 15 )
		{
#ifdef _ISR_DEBUG
			v_bInfo = false;
			sprintf(v_strInfo, "ok, len=%lu", nCounter);
			v_bInfo = true;
#endif
			//nTotal++;
			//v_nTotal = nTotal;
			v_nTotal++;
		} else
		{
			v_nErrors++;
#ifdef _ISR_DEBUG
			long nTick = millis();
			v_bInfo = false;
			sprintf(v_strInfo, "ERR, len=%lu, t=%lu", nCounter, nTick-nRising);
			v_bInfo = true;
#endif
		}
	}

	bLastSignal = bSignal;
	nLastVal = nValue;
}

void emeter_init()
{
  pinMode(A0, OUTPUT);		// -
  pinMode(A1, OUTPUT);		// +
  pinMode(A3, INPUT);		// sig

  digitalWrite(A0, 0);
  digitalWrite(A1, 1);
  pinMode(13, OUTPUT);		// internal led
  pinMode(A5, INPUT);		// reset
 
  int nFreq = 30;
  Timer1.initialize(1000000UL / nFreq); // [us]
  Timer1.attachInterrupt( timerIsr ); 
}
/*
void emeter_pause()
{
	Timer1.stop();
}
void emeter_resume()
{
	Timer1.resume();
}*/

void timerIsr()
{
    // Toggle LED
    //digitalWrite( 13, digitalRead( 13 ) ^ 1 );
	ProcessSample( analogRead(A3) );

	if ( v_nWatchdog++ > 70000 / 30 ) // 70 seconds interval
	{/*
		v_bInfo = false;
		sprintf(v_strInfo, "Watchdog reset");
		v_bInfo = true;
		*/
		writeEE( EE_TOTAL, v_nTotal );
		reset();
		while (1);
	}
}
// }}}


// hash {{{
static PROGMEM prog_uint32_t crc_table[16] = {
    0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
    0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
    0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
};

unsigned long crc_update(unsigned long crc, byte data)
{
    byte tbl_idx;
    tbl_idx = crc ^ (data >> (0 * 4));
    crc = pgm_read_dword_near(crc_table + (tbl_idx & 0x0f)) ^ (crc >> 4);
    tbl_idx = crc ^ (data >> (1 * 4));
    crc = pgm_read_dword_near(crc_table + (tbl_idx & 0x0f)) ^ (crc >> 4);
    return crc;
}
	
unsigned long crc_string(char *s, unsigned long base = ~0L)
{
  unsigned long crc = base;
  while (*s)
    crc = crc_update(crc, *s++);
  crc = ~crc;
  return crc;
}

unsigned long crc_string(const char *s, unsigned long base = ~0L)
{
  unsigned long crc = base;
  while (*s)
    crc = crc_update(crc, *s++);
  crc = ~crc;
  return crc;
}

// }}}

void calchash(char *url)
{
	unsigned long crc = LICENSE_BASE;
	static const char* secret = LICENSE_KEY;
	crc = crc_string( secret, crc );
	crc = crc_string( url, crc );

	unsigned long lDigest = crc;
	static PROGMEM const char hexits[16] = {'0', '1', '2', '3', '4', 
		'5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

	char *hash32 = url + strlen(url) - 8;
	for ( int i=0; i<8; i++ )
		hash32[7-i] = pgm_read_byte_near(hexits + ((lDigest>>(i*4)) & 15));
}

void buildurl(char* url)
{
	char single[32];

	//long lCounter = 17, lLow = 0, lHigh = 342, lSnr = 43;
	unsigned long lCur = millis();

	strcpy(url, "/redir/add.php?v=" VERSION "&");
	//strcat(url, "imei="); strcat(url, imei); strcat(url, "&");
	sprintf( single, "imei=%s&", g_imei ); strcat( url, single );
	sprintf( single, "uptime=%lu&", g_lUptime ); strcat( url, single );
	sprintf( single, "counter=%lu&", v_nTotal ); strcat( url, single );
	sprintf( single, "tick=%lu&", lCur ); strcat( url, single );
	sprintf( single, "calls=%lu&", v_nTicks ); strcat( url, single );
	sprintf( single, "dbg_err=%lu&", v_nErrors ); strcat( url, single );
	sprintf( single, "dbg_sum=%lu&", v_nDbgSum ); strcat( url, single );

	sprintf( single, "dbg_pwr=%lu&", g_lPowerCount ); strcat( url, single );
	sprintf( single, "dbg_ll=%lu&", v_nDbgLastLen ); strcat( url, single );
	sprintf( single, "dbg_snr=%lu&", v_nDbgSnr ); strcat( url, single );
	sprintf( single, "hash=00000000" ); strcat( url, single );

	calchash(url+15);

	v_nTicks = 0;
	v_nDbgSum = 0;
	v_nDbgLastLen = 0;
	v_nDbgSnr = 0;

/*
	sprintf( single, "dbg_low=%ld&", lLow ); strcat( url, single );

	sprintf( single, "dbg_high=%ld&", lHigh ); strcat( url, single );
	Serial.print(":");delay(1000);
	sprintf( single, "dbg_snr=%lu&", lSnr ); strcat( url, single );
	sprintf( single, "hash=00000000" ); strcat( url, single );
	*/
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
	//Serial connection.
	Serial.begin(9600);
	Serial.print(F("\n\nValky.eu 2013 - energy meter v" VERSION "\n"));
	Serial.print(F("Built " __DATE__ " " __TIME__ "\n"));

	if ( readEE( EE_CHECK ) != CHECK_VALUE )
	{
		Serial.print(F("And a new life was born!\n"));
		writeEE( EE_CHECK, CHECK_VALUE );
		writeEE( EE_TOTAL, 0 );
		writeEE( EE_PWR, 0 );
	}

	v_nTotal = readEE(EE_TOTAL);	// will be nonzero in case of device reboot
	Serial.print(F("EEPROM: EE_TOTAL="));
	Serial.print(v_nTotal);
	Serial.print(F(" EE_PWR="));
	Serial.print(v_nTotal);
	Serial.print(F("\n"));

	if ( v_nTotal != 0 )
		writeEE( EE_TOTAL, 0 );

	g_lPowerCount = readEE( EE_PWR );
	g_lPowerCount++;
	writeEE( EE_PWR, g_lPowerCount );

	Serial.print(F("Meter Init..."));
	emeter_init();
	Serial.print(F(" Ok.\n"));

	Serial.print(F("GSM Init..."));
	while ( !gsm.begin(2400) )
	{
		Serial.print(F(" Error\n"));
		writeEE( EE_TOTAL, v_nTotal );
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

void loop() 
{
	v_nWatchdog = 0; // reset WDT
	long lCur = millis();
	if ( v_bInfo )
	{
		Serial.print(F("EM<"));
		Serial.print(v_strInfo);
		Serial.print(F(">\n"));
		v_bInfo = false;
	}

	if ( lCur >= 0x10000000 )
	{
		writeEE( EE_TOTAL, v_nTotal );
		reset();
	}

	if ( lCur - g_lTick > 60000 )
	{
		char url[180];
		buildurl(url);
		Serial.print(F("Sending request..."));

		Serial.print(F(" (len="));
		Serial.print(strlen(url));
		Serial.print(F(" data='"));
		Serial.print(url);
		Serial.print(F("')\n"));

		// takes approx 15sec
		if ( !inet.httpGET("pub.valky.eu", 80, url) )
		{
			Serial.print(F(" Error!\n"));
			if ( ++nFailedCounter >= 3 )
			{
				writeEE( EE_TOTAL, v_nTotal );
				reset();
			}
		} else
		{
			nFailedCounter = 0;
			Serial.print(F(" Ok.\n"));
		}
		/*
		gsm.Read(5000, 50, url, sizeof(url));
		Serial.print("Reply<");
		Serial.print(url);
		Serial.print(">\n");
		*/
		g_lUptime += 60;
		g_lTick = lCur;
	}

	gsm.SimpleRead();
};
