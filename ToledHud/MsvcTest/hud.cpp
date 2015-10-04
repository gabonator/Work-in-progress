#include "stdafx.h"
#include <afxtempl.h>	
#include <crtdbg.h>
#include "btspp.h"


/*
1 - doprava 45d
3 - doprava 90d
4 - doprava ostra	
6 - dolava ostra
8 - dolava 90d
9 - dolava 45d
11 - uturn doprava
12 - uturn dolava
13 - rb 2 hodiny
15 - rb doprava
16 - rb 5 hodin
18 - rb dolava 7 hodin
21 - rb dolava 9 hodin
22 - rb dolava 11 hodin
24 - rb rovno
26 - ikona Q
29 - ikona R
30 - ikona P / finish
31 - ikona T
32 - Y krizovatka, chod dolava
33 - Y krizovatka, chod doprava
34 - krizovatka rovno, chod dolava
35 - krizovatka rovno, chod doprava
36 - sipka dolava
37 - sipka doprava
38..41 - plne roudabouty
42 - ikona M
43 - ikona C
45 - animacia loading
46 - ikona loading postupna zlava
47 - ikona loading postupna sprava
48..58 anglicke rb

128... lanes  [_][X][X] straight
138    lanes  [_][X][_] straight
148    lanes  [X][_][X] ...
158           [_][X][X]
168           [_][M][X]
178           [_][X][X]
180 ... bordel

*/
CBluetoothSpp bt;
int q = 0;

CString Hex(int n)
{
	CString str;
	str.Format( _T("%02x"), n );
	return str;
}

void SendToled(unsigned char* pBuf, int nLen)
{
	CArray<int> arrPacket;
	arrPacket.Add( '$' );
	arrPacket.Add( 'H' );
	_ASSERT(nLen == 34);

	for ( int i=0; i<nLen; i++)
		arrPacket.Add( pBuf[i] );
	
	//crc
	unsigned char nCrc = 0;
	for ( int i=0; i<arrPacket.GetSize(); i++)
		nCrc += arrPacket[i];

	arrPacket.Add( nCrc );
	_ASSERT(arrPacket.GetSize()-1 == 36);  // DOC!!!
	arrPacket.Add( arrPacket.GetSize()-1 );

	CString strPacket;
	for ( int i=0; i<arrPacket.GetSize(); i++)
	{
		strPacket += Hex( arrPacket[i] );
		// stuffing
		//if ( i > 0 && i < arrPacket.GetSize()-2 && arrPacket[i] == 0x10 )
//			strPacket += Hex( arrPacket[i] );
	}
	bt.Send( strPacket );
}

DWORD Nibble(DWORD dw)
{
	unsigned char *pData = (unsigned char*)&dw;
	unsigned char newData[4] = {pData[3], pData[2], pData[1], pData[0]};
	return *((DWORD*)newData);
}

void SendToled()
{
	typedef unsigned char BYTE; 
	enum {
		UnitsMeters = 0,
		UnitsMiles = 1,
		UnitsDotMile = 2,
		UnitsFeet = 3
	};
	enum {
		InfoNone = 0,
		InfoCall = 1,
		InfoSms = 2
	};
	enum {
		LcdOff = 0,
		LcdOn = 1
	};
#pragma pack(1)
	struct {
		BYTE bRouteAvailability;
		DWORD dwPrimaryDistance; // 10m intervaly
		BYTE bPrimaryDirection;
		DWORD dwSecondaryDistance; // 10m intervaly
		BYTE bSecondaryDirection;
		DWORD dwSpeedCameraDistance; // 10m intervaly
		DWORD dwSpeedCameraLimit; // 10m intervaly
		DWORD dwCurrentSpeed; // 10m intervaly
		DWORD dwDistanceToDestination; // 10m intervaly
		BYTE eUnitsSpeed; 
		BYTE eUnitsSpeedCamera; 
		BYTE eUnitsDestination; 
		BYTE eUnitsPrimary;
		BYTE eUnitsSecondary;
		BYTE eInfo;
		BYTE eLcd;
	} toledBuf;
	
	toledBuf.bRouteAvailability = 1;
	toledBuf.dwPrimaryDistance = Nibble(q*5);
//	strcpy(toledBuf.strPrimaryDistance, "523");
	toledBuf.bPrimaryDirection = q; 
	toledBuf.dwSecondaryDistance = Nibble(50);
	toledBuf.bSecondaryDirection = q; 

	toledBuf.dwSpeedCameraDistance = Nibble(q);
	toledBuf.dwSpeedCameraLimit = Nibble(100-(q%100));
	toledBuf.dwCurrentSpeed = Nibble(q);
	toledBuf.dwDistanceToDestination = Nibble(q);

	BYTE bUnits1 = 1, bUnits2 = 2;
	toledBuf.eUnitsSpeed = bUnits1;
	toledBuf.eUnitsSpeedCamera = bUnits1;
	toledBuf.eUnitsDestination = bUnits2;
	toledBuf.eUnitsPrimary = bUnits1;
	toledBuf.eUnitsSecondary = bUnits1;
	toledBuf.eInfo = InfoNone;
	toledBuf.eLcd = LcdOn;

	_ASSERT( sizeof(toledBuf) == 34 );
	SendToled( (unsigned char*)&toledBuf, sizeof(toledBuf) );
}

int _tmain(int argc, _TCHAR* argv[])
{
	bt.Connect();
	if ( !bt.IsConnected() )
		return 0;
	Sleep(1000);
	
	if (1)
	while(1)
	{
		scanf("%d", &q);
		SendToled();
	}

	for ( int i =1; i< 200; i++)
	{
	//	printf("%d\n", i);
		q = i;
		SendToled();
		Sleep(250);
	}
	bt.Disconnect();
	return 1;
}
