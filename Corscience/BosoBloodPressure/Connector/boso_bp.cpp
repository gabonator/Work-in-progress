// boso_bp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

BOOL bRunning = TRUE;

class CBloodPressureTypes
{
public:
	struct DateTime {
		BYTE y, m, d;
		BYTE h, n, s;
		CString toString()
		{
			CString strAux;
			strAux.Format("%04d%02d%02d%02d%02d%02d", 
				y + 2000, m, d, 
				h, n, s);
			return strAux;
		}
	} timestamp;
	struct BloodPressure {
		BYTE ihb;
		WORD sys;
		BYTE dia;
		BYTE pulse;
	} meas;

	struct Measurement {
		DateTime dt;
		BloodPressure bp;
	};
};

class CCorscience
{
protected:
	BYTE g_bPacketCounter;

private:
	WORD crc16(WORD crc, unsigned char x)
	{
		unsigned crc_new = (unsigned char)(crc >> 8) | (crc << 8);
		crc_new ^= x;
		crc_new ^= (unsigned char)(crc_new & 0xff) >> 4;
		crc_new ^= crc_new << 12;
		crc_new ^= (crc_new & 0xff) << 5;
		return crc_new;
	}

	WORD GetCrc( CArray<BYTE>&arrPacket )
	{
		WORD crc = 0xffff;
		for (int i=0; i<arrPacket.GetSize(); i++)
			crc = crc16(crc, arrPacket[i] );
		return crc;
	}

public:
	CCorscience()
	{
		g_bPacketCounter = 0;
	}

	int DecodePacket(BYTE* buf, int nLen, BYTE& bId, WORD &wCode)
	{
		if (nLen == 0)
			return 0;
		_ASSERT( buf[0] == 0xFC ); //packet start

		int nTerminator = -1;
		for (int i=0; i<nLen; i++)
			if ( buf[i] == 0xFD )
			{
				nTerminator = i;
				break;
			}

		_ASSERT( nTerminator > 0 );
		nLen = nTerminator+1;

		_ASSERT( buf[nLen-1] == 0xFD ); // packet end

		CArray<BYTE> arrPacket;

		for (int i=1; i<nLen-1; i++)
		{
			BYTE b = buf[i];
			_ASSERT( b != 0xfc && b != 0xfd );
			if ( b == 0xfe )
			{
				i++;
				b = buf[i] ^ 0x20;
			}
			arrPacket.Add( b );
		}

		WORD crc = 0xffff;
		for (int i=0; i<arrPacket.GetSize()-2; i++)
			crc = crc16(crc, arrPacket[i]);

		_ASSERT( arrPacket[ arrPacket.GetSize()-2 ] == (crc & 0xff) );
		_ASSERT( arrPacket[ arrPacket.GetSize()-1 ] == (crc >> 8) );

		BYTE nPacketNr = arrPacket[0];
		WORD wPacketCode = (arrPacket[2]<<8) | arrPacket[1];

		arrPacket.RemoveAt(0, 3); // packet nr, packet code 
		arrPacket.SetSize( arrPacket.GetSize()-2 ); // crc

		AnalysePacket( wPacketCode, arrPacket );
		bId = nPacketNr;
		wCode = wPacketCode;
		return nLen;
	}

	void SendPacket( HANDLE f, CArray<BYTE>&arrPacket )
	{
		BYTE buf[128];
		BYTE* pbuf = buf;
		int i=0;

		//crc
		WORD wCrc = GetCrc( arrPacket );
		arrPacket.Add( wCrc & 0xff );
		arrPacket.Add( wCrc >> 8 );

		*pbuf++ = 0xfc;
		for (int j=0; j<arrPacket.GetSize(); j++)
		{
			BYTE b = arrPacket[j];
			if ( b == 0xfc || b == 0xfd || b == 0xfe )
			{
				*pbuf++ = 0xfe;
				*pbuf++ = b ^ 0x20;
			} else
			{
				*pbuf++ = b;
			}
		}
		*pbuf++ = 0xfd;

		int nCount = pbuf-buf;
		/*
		printf("send=%d {", nCount);
		for (int i=0; i<(int)nCount; i++)
		printf("0x%02x, ", buf[i]);
		printf("}\n");
		*/

		DWORD dwWritten = 0;
		WriteFile( f, buf, nCount, &dwWritten, NULL ); 
		_ASSERT( dwWritten == nCount );
	}

	int Receive( HANDLE h, BYTE* buf, int nMax)
	{
		DWORD dwRead;
		ReadFile( h, buf, nMax, &dwRead, NULL );
		/*
		printf("read=%d {", dwRead);
		for (int i=0; i<(int)dwRead; i++)
		printf("0x%02x, ", buf[i]);
		printf("}\n");
		*/
		return dwRead;
	}

	virtual void AnalysePacket( WORD wPacketCode, CArray<BYTE>& arrPacket )
	{
		_ASSERT(0);
	}
};

class CPressureMeter : public CCorscience, public CBloodPressureTypes
{
protected:
	CString m_strId;
	BYTE m_buffer[1024];
	int m_nLength;

public:
	CPressureMeter()
	{
		m_nLength = 0;
	}

	virtual void ReceivePacket( HANDLE f, BYTE& bId, WORD& wType )
	{
		int nLen = Receive( f, m_buffer+m_nLength, 1024-m_nLength );
		m_nLength += nLen;
		if ( m_nLength == 0 )
			return;

		if ( m_buffer[0] != 0xFC )
		{
			printf("Packet begin mismatch, throwing away...\n");
			int nBegin = -1;
			for (int i=0; i<m_nLength; i++)
			{
				if (m_buffer[i] == 0xfc)
				{
					nBegin = i;
					break;
				}
			}
			if (nBegin == -1)
			{
				m_nLength = 0;
				return;
			}
			for (int i=nBegin; i<m_nLength; i++)
				m_buffer[i-nBegin] = m_buffer[i];
			m_nLength -= nBegin;
		}

		while ( m_nLength > 0 )
		{
			int nTerminator = -1;
			for (int i=0; i<m_nLength; i++)
				if ( m_buffer[i] == 0xFD )
				{
					nTerminator = i;
					break;
				}

			if ( nTerminator == -1 )
				return;

			int nUsedLength = DecodePacket( m_buffer, m_nLength, bId, wType );
			_ASSERT(nUsedLength);
			if (nUsedLength==0)
				break;
			// skip bytes;
			for (int i=nUsedLength; i<m_nLength; i++)
				m_buffer[i-nUsedLength] = m_buffer[i];
			m_nLength -= nUsedLength;
			//nProcessed += nUsedLength;
		}
	}

	virtual void SendPacket( HANDLE f, WORD wId, WORD wParam = 0)
	{
		CArray<BYTE> arrPacket;

		arrPacket.Add( g_bPacketCounter++ );
		arrPacket.Add( wId & 0xff );
		arrPacket.Add( wId >> 8 );

		if ( wId == 0x0800 ) // request commmand
		{
			arrPacket.Add( wParam & 0xff );
			arrPacket.Add( wParam >> 8 );
		}
		if ( wId == 0x0200 ) // ack
		{
			arrPacket.Add((BYTE)wParam);
		}
		if ( wId == 0x0000 ) // close conn
		{
		}

		CCorscience::SendPacket( f, arrPacket );
	}


	virtual void AnalysePacket( WORD wPacketCode, CArray<BYTE>& arrPacket)
	{
		switch ( wPacketCode )
		{
			case 0x0500:
			{
				_ASSERT( arrPacket.GetSize() == 14 || arrPacket.GetSize() == 22 ); // 25 neviem preco
				BYTE bProducerId = arrPacket[0];
				BYTE bDeviceId = arrPacket[1];
				CHAR strSerial[16] = {0};
				memcpy( strSerial, &(arrPacket[2]), 14 );

				printf("(0x0500) Identification: ProducerId=%d, DeviceId=%d, Serial=%s\n", bProducerId, bDeviceId, strSerial);
				m_strId = CString(strSerial);
				break;
			}
			case 0x0706:
			{
				DateTime timestamp;
				BloodPressure meas;
				//ASSERT( arrPacket.GetSize() == 21 || arrPacket.GetSize() == 27 ); // 27 neviem preco
				timestamp.y = arrPacket[0];
				timestamp.m = arrPacket[1];
				timestamp.d = arrPacket[2];
				timestamp.h = arrPacket[3];
				timestamp.n = arrPacket[4];
				timestamp.s = arrPacket[5];
				meas.ihb = arrPacket[6];
				meas.sys = arrPacket[7] | (arrPacket[8]<<8);
				meas.dia = arrPacket[9];
				meas.pulse = arrPacket[10];

				printf("(0x0607) Blood pressure data:%02d.%02d.%04d %02d:%02d:%02d Ihb:%d, Systolic:%d, Diastolic:%d, Heart rate:%d\n", 
					timestamp.d, timestamp.m, timestamp.y + 2000, 
					timestamp.h, timestamp.n, timestamp.s,
					meas.ihb, meas.sys, meas.dia, meas.pulse);

				DataHandler(timestamp, meas);
				break;
			}
			case 0x07FA:
			{
				_ASSERT( arrPacket.GetSize() == 0 );
				printf("(0x07FA) No more data\n");
				break;
			}
			case 0x0300:
			{
				_ASSERT( arrPacket.GetSize() == 1 );
				printf("(0x0300) Not acknowledged, probably crc mismatch\n");
				break;
			}
			default:
				printf("(0x%04x) Unknown command, %d bytes\n", wPacketCode, arrPacket.GetSize() );

		}
	}

	virtual void DataHandler( DateTime& dt, BloodPressure& bp )
	{
		_ASSERT(0);
	}

	virtual void Comm(HANDLE h)
	{
		BYTE bId;
		WORD wType = -1;

		ReceivePacket( h, bId, wType );
		if (wType != (WORD)-1)
		{
			// after successfull connection, sents its identification - only once
			_ASSERT( wType == 0x0500 );
		}

		// reqest
		SendPacket( h, 0x0800, 0x0706 );	
		do {
			ReceivePacket( h, bId, wType );

			if (wType == 0x0300)
				return;

			SendPacket( h, 0x0200, bId );
		} while ( wType == 0x0706 );	

		_ASSERT ( wType == 0x07FA );	 // no more measurements available
		Sleep(500);
		ReceivePacket( h, bId, wType );	// dummy, any unwaited response?
	}
};

class CPressureMeterServer : public CPressureMeter
{
private:
	CArray <Measurement> g_arrMeasurements;

public:
	virtual void Comm(HANDLE h)
	{
		CPressureMeter::Comm( h );
		DataFlush();
	}

private:
	BOOL MakeUrlRequest( CString strUrl, CString strIp, CString strPath, CString strGet )
	{
		CString strRequest;	
		SOCKET sock;
		struct sockaddr_in serveraddr;

		strRequest.Format(
			"GET /%s?%s HTTP/1.0\r\n"
			"Host: %s\r\n"
			"\r\n", strPath, strGet, strUrl);

		//printf("Request:\n==========\n%s\n==========\n", strRequest);

		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			_ASSERT( !!!"WSAStartup" );

		if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
			_ASSERT( !!!"socket() failed");

		memset(&serveraddr, 0, sizeof(serveraddr));
		serveraddr.sin_family      = AF_INET;
		serveraddr.sin_addr.s_addr = inet_addr(strIp);
		serveraddr.sin_port        = htons((unsigned short) 80);

		if (connect(sock, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
			_ASSERT(!!!"connect() failed");

		if (send(sock, strRequest.GetBuffer(), strRequest.GetLength(), 0) != strRequest.GetLength())
			_ASSERT(!!!"send() sent a different number of bytes than expected");

		CString strResponse;	
		LONG lTick = GetTickCount();
		int nRecv = recv(sock, strResponse.GetBuffer(1024), 1024-1, 0);
		if (nRecv > 0)
			strResponse.ReleaseBuffer(nRecv);
		else
			_ASSERT(0);

		closesocket( sock );
		WSACleanup();
		//printf("Response length=%d, Response data:\n=======\n%s\n========\n", nRecv, strResponse);

		if ( strResponse.Find( "result:1") > -1 )
		{
			return TRUE;	
		} else
		if ( strResponse.Find( "result:0") > -1 )
		{
			return FALSE;
		}
		_ASSERT(0);
		return FALSE;	
	}

	virtual void DataHandler(DateTime& dt, BloodPressure& bp)
	{
		Measurement meas;	
		meas.dt = dt;		
		meas.bp = bp;
		g_arrMeasurements.Add( meas );
	}

	void DataFlush()	
	{	
		CString strUrlRequest;
		if ( g_arrMeasurements.GetSize() <= 0 )	
			return;

		if ( g_arrMeasurements.GetSize() > 1 )	
			strUrlRequest = "add=[";
		else
			strUrlRequest = "add=";

		for ( int i=0; i<g_arrMeasurements.GetSize(); i++)
		{
			Measurement& meas = g_arrMeasurements[i];
			CString strMeas;	
			CString strId = m_strId.IsEmpty() ? "Unknown" : m_strId;	
			strMeas.Format("{type:boso_bp_1,id:%s,timestamp:%s,sys:%d,dia:%d,pul:%d,flags:%d}",
				strId,	
				meas.dt.toString(), meas.bp.sys, meas.bp.dia, meas.bp.pulse, meas.bp.ihb );

			if (i>0)
				strUrlRequest += ",";
			strUrlRequest += strMeas;
		}

		if ( g_arrMeasurements.GetSize() > 1 )	
			strUrlRequest += "]";

		BOOL bOk = MakeUrlRequest( "pub.valky.eu", "217.67.30.39", "bp/", strUrlRequest );

		_ASSERT( bOk );
		g_arrMeasurements.RemoveAll();
	}
};

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

int main(int argc, CHAR* argv[])
{
	CPressureMeterServer MeterServer;

	SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE );
	HANDLE h = INVALID_HANDLE_VALUE;

	printf("Connecting to target...\n");

	do {
		h = CreateFile( "COM6:", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL );
		if (h != INVALID_HANDLE_VALUE)
			break;
		printf(".");
		for (int i=0; i<50 && bRunning; i++)
			Sleep(100);
		if (!bRunning)
			return 1;
	} while (h == INVALID_HANDLE_VALUE );


	COMMTIMEOUTS comTimeOut;                   
	comTimeOut.ReadIntervalTimeout = 3;
	comTimeOut.ReadTotalTimeoutMultiplier = 3;
	comTimeOut.ReadTotalTimeoutConstant = 2;
	comTimeOut.WriteTotalTimeoutMultiplier = 3;
	comTimeOut.WriteTotalTimeoutConstant = 2;
	SetCommTimeouts(h, &comTimeOut);

	_ASSERT( h != INVALID_HANDLE_VALUE && h );
	printf("Ok.\n");
	while (bRunning)
	{
		MeterServer.Comm( h );
		printf("Waiting...\n");
		for (int i=0; i<50 && bRunning; i++)
			Sleep(100);
	}
	printf("Closing port\n");
	CloseHandle(h);

	return 0;
}

