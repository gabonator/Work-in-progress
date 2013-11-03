
#include <afxtempl.h>
//#include <crtdbg.h>
#include <winsock2.h>

#ifndef _WIN32_WCE
#pragma comment(lib, "ws2_32.lib")
#define BT_ADDR BTH_ADDR
#define AF_BT AF_BTH
#include "Lib\Ws2bth.h"
#else
/*
#pragma comment(lib, "ws2.lib")
#define BT_ADDR BTH_ADDR
#define AF_BT AF_BTH
#include <Ws2bth.h>
*/
#define SERIALBT
#include <bt_api.h>
#pragma comment(lib, "btdrt.lib")
#define DEFAULT_RFCOMM_CHANNEL 0 //15
#define CHANNEL_MASK 31
#define DEFAULT_MTU 100
//#include "../ce/bt/BtSdkCe.h"
//#pragma comment(lib, "D:\\Projects\\Git\\repository\\Main\\Sources\\Driver\\Source\\CE\\bt\\BtSdkCE30.lib")
#endif

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

class CConsole
{
	static CList<int> arrColorStack;
	static int nColor;
	static FILE* fLog;
	static CMutex m_Mutex;

public:
	CConsole(int c)
	{
		CScopedMutex m(&m_Mutex);
		if ( arrColorStack.IsEmpty() )
			arrColorStack.AddTail(0x07);

		arrColorStack.AddTail( c );
		Color(c);
	}
	~CConsole()
	{
		CScopedMutex m(&m_Mutex);
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
#ifdef _WIN32_WCE
		fLog = fopen("\\SDMMC\\log.txt", "w");
		if ( fLog == INVALID_HANDLE_VALUE )
#else
		if ( fopen_s(&fLog, "log.txt", "w") != 0 )
#endif
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
		CScopedMutex m(&m_Mutex);
		nColor = c;
#ifndef _WIN32_WCE
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, c);
#endif
	}
	static void Print(CHAR* pFormat, ...)
	{
		CScopedMutex m(&m_Mutex);
		static CHAR buff[1024];
		va_list argList;

		va_start(argList, pFormat);
#ifdef _WIN32_WCE
		vsprintf(buff, pFormat, argList);
#else
		vsprintf_s(buff, 1023, pFormat, argList);
#endif
		va_end(argList);

		printf(buff);
		CString strBuf(buff);
		OutputDebugString(strBuf);
		if ( fLog )
		{
			fprintf(fLog, "{%02x}", nColor);
			fprintf(fLog, buff);
#ifdef _WIN32_WCE
			fflush(fLog);
#endif
		}
	}

};

CList<int> CConsole::arrColorStack;
int CConsole::nColor = 0;
FILE* CConsole::fLog = NULL;
CMutex CConsole::m_Mutex;

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
#ifndef _WIN32_WCE
		SetConsoleCtrlHandler(CtrlHandler, TRUE);
#endif
	}
	void operator ()()
	{
		SetEvent( m_hTerminate );
	}
	void Sleep(int nMs)
	{
		WaitForSingleObject( m_hTerminate, nMs );
	}
#ifndef _WIN32_WCE
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
#endif
} m_Terminator;

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

#if defined(SERIALBT)
class CBluetoothSpp 
{
	bool m_bConnected;
	bool m_bInquiry;
	HANDLE hDevice;
	HANDLE hPort;

public:	
	CBluetoothSpp()
	{
		m_bConnected = false;
		m_bInquiry = true;
		hDevice = NULL;
		hPort = NULL;
	}

	~CBluetoothSpp()
	{
	}


private:
	bool Inquiry()
	{
		if ( hDevice )
		{
			CConsole::Print("Device already created.\n");
			return true;
		}
		BT_ADDR addr = 0;
		unsigned char paddr[] = {0x10, 0xc6, 0xfc, 0x5e, 0xd5, 0xd3};
		for ( int i=0; i<6; i++)
			((unsigned char*)&addr)[5-i] = paddr[i];

		int e = BthSetPIN(&addr, 4, (unsigned char*)"1234");
		CConsole::Print("Set pin returned: %d\n", e);

		if ( !CreateDevice(3, 0, &addr) )
		{
			CConsole::Print("Create device failed.\n");
			return false;
		}
		CConsole::Print("Create device ok\n");
		return true;
	}

	bool ConnectService()
	{
		hPort = ::CreateFile(_T("COM3:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		if ( hPort == INVALID_HANDLE_VALUE )
		{
			CConsole::Print("Open port failed - error %d\n", GetLastError());
			return false;
		}
		CConsole::Print("Open port ok\n");
		return false;
	}
	void DisconnectService()
	{
		::CloseHandle(hPort);
		RemoveDevice();
	}

	BOOL CreateDevice( UINT nPortIndex, UINT nRfChannel, BT_ADDR* pAddr /* = NULL */ )
	{
		WCHAR szErrW[256];
		int rfChannel = 0;

		PORTEMUPortParams pp;
		ZeroMemory (&pp, sizeof(PORTEMUPortParams));

		// Verify channel supplied is okay or not
		if ( nRfChannel != 0 ) {
			if ( (nRfChannel <= 31) && (nRfChannel >= 1) )
				rfChannel = (unsigned char)nRfChannel; // Default overriden by user
			else {
				wsprintf (szErrW, L"User supplied RfChannel is invalid");
				MessageBox( NULL, szErrW, L"LwVirtualCom", MB_OK );

				return FALSE;
			}
		}
		else {
			rfChannel = DEFAULT_RFCOMM_CHANNEL;
		}

		if (!pAddr) {
			// Following, required for server port
			pp.flocal = TRUE; // This enables a server COM port to accept incoming connections
			pp.channel = rfChannel & CHANNEL_MASK; // The server channel is specified explicitly by setting channel. 
		}
		else {
			// Following, required for client port
			CopyMemory(&pp.device, pAddr, sizeof(BT_ADDR));

			//pp.imtu = DEFAULT_MTU;
			pp.channel = 0; //rfChannel & CHANNEL_MASK;
			
			HRESULT hr = CLSIDFromString( _T("{00001101-0000-1000-8000-00805f9b34fb}"), (GUID*)&pp.uuidService );
			if ( hr != S_OK )
				CConsole::Print("GUID Failed!\n");
			else
				CConsole::Print("GUID ok!\n");

			pp.uiportflags = 0; //RFCOMM_PORT_FLAGS_REMOTE_DCB;
		}

		// Register the Bluetooth Protocol stack with the virtual COM port
		hDevice = RegisterDevice (L"COM", nPortIndex, L"btd.dll", (DWORD)&pp);
		if (hDevice == NULL) {
			wsprintf (szErrW, L"RegisterDevice failed, error = %d\n", GetLastError ());
			//POPMSG(szErrW);
			MessageBox( NULL, szErrW, L"LwVirtualCom", MB_OK );

			return FALSE;
		}

		return TRUE;	
	}

	VOID RemoveDevice()
	{
		if (hDevice) {
			// Ensure that COM port is not in service first
			//..
			//..

			DeregisterDevice(hDevice);
			hDevice = NULL;
		}
	}

public:
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
		CConsole::Print("Connected!\n");
		return true;
	}

	void Disconnect()
	{
		DisconnectService();
	}

	CString Read()
	{
		return CString();
	}

	void Send( CString strText )
	{
		_ASSERT( m_hSocket );

		// pozor !!! ascii!
		CAscii ascii(strText, 1);
		DWORD dwWritten = 0;
		::WriteFile(hPort, ascii.m_pData, ascii.m_nLength, &dwWritten, NULL);
	}

	bool IsConnected()
	{
		return m_bConnected;
	}
};

#elif defined(WIDCOMM)
class CBluetoothSpp :public CBtIf, public CRfCommPort
{
	bool m_bConnected;
	bool m_bInquiry;
	BD_ADDR m_BdAddr;
	bool m_bFound;
	CRfCommIf m_RfCommIf;
	GUID m_ServiceGuid;

private:
	bool Inquiry()
	{
		memcpy( &m_ServiceGuid, &CBtIf::guid_SERVCLASS_SERIAL_PORT, sizeof(GUID) );
		memset( m_BdAddr, 0, sizeof(BD_ADDR) );
		m_bInquiry = TRUE;
		m_bFound = FALSE;
		CConsole::Print("Starting inquiry\n");
		StartInquiry();
		LONG lTick = GetTickCount();
		while ( GetTickCount() - lTick < 20000 && m_bInquiry )
			Sleep(1000);
		CConsole::Print("Stopping inquiry, inProgress=%d, found=%d\n", m_bInquiry, m_bFound);
		StopInquiry();
		return m_bFound;
	}

	bool ConnectService()
	{
		CSdpDiscoveryRec Sdp_Record;
		CConsole::Print("ConnectService: ReadDiscoveryRecords\n");
		if (!ReadDiscoveryRecords(m_BdAddr, 1, &Sdp_Record, &m_ServiceGuid))
			return false;
		UINT8   scn;
		CConsole::Print("ConnectService: FindRFCommScn\n");
		if ( !Sdp_Record.FindRFCommScn(&scn) )
			return false;
		CConsole::Print("ConnectService: AssignScnValue\n");
		if (!m_RfCommIf.AssignScnValue(&m_ServiceGuid,scn))
			return false;
		/*
		if (!m_RfCommIf.SetSecurityLevel(_T("Widcomm SDK RFComm Service"),BTM_SEC_NONE, FALSE))
			return false;
			*/
		CConsole::Print("ConnectService: OpenClient\n");
		OpenClient(m_RfCommIf.GetScn(), m_BdAddr);                                     

		return false;
	}
	void DisconnectService()
	{
	}
	virtual void OnDeviceResponded (BD_ADDR bda, DEV_CLASS devClass, BD_NAME bdName, BOOL bConnected)
	{
		CConsole::Print("OnDeviceResponded (addr:%02x%02x%02x%02x%02x%02x, class:%d, name:%s, connected:%d\n", 
			bda[0], bda[1], bda[2], bda[3], bda[4], bda[5],
			devClass, bdName, bConnected);

		if ( CString(bdName) == _T("GARMIN HUD") )
		{
			m_bFound = TRUE;
			memcpy(m_BdAddr, bda, BD_ADDR_LEN);
			CConsole::Print("Device found! Starting discovery\n");
			StartDiscovery (bda, &m_ServiceGuid);
		}
	}
	virtual void OnDiscoveryComplete()
	{
		CConsole::Print("OnDiscoveryComplete");
		m_bInquiry = FALSE;
	}
	virtual void OnEventReceived (UINT32 event_code)
	{
		/*
		Cette fonction est appelée lorsqu'un évenement sur la connection apparait.
		*/
		CConsole::Print("OnEvendReceived (%d)", event_code);

		switch (event_code)
		{
		case PORT_EV_CONNECTED: //Connection OK.
			CConsole::Print(" PORT_EV_CONNECTED");
			break;
		case PORT_EV_CONNECT_ERR: //Erreur à la connection.
			CConsole::Print(" PORT_EV_CONNECT_ERR");
			break;
		}
		CConsole::Print("\n");
	}
	virtual void OnDataReceived (void *p_data, UINT16 len)
	{
		CConsole::Print("Received %d bytes\n", len);
	}
public:
	CBluetoothSpp()
	{
		m_bConnected = false;
		m_bInquiry = true;
	}

	~CBluetoothSpp()
	{
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
		CConsole::Print("Connected!\n");
		return true;
	}

	void Disconnect()
	{
		DisconnectService();
	}

	CString Read()
	{
		return CString();
	}

	void Send( CString strText )
	{
		_ASSERT( m_hSocket );

		// pozor !!! ascii!
		CAscii ascii(strText, 1);
        
		unsigned short length_written;
		Write((void*)&ascii.m_pData, ascii.m_nLength, &length_written);
		_ASSERT( length_written == ascii.m_nLength );
	}

	bool IsConnected()
	{
		return m_bConnected;
	}

};

#else
class CBluetoothSpp 
{
	SOCKADDR_BTH m_addrTarget;
	SOCKET m_hSocket;
	bool m_bConnected;

private:
	/*
	bool Pair()
	{
		HANDLE hPairedEvent = CreateEvent ( NULL, TRUE, FALSE, BTPAIRAPI_NEWDEVICE_PAIRING_EVENT );
		HANDLE hPairFailedEvent = CreateEvent ( NULL, TRUE, FALSE, BTPAIRAPI_FAILED_PAIR_ATTEMPT_EVENT );
		HANDLE arEvents[2] ={ hPairedEvent, hPairFailedEvent};
		char strPin[] = "1234";
		DWORD dwResult = StartBTPair ( m_addrTarget, strPin, 4 );
		CConsole::Print("StartBTPair - result %d\n", dwResult);
		if ( dwResult == ERROR_SUCCESS )
		{
			BOOL fEventReceived = FALSE;
			for ( nLoopCount = 0; !fEventReceived && nLoopCount < 10; ++nLoopCount )
			{
				WORD dwWait = WaitForMultipleObjects ( 2, arEvents, FALSE, 1000 * 60 );

				switch (dwWait)
				{
				case WAIT_OBJECT_0:
					CConsole::Print("Pairing succeeded\n");
//					fEventReceived = TRUE;
					break;
				case WAIT_OBJECT_0 + 1:
					CConsole::Print("Pairing failed\n");
					//RETAILMSG ( 1, ( TEXT ( "BTPairSvcSample: Pairing failed\r\n" ), dwResult ));
//					fEventReceived = TRUE;
					break;
				default:
					// must be WAIT_TIMEOUT
					CConsole::Print("Pairing timeout\n");
					break;
				}

			}
		}
		CloseHandle ( hPairedEvent );
		CloseHandle ( hPairFailedEvent );
	}
	*/
	bool Inquiry()
	{
		//m_nStatus = 0x1000;
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
		if ( ERROR_SUCCESS != WSALookupServiceBegin (&wsaq, LUP_CONTAINERS, &hLookup) )
		{
			//m_nStatus = 0x2000 | WSAGetLastError();
			CConsole con(0x0c);
			CConsole::Print("WSALookupServiceBegin failed %d\r\n", WSAGetLastError());
			return false;
		}
		ZeroMemory(pwsaResults, sizeof(WSAQUERYSET));
		pwsaResults->dwSize = sizeof(WSAQUERYSET);
		pwsaResults->dwNameSpace = NS_BTH;
		pwsaResults->lpBlob = NULL;
		//m_nStatus = 0x3000;
		DWORD dwStatus = -1;
		CConsole::Print("WSALookupServiceNext (%08x)\n", hLookup);
		while (ERROR_SUCCESS == (dwStatus = WSALookupServiceNext (hLookup, LUP_RETURN_NAME | LUP_RETURN_ADDR, &dwSize, pwsaResults)))
		{
			_ASSERT (pwsaResults->dwNumberOfCsAddrs == 1);
			BT_ADDR b = ((SOCKADDR_BTH *)pwsaResults->lpcsaBuffer->RemoteAddr.lpSockaddr)->btAddr;
			bHaveName = pwsaResults->lpszServiceInstanceName && *(pwsaResults->lpszServiceInstanceName);
			if (bHaveName && _tcscmp(pwsaResults->lpszServiceInstanceName, _T("GARMIN HUD")) == 0 )
				m_addrTarget = *((SOCKADDR_BTH *)pwsaResults->lpcsaBuffer->RemoteAddr.lpSockaddr);
//			wCConsole::Print (L"%s%s%04x%08x%s\n", bHaveName ? pwsaResults->lpszServiceInstanceName : L"", 
//				bHaveName ? L"(" : L"", GET_NAP(b), GET_SAP(b), bHaveName ? L")" : L"");
		}
		CConsole::Print("WSALookup ended with %d, err %d\n", dwStatus, WSAGetLastError());
		WSALookupServiceEnd(hLookup);
		if ( m_addrTarget.btAddr == 0 )
		{
			//m_nStatus = 0x4000;
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
			//m_nStatus = 0x6000;
			CConsole con(0x0c);
			CConsole::Print("CLSIDFromString failed\n");
			return false;
		}

		m_hSocket = socket (AF_BT, SOCK_STREAM, BTHPROTO_RFCOMM);
		if (connect (m_hSocket, (SOCKADDR *)&addr, sizeof(m_addrTarget))) 
		{
			//m_nStatus = 0x6000;
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
		CConsole::Print("Connected!\n");
		return true;
	}

	void Disconnect()
	{
		DisconnectService();
	}

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

		// pozor !!! ascii!
		CAscii ascii(strText, 1);
		send( m_hSocket, ascii, ascii, 0);
	}

	bool IsConnected()
	{
		return m_bConnected;
	}

};
#endif

class CGarminHud : public CThread, private CBluetoothSpp
{
	CList<CString> m_lstTransmit;
	CList<CString> m_lstReceive;

protected:

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
				if (!strRead.IsEmpty())
					DidRead( strRead );

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
		if ( !IsConnected() )
			return;
		CConsole con(0x08);
		CConsole::Print( "<'%s'\n", CAscii(strText).m_pData );
		CScopedMutex m(&m_Mutex);
		m_lstTransmit.AddTail( strText );
	}

	bool IsConnected()
	{
		// todo: thread safe?
		return CBluetoothSpp::IsConnected();
	}
	void Reconnect()
	{
		{
			CScopedMutex m(&m_Mutex);
			m_lstTransmit.RemoveAll();
			m_lstReceive.RemoveAll();
		}
		CBluetoothSpp::Disconnect();
	}
	// iface



	void Request( CString strReq )
	{
		Write( strReq );
	}

	CString Response()
	{
		return Read();		
	}

	bool IsReady()
	{
		return IsConnected();
	}

};
