CString Hex(int n)
{
	CString str;
	str.Format( _T("%02x"), n );
	return str;
}

void SendHud(unsigned char* pBuf, int nLen)
{
	CArray<int> arrPacket;
	arrPacket.Add( 0x10 );
	arrPacket.Add( 0x7b );
	arrPacket.Add( nLen+6 );
	arrPacket.Add( nLen );
	arrPacket.Add( 0x00 );
	arrPacket.Add( 0x00 );
	arrPacket.Add( 0x00 );
	arrPacket.Add( 0x55 );
	arrPacket.Add( 0x15 );
	for ( int i=0; i<nLen; i++)
		arrPacket.Add( pBuf[i] );
	
	//crc
	unsigned int nCrc = 0;
	for ( int i=1; i<arrPacket.GetSize(); i++)
		nCrc += arrPacket[i];
	nCrc = (-(int)nCrc) & 0xff;

	arrPacket.Add( nCrc );
	arrPacket.Add( 0x10 );
	arrPacket.Add( 0x03 );

	CString strPacket;
	for ( int i=0; i<arrPacket.GetSize(); i++)
	{
		strPacket += Hex( arrPacket[i] );
		// stuffing
		if ( i > 0 && i < arrPacket.GetSize()-2 && arrPacket[i] == 0x10 )
			strPacket += Hex( arrPacket[i] );
	}
	bt.Send( strPacket );
}

int Digit(int n)
{
	n = n % 10;
	if ( n == 0 )
		return 10;
	return n;
}

void SetTime(int nH, int nM)
{
	bool bColon = true;
	bool bFlag = false;
	bool bTraffic = true;
	unsigned char arr[] = {0x05, 
		bTraffic ? 0xff : 0x00, 
		Digit(nH/10), Digit(nH), bColon ? 0xff : 0x00, 
		Digit(nM/10), Digit(nM), bFlag ? 0x00 : 0xff, 0x00};
	SendHud(arr, sizeof(arr));
}

void SetDistance(int nDist)
{
	enum {
		None = 0,
		Metres = 1,
		Kilometres = 3,
		Miles = 5
	} units = Metres;

	bool bDecimal = false;
	unsigned char arr[] = {0x03, 
		Digit(nDist/1000), Digit(nDist/100), Digit(nDist/10), bDecimal ? 0xff : 0x00, Digit(nDist), (int)units};

	SendHud(arr, sizeof(arr));
}

void SetDirection(int nDir)
{
	enum {
		SharpRight = 0x02,
		Right = 0x04,
		EasyRight = 0x08,
		Straight = 0x10,
		EasyLeft = 0x20,
		Left = 0x40,
		SharpLeft = 0x80
	} eOutAngle = EasyRight;

	unsigned char arr[] = {0x01, 0x01, 0x00, (int)eOutAngle};
	SendHud(arr, sizeof(arr));
}

void SetLanes( CString strLanes )
{
	for (int i=strLanes.GetLength(); i < 6; i++ )
		if (i&1)
			strLanes = _T(" ") + strLanes;
		else
			strLanes = strLanes + _T(" ");

	int nOutline = 0, nArrow = 0;
	for ( int i=0; i<6; i++)
	{
		char ch = (char)strLanes[i];
		if (ch == '0' || ch == '1')
			nOutline |= 1<<(6-i);
		if (ch == '1')
			nArrow |= 1<<(6-i);
	}

	unsigned char arr[] = {0x02, nOutline, nArrow};
	SendHud(arr, sizeof(arr));
}

void SetSpeedWarning(int nSpeed, int nLimit)
{
	bool bSpeeding = true;
	bool bIcon = true;
	unsigned char arr[] = {0x06, 
		(nSpeed/100)%10, Digit(nSpeed/10), Digit(nSpeed), 0xff,
		(nLimit/100)%10, Digit(nLimit/10), Digit(nLimit), bSpeeding ? 0xff : 0x00, bIcon ? 0xff : 0x00};

	SendHud(arr, sizeof(arr));
}

void ShowCameraIcon()
{
	unsigned char arr[] = {0x04, 0x01};
	SendHud( arr, sizeof(arr) );
}

void ShowGpsLabel()
{
	unsigned char arr[] = {0x07, 0x01};
	SendHud( arr, sizeof(arr) );
}
