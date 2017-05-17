class CTimer8254
{
	int nReset0;
	int nReset1;
	int nReset2;
	int nSpkrFrequency;

	WORD wLatch0;

public:
	CTimer8254()
	{
		nReset0 = 0;
		nReset1 = 0;
		nReset2 = 0;
		nSpkrFrequency = 0;
	}

	WORD Read18Hz()
	{
		return (WORD)((FLOAT)GetTickCount()*65543.0f/(1000.0f*60.0f*60.0f));
	}

	void WriteCtl(BYTE arg) // 43h
	{
		int nChannel = arg >> 6;
		int nAccess = (arg >> 4) & 3; // 0 = citame, 2 = ideme zapisovat
		int nMode = (arg >> 1) & 7; // 0 = irq on count, 3 = sq wave
		int nFormat = arg & 1; // 0 = 16 bit, 1 = bcd 4 digit

		switch ( nChannel )
		{
			case 0: 

				_ASSERT(arg==0);  // nAccess = 0 -> Latch for reading
				wLatch0 = -Read18Hz(); 
				wLatch0 = -(WORD)(GetTickCount()/5);
				//wLatch0 = 0;
				//nReset0 = 1; 
				break;
			case 1: nReset1 = 1; break;
			case 2: 
				nReset2 = 1; 
				break;
			default:
				_ASSERT(0);
		}
	}
	BYTE ReadCounter0() // 40h
	{
		BYTE b = wLatch0 >> 8;
		wLatch0 <<= 8;
		return b;
	}
	BYTE ReadCounter1() // 41h
	{
		_ASSERT(0);
		return 0;
	}
	BYTE ReadCounter2() // 42h
	{
		_ASSERT(0);
		return 0;
	}

	void WriteCounter0(BYTE arg)
	{
		_ASSERT(0);
	}
	void WriteCounter1(BYTE arg)
	{
		_ASSERT(0);
	}
	void WriteCounter2(BYTE arg)
	{
		static int nFreqLow;
		static int nFreqHigh;

		switch ( nReset2++ )
		{
		case 1: nFreqLow = arg; break;
		case 2: nFreqHigh = arg; 
			{
				int nFreqDiv = nFreqHigh*256 + nFreqLow;
				INT nSpkrFrequency = 1193180/nFreqDiv;
				///printf("Tone %d Hz\n", nSpkrFrequency);
				//Beep(nSpkrFrequency*2, 100);
			}
			break;
		default:
			_ASSERT(0);
		}
	}

	int GetFrequency()
	{
		return nSpkrFrequency;
	}
	BOOL Out(WORD port, BYTE val)
	{
		switch ( port )
		{
			case 0x43: WriteCtl(val); return TRUE;
			case 0x40: WriteCounter0(val); return TRUE;
			case 0x41: WriteCounter1(val); return TRUE;
			case 0x42: WriteCounter2(val); return TRUE;
		}
		return FALSE;
	}

	BYTE In(WORD port)
	{
		switch ( port )
		{
			case 0x40: return ReadCounter0();
			case 0x41: return ReadCounter1();
			case 0x42: return ReadCounter2();
		}
		_ASSERT(0);
		return 0;
	}
};

