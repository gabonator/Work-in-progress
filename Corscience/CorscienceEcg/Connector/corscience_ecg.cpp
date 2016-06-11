// boso_bp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WebSocket.h"

BOOL bRunning = TRUE;

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

class CEcg : public CCorscience
{
	BYTE m_buffer[1024];
	int m_nLength;
public:

	CEcg()
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


		/*
		BYTE buf[128];
		int nLen = Receive( f, buf, 128 );
		if (nLen == 0)
			return;
			*/
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
		if ( wId == 0x0901 ) // config_analog_req
		{
			arrPacket.Add( 1 ); // 1 = one ECG channel, 2 = two ECG channels
			arrPacket.Add( 5 ); // 5 = 500 kHz sampling, 10 = 1 kHz sampling
			arrPacket.Add(0x32); // 0x32 = 50 Hz country, 0x3C = 60 Hz country
		}
		if ( wId == 0x0926 ) // start_stop_offline_ecm
		{
			arrPacket.Add( (BYTE)wParam );
		}
		if ( wId == 0x0905 ) // start_stop_ecg_transmission
		{
			arrPacket.Add( (BYTE)wParam );
		}
		CCorscience::SendPacket( f, arrPacket );
	}


	virtual void AnalysePacket( WORD wPacketCode, CArray<BYTE>& arrPacket)
	{
		switch ( wPacketCode )
		{
			case 0x0500:
			{
				_ASSERT( arrPacket.GetSize() == 10 ); 
				BYTE bProducerId = arrPacket[0];
				BYTE bDeviceId = arrPacket[1];
				UCHAR strSerial[16] = {0};
				memcpy( strSerial, &(arrPacket[2]), 8 );

				printf("(0x0500) Identification: ProducerId=%d, DeviceId=%d, Serial=%02x %02x %02x %02x %02x %02x %02x %02x\n", 
					bProducerId, bDeviceId, 
					strSerial[0], strSerial[1], strSerial[2], strSerial[3], 
					strSerial[4], strSerial[5], strSerial[6], strSerial[7]);
				break;
			}
			case 0x0100:
			{
				_ASSERT( arrPacket.GetSize() == 4 ); 
				BYTE bProtocolVersion = arrPacket[0];
				WORD wPayload = arrPacket[1] | (arrPacket[2]<<8);
				BYTE bMaxCached = arrPacket[3];

				printf("(0x0100) Protocol: Version=%d, MaxPayload=%d, Max cached packets=%d\n", bProtocolVersion, wPayload, bMaxCached);
				break;
			}
			case 0x0502:
			{
				_ASSERT( arrPacket.GetSize() == 2 ); // 25 neviem preco
				WORD wVersion = arrPacket[0] | (arrPacket[1]<<8);

				printf("(0x0502) Hardware version: %04x\n", wVersion);
				break;
			}
			case 0x0701:
			{
				_ASSERT( arrPacket.GetSize() == 3 ); 
				BYTE bChannel = arrPacket[0];
				BYTE bSampling = arrPacket[1];
				BYTE bMainsFrequency = arrPacket[2];
				
				PSTR strChannel = "Unknown";
				switch ( bChannel )
				{
					case 1: strChannel = "one ECG channel"; break;
					case 2: strChannel = "two ECG channel"; break;
				}

				PSTR strSampling = "Unknown";
				switch ( bSampling )
				{
					case 0x05: strSampling = "500 Hz"; break;
					case 0x0A: strSampling = "1 kHz"; break;
				}


				PSTR strMains = "Unknown";
				switch ( bMainsFrequency )
				{
					case 0x32: strMains = "50 Hz"; break;
					case 0x3C: strMains = "60 Hz"; break;
				}

				printf("(0x0701) CONFIG_ANALOG_CFM: Channels=%s (%d), Sampling=%s (%d), Mains frequency=%s (%d)\n", 
					strChannel, bChannel, strSampling, bSampling, strMains, bMainsFrequency);
				break;
			}

			case 0x0726:
			{
				_ASSERT( arrPacket.GetSize() == 14 );
				BYTE bEcmStatus1 = arrPacket[0];
				BYTE bEcmStatus2 = arrPacket[1];
				BYTE arrPayload[12];
				memcpy(arrPayload, &(arrPacket[2]), 12);

				BYTE nL = (bEcmStatus1 & 4)?1:0;
				BYTE nR = (bEcmStatus1 & 2)?1:0;
				BYTE nF = (bEcmStatus1 & 1)?1:0;
				BYTE nN = (bEcmStatus2 & 64)?1:0;
				printf("(0x0726) OFFLINE_ECM_CFM: (N=%d, 0x%02x%02x%02x), (F=%d, 0x%02x%02x%02x), (L=%d, 0x%02x%02x%02x), (R=%d, 0x%02x%02x%02x)\n", 
					nN, arrPayload[2], arrPayload[1], arrPayload[0],
					nF, arrPayload[5], arrPayload[4], arrPayload[3],
					nL, arrPayload[6], arrPayload[7], arrPayload[6],
					nR, arrPayload[11], arrPayload[10], arrPayload[9]
					);

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
			case 0x0200:
			{
				_ASSERT( arrPacket.GetSize() == 1 );
				printf("(0x0200) Acknowledged\n");
				break;
			}
			case 0x0400:
			{
				_ASSERT( arrPacket.GetSize() == 1 );
				printf("(0x0400) Packet rejected, probably incorrect parameters\n");
				break;
			}
			case 0x0724:
			{
				//_ASSERT( arrPacket.GetSize() == 1 );
				WORD wPacketNumber = 0; //arrPacket[0] | (arrPacket[1] << 8);
				BYTE bPulse = arrPacket[2];
				BYTE arrMonitorBytes[2];
				memcpy( arrMonitorBytes, &(arrPacket[3]), 2 );

				BYTE bError = arrPacket[ arrPacket.GetSize()-4 ];
				DWORD dwCounter = 
					(arrPacket[ arrPacket.GetSize()-3 ]) | 
					(arrPacket[ arrPacket.GetSize()-2 ]<<8) | 
					(arrPacket[ arrPacket.GetSize()-1 ]<<16);

				BYTE* pPayload = &(arrPacket[5]);
				int nPayloadLen = arrPacket.GetSize() - 9;
				_ASSERT( nPayloadLen + 9 == arrPacket.GetSize() );
				// payload
				// error byte
				// datasets
				printf("(0x0724) ECG_DATA_TRANSMISSION:  Pulse=%d, Monitor=%02x%02x, Error=%d, Counter=%d, Payload length=%d\n",
					bPulse, arrMonitorBytes[0], arrMonitorBytes[1], bError, dwCounter, nPayloadLen );
				DecodeEcgPayload( pPayload, nPayloadLen );
				break;
			}
			//772,600
			default:
				printf("(0x%04x) Unknown command, %d bytes\n", wPacketCode, arrPacket.GetSize() );

		}
	}

	void DecodeEcgPayload( BYTE* pPayload, int nPayloadLen )
	{
		CArray<int> arrSamples;
		int i=0;
		while (i<nPayloadLen)
		{
			BYTE b0 = pPayload[i++];
			if ( (b0 & 1) == 0 )
			{
				// single byte
				*((CHAR*)&b0) >>= 1;	// vymaz bit, zachovaj znamienko
				CHAR cb0 = *((CHAR*)&b0);
				arrSamples.Add( (int)cb0 );
			} else
			{
				// two bytes
				_ASSERT( i<nPayloadLen );
				BYTE b1 = pPayload[i++];
				*((CHAR*)&b0) >>= 1;	// vymaz bit, zachovaj znamienko
				WORD wData = (b0<<8)|b1;
				SHORT shData = *((SHORT*)&wData);
				arrSamples.Add( shData );				
			}
		}

		TransferEcgData( arrSamples );
	}

	virtual void TransferEcgData( CArray<int>& arrSamples )
	{
		for (int i=0; i<arrSamples.GetSize(); i++)
		{
			printf("%d, ", arrSamples[i]);
		}
		printf("\n");
	}

	void Comm(HANDLE h)
	{
		BYTE bId;
		WORD wType = -1;

		// Cleanup
		ReceivePacket( h, bId, wType );

		if ( wType == 0x0726 )
		{
			printf("Stopping offline ecm...\n");
			SendPacket( h, 0x0926, 0 ); // stop offline ecm
			ReceivePacket( h, bId, wType );
		}
		if ( wType == 0x0724 )
		{
			printf("Stopping ecg transmission...\n");
			SendPacket( h, 0x0905, 0 );
			ReceivePacket( h, bId, wType );
		}

 		if (!bRunning)
			return;
			
		// Request identification
		SendPacket( h, 0x0800, 0x0500 );
		// Get identification
		ReceivePacket( h, bId, wType );
		_ASSERT( wType == 0x0500 );

		// Request protocol version
		SendPacket( h, 0x0800, 0x0100 );
		// Get protocol version
		ReceivePacket( h, bId, wType );
		_ASSERT( wType == 0x0100 );

		// CONFIG_ANALOG_REQ
		SendPacket( h, 0x0901 );
		// CONFIG_ANALOG_CFM
		ReceivePacket( h, bId, wType );
		_ASSERT( wType == 0x0701 );

		// START_OFFLINE_ECM
		SendPacket( h, 0x0926, 1 );
		// Ack
		ReceivePacket( h, bId, wType );
		_ASSERT( wType == 0x0726 || wType == 0x200 );

		wType = -1;
		LONG lTick = GetTickCount();
		while ( GetTickCount()-lTick < 3000 && bRunning )
			ReceivePacket( h, bId, wType );

		// STOP_OFFLINE_ECM
		SendPacket( h, 0x0926, 0 );
		// Ack
		ReceivePacket( h, bId, wType );
		_ASSERT( wType == 0x0200 );

		// START_STOP_ECG_TRANSMISSION
		SendPacket( h, 0x0905, 1 );

		//lTick = GetTickCount();
		while ( /*GetTickCount()-lTick < 20000 */ bRunning )
			ReceivePacket( h, bId, wType );

		// START_STOP_ECG_TRANSMISSION
		SendPacket( h, 0x0905, 0 );
		// Ack
		ReceivePacket( h, bId, wType );
		if ( wType == 0x300 ) // not acknowledged
		{
			SendPacket( h, 0x0905, 0 );
			ReceivePacket( h, bId, wType );
		}
		_ASSERT( wType == 0x0200 );

		printf("Transmission stoped.\n");
	}
};

class CEcgWebsocket : public CEcg
{
public:
	CWebSockets m_ws;
	FILE* f;

	CEcgWebsocket()
	{
		m_ws.SetListener( Listener );
		m_ws.Start();
		f = fopen("recording1.bin", "wb");
	}
	~CEcgWebsocket()
	{
		m_ws.Stop();
		fclose(f);
	}

	static void Listener( UCHAR* msg )
	{
		printf( "WS: %s\n", msg );
	}

	virtual void TransferEcgData( CArray<int>& arrSamples )
	{
		CString strData = "[";

		for (int i=0; i<arrSamples.GetSize(); i++)
		{
			CString strVal;
			strVal.Format("%d", arrSamples[i]);
			if (i>0)
				strData += ",";
			strData += strVal;
		}
		strData += "]";
		m_ws.Send( strData.GetBuffer() );
		fwrite(arrSamples.GetData(), arrSamples.GetSize()*4, 1, f);
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
    SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE );

	HANDLE h = INVALID_HANDLE_VALUE;

	printf("Connecting to target...\n");

	do {
		h = CreateFile( "COM8:", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL );
		if (h != INVALID_HANDLE_VALUE)
			break;
		Sleep(5000);
		printf(".");
	} while (h == INVALID_HANDLE_VALUE);

	DCB dcbSerial = {0};
	dcbSerial.DCBlength=sizeof(dcbSerial);
	if (!GetCommState(h, &dcbSerial)) {
		//error getting state
		_ASSERT(0);
	}
	dcbSerial.BaudRate=CBR_115200;
	dcbSerial.ByteSize=8;
	dcbSerial.StopBits=ONESTOPBIT;
	dcbSerial.Parity=NOPARITY;
	if(!SetCommState(h, &dcbSerial)){
		//error setting serial port state
		_ASSERT(0);
	}

	COMMTIMEOUTS comTimeOut;                   
	comTimeOut.ReadIntervalTimeout = 3;
	comTimeOut.ReadTotalTimeoutMultiplier = 3;
	comTimeOut.ReadTotalTimeoutConstant = 2;
	comTimeOut.WriteTotalTimeoutMultiplier = 3;
	comTimeOut.WriteTotalTimeoutConstant = 2;
	SetCommTimeouts(h, &comTimeOut);

	_ASSERT( h != INVALID_HANDLE_VALUE && h );
	printf("Ok.\n");
	
	CEcgWebsocket ecg;

	ecg.Comm( h );
	//Sleep(10000);

	CloseHandle(h);
	printf("Done.\n");

//	char x[4];
//	fgets(x, 4, stdin);
	return 0;
}

