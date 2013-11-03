#include "Bluetooth.h"

CBluetoothSpp bt;

#include "HudInterface.cpp"

int _tmain(int argc, _TCHAR* argv[])
{
	bt.Connect();
	if ( !bt.IsConnected() )
		return 0;

	Sleep(1000);

	for ( int i =0; i< 255; i++)
	{
		SetTime(12, 34);
		SetDistance( 9876 );
		SetDirection(1);
		SetLanes( _T("0110") );
		SetSpeedWarning(234, 123);
		Sleep(250);
	}

	bt.Disconnect();
	return 1;
}

