#define _AFXDLL
#include <afxtempl.h>
#include <WinSock2.h>
#include <math.h>

#pragma comment(lib, "ws2_32.lib")

typedef CArray<BYTE> Buffer;

#define DeviceIp "192.168.1.76"

void SendTcp(Buffer& data, char* addr, int port)
{
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr( addr );
	server.sin_port = htons( port );
	SOCKET s = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( s == INVALID_SOCKET )
		return;
	if( connect(s,(struct sockaddr*)&server,sizeof(server)) == INVALID_SOCKET)
		return;
	send(s, (char*)data.GetData(), data.GetSize(), 0);
	closesocket(s);
}

void SendUdp(Buffer& data, char* addr, int port, bool broadcast = false)
{
	sockaddr_in dest;
	/*
	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = 0; // choose any
	*/
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr( addr );
	dest.sin_port = htons( port );
	SOCKET s = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
	if ( broadcast )
	{
		BOOL enabled = TRUE;
		if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char*)&enabled, sizeof(BOOL)) < 0)
		{
			perror("broadcast options");
			closesocket(s);
			return;
		}
	}
//	bind( s, (sockaddr *)&local, sizeof(local) );
	int ret = sendto( s, (const char*)data.GetData(), data.GetSize(), 0, (sockaddr *)&dest, sizeof(dest) );
	closesocket(s);
}

BYTE LoByte(WORD wData)
{
	return wData & 0xff;
}

BYTE HiByte(WORD wData)
{
	return wData >> 8;
}

void CopyBuffer( Buffer& Buf, char* data)
{
	Buf.SetSize( strlen(data) );
	memcpy(Buf.GetData(), data, Buf.GetSize());
}

void BuildPacket(Buffer& Packet, const Buffer& DmxData)
{
	WORD wOpcode = 0x5000;
	WORD wVersion = 14;
	WORD wUniverse = 0;
	BYTE bPhysical = 0;
	static BYTE bSequence = 0;

	Packet.RemoveAll();
	Packet.Add('A');
	Packet.Add('r');
	Packet.Add('t');
	Packet.Add('-');
	Packet.Add('N');
	Packet.Add('e');
	Packet.Add('t');
	Packet.Add(0x00);

	Packet.Add( LoByte( wOpcode ) );
	Packet.Add( HiByte( wOpcode ) );
	Packet.Add( HiByte( wVersion ) );
	Packet.Add( LoByte( wVersion ) );
	// bSequence - incremented on sending every packet, used by the receiver
	// to reorder the UDP packets if received in incorrect order
	Packet.Add( bSequence ); 
	Packet.Add( bPhysical ); 
	Packet.Add( LoByte(wUniverse) ); 
	Packet.Add( HiByte(wUniverse) ); 
	// how many bytes are we sending?
	Packet.Add( HiByte(DmxData.GetSize()) ); 
	Packet.Add( LoByte(DmxData.GetSize()) ); 
	// append data
	for ( int i = 0; i < DmxData.GetSize(); i++ )
		Packet.Add( DmxData[i] );

	bSequence++;
}

void DmxTest()
{
	float a = 0;
	for ( int l=0; l<5000; l++)
	{
		Buffer packet, dmx;

		int nVal = (int)(sin(a)*100.0f+100.0f);
		a += 0.1f;

		if ( nVal < 0 ) nVal = 0;
		if ( nVal > 255 ) nVal = 255;

		printf("set value %d\n", nVal);
		dmx.Add( nVal );
		BuildPacket( packet, dmx );
		
		// use this when sending packet to known IP on local subnet
		//SendUdp(packet, DeviceIp, 6454);

		// use this to send packet to unknown IP or outside the subnet
		SendUdp(packet, "255.255.255.255", 6454, true);

		Sleep(50);
	}

}

void GateTest()
{
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
	{
		perror("socket creation");
		return;
	}

	BOOL enabled = TRUE;
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&enabled, sizeof(BOOL)) < 0)
	{
		perror("broadcast options");
		closesocket(sock);
		return;
	}

	struct sockaddr_in Sender_addr;
	Sender_addr.sin_family = AF_INET;
	Sender_addr.sin_port = htons(3333);
	Sender_addr.sin_addr.s_addr = inet_addr("255.255.255.255");

	struct sockaddr_in Recv_addr;
	Recv_addr.sin_family = AF_INET;
	Recv_addr.sin_port = htons(3330);
	Recv_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock, (sockaddr*)&Recv_addr, sizeof(Recv_addr)) < 0)
	{
		perror("bind");
		closesocket(sock);
		return;
	}

	char msg[] = "ESPP\x01";

	printf(".");
	if (sendto(sock, msg, strlen(msg), 0, (sockaddr *)&Sender_addr, sizeof(Sender_addr)) < 0)
	{
		closesocket(sock);
		return;
	}

	unsigned char buff[1024];
	int SenderAddrSize = sizeof (Recv_addr);
	int n = recvfrom(sock, (char*)buff, 1024, 0, (sockaddr *)&Recv_addr, &SenderAddrSize);
	if ( n > 0 )
	{
		printf("from %d.%d.%d.%d:", 
			Recv_addr.sin_addr.S_un.S_un_b.s_b1, Recv_addr.sin_addr.S_un.S_un_b.s_b2,
			Recv_addr.sin_addr.S_un.S_un_b.s_b3, Recv_addr.sin_addr.S_un.S_un_b.s_b4);

		if ( strncmp((char*)buff, "ESPR", 4) == 0 )
		{
			char name[11] = {0};
			char data[1024] = {0};
			memcpy(name, buff+14, 10);
			memcpy(data, buff+27, n-27);		

			for ( int i=0; i<n-27; i++)
				if ( data[i] == 0 ) data[i] = '_';

			printf(" mac=%02x-%02x-%02x-%02x-%02x-%02x "
				"type=%04x ver=%d.%d switch=%02x name='%s' "
				"opt=%02x tos=%02x ttl=%02x datalen=%d data='%s'\n",
				buff[4], buff[5], buff[6], buff[7], buff[8], buff[9],
				buff[10]*256 + buff[11], buff[12]/10, buff[12]%10, buff[13], name,
				buff[24], buff[25], buff[26], n-27, data);
		}
		/*
		for ( int i=0; i<n; i++)
		if ( buff[i] == 0 ) buff[i] = '_';
		buff[n] = 0;
		printf("recv='%s'\n", buff);
		*/
	}
	closesocket(sock);
}

void DmxConfig()
{
	Buffer data;
	/*
	// config
	Buffer head, ip, name;
	CopyBuffer( head, "ESNC");
	ip.Add( 192 ); ip.Add( 168 ); ip.Add( 1 ); ip.Add( 79 );
	CopyBuffer( name, "Open DMX  ");

	data.Append( head );
	data.Append( ip );
	data.Append( name );
	data.Add(0); // options
	data.Add(0); // tos
	data.Add(0); // ttl
	SendTcp(data, DeviceIp, 3333); // 6456 3333 3330
	*/
	// send reset command
	CopyBuffer( data, "ESZZ");
	SendTcp(data, DeviceIp, 3333);
}

int _tmain(int argc, _TCHAR* argv[])
{
	WSAData data;
	WSAStartup( MAKEWORD( 2, 2 ), &data );
	GateTest();
	DmxTest();
	//DmxConfig();
	WSACleanup();
	return 0;
}

