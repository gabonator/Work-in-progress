// nocache.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <crtdbg.h>
#include <string.h>
#include "WebSocket.h"
#include <vector>
using namespace std;

#define _ASSERT_VALID(e) { if ( !(e) ) _ASSERT(0); }

bool bRunning = true;

CWebSockets m_ws;
volatile int nRequest = 0;
//CHAR sendmsg[1024] = {0};
list<string> lstSend;
HANDLE hFile = NULL;
CRITICAL_SECTION m_cs;

BOOL Do(HANDLE hFile)
{
	char buf[128];
	DWORD wr;

	EnterCriticalSection(&m_cs);
	while ( !lstSend.empty() )
	{
		string& str = lstSend.back();
		if ( !WriteFile( hFile, str.c_str(), str.length(), &wr, NULL ) ||
			wr != str.length() )
		{
			printf("Write error, %d\n", GetLastError());
		}
		lstSend.pop_back();
	}
	LeaveCriticalSection(&m_cs);

	DWORD rd;
	//printf("r");
	if( !ReadFile(hFile, buf, 127, &rd, NULL ))
	{
		printf("Read failed. System error %d", GetLastError() );
		return FALSE;
	}
	//printf(rd>0?"R":"0");
	if ( rd > 0 )
	{
		buf[rd] = 0;
		m_ws.Send( buf );
	}


	return TRUE;
}

BOOL CtrlHandler( DWORD fdwCtrlType )
{
	switch( fdwCtrlType ) {
	case CTRL_C_EVENT:
		bRunning = FALSE;
		printf( "Ctrl-C event\n\n" );
		return TRUE;
	default:
		return FALSE;
	}
}

void listener( UCHAR* pstr )
{
	if ( pstr )
	{
		EnterCriticalSection(&m_cs);
		lstSend.push_front( string( (char*)pstr) );
		LeaveCriticalSection(&m_cs);
	}
}

void InitSerial( HANDLE hComm )
{
	DCB dcb;
	COMMTIMEOUTS cto = { MAXDWORD, 0, 0, 4, 4 }; 

		if (!SetCommTimeouts(hComm, &cto))
	{
		fprintf(stderr, "SetCommState failed." );
		//_close(fd);
		//return -1;
	}

		dcb.DCBlength = sizeof(dcb);
	memset(&dcb, sizeof(dcb), 0);

	if (!GetCommState(hComm, &dcb))
	{
		//_close(fd);
		//return -1;	
		fprintf(stderr, "GetCommState failed." );
	}

	dcb.BaudRate = 57600;
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
	dcb.ByteSize = 8; //sio->info.databits;
	/*
	switch (sio->info.parity)
	{
	case SIO_PARITY_NONE: dcb.Parity = 0; break;
	case SIO_PARITY_ODD: dcb.Parity = 1; break;
	case SIO_PARITY_EVEN: dcb.Parity = 2; break;		
	default: CloseHandle(fd); return -1;
	}

	switch (sio->info.stopbits)
	{
	case 1: dcb.StopBits = 0; break;
	case 2: dcb.StopBits = 2; break;
	default: CloseHandle(fd); return -1;
	}*/
	dcb.Parity = 0;
	dcb.StopBits = 0;

	if (!SetCommState(hComm, &dcb))
	{
		fprintf(stderr, "SetCommState failed." );
		//_close(fd);
		//return -1;
	}	


}
int main(int argc, CHAR* argv[])
{
	SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE );
	m_ws.SetListener( listener );
	
	//Initilize the critical section
	InitializeCriticalSection(&m_cs);

	hFile = CreateFileA( "COM1:" , GENERIC_READ | GENERIC_WRITE, 0, NULL,
			     OPEN_EXISTING, 0, NULL);
	if ( hFile == INVALID_HANDLE_VALUE )
	{ 
		printf("Error opening port %d\n", GetLastError());
		return 1;
	}
	InitSerial(hFile);
	m_ws.Start();
	while (bRunning && Do(hFile) )
	{
		Sleep(10);
	}
	m_ws.Stop();

	CloseHandle(hFile);
	return 0;
}
