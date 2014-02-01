#include "Wire.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include <SPI.h>
#include <Ethernet.h>
#include "dht11.h"
#include "Adafruit_BMP085.h"
#include <TimerOne.h>
#include <EEPROM.h>


#define VALVEMIN 0
#define VALVEMAX 135


#define ADDRESS IPAddress(192, 168, 1, 50)
#define SERVER IPAddress(192, 168, 1, 2)
#define URL "/tlog2/remote.php"
#define MAC {0x00, 0x01, 0xA3, 0xD0, 0x6A, 0xB0 };
#define LOCAL_ADDR "192.168.1.50"

IPAddress ip = ADDRESS;
EthernetServer server(80);

// DS18S20 Temperature chip i/o
OneWire ds(2);  // on pin 10
DallasTemperature sensors(&ds);
dht11 Dht11;	
Adafruit_BMP085 bmp;
volatile bool bUpload = false;
volatile unsigned long lUptime = 0;

unsigned char failures = 0;

char state = 0;

void hstop()
{
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	digitalWrite(7, LOW);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	state = 0;
}

void hminus()
{
	digitalWrite(6, 0); // ENB=0

	digitalWrite(5, 1); // IN1=1
	digitalWrite(4, 1); // ENA=1
	state = -1;
}

void hplus()
{
	digitalWrite(4, 0); // ENA=0

	digitalWrite(7, 0); // IN2=1
	digitalWrite(6, 1); // ENB=1
	state = +1;
}

void setup(void) 
{
	// initialize inputs/outputs
	// start serial port
	hstop();
	Serial.begin(9600);

	load();

	/*
	pinMode(2, OUTPUT);
	digitalWrite(2, LOW);
	pinMode(4, OUTPUT);
	digitalWrite(4, HIGH);
	*/

#ifdef _USE_DHCP
	Serial.print(F("Requesting IP from DHCP server...\n"));
	// start the Ethernet connection and the server:

	while (1)
	{
		if ( Ethernet.begin(mac) )
		{
			//Serial.print("cannot use DHCP\n");
			//Ethernet.begin(mac, ip);
			//Serial.print("ethernet error");
			break;
		} 
		Serial.print("Waiting 10s for DHCP server\n");
		delay(10 * 1000);
	}
#else
	{
		byte mac[] = MAC;
		Ethernet.begin(mac, ip);
	}
#endif
	Serial.print(F("server is at "));
	Serial.println(Ethernet.localIP());


	/*
	pinMode(A1, OUTPUT);
	digitalWrite(A1, LOW);
	pinMode(A2, OUTPUT);
	digitalWrite(A2, HIGH);
	*/
	//sensors.setWaitForConversion(false);

#define I_FREQ 1
	int nFreq = I_FREQ;//50;
	Timer1.initialize(1000000UL / nFreq); // [us]
	Timer1.attachInterrupt( timerIsr ); 
}

volatile int hcycles = 0;
volatile int hsetcycles = 0;
volatile int clock = 0;
volatile int counter = 0;

void timerIsr()
{
	lUptime += 1; // 1/I_FREQ

	if ( state != 0 )
	{
		counter += state;
		if ( counter > VALVEMAX )
			counter = VALVEMAX;
		if ( counter < VALVEMIN )
			counter = VALVEMIN;
	}
	if ( ++clock >= 60*I_FREQ )
	{
		clock = 0;
		minuteIsr();
	}
	if ( hcycles > 0 )
	{
		if ( --hcycles <= 0 )
			hstop();
	}
	if ( hsetcycles != 0 )
	{
		if ( hsetcycles > 0 )
		{
			hplus();
			hcycles = hsetcycles;
		} else {
			hminus();
			hcycles = -hsetcycles;
		}
		hsetcycles = 0;
	}
}

int nLimitMin = 19;
int nLimitMax = 23;
int nLimitStep = 10;
bool bLimitOn = true;

void minuteIsr()
{
	Serial.print(F("(Minute timer)\n"));
	if ( !hasReference() )
		readReference();
	if ( hasReference() )
	{
		if ( bLimitOn )
		{
			float fTemp = getReference();
			if ( fTemp < (float)nLimitMin )
			{
				Serial.print(F("Add!"));
				hsetcycles = nLimitStep;
			}
			if ( fTemp > (float)nLimitMax )
			{
				Serial.print(F("Sub!"));
				hsetcycles = -nLimitStep;
			}
		}
	} else
		Serial.print(F("Error - no ref!\n"));

	bUpload = true;
}

void readReference()
{
	sensors.begin();
	sensors.requestTemperatures(); // Send the command to get temperatures
	for (int i=0; i<sensors.getDeviceCount(); i++)
	{
		byte addr[8];
		sensors.getAddress( addr, i );

		if ( addr[7] != 0xa9 )
			continue;

		byte pad[9];
		if ( !sensors.isConnected(addr, pad ) )
			continue;

		sensors.readScratchPad( addr, pad );
		float fTemp = sensors.calculateTemperature(addr, pad);
		setReference( fTemp );
	}
}

float fRefTemperature = 0;
long lRefTime = -999999;
void setReference(float f)
{
	fRefTemperature = f;
	lRefTime = millis();
}

bool hasReference()
{
	return ( millis() - lRefTime < 120000 );
}

float getReference()
{
	return fRefTemperature;
}


void load()
{
#define VERSION 17

	if ( EEPROM.read(0) == VERSION )
	{
		nLimitMin = EEPROM.read(1);
		nLimitMax = EEPROM.read(2);
		nLimitStep = EEPROM.read(3);
		bLimitOn = EEPROM.read(4);
		Serial.print(F("eeprom load ok.\n"));
	} else
	{
		save();
	}
}

void save()
{
	EEPROM.write(1, nLimitMin);
	EEPROM.write(2, nLimitMax);
	EEPROM.write(3, nLimitStep);
	EEPROM.write(4, bLimitOn);
	EEPROM.write(0, VERSION);
	Serial.print(F("eeprom set.\n"));
}

//#define Count(a) (int)(sizeof(a)/sizeof(a[0]))

char* tohex(byte n)
{
	const char hex[] = "0123456789abcdef";
	static char str[3];
	str[0] = hex[n>>4];
	str[1] = hex[n&15];
	str[2] = 0;
	return str;
}

void owReportSimple( EthernetClient* p ) 
{
	//int nLength = 0;

	sensors.begin();
	sensors.requestTemperatures(); // Send the command to get temperatures
	for (int i=0; i<sensors.getDeviceCount(); i++)
	{
		p->print(F("ow_"));

		byte addr[8];
		sensors.getAddress( addr, i );

		switch (addr[7])
		{
		case 0x01: p->print(F("yellow")); break;
		case 0xeb: p->print(F("green")); break;
		case 0x6f: p->print(F("black")); break;
		case 0xa9: p->print(F("red")); break;
		case 0xa4: p->print(F("purple")); break;
		default:
			for ( int j = 0; j < 8; j++)
				p->print( tohex(addr[j]) );
		}

		p->print("=");
		//nLength += 3+8*2+1;

		byte pad[9];
		if ( !sensors.isConnected(addr, pad ) )
		{
			//nLength += 6;
			p->print(F("error&"));
			continue;
		}

		sensors.readScratchPad( addr, pad );
		//nLength += 2*9;
		//	for ( int j = 0; j < 9; j++)
		//		p->print( tohex(pad[j]) );
		float fTemp = sensors.calculateTemperature(addr, pad);

		char report[8];
		FloatToString(report, fTemp, 2);
		p->print(report);

		if ( addr[7] == 0xa9 )
		{
			// reference thermo
			setReference( fTemp );
		}
		//nLength ++;
		p->print('&');
	}

	if ( Dht11.read(3) == DHTLIB_OK )
	{
		//	nLength += 6 + 5*2 + 1;

		p->print(F("dht11_temp="));
		p->print(Dht11.temperature);
		p->print(F("&dht11_hum="));
		p->print(Dht11.humidity);
		//for ( int j = 0; j < 5; j++)
		//			p->print( tohex(Dht11.bits[j]) );
		p->print('&');
	} else {
		//nLength += 12;
		p->print(F("dht11=error&") );
	}

	p->print(F("light="));
	int nX = analogRead(A3);
	p->print( nX, DEC );
	p->print(F("&valve="));
	p->print( counter, DEC );

	if (bmp.begin())
	{	
		//nLength ++;
		p->print('&');
		float fPressure = bmp.readPressure() / 1000.0f;
		float fTemp = bmp.readTemperature();
		char report[16];
		//nLength += ???;
		p->print(F("bmp085_baro="));
		FloatToString(report, fPressure, 3);
		p->print(report);

		p->print(F("&bmp085_temp="));
		FloatToString(report, fTemp, 2);
		p->print(report);
	}
	p->print(F("&uptime="));
	p->print(lUptime);
}

void owReport( EthernetClient* p ) 
{
	sensors.begin();
	sensors.requestTemperatures(); // Send the command to get temperatures
	//p->print("// Requesting temperatures...\r\n");

	p->print("// A.Devices found: ");
	p->print(sensors.getDeviceCount(), DEC);
	p->print("\r\n");

	for (int i=0; i<sensors.getDeviceCount(); i++)
	{
		p->print("device[\"");
		p->print(i, DEC);

		byte addr[8];
		sensors.getAddress( addr, i );
		for ( int j = 0; j < 8; j++)
			p->print( tohex(addr[j]) );

		p->print("\"] = ");
		byte pad[9];
		if ( !sensors.isConnected(addr, pad ) )
		{
			p->print(F("{status:\"error\", pin:\"2\"};\r\n"));
			continue;
		}

		p->print(F("{status:\"ok\", pin:\"2\", "));

		switch (addr[0])
		{
		case DS18B20MODEL:
			p->print(F("type:\"DS18B20\", "));
			break;
		case DS1822MODEL:
			p->print(F("type:\"DS1822\", "));
			break;
		case DS18S20MODEL:
			p->print(F("type:\"DS18S20\", "));
			break;
		}

		p->print(F("data:\""));

		sensors.readScratchPad( addr, pad );
		for ( int j = 0; j < 9; j++)
			p->print( tohex(pad[j]) );

		p->print(F("\", temperature:"));

		float fTemp = sensors.calculateTemperature(addr, pad);
		p->print(fTemp);
		p->print("};\r\n");

		if ( addr[7] == 0xa9 )
		{
			// reference thermo
			setReference( fTemp );
		}

	}

	p->print(F("device[\"dht11\"] = { "));
	if ( Dht11.read(3) == DHTLIB_OK )
	{
		p->print(F("status:\"ok\", type:\"dht11\", data:\""));
		for ( int j = 0; j < 5; j++)
			p->print( tohex(Dht11.bits[j]) );
		p->print( F("\", temperature: ") );
		p->print( Dht11.temperature );
		p->print( F(", humidity: ") );
		p->print( Dht11.humidity );
	} else {
		p->print("status:\"error\"" );
	}
	p->print("};\r\n" );

	p->print( F("device[\"light\"] = { type:\"KeyesLightSensor\", status:\"ok\", ") );
	p->print( F("value:") );
	int nX = analogRead(A3);
	p->print( nX, DEC );
	p->print( F("};\r\n") );

	p->print( F("device[\"valve\"] = { type:\"Komextherm\", status:\"ok\", ") );
	p->print( F("value:") );
	p->print( counter, DEC );
	p->print( F(", range: ") );
	p->print( VALVEMAX, DEC );
	p->print( F("};\r\n") );

	/*
	p->print("device[\"wet\"] = { type:\"WetSensor\", source:\"A4\", status:\"ok\", ");
	p->print("value:" );
	nX = analogRead(A4);
	p->print( nX, DEC );
	p->print("};\r\n" );

	p->print("device[\"mq9\"] = { type:\"GasSensorMq9\", source:\"A5\", status:\"ok\", ");
	p->print("value:" );
	nX = analogRead(A5);
	p->print( nX, DEC );
	p->print("};\r\n" );

	p->print("device[\"relay\"] = { type:\"Keyes2R1B\", source:\"6,7\", status:\"ok\", ");
	p->print("value:" );
	nX = digitalRead(6)*1+digitalRead(7)*2;
	p->print( nX, DEC );
	p->print("};\r\n" );
	*/
	if (bmp.begin())
	{	
		float fPressure = bmp.readPressure() / 1000.0f;
		float fTemp = bmp.readTemperature();
		char report[16];
		p->print( F("device[\"bmp085\"] = { type:\"BMP085\", status:\"ok\", ") );
		p->print( F("pressure:") );
		FloatToString(report, fPressure, 2);
		p->print(report);
		p->print( F(", temperature:") );
		FloatToString(report, fTemp, 2);
		p->print(report);
		p->print( F("};\r\n") );
	}
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

void loop() 
{
	char command[16];
	int cmdi = -1;
	// listen for incoming clients
	EthernetClient client;
	if ( bUpload )
	{
		bUpload = false;
		if ( !hasReference() )
			readReference();
		float fTemp = getReference();

		if ( client.connect( SERVER, 80 ) )
		{
			Serial.println( F("upload-connected\n") );
			client.print( F("POST ") );
			client.print( F(URL) );
			client.println( F(" HTTP/1.1") );
			client.print( F("Host: ") );
			client.println( F(LOCAL_ADDR) );
			client.println( F("User-Agent: Wiznet W5100 (Arduino Uno R3) SensorBoard Collector2014b") );
			client.println( F("Connection: close") );
			client.print( F("Cookie: _boardPlatform=Arduino R3; _boardType=Collector2014b; _boardId=") );
			{
				byte mac[] = MAC;
				for ( int j = 0; j < 6; j++)
					client.print( tohex(mac[j]) );
			}
			client.println( F(";") );
			client.println( F("Content-Type: application/x-www-form-urlencoded") );
			client.println( F("Content-Length: 256") ); // !!!!
			client.println();

			owReportSimple(&client);

			client.println( F("&dummy=") ); // !!!!
			client.println();
			client.println();
			client.stop();

			failures = 0;
		} else
		{
			Serial.println( F("upload-failed\n") );
			if ( ++failures > 3 )
			{
				// try reconnecting
				byte mac[] = MAC;
				Ethernet.begin(mac, ip);
			}
		}
	}


	client = server.available();
	if (client) 
	{
		Serial.println(F("new client"));
		// an http request ends with a blank line
		boolean currentLineIsBlank = true;
		char lc = 0;
		bool bset = false, quick = false;

		cmdi = -1;
		command[0] = 0;
		while (client.connected()) 
		{
			if (client.available()) 
			{
				char c = client.read();
				if ( cmdi >= 0 && cmdi < 15 )
				{
					if ( c == '\n' || c==' ')
					{
						//Serial.print(">>>");
						cmdi = -1;
					} else
					{
						command[cmdi++] = c;
						command[cmdi] = 0;
						//Serial.print(".");
					}
				}
				if ( c=='?' )
				{
					//Serial.print("<<<");
					cmdi = 0;
				}
				//Serial.write(c);
				// if you've gotten to the end of the line (received a newline
				// character) and the line is blank, the http request has ended,
				// so you can send a reply
				if (c == '\n' && currentLineIsBlank) {
					Serial.print("QUERY_STRING='");
					Serial.print(command);
					Serial.print("'\n");

					// send a standard http response header
					client.println(F("HTTP/1.1 200 OK"));
					client.println(F("Content-Type: text/html"));
					client.println(F("Connection: close"));
					client.println();

					if ( command[0] == 0 )
					{
						long lTimeBegin = millis();
						if (!bset)
						{
							owReport( &client );
						}
						long lTimePassed = millis() - lTimeBegin;
						Serial.print(F("Generating took:"));
						Serial.print(lTimePassed, DEC);
						Serial.print("\n");
					} else {
						client.print(F("QUERY_STRING='"));
						client.print(command);
						client.print("'\n");

						if ( strcmp(command, "simple") == 0 )
							owReportSimple( &client ) ;

						if ( strcmp(command, "plus") == 0 )
							hplus();
						if ( strcmp(command, "minus") == 0 )
							hminus();
						if ( strcmp(command, "stop") == 0 )
						{
							hstop();
							hcycles = 0;
						}
						if ( strncmp(command, "rel=", 4) == 0 )
							hsetcycles = atoi(command+4);
						if ( strncmp(command, "setmin=", 7) == 0 )
						{
							nLimitMin = atoi(command+7);
							save();
						}
						if ( strncmp(command, "setmax=", 7) == 0 )
						{
							nLimitMax = atoi(command+7);
							save();
						}
						if ( strncmp(command, "setstep=", 8) == 0 )
						{
							nLimitStep = atoi(command+8);
							save();
						}
						if ( strncmp(command, "limit=", 6) == 0 )
						{
							bLimitOn = atoi(command+6);
							save();
						}
						if ( strncmp(command, "counter=", 8) == 0 )
						{
							counter = atoi(command+8);
						}
						if ( strncmp(command, "config", 6) == 0 )
						{
							float fTemp = getReference();
							client.print( F("RefTemp=") );
							client.print( (int)fTemp );
							client.print('.');
							client.print( (int)((fTemp - (int)fTemp)*10) );
							client.print( F("\nRefValid=") );
							client.print( hasReference() );
							client.print( F("\nlimitMin=") );
							client.print( nLimitMin );
							client.print( F("\nlimitMax=") );
							client.print( nLimitMax );
							client.print( F("\nlimitStep=") );
							client.print( nLimitStep );
							client.print( F("\nlimitOn=") );
							client.print( bLimitOn );
							client.print( F("\ncounter=") );
							client.print( counter );
							client.print( F("\nuptime=") );
							client.print( lUptime );
							client.print( F("\n") );
						}
					}

					break;
				}
				if (c == '\n') {
					// you're starting a new line
					currentLineIsBlank = true;
				}
				else if (c != '\r') {
					// you've gotten a character on the current line
					currentLineIsBlank = false;
				}
			}
		}
		// give the web browser time to receive the data
		delay(1);
		// close the connection:
		client.stop();
		Serial.println("client disonnected");
	}
}

