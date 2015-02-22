#include "stdafx.h"
#include "HUDSerial.h"

bool HUDSerial::Init(const char * port, int baud)
{
	m_hCommPort = ::CreateFile(port,
		GENERIC_READ | GENERIC_WRITE, // access ( read and write)
		0, // (share) 0:cannot share the
		// COM port
		0, // security (None)
		OPEN_EXISTING, // creation : open_existing
		0, // we dont want overlapped operation
		0 // no templates file for
		// COM port...
		);

	if (m_hCommPort == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "Cannot open COM port %s\n", port);
		return false;
	}
	/* Declare and Init the DCB */
	DCB dcbSerialParams = { 0 };

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!::GetCommState(m_hCommPort, &dcbSerialParams))
	{
		fprintf(stderr, "Get configuration port has problem.\n");
		return false;
	}
	//fill up params
	dcbSerialParams.BaudRate = baud;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	if (!::SetCommState(m_hCommPort, &dcbSerialParams))
	{
		/* Error occurred. Inform user */
		fprintf(stderr, "Set configuration port has problem.\n");
		return false;
	}
	return true;
}


HUDSerial::~HUDSerial()
{
	if (m_hCommPort != INVALID_HANDLE_VALUE)
		CloseHandle(m_hCommPort);
}

int HUDSerial::SendPacket(const unsigned char* pBuf, int nLen)
{
	if (m_hCommPort != INVALID_HANDLE_VALUE)
	{
		DWORD dwBytesWritten;
		if (WriteFile(m_hCommPort, pBuf, nLen, &dwBytesWritten, NULL))
			return dwBytesWritten;
		else
			return -2;
	}
	else
		return -1;
}
