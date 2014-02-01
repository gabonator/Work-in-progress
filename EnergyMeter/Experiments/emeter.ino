#include <TimerOne.h>

volatile bool v_bSignal = false;
volatile long v_nTotal = 0;
volatile long v_nTicks = 0;
volatile long v_nDbgLastLen = 0;
volatile long v_nDbgSnr = 0;

void ProcessSample( long nValue )
{
	#define TOFIXED(a) ((a)<<10)
	#define FROMFIXED(a) ((a)>>10)
	
	static long nLastVal = 0;
	static long x=0;
	static long nFloatAvg = 0;
	static long nFloatMin = 0;
	const long nFactor = 240;
	const long nFactorMin = 240;
	const long nFactorCharge = 240;
	const long nFactorDischarge = 252;
	static long nCounter = -1;
	static long nTotal = 0;

	static long nSnr = 0;
	static long nRising = 0;
	
	v_nTicks++;
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

	bool bSignal = FROMFIXED(nFloatAvg) > nValue + 15;
	//tmp_nFloatAvg = nFloatAvg;

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
		if ( nCounter >= 3 && nCounter < 15 )
		{
			/*
			Serial.print("pulse len=");
			Serial.print(nCounter, DEC);
			Serial.print("\n");
			*/
			nTotal++;
			v_nTotal = nTotal;
		} else
		{
			long nTick = millis();
			Serial.print("invalid signal! len=");
			Serial.print(nCounter, DEC);
			Serial.print(" (");
			Serial.print(nTick-nRising, DEC);
			Serial.print("ms)\n");
		}
	}

	bLastSignal = bSignal;
	nLastVal = nValue;
}


void setup()
{
  Serial.begin(9600);
  Serial.print("Boot...\n");

  pinMode(13, OUTPUT);    
  pinMode(A0, INPUT);    
  
  int nFreq = 30;
  Timer1.initialize(1000000UL / nFreq); // [us]
  Timer1.attachInterrupt( timerIsr ); 
}

void loop()
{
	v_nTicks = 0;
	delay(1000);
	Serial.print(" lastlen=");
	Serial.print(v_nDbgLastLen);
	Serial.print(" snr=");
	Serial.print(v_nDbgSnr);
	Serial.print(" calls=");
	Serial.print(v_nTicks);
	Serial.print(" pulses=");
	Serial.print(v_nTotal);
	Serial.print("\n");
	
	v_nDbgLastLen = 0;
	v_nDbgSnr = 0;
}

void timerIsr()
{
    // Toggle LED
    digitalWrite( 13, digitalRead( 13 ) ^ 1 );
	ProcessSample( analogRead(A0) );
}