// HUDTestSerial.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "HUDSerial.h"

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s COMPort Baud\n", argv[0]);
		return -1;
	}
	HUDSerial *pHUDSerial = new HUDSerial();
	if (!pHUDSerial->Init(argv[1], atoi(argv[2])))
	{
		delete pHUDSerial;
		return -1;
	}
	pHUDSerial->SetDistance(500, HUDInterface::Metres);
	pHUDSerial->SetDirection(HUDInterface::Right, HUDInterface::RightRoundabout);
	pHUDSerial->SetTime(10, 40);
	pHUDSerial->SetLanes(HUDInterface::InnerRight | HUDInterface::InnerLeft, HUDInterface::InnerRight | HUDInterface::InnerLeft | HUDInterface::DotsRight | HUDInterface::DotsLeft);
	pHUDSerial->SetSpeedWarning(140, 130);
	pHUDSerial->ShowCameraIcon();
	delete pHUDSerial;
	return 0;
}

