#include <winsock2.h>
#include <Ws2bth.h>

#pragma comment(lib, "ws2_32.lib")
#define BT_ADDR BTH_ADDR
#define AF_BT AF_BTH

class CConsole
{
	static CList<int> arrColorStack;
	static int nColor;
	static FILE* fLog;

public:
	CConsole(int c)
	{
		if ( arrColorStack.IsEmpty() )
			arrColorStack.AddTail(0x07);

		arrColorStack.AddTail( c );
		Color(c);
	}
	~CConsole()
	{
		if ( arrColorStack.GetSize() > 0 )
		{
			arrColorStack.RemoveTail();
			_ASSERT( arrColorStack.GetSize() > 0 );
			Color( arrColorStack.GetTail() );
		}
	}
	static void StartLogging()
	{
		_ASSERT( !fLog );
		if ( fopen_s(&fLog, "log.txt", "w") != 0 )
		{
			_ASSERT(0);
			fLog = NULL;
		}
		if ( fLog )
			fprintf(fLog, "Log opened!\n");
	}
	static void FinishLogging()
	{
		_ASSERT( fLog );
		if ( fLog )
		{
			fprintf(fLog, "Closing log\n");
			fclose(fLog);
			fLog = NULL;
		}
	}
	static void Color(int c)
	{
		nColor = c;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, c);
	}
	static void Print(CHAR* pFormat, ...)
	{
		static CHAR buff[1024];
		va_list argList;

		va_start(argList, pFormat);
		vsprintf_s(buff, 1023, pFormat, argList);
		va_end(argList);

		printf(buff);
		if ( fLog )
		{
			fprintf(fLog, "{%02x}", nColor);
			fprintf(fLog, buff);
		}
	}

};

CList<int> CConsole::arrColorStack;
int CConsole::nColor = 0;
FILE* CConsole::fLog = NULL;

class CAscii
{
public:
	char* m_pData;
	int m_nLength;

	static int HexToNum(wchar_t ch)
	{
		if ( ch >= '0' && ch <= '9')
			return ch - '0';
		if ( ch >= 'a' && ch <= 'f')
			return ch - 'a' + 10;
		if ( ch >= 'A' && ch <= 'F')
			return ch - '0' + 10;
		_ASSERT(0);
		return 0;
	}
	CAscii( CString str, int nBin = 0 )
	{
		if ( nBin )
		{
			_ASSERT( str.GetLength() % 2 == 0 );
			m_nLength = str.GetLength()/2;
			m_pData = new char[m_nLength];
			for (int i=0; i<m_nLength; i++)
				m_pData[i] = HexToNum(str[i*2])*16 | HexToNum(str[i*2+1]);
			return;
		}
		m_nLength = str.GetLength() + 1;
		m_pData = new char[m_nLength];
		int i;
		for ( i = 0; i < str.GetLength(); i++ )
			m_pData[i] = (char)str[i];
		m_pData[i] = 0;
	}
	~CAscii()
	{
		delete m_pData;
	}
	operator const char*()
	{
		return m_pData;
	}
	operator const long()
	{
		return m_nLength;
	}
	static CString ToHexString(char *p, int n)
	{
		CString strCode;
		for (int i=0; i<n; i++)	
		{
			CString strFmt;
			strFmt.Format(_T("%02x"), p[i]);
			strCode += strFmt;
		}
		return strCode;
	}
};

class CTerminator
{
public:
	HANDLE m_hTerminate;
	HANDLE m_hTerminateUser;

	CTerminator()
	{
		m_hTerminate = CreateEvent(NULL, FALSE, FALSE, _T("Terminate"));
		m_hTerminateUser = CreateEvent(NULL, FALSE, FALSE, _T("TerminateUser"));
		SetConsoleCtrlHandler(CtrlHandler, TRUE);
	}
	void operator ()()
	{
		SetEvent( m_hTerminate );
	}
	void Sleep(int nMs)
	{
		WaitForSingleObject( m_hTerminate, nMs );
	}

	static BOOL WINAPI CtrlHandler(DWORD fdwCtrlType) 
	{
		if (fdwCtrlType == CTRL_C_EVENT) 
		{
			CConsole c(0x1F);
			CConsole::Print("Control C\n");
			SetEvent( m_Terminator.m_hTerminateUser );
			return TRUE;
		}
		return FALSE;
	}
} m_Terminator;

class CMutex
{
public:
	CMutex( void ) { InitializeCriticalSection(&cs); }
	~CMutex( ) { DeleteCriticalSection(&cs); }

	void Lock( void ) { EnterCriticalSection(&cs); }
	void Unlock( void ) { LeaveCriticalSection(&cs); }

private:
	CRITICAL_SECTION cs;
};

class CScopedMutex
{
	CMutex* m_pMutex;

public:
	CScopedMutex( CMutex* m )
	{
		m_pMutex = m;
		m_pMutex->Lock();
	}
	~CScopedMutex()
	{
		m_pMutex->Unlock();
	}
};

class CThread
{
public:
	HANDLE m_hThread;
	DWORD m_dwThreadId;
	BOOL m_bRunning;
	CMutex m_Mutex;

public:
	CThread()
	{
		m_hThread = NULL;
		m_dwThreadId = 0;
		m_bRunning = false;
	}

	void Terminate()
	{
		m_bRunning = false;
	}

	virtual void Thread() { _ASSERT(0); }

	static DWORD WINAPI Thread( LPVOID lpParam ) 
	{
		CThread* pThis = (CThread*) lpParam;
		CConsole::Print("Starting\n");
		pThis->Thread();
		CConsole::Print("Terminating\n");
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

class CBluetoothSpp 
{
	SOCKADDR_BTH m_addrTarget;
	SOCKET m_hSocket;
	bool m_bConnected;
	bool m_bNewConnection;

private:
	bool Inquiry()
	{
		CConsole::Print("Inquiry...\n");
		memset( &m_addrTarget, 0, sizeof(m_addrTarget) );
		WSAQUERYSET wsaq;
		HANDLE hLookup;
		union {
			CHAR buf[5000];
			double __unused; // ensure proper alignment
		};
		LPWSAQUERYSET pwsaResults = (LPWSAQUERYSET) buf;
		DWORD dwSize  = sizeof(buf);
		BOOL bHaveName;
		ZeroMemory(&wsaq, sizeof(wsaq));
		wsaq.dwSize = sizeof(wsaq);
		wsaq.dwNameSpace = NS_BTH;
		wsaq.lpcsaBuffer = NULL;
		if (ERROR_SUCCESS != WSALookupServiceBegin (&wsaq, LUP_CONTAINERS, &hLookup))
		{
			CConsole con(0x0c);
			CConsole::Print("WSALookupServiceBegin failed %d\r\n", GetLastError());
			return false;
		}
		ZeroMemory(pwsaResults, sizeof(WSAQUERYSET));
		pwsaResults->dwSize = sizeof(WSAQUERYSET);
		pwsaResults->dwNameSpace = NS_BTH;
		pwsaResults->lpBlob = NULL;
		while (ERROR_SUCCESS == WSALookupServiceNext (hLookup, LUP_RETURN_NAME | LUP_RETURN_ADDR, &dwSize, pwsaResults))
		{
			_ASSERT (pwsaResults->dwNumberOfCsAddrs == 1);
			BT_ADDR b = ((SOCKADDR_BTH *)pwsaResults->lpcsaBuffer->RemoteAddr.lpSockaddr)->btAddr;
			bHaveName = pwsaResults->lpszServiceInstanceName && *(pwsaResults->lpszServiceInstanceName);
			if (bHaveName && _tcscmp(pwsaResults->lpszServiceInstanceName, _T("HUD_BT")) == 0 )
				m_addrTarget = *((SOCKADDR_BTH *)pwsaResults->lpcsaBuffer->RemoteAddr.lpSockaddr);
			CConsole::Print ("%S%S%04x%08x%S\n", bHaveName ? pwsaResults->lpszServiceInstanceName : L"", 
				bHaveName ? L"(" : L"", GET_NAP(b), GET_SAP(b), bHaveName ? L")" : L"");

			unsigned char paddr[] = {0x10, 0xc6, 0xfc, 0x5e, 0xd5, 0xd3};
			for ( int i=0; i<6; i++)
				((unsigned char*)&b)[5-i] = paddr[i];
//			memcpy(&b, paddr, sizeof(paddr));
			CConsole::Print ("%S%S%04x%08x%S\n", bHaveName ? pwsaResults->lpszServiceInstanceName : L"", 
				bHaveName ? L"(" : L"", GET_NAP(b), GET_SAP(b), bHaveName ? L")" : L"");

		}
		WSALookupServiceEnd(hLookup);
		if ( m_addrTarget.btAddr == 0 )
		{
			CConsole con(0x0c);
			CConsole::Print("OBDII interface not found\n");
		}
		return m_addrTarget.btAddr != 0;
	}

	bool ConnectService()
	{
		CConsole::Print("Connect...\n");
		SOCKADDR_BTH addr = m_addrTarget;
		HRESULT hr = CLSIDFromString( _T("{00001101-0000-1000-8000-00805f9b34fb}"), (GUID*)&addr.serviceClassId );
		if ( hr != S_OK )
		{
			CConsole con(0x0c);
			CConsole::Print("CLSIDFromString failed\n");
			return false;
		}

		m_hSocket = socket (AF_BT, SOCK_STREAM, BTHPROTO_RFCOMM);
		if (connect (m_hSocket, (SOCKADDR *)&addr, sizeof(m_addrTarget))) 
		{
			CConsole con(0x0c);
			CConsole::Print("connect failed - %d\n", GetLastError());
			closesocket ( m_hSocket );
			m_hSocket = NULL;
			return false;
		}

		u_long lMode = 1;
		ioctlsocket( m_hSocket, FIONBIO, &lMode); 

		return true;
	}

	void DisconnectService()
	{
		//CConsole c(0x1f);
		//CConsole::Print("DisconnectService!");
		m_bConnected = false;
		if ( m_hSocket )
		{
			closesocket( m_hSocket );
			m_hSocket = NULL;
		}
	}

public:
	CBluetoothSpp()
	{
		WSADATA wsd;
		WSAStartup (MAKEWORD(1,0), &wsd);
		m_hSocket = NULL;
		m_bConnected = false;
		m_bNewConnection = false;
		memset( &m_addrTarget, 0, sizeof(m_addrTarget) );
	}

	~CBluetoothSpp()
	{
		WSACleanup();
	}

	bool Connect()
	{
		m_bConnected = false;
		if ( !Inquiry() )
		{
			CConsole::Print("Inquiry failed\n");
			return false;
		}
		if ( !ConnectService() )
		{
			CConsole::Print("Connect service failed\n");
			return false;
		}
		m_bConnected = true;
		m_bNewConnection = true;
		CConsole::Print("Connected!\n");
		return true;
	}

	void Disconnect()
	{
		DisconnectService();
	}
/*
	CString Read()
	{
		CConsole con(0x0c);
		_ASSERT( m_hSocket );

		char buf[1024];
		int len = recv(m_hSocket, buf, sizeof(buf)-1, 0);
		int nErr = GetLastError();
		switch ( nErr )
		{
			case 0:
			case WSAEWOULDBLOCK:
			break;
			case WSAECONNABORTED:
				// comm failure -> reconnect
				CConsole::Print("WSA Error - trying to reconnect\n");
				DisconnectService();
			default:
				CConsole::Print("<error=%d>", nErr);	
		}

		if ( len < 0 )
		{
			// nothing to read
			return _T("");
		}
		buf[len] = 0;
		return CString(buf);
	}

	void Send( CString strText )
	{
		_ASSERT( m_hSocket );

		strText += _T("\r\n");
		// pozor !!! ascii!
		CAscii ascii(strText);
		send( m_hSocket, ascii, ascii, 0);
	}*/
	CString Read()
	{
		CConsole con(0x0c);
		_ASSERT( m_hSocket );

		char buf[1024];
		int len = recv(m_hSocket, buf, sizeof(buf)-1, 0);
		int nErr = GetLastError();
		switch ( nErr )
		{
			case 0:
			case WSAEWOULDBLOCK:
			break;
			case WSAECONNABORTED:
				// comm failure -> reconnect
				CConsole::Print("WSA Error - trying to reconnect\n");
				DisconnectService();
			default:
				CConsole::Print("<error=%d>", nErr);	
		}

		if ( len < 0 )
		{
			// nothing to read
			return _T("");
		}
		return CAscii::ToHexString(buf, len);
	}

	void Send( CString strText )
	{
		_ASSERT( m_hSocket );
		strText.Replace( _T(" "), _T("") );
		// pozor !!! ascii!
		CAscii ascii(strText, 1);
		send( m_hSocket, ascii, ascii, 0);
	}


	bool IsConnected()
	{
		return m_bConnected;
	}

	bool IsNewConnection()
	{
		if ( !m_bNewConnection )
			return false;
		//CConsole c(0x1f);
		//CConsole::Print("NewConnection!");
		m_bNewConnection = false;
		return true;
	}
};

class CBluetoothComm : public CThread, private CBluetoothSpp
{
	CList<CString> m_lstTransmit;
	CList<CString> m_lstReceive;
	CString m_strBuffer;

protected:
	CString GetLine( CString& strBuf )
	{
		int nDelim = -1;
		for ( int i = 0; i < strBuf.GetLength(); i++ )
		{
			wchar_t ch = strBuf[i];
			if ( ch == 0x0d || ch == 0x0a )
			{
				nDelim = i;
				break;
			}
		}
		if ( nDelim == -1 )
			return _T("");
		
		CString strLine = strBuf.Left(nDelim);
		if ( strLine[0] == '<' )
			strLine = strLine.Mid(1);
		
		while ( nDelim < strBuf.GetLength() && ( strBuf[nDelim] == 0x0d || strBuf[nDelim] == 0x0a ) )
			nDelim++;

		strBuf = strBuf.Mid( nDelim+1 );
		return strLine;
	}

	virtual void Thread() 
	{
		while ( m_bRunning )
		{
			if ( WaitForSingleObject( m_Terminator.m_hTerminate, 200 ) == 0 )
				break;

			if ( !IsConnected() )
			{
				CBluetoothSpp::Connect();
				if ( !IsConnected() )
				{
					CConsole::Print("[");
					m_Terminator.Sleep(5000);
					CConsole::Print("]");
				}
			} else
			{
				CString strRead = CBluetoothSpp::Read();
				if ( !strRead.IsEmpty() )
				{
					m_strBuffer += strRead;
					CString strLine;
					do {
						strLine = GetLine( m_strBuffer );
						if ( !strLine.IsEmpty() )
							DidRead( strLine );
					} while ( !strLine.IsEmpty() );
					
					if ( m_strBuffer.GetLength() > 1024 )
					{
						CConsole con(0x0c);
						CConsole::Print("Read buffer overflow!\n");
						m_strBuffer.Empty();
					}
				}

				CString strSend = ToWrite();
				if ( !strSend.IsEmpty() )
					CBluetoothSpp::Send( strSend );
			}
		}
		CBluetoothSpp::Disconnect();
	}

protected:
	CString ToWrite()
	{
		CScopedMutex m(&m_Mutex);
		if ( m_lstTransmit.GetSize() > 0 )
			return m_lstTransmit.RemoveHead();
		return _T("");
	}

	void DidRead( CString strText )
	{
		CConsole con(0x08);
		CConsole::Print( ">'%s'\n", CAscii(strText).m_pData );
		CScopedMutex m(&m_Mutex);
		m_lstReceive.AddTail( strText );
	}

public:
	CString Read()
	{
		CScopedMutex m(&m_Mutex);
		if ( m_lstReceive.GetSize() > 0 )
			return m_lstReceive.RemoveHead();
		return _T("");
	}

	void Write( CString strText )
	{
		CConsole con(0x08);
		CConsole::Print( "<'%s'\n", CAscii(strText).m_pData );
		CScopedMutex m(&m_Mutex);
		m_lstTransmit.AddTail( strText );
	}

	bool IsReady()
	{
		bool bBufferEmpty = false;
		{
			CScopedMutex m(&m_Mutex);
			bBufferEmpty = m_lstTransmit.IsEmpty() ? true : false;
		}
		return bBufferEmpty && IsConnected();
	}
	bool IsConnected()
	{
		// todo: thread safe?
		return CBluetoothSpp::IsConnected();
	}
	bool IsNewConnection()
	{
		return CBluetoothSpp::IsNewConnection();
	}
	void Reconnect()
	{
		{
			CScopedMutex m(&m_Mutex);
			m_lstTransmit.RemoveAll();
			m_lstReceive.RemoveAll();
			m_strBuffer.Empty();
		}
		CBluetoothSpp::Disconnect();
	}
};
