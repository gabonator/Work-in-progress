#include <Windows.h>
#include <stdio.h>
#include <crtdbg.h>

char* g_strCom = "COM1:";
char* g_strFile = "screen.bmp";
int g_nBaud = 38400;

class CSerial
{
	HANDLE m_hSerial;

public:
	CSerial()
	{
		m_hSerial = NULL;
	}

	void Close()
	{
		if ( m_hSerial )
			CloseHandle( m_hSerial );
	}
	bool Open( char* strCom, int nBaud )
	{
		m_hSerial = CreateFileA( g_strCom, GENERIC_READ | GENERIC_WRITE, 0, NULL,
			OPEN_EXISTING, 0, NULL);

		DCB dcb;
		COMMTIMEOUTS cto = { 500, 0, 100, 4, 500 }; 

		if (!SetCommTimeouts(m_hSerial, &cto))
		{
			_ASSERT(!!!"SetCommTimeouts failed.");
			return false;
		}

		dcb.DCBlength = sizeof(dcb);
		memset(&dcb, sizeof(dcb), 0);

		if (!GetCommState(m_hSerial, &dcb))
		{
			_ASSERT(!!!"GetCommState failed.");
			return false;
		}

		dcb.BaudRate = g_nBaud;
		dcb.fBinary = TRUE;
		dcb.fParity = FALSE; //(sio->info.parity == SIO_PARITY_NONE) ? FALSE : TRUE;
		dcb.fOutxCtsFlow = FALSE;
		dcb.fOutxDsrFlow = FALSE;
		dcb.fDtrControl = DTR_CONTROL_DISABLE;
		dcb.fDsrSensitivity = FALSE;
		dcb.fTXContinueOnXoff = FALSE;
		dcb.fOutX = FALSE;
		dcb.fInX = FALSE;
		dcb.fErrorChar = FALSE;
		dcb.fNull = FALSE;
		dcb.fRtsControl = RTS_CONTROL_DISABLE;
		dcb.fAbortOnError = FALSE;
		dcb.ByteSize = 8; 

		dcb.Parity = 0;
		dcb.StopBits = 0;

		// required by bk 2650
		//dcb.fDtrControl = DTR_CONTROL_ENABLE;
		//dcb.fRtsControl = RTS_CONTROL_ENABLE;

		if (!SetCommState(m_hSerial, &dcb))
		{
			_ASSERT(!!!"SetCommState failed.");
			return false;
		}	
		FlushFileBuffers( m_hSerial );
		return true;
	}

	//CSerial& operator >>(int& ch)
	int Read()
	{
		BYTE bData;
		DWORD dwRead;
		ReadFile( m_hSerial, &bData, 1, &dwRead, NULL );
		if ( dwRead != 1 )
		{
			//printf("Read error\n");
			return -1;
		}
		return bData;
	}

	bool Write( const char* strMsg )
	{
		DWORD dwWritten;
		WriteFile( m_hSerial, strMsg, strlen(strMsg), &dwWritten, NULL );
		if ( dwWritten != strlen(strMsg) )
			return false;
		return true;
	}

	bool TestLoopback()
	{
		DWORD dwState = 0;
		// RTS is internally connected to CTS
		// required to be set to 1 

		EscapeCommFunction( m_hSerial, CLRRTS );
		Sleep(10);
		GetCommModemStatus( m_hSerial, &dwState );
		if ( dwState & MS_CTS_ON )
			return false;

		EscapeCommFunction(m_hSerial, SETRTS);
		Sleep(10);
		GetCommModemStatus( m_hSerial, &dwState );
		if ( !(dwState & MS_CTS_ON) )
			return false;

		return true;
	}

};

class CBKPrinter
{
public:
	enum {
		ScreenWidth = 512,
		ScreenHeight = 370
	};

	BYTE m_bitmap[ScreenHeight][ScreenWidth];
	
	CBKPrinter()
	{
		ZeroMemory( m_bitmap, sizeof( m_bitmap ) );
	}
	
	bool Identify( CSerial& Serial )
	{
		if ( !Serial.Write("VER\x0d\x0a") )
			return false;

		char strIdentify[16];
		int i, ch;
		for ( i = 0; i < 16; i++ )
		{
			if ( ( ch = Serial.Read() ) == -1 )
				break;
			if ( ch == 0x0d || ch == 0x0a ) 
				ch = 0;
			strIdentify[i] = ch;
		}
		strIdentify[i] = 0;

		if ( strIdentify[0] == 0 )
			return false;
		printf("Device version = %s\n", strIdentify );
		return true;
	}

	bool Process( CSerial& Serial )
	{
		int nRead;
		int nCount = 0;
		int y = 0;
		// Wait 10 seconds...
		long lWait = GetTickCount() + 10000;
		bool bWait = true;

		if ( !Serial.Write("PRTSIW\x0d\x0a") )
			return false;

		printf("Waiting for device...\n");
		
		while ( (long)GetTickCount() < lWait )
		{
			nRead = Serial.Read();
			if ( nRead != -1 )
				break;
		}
		if ( nRead == -1 )
			return false;

		while ( ( nRead = Serial.Read() ) >= 0 )
		{
			printf("\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08");
			printf("Printing %d%%", y*100/21);

			if ( nRead == 0x1b )
			{
				nRead = Serial.Read();
				_ASSERT( nRead >= 0 );
				if ( nRead == 'l' )
				{
					CHAR count[5] = {0};
					count[0] = Serial.Read();
					count[1] = Serial.Read();
					count[2] = Serial.Read();
					count[3] = Serial.Read();
					nCount = atoi(count);
					_ASSERT(nCount == 370);
					for (int x=0; x<nCount; x++)
					{
						union {
							WORD pix;
							BYTE b[2];
						} p;
						p.b[1] = Serial.Read();
						p.b[0] = Serial.Read();
						for ( int z = 0; z < 16; z++ )
							if ( p.pix & (1<<(15-z)) )
							{
								int _x = y*16+z;
								int _y = x;
								_ASSERT( _x < ScreenWidth && _y < ScreenHeight );
								if ( _x < ScreenWidth && _y < ScreenHeight )
									m_bitmap[ScreenHeight-_y-1][_x] = 1;
							}
					}
					y++;
					if (y==22)
						break;
				}
				continue;
			}
		}
		printf("\nOk.\n");
		return true;
	}

	char* GetBitmap()
	{
		return (char*)m_bitmap;
	}
	int GetWidth()
	{
		return ScreenWidth;
	}
	int GetHeight()
	{
		return ScreenHeight;
	}
};

class CBitmap 
{
public:
	void GetClipArea( CHAR * bitmap, int width, int height, int& x1, int& y1, int& x2, int& y2)
	{
		x1 = x2 = width/2;
		y1 = y2 = height/2;
		
		for ( int y=0; y<height; y++)
			for ( int x=0; x<width; x++)
			{
				if ( bitmap[y*width+x] )
				{
					x1 = min(x, x1);
					x2 = max(x, x2);
					y1 = min(y, y1);
					y2 = max(y, y2);
				}
			}
		x2++;
		y2++;
	}

	bool Save(const char* filename, CHAR * bitmap, int width_, int height_)
	{
		int x1, y1, x2, y2;
		GetClipArea( bitmap, width_, height_, x1, y1, x2, y2 );
		int width = x2-x1, height = y2-y1;

		if ( width < 8 || height < 8 )
		{
			printf("Bitmap cannot be clipped\n");
			return false;
		}

		// align width
		if ( width % 4 != 0 )
			width += 4 - (width % 4);

		// create file
		HANDLE file = CreateFile( filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, NULL );

		// save bitmap file headers
		BITMAPFILEHEADER fileHeader;
		BITMAPINFOHEADER infoHeader;

		fileHeader.bfType      = 0x4d42;
		fileHeader.bfSize      = 0;
		fileHeader.bfReserved1 = 0;
		fileHeader.bfReserved2 = 0;
		fileHeader.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 2*4;

		infoHeader.biSize          = sizeof(infoHeader);
		infoHeader.biWidth         = width;
		infoHeader.biHeight        = height;
		infoHeader.biPlanes        = 1;
		infoHeader.biBitCount      = 8;
		infoHeader.biCompression   = BI_RGB;
		infoHeader.biSizeImage     = 0;
		infoHeader.biXPelsPerMeter = 3780;
		infoHeader.biYPelsPerMeter = 3780;
		infoHeader.biClrUsed       = 0;
		infoHeader.biClrImportant  = 0;

		DWORD dwWritten;
		WriteFile( file, &fileHeader, sizeof(fileHeader), &dwWritten, NULL );
		_ASSERT( dwWritten == sizeof(fileHeader) );

		WriteFile( file, &infoHeader, sizeof(infoHeader), &dwWritten, NULL );
		_ASSERT( dwWritten == sizeof(infoHeader) );

		// palette
		for (int i=0; i<256; i++)
		{
			DWORD clr = (i==1) ? RGB(0, 0, 0) : RGB(255, 255, 255);
			WriteFile( file, &clr, 4, &dwWritten, NULL );
			_ASSERT( dwWritten == 4 );
		}

		// dibsection information
		BITMAPINFO info;
		info.bmiHeader = infoHeader; 

		for (int y=height-1; y>=0; y--)
		{
			int basex = x1;
			int basey = y1 + y;
			CHAR* baseptr = bitmap + basey*width_ + basex;
			WriteFile( file, baseptr, width, &dwWritten, NULL );
			_ASSERT( dwWritten == width );
		}
		CloseHandle(file);
		printf("Bitmap (%dx%d) saved as '%s'\n", width, height, filename);
		return true;
	}
};

void About()
{
	printf("BK2650 printer emulator, 2012 valky.eu\n"
		"Built " __DATE__ " " __TIME__ "\n"
		"\n");
}

void Help()
{
	printf(
		"Usage:\n"
		"  bkprint.exe %s %s\n"
		"\n", g_strCom, g_strFile);
}

int main(int argc, CHAR* argv[])
{
	About();
	if ( argc <= 1 )
	{
		Help();
	} else
	{
		if (argc > 1)
			g_strCom = argv[1];
		if (argc > 2)
			g_strFile = argv[2];
	}

	CSerial Serial;
	if ( !Serial.Open( g_strCom, g_nBaud ) )
	{
		printf("Cannot open port %s at baudrate %d\n", g_strCom, g_nBaud);
		return 1;
	}
	if ( !Serial.TestLoopback() )
	{
		printf("Device not attached to the port.\n");
		Serial.Close();
		return 1;
	}
	CBKPrinter Printer;
	if ( Printer.Identify( Serial ) )
	{
		if ( Printer.Process( Serial ) )
		{
			CBitmap Bitmap;
			Bitmap.Save( g_strFile, Printer.GetBitmap(), Printer.GetWidth(), Printer.GetHeight() );
		} else
			printf("Device not responding\n");
	} else
		printf("Device failed to identify\n");

	Serial.Close();
	return 0;
}

