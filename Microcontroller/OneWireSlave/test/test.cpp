// ds2480.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

HANDLE OpenSerial()
{
	HANDLE        hPort;
  if ((hPort = CreateFile ( "\\\\.\\COM5",
      GENERIC_READ | GENERIC_WRITE,
      0,              // exclusive access
      NULL,           // no security attrs
      OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL,
      NULL)) != INVALID_HANDLE_VALUE)
  {
      printf("SUCCESS opening the port\n");// success
	  
  } else
  {
	  return NULL;
  }
  DCB dcb;
  dcb.DCBlength = sizeof(dcb);
  memset(&dcb, sizeof(dcb), 0);

  GetCommState (hPort, &dcb);
  dcb.BaudRate        = CBR_9600;
  dcb.fOutX           = 0;
  dcb.fInX            = 0;
  dcb.ByteSize = 8;
  dcb.fBinary = TRUE;
  SetCommState(hPort, &dcb);

	COMMTIMEOUTS cto = { MAXDWORD, 0, 0, 4, 4 }; 
	if (!SetCommTimeouts(hPort, &cto))
	{
		printf("SetCommState failed." );
		return NULL;
	}


  return hPort;
}

void CloseSerial(HANDLE h)
{
	CloseHandle(h);
}

void Send(HANDLE h, void* data, int len)
{
	DWORD written = 0;
	WriteFile(h, data, len, &written, NULL);
}

void Read(HANDLE h, void* data, int len)
{
	DWORD transferred = 0;
	ReadFile(h, data, len, &transferred, NULL);
}

int main(int argc, char* argv[])	
{
	HANDLE h = OpenSerial();
	
	//unsigned char buf[] = {0xc1, 0xe1, 0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3};
	//unsigned char buf[] = {0xc1, 0xe1, 0x33, 0xff, 0xe3};
	//unsigned char buf[] = {0xc1, 0xe1, 0x33, 0xff, 0xff, 0xe3};
	unsigned char buf[] = {0xc1, 0xe1, 0xcc, 0xf0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe3};
	//unsigned char buf[] = {0xc1, 0xe1, 0xcc, 0xf0, 0xff, 0xff, 0xe3};
	int i=0;
	FILE *f = fopen("COM5:", "wb");
	while (1)
	{
		for (int i=0; i<sizeof(buf)/sizeof(buf[0]); i++)
		{
			unsigned char send = buf[i];
			Send(h, &send, 1);
			int recv = 0;
			Sleep(20);
			Read(h, &recv, 1);
			//if ( i >= 3 && i < 3+8 )
				printf("%02x ", recv);
			//printf("%02x -> %02x \n", send, recv);
		}
		//printf ("  - %02x %02x %02x", i, (~i) & 0xff, (i + (~i)) & 0xff);
		printf("\n");
		Sleep(200);
		i++;
		//buf[3] = i;
		//buf[4] = ~i;
		buf[4] = i*8;
	}	
	CloseSerial(h);
	return 0;
}

