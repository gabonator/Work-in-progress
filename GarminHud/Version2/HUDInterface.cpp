#include "stdafx.h"
#include "HUDInterface.h"


HUDInterface::HUDInterface()
{
}


HUDInterface::~HUDInterface()
{
}


void HUDInterface::SendHud(unsigned char* pBuf, int nLen)
{
	unsigned char sendBuf[255], len = 0;
	unsigned int nCrc = 0xeb + nLen + nLen;

	sendBuf[len++] = 0x10;
	sendBuf[len++] = 0x7b;
	sendBuf[len++] = nLen + 6;
	if (nLen == 0xa)
		sendBuf[len++] = 0x10;
	sendBuf[len++] = nLen;
	sendBuf[len++] = 0x00;	
	sendBuf[len++] = 0x00;
	sendBuf[len++] = 0x00;
	sendBuf[len++] = 0x55;
	sendBuf[len++] = 0x15;
	for (int i = 0; i < nLen; i++)
	{
		nCrc += pBuf[i];
		sendBuf[len++] = pBuf[i];
		if (pBuf[i] == 0x10) //Escape LF
			sendBuf[len++] = 0x10;
	}

	sendBuf[len++] = (-(int)nCrc) & 0xff;
	sendBuf[len++] = 0x10;
	sendBuf[len++] = 0x03;
	
	SendPacket(sendBuf, len);
}

int HUDInterface::Digit(int n)
{
	n = n % 10;
	if (n == 0)
		return 10;
	return n;
}

void HUDInterface::SetDirection(eOutAngle nDir, eOutType nType, eOutAngle nRoundaboutOut)
{
	unsigned char arr[] = { 0x01, (nDir == LeftDown) ? 0x10 : ((nDir == RightDown) ? 0x20 : (unsigned char) nType), 
		(nType == RightRoundabout || nType == LeftRoundabout) ? ((nRoundaboutOut == AsDirection) ? nDir : nRoundaboutOut) : 0x00, 
		(nDir == LeftDown || nDir == RightDown) ? 0x00 : (unsigned char)nDir };
	SendHud(arr, sizeof(arr));
}

void HUDInterface::SetLanes(unsigned char nArrow, unsigned char nOutline)
{
	unsigned char arr[] = { 0x02, nOutline, nArrow };
	SendHud(arr, sizeof(arr));
}

void HUDInterface::SetDistance(int nDist, eUnits unit, bool bDecimal, bool bLeadingZero)
{
	unsigned char arr[] = { 0x03,
		Digit(nDist / 1000), Digit(nDist / 100), Digit(nDist / 10), bDecimal ? 0xff : 0x00, Digit(nDist), (unsigned char)unit };
	if (!bLeadingZero)
	{
		if (arr[1] == 0xa)
		{
			arr[1] = 0;
			if (arr[2] == 0xa)
			{
				arr[2] = 0;
				if (arr[3] == 0xa)
				{
					arr[3] = 0;
				}
			}
		}
	}

	SendHud(arr, sizeof(arr));
}

void HUDInterface::ShowCameraIcon()
{
	unsigned char arr[] = { 0x04, 0x01 };
	SendHud(arr, sizeof(arr));
}

void HUDInterface::SetTime(int nH, int nM, bool bColon, bool bFlag, bool bTraffic)
{
	unsigned char arr[] = { 0x05,
		bTraffic ? 0xff : 0x00,
		Digit(nH / 10), Digit(nH), bColon ? 0xff : 0x00,
		Digit(nM / 10), Digit(nM), bFlag ? 0x00 : 0xff, 0x00 };
	SendHud(arr, sizeof(arr));
}

void HUDInterface::SetSpeedWarning(int nSpeed, int nLimit, bool bSpeeding, bool bIcon, bool bSlash)
{
	unsigned char arr[] = { 0x06,
		(nSpeed / 100) % 10, Digit(nSpeed / 10), Digit(nSpeed), bSlash ? 0xff : 0x00,
		(nLimit / 100) % 10, Digit(nLimit / 10), Digit(nLimit), bSpeeding ? 0xff : 0x00, bIcon ? 0xff : 0x00 };

	SendHud(arr, sizeof(arr));
}

void HUDInterface::ShowGpsLabel()
{
	unsigned char arr[] = { 0x07, 0x01 };
	SendHud(arr, sizeof(arr));
}
