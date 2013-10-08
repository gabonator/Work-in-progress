#include "stdafx.h"

HANDLE g_hTerminateUser;
HANDLE g_hTerminateAll;

class CSerial
{
	HANDLE m_hHandle;

public:
	CSerial()
	{
		m_hHandle = NULL;
	}

	~CSerial()
	{
		Close();
	}

	bool Open(char* strDevice, int nBaud)
	{
		m_hHandle = CreateFileA( strDevice, GENERIC_READ | GENERIC_WRITE, 0, NULL,
			OPEN_EXISTING, 0, NULL);

		if ( m_hHandle == INVALID_HANDLE_VALUE )
		{
			printf("(%s @ %d baud) Cannot open port.\n", strDevice, nBaud);
			return false;
		}

		DCB dcb;
		COMMTIMEOUTS cto = { 500, 0, 100, 4, 500 }; 

		if (!SetCommTimeouts(m_hHandle, &cto))
		{
			printf("(%s @ %d baud) SetCommTimeouts failed.\n", strDevice, nBaud);
			return false;
		}

		dcb.DCBlength = sizeof(dcb);
		memset(&dcb, sizeof(dcb), 0);

		if (!GetCommState(m_hHandle, &dcb))
		{
			printf("(%s @ %d baud) GetCommState failed.\n", strDevice, nBaud);
			return false;
		}

		dcb.BaudRate = nBaud;
		dcb.fBinary = TRUE;
		dcb.fParity = FALSE; //(sio->info.parity == SIO_PARITY_NONE) ? FALSE : TRUE;
		dcb.fOutxCtsFlow = FALSE;
		dcb.fOutxDsrFlow = FALSE;
		dcb.fDtrControl = DTR_CONTROL_DISABLE;
		dcb.fDsrSensitivity = FALSE;
		dcb.fTXContinueOnXoff = FALSE;
		dcb.fOutX = FALSE;
		dcb.fInX = FALSE;
		dcb.fErrorChar = FALSE;
		dcb.fNull = FALSE;
		dcb.fRtsControl = RTS_CONTROL_DISABLE;
		dcb.fAbortOnError = FALSE;
		dcb.ByteSize = 8; 

		dcb.Parity = 0;
		dcb.StopBits = 0;

		if (!SetCommState(m_hHandle, &dcb))
		{
			printf("(%s @ %d baud) SetCommState failed.\n", strDevice, nBaud);
			return false;
		}	
		FlushFileBuffers( m_hHandle );
		return true;
	}

	CString Recv()
	{
		CHAR buffer[1024];
		DWORD dwRead;
		ReadFile( m_hHandle, buffer, 1024, &dwRead, NULL );
		if ( dwRead > 0 ) 
		{
			CString strAux(buffer, dwRead);
			return strAux;
		}
		return _T("");
	}

	void Send(CString strData)
	{
		DWORD dwWritten;
		WriteFile( m_hHandle, strData.GetBuffer(), strData.GetLength(), &dwWritten, NULL );
		_ASSERT ( dwWritten != strData.GetLength() );
	}

	void Close()
	{
		if ( m_hHandle )
			CloseHandle( m_hHandle );
		m_hHandle = NULL;
	}
};

class Mutex
{
public:
   Mutex( void ) { InitializeCriticalSection(&cs); }
   ~Mutex( ) { DeleteCriticalSection(&cs); }
   
   void Lock( void ) { EnterCriticalSection(&cs); }
   void Unlock( void ) { LeaveCriticalSection(&cs); }

private:
   CRITICAL_SECTION cs;
};

class CGeiger
{
public:
	HANDLE m_hThread;
	DWORD m_dwThreadId;
	BOOL m_bRunning;
	Mutex m_Mutex;
	int m_nPulses;
	float m_fRate;
	LONG m_lLastAcquired;

public:
	CGeiger()
	{
		m_hThread = NULL;
		m_dwThreadId = 0;
		m_bRunning = false;
		m_nPulses = -1;
		m_fRate = 0;
		m_lLastAcquired = 0;
	}

	void Terminate()
	{
		m_bRunning = false;
	}

	void Thread();

	static DWORD WINAPI Thread( LPVOID lpParam ) 
	{
		CGeiger* pThis = (CGeiger*) lpParam;
		pThis->Thread();
		printf("Terminating geiger\n");
		return 0;
	}

	void CreateThread()
	{
		m_bRunning = true;
        m_hThread = ::CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            Thread,       // thread function name
            this,          // argument to thread function 
            0,                      // use default creation flags 
            &m_dwThreadId);   // returns the thread identifier 
	}

	void DeleteThread()
	{
		CloseHandle( m_hThread );
		m_hThread = NULL;
	}

public:
	bool IsValid()
	{
		return ( GetTickCount() - m_lLastAcquired < 10000 );
	}

	bool GetState( int& nPulses, float& fRate )
	{
		m_Mutex.Lock();
		nPulses = m_nPulses;
		fRate = m_fRate;
		bool bValid = IsValid();
		m_Mutex.Unlock();

		return bValid;
	}
};

class CGps
{
public:
	HANDLE m_hThread;
	DWORD m_dwThreadId;
	BOOL m_bRunning;
	Mutex m_Mutex;
	FLOAT m_fLatitude;
	FLOAT m_fLongitude;
	FLOAT m_fSpeed;
	LONG m_lLastAcquired;

public:
	CGps()
	{
		m_hThread = NULL;
		m_dwThreadId = 0;
		m_bRunning = false;
		m_fLatitude = 0;
		m_fLongitude = 0;
		m_fSpeed = 0;
		m_lLastAcquired = 0;
	}

	void Terminate()
	{
		m_bRunning = false;
	}

	void Thread();

	static DWORD WINAPI Thread( LPVOID lpParam ) 
	{
		CGps* pThis = (CGps*) lpParam;
		pThis->Thread();
		printf("Terminating gps\n");
		return 0;
	}

	void CreateThread()
	{
		m_bRunning = true;
        m_hThread = ::CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            Thread,       // thread function name
            this,          // argument to thread function 
            0,                      // use default creation flags 
            &m_dwThreadId);   // returns the thread identifier 
	}

	void DeleteThread()
	{
		CloseHandle( m_hThread );
		m_hThread = NULL;
	}

public:
	bool IsValid()
	{
		return ( GetTickCount() - m_lLastAcquired < 5000 );
	}

	BOOL GetState(FLOAT& fLatitude, FLOAT& fLongitude, FLOAT& fSpeed)
	{
		m_Mutex.Lock();
		fLatitude = m_fLatitude;
		fLongitude = m_fLongitude;
		fSpeed = m_fSpeed;
		bool bValid = IsValid();
		m_Mutex.Unlock();

		return bValid;
	}
};

class CController
{
public:
	HANDLE m_hThread;
	DWORD m_dwThreadId;
	BOOL m_bRunning;
	
	CGps* m_pGps;
	CGeiger* m_pGeiger;

public:
	CController( CGps* pGps, CGeiger* pGeiger )
	{
		m_hThread = NULL;
		m_dwThreadId = 0;
		m_bRunning = false;
		m_pGps = pGps;
		m_pGeiger = pGeiger;
	}

	void Terminate()
	{
		m_bRunning = false;
	}

	void Thread();

	static DWORD WINAPI Thread( LPVOID lpParam ) 
	{
		CController* pThis = (CController*) lpParam;
		pThis->Thread();
		printf("Terminating controller\n");
		return 0;
	}

	void CreateThread()
	{
		m_bRunning = true;
        m_hThread = ::CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            Thread,       // thread function name
            this,          // argument to thread function 
            0,                      // use default creation flags 
            &m_dwThreadId);   // returns the thread identifier 
	}
	void DeleteThread()
	{
		CloseHandle( m_hThread );
		m_hThread = NULL;
	}
};

// Main implementation

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType) 
{
    if (fdwCtrlType == CTRL_C_EVENT) 
    {
        printf("Control C\n");
		SetEvent( g_hTerminateUser );
        return TRUE;
    }
    return FALSE;
}

CString GetToken( CString& strLine, char ch )
{
	int nPos = strLine.Find( ch );
	_ASSERT( nPos >= 0 );
	CString strToken = strLine.Left(nPos);
	strLine = strLine.Mid(nPos+1);
	return strToken;
}

CString GetChars( CString& strLine, int nCount )
{
	CString strAux = strLine.Left(nCount);
	strLine = strLine.Mid(nCount);
	return strAux;
}

void CGps::Thread()
{
	CSerial serial;
	if ( !serial.Open("\\\\.\\COM1", 38400) )
	{
		printf("CGps: cannot open port!\n");
		WaitForSingleObject( g_hTerminateAll, 5000 ); // same as sleep(5000)
		return;
	}
	CString strBuffer;
	LONG lLastInfo = 0;
	while ( m_bRunning )
	{
		if ( WaitForSingleObject( g_hTerminateAll, 200 ) == 0 )
			break;

		CString strReply = serial.Recv();
		strBuffer += strReply;

		if ( !IsValid() && GetTickCount() - lLastInfo > 15000 )
		{
			printf("GPS-INFO: No response\n");
			lLastInfo = GetTickCount();
		}

		int nCr;
		while ( (nCr = strBuffer.Find(_T("\n"))) != -1)
		{
			CString strLine = strBuffer.Mid( 0, nCr );
			strBuffer = strBuffer.Mid( nCr+1 );
			
			// process line
			if ( strLine.Mid(0, 6) == _T("$GPRMC") )
			{
				float fFix;
				char chStatus;
				LONG lLatDec;
				float lLatFlo;
				char chLatSphere;
				LONG lLonDec;
				float lLonFlo;
				char chLonSphere;
				float fSpeed;
				float fAngle;
				LONG lDate;
				int nChecksum;

				if ( !IsValid() && GetTickCount() - lLastInfo > 10000 )
				{
					printf("GPS-INFO: %s\n", strLine.GetBuffer() );
					lLastInfo = GetTickCount();
				}
 				GetToken(strLine, ','); // $GPRMC
				fFix = (float)atof( GetToken(strLine, ',').GetBuffer() );
				chStatus = GetToken(strLine, ',')[0];
				lLatDec = atoi(GetChars(strLine, 2).GetBuffer() );
				lLatFlo = (float)atof(GetToken(strLine, ',').GetBuffer() );
				chLatSphere = GetToken(strLine, ',')[0];
				lLonDec = atoi(GetChars(strLine, 3).GetBuffer() );
				lLonFlo = (float)atof(GetToken(strLine, ',').GetBuffer() );
				chLonSphere = GetToken(strLine, ',')[0];
				fSpeed = (float)atof(GetToken(strLine, ',').GetBuffer() )*1.852f; // knots->kmh
				fAngle = (float)atof(GetToken(strLine, ',').GetBuffer() );
				lDate = atoi(GetToken(strLine, ',').GetBuffer() );
				GetToken(strLine, ','); // magvar
				GetToken(strLine, '*'); // magvar
				if ( sscanf( strLine.GetBuffer(), "%x", &nChecksum ) == 1 )
				{
					if ( chStatus == 'A' )
					{
						m_Mutex.Lock();
						m_fLatitude = lLatDec + lLatFlo/60.0f;
						m_fLongitude = lLonDec + lLonFlo/60.0f;
						m_fSpeed = fSpeed;
						m_lLastAcquired = GetTickCount();
						m_Mutex.Unlock();
					}
				}

			}
		} 
		if ( strBuffer.GetLength() > 1024 )
			strBuffer = strBuffer.Mid( strBuffer.GetLength()-1024 );

	}
	serial.Close();
}

void CGeiger::Thread()
{
	CSerial serial;
	if ( !serial.Open("\\\\.\\COM11", 115200) )
	{
		printf("CGeiger: cannot open port!\n");
		WaitForSingleObject( g_hTerminateAll, 5000 ); // same as sleep(5000)
		return;
	}
	CString strBuffer;
	while ( m_bRunning )
	{
		if ( WaitForSingleObject( g_hTerminateAll, 200 ) == 0 )
			break;
		//serial.Send("WND.Message( WND.Find('CWndGeiger'), -1, 0x6780);\n");
		CString strReply = serial.Recv();
		strBuffer += strReply;

		int nCr;
		while ( (nCr = strBuffer.Find(_T("\n"))) != -1 )
		{
			CString strLine = strBuffer.Mid( 0, nCr );
			strBuffer = strBuffer.Mid( nCr+1 );
			
			// process line
			int nToken = strLine.Find("Geiger=");
			if ( nToken != -1 )
			{
				int nPulses = 0;
				if ( sscanf( strLine.GetBuffer() + nToken + 7, "%d", &nPulses ) == 1 )
				{
					m_Mutex.Lock();
					m_nPulses = nPulses;
					m_lLastAcquired = GetTickCount();
					m_Mutex.Unlock();
				}
			}

			nToken = strLine.Find("Rate=");
			if ( nToken != -1 )
			{
				float fRate = 0;
				if ( sscanf( strLine.GetBuffer() + nToken + 5, "%f", &fRate) == 1 )
				{
					m_Mutex.Lock();
					m_fRate = fRate;
					m_Mutex.Unlock();
				}
			}

		} 
		if ( strBuffer.GetLength() > 1024 )
			strBuffer = strBuffer.Mid( strBuffer.GetLength()-1024 );
	}
	serial.Close();
}

CString GetTimestamp()
{
	CTime time = CTime::GetCurrentTime();
	return time.Format("%Y%m%d-%H%M%S");
}

void CController::Thread()
{
	CString strName = GetTimestamp() + ".txt";

	FILE* f = fopen( strName.GetBuffer(), "a" );

	while ( m_bRunning )
	{
		if ( WaitForSingleObject( g_hTerminateAll, 1000 ) == 0 )
			break;
			
		int nPulses = 0;
		float fLatitude = 0;
		float fLongitude = 0;
		float fSpeed = 0;
		float fRate = 0;

		BOOL bGps = m_pGps->GetState( fLatitude, fLongitude, fSpeed );
		BOOL bGeiger = m_pGeiger->GetState( nPulses, fRate );

		printf("GPS: ");
		if ( bGps )
			printf("lat:%.6f lon:%.6f spd:%4.1f", fLatitude, fLongitude, fSpeed );
		else
			printf("Error");
		printf("  Geiger: ");
		if ( bGeiger )
			printf("rate:%.4f  count:%5d", fRate, nPulses );
		else
			printf("Error");
		printf("\n");

		if ( bGps && bGeiger )
		{
			CString strLog;
			ULONGLONG ullTimestamp = CTime::GetCurrentTime().GetTime();
			LONG lTimestamp = (LONG)ullTimestamp;
			strLog.Format(_T("add({timestamp:%d,lat:%.6f,lon:%.6f,spd:%.1f,rate:%.3f,imp:%d});\n"), 
				lTimestamp, fLatitude, fLongitude, fSpeed, fRate, nPulses );
			fputs( strLog.GetBuffer(), f );
			// add to log
		}
	}
	
	fclose( f );
}

class CStandby
{
public:
	CStandby()
	{
		if (SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED) == NULL)
		{
			// try XP variant as well just to make sure 
			bool bOk = SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED) != NULL;
			_ASSERT( bOk );
		} 
	}
	~CStandby()
	{
		SetThreadExecutionState(ES_CONTINUOUS);
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	g_hTerminateUser = CreateEvent(NULL, FALSE, FALSE, _T("TerminateUser"));
	g_hTerminateAll = CreateEvent(NULL, FALSE, FALSE, _T("TerminateAll"));

    SetConsoleCtrlHandler(CtrlHandler, TRUE);

	CGps mGps;
	CGeiger mGeiger;
	CController mController(&mGps, &mGeiger);
	CStandby mStandby;

	mGeiger.CreateThread();
	mGps.CreateThread();
	mController.CreateThread();

	HANDLE hThreadArray[4] = {mGeiger.m_hThread, mGps.m_hThread, mController.m_hThread, g_hTerminateUser};

	printf("Running...\n");
	while ( true )
	{
		DWORD dwFailure = WaitForMultipleObjects(4, hThreadArray, FALSE, 1000);
		if ( dwFailure != WAIT_TIMEOUT )
		{
			_ASSERT( dwFailure >= 0 && dwFailure < 4 );
			if ( hThreadArray[dwFailure] == g_hTerminateUser )
			{
				SetEvent( g_hTerminateAll );
				break;
			}
			printf("Restarting thread... 0x%08x\n", dwFailure);
			if ( hThreadArray[dwFailure] == mGeiger.m_hThread )
			{
				mGeiger.CreateThread();
				hThreadArray[dwFailure] = mGeiger.m_hThread;
			}
			if ( hThreadArray[dwFailure] == mGps.m_hThread )
			{
				mGps.CreateThread();
				hThreadArray[dwFailure] = mGps.m_hThread;
			}
			if ( hThreadArray[dwFailure] == mController.m_hThread )
			{
				mController.CreateThread();
				hThreadArray[dwFailure] = mController.m_hThread;
			}
		}
	}

	printf("Stopping...\n");
	mGeiger.Terminate();
	mGps.Terminate();
	mController.Terminate();
	
    WaitForMultipleObjects(3, hThreadArray, TRUE, INFINITE);
	printf("Finished.\n");

	mGeiger.DeleteThread();
	mGps.DeleteThread();
	mController.DeleteThread();
	return 0;
}

