#include <Windows.h>
#include <stdio.h>
#include <crtdbg.h>

#include "C:\Data\Work\alley\1\cat_code.h"


// js {{{
WORD _data16get(int addr)
{
	return _data[addr] | (_data[addr+1]<<8);
	//return *(WORD*)&_data[addr];
}
void _data16set( int addr, WORD value )
{
  _data[addr] = value & 0xff;
  _data[addr+1] = value >> 8;

//	*(WORD*)&_data[addr] = value;
}
WORD _video16get(int addr)
{
	return *(WORD*)&_video[addr];
}
void _video16set( int addr, WORD value )
{
	*(WORD*)&_video[addr] = value;
}
WORD get_ax() { return ax; }
WORD get_bx() { return bx; }
WORD get_cx() { return cx; }
WORD get_dx() { return dx; }
void set_ax(WORD w) { ax = w; }
void set_bx(WORD w) { bx = w; }
void set_cx(WORD w) { cx = w; }
void set_dx(WORD w) { dx = w; }
WORD _pop() { WORD w; _pop(w); return w; }

// }}} js
BYTE& CData::operator[] (ULONGLONG i)
{
//	_ASSERT( (char)_data.raw[0x698] >= 0 );
	_ASSERT( i != 0x5A10 && i != 0x5A0E );
	if (!_reg.ignore)
	{
		if ( i == 0x56e )
		{

			int f = 9;
		}
	}

	/*
	if ( i == 0x963 || i == 0x6150)
	{
		int f = 9;
	}
	if ( i >= 0xb800*16)
		return _video[i-0xb800*16];
		*/
	_ASSERT( i >=0 && i < 0xb800 );
	return *(raw+i);
}

void tick();
void procVideo();
treg _reg;
//BYTE _data[0x10000];
CData _data;
BYTE _video[0x10000];
WORD stack[1024];
int stacki = 0;
BYTE sndport = 0;
DWORD _cgaPalette[4] = {0x000000, 0x808080, 0xb0b0b0, 0xffffff};
DWORD _cgaBackground;

int _key = 0;
int AnyKey()
{
	BOOL bAny = FALSE;
	int keys[] = {VK_UP, VK_RIGHT, VK_LEFT, '?', '?', 'Y', 'N', 'K', 'H', 'T', 'A', 'S', 'R', VK_CONTROL, VK_DELETE, 0};
	for (int i=0; keys[i]; i++)
		if ( GetAsyncKeyState(keys[i]) )
		{
			_data[0x6BC+i] = 0x00; // Y, N
			bAny = TRUE;
		}
		else
			_data[0x6BC+i] = 0x80; // Y, N
	if ( GetAsyncKeyState(' ') )
		bAny = TRUE;
	return bAny;
}

class CTimer8254
{
	int nReset0;
	int nReset1;
	int nReset2;
	int nSpkrFrequency;

	WORD wLatch0;

public:
	CTimer8254()
	{
		nReset0 = 0;
		nReset1 = 0;
		nReset2 = 0;
		nSpkrFrequency = 0;
	}

	WORD Read18Hz()
	{
		return (WORD)((FLOAT)GetTickCount()*65543.0f/(1000.0f*60.0f*60.0f));
	}

	void WriteCtl(BYTE arg) // 43h
	{
		int nChannel = arg >> 6;
		int nAccess = (arg >> 4) & 3; // 0 = citame, 2 = ideme zapisovat
		int nMode = (arg >> 1) & 7; // 0 = irq on count, 3 = sq wave
		int nFormat = arg & 1; // 0 = 16 bit, 1 = bcd 4 digit

		switch ( nChannel )
		{
			case 0: 

				_ASSERT(arg==0);  // nAccess = 0 -> Latch for reading
				wLatch0 = -Read18Hz(); 
				if (!_reg.ignore)
				{
					int f= 9;
				}

				//wLatch0 = -(WORD)(GetTickCount()/5);
				//wLatch0 = 0;
				//nReset0 = 1; 
				break;
			case 1: nReset1 = 1; break;
			case 2: 
				nReset2 = 1; 
				break;
			default:
				_ASSERT(0);
		}
	}
	BYTE ReadCounter0() // 40h
	{
		BYTE b = wLatch0 >> 8;
		wLatch0 <<= 8;
		return b;
	}
	BYTE ReadCounter1() // 41h
	{
		_ASSERT(0);
		return 0;
	}
	BYTE ReadCounter2() // 42h
	{
		_ASSERT(0);
		return 0;
	}

	void WriteCounter0(BYTE arg)
	{
		_ASSERT(0);
	}
	void WriteCounter1(BYTE arg)
	{
		_ASSERT(0);
	}
	void WriteCounter2(BYTE arg)
	{
		static int nFreqLow;
		static int nFreqHigh;

		switch ( nReset2++ )
		{
		case 1: nFreqLow = arg; break;
		case 2: nFreqHigh = arg; 
			{
				int nFreqDiv = nFreqHigh*256 + nFreqLow;
				INT nSpkrFrequency = 1193180/nFreqDiv;
				///printf("Tone %d Hz\n", nSpkrFrequency);
				//Beep(nSpkrFrequency*2, 100);
			}
			break;
		default:
			_ASSERT(0);
		}
	}

	int GetFrequency()
	{
		return nSpkrFrequency;
	}
	BOOL Out(WORD port, BYTE& val)
	{
		switch ( port )
		{
			case 0x43: WriteCtl(val); return TRUE;
			case 0x40: WriteCounter0(val); return TRUE;
			case 0x41: WriteCounter1(val); return TRUE;
			case 0x42: WriteCounter2(val); return TRUE;
		}
		return FALSE;
	}

	BOOL In(WORD port, BYTE& val)
	{
		switch ( port )
		{
			case 0x40: val = ReadCounter0(); return TRUE;
			case 0x41: val = ReadCounter1(); return TRUE;
			case 0x42: val = ReadCounter2(); return TRUE;
		}
		return FALSE;
	}
} i8254;

void _int(BYTE i)
{
	if ( i == 0x11 )
	{
		// al = 0001 1110
		// ah = 1011 1001
		ax = 0xb91e;
		return;
	}
	if ( i == 0x10 )
	{
		if (ah == 0x00)
		{	
			// set video mode
			return;
		}
		if (ah == 0x02)
		{
			putchar('\n');
			return;
			// cursor, bh=page, dh=row, dl=col
			_ASSERT( bh == 0 );
			COORD coord;
			coord.X = dl;
			coord.Y = dh;
			SetConsoleCursorPosition(
				GetStdHandle( STD_OUTPUT_HANDLE ),
				coord);
			return;
		}
		if ( ah == 0x0b )
		{
			if ( bh == 0x00 )
			{
				_cgaBackground = bl;
				return;
			}
			if ( bh == 0x01 )
			{
				if (bl == 0x00)
				{
					_cgaPalette[0] = 0x000000;
					_cgaPalette[1] = 0x00b000;
					_cgaPalette[2] = 0xb00000;
					_cgaPalette[3] = 0xb0b000;
					return;
				}
				if (bl == 0x01)
				{
					_cgaPalette[0] = 0x000000;
					_cgaPalette[1] = 0x00ffff;
					_cgaPalette[2] = 0xff00ff;
					_cgaPalette[3] = 0xffffff;
					return;
				}
			}
		}
		if ( ah == 0x0e )
		{
			// al = char, bh = page, bl = color
			putchar(al);
			return;
		}
		
	}
	if ( i == 0x1A )
	{
		static DWORD dwBase = 0;
		DWORD dwTime = (WORD)((FLOAT)GetTickCount()	);
		if ( ah == 0x00 )
		{
			//http://vitaly_filatov.tripod.com/ng/asm/asm_029.1.html
			//DWORD dwTime = (WORD)(GetTickCount()*18.2f/1000.0f);
			if ( dwBase == 0 )
				dwBase = dwTime;
			dwTime -= dwBase;
			cx = dwTime >> 16;
			dx = dwTime & 0xffff;
			return;
		}
		if ( ah == 0x01 )
		{
			if ( cx == 0 && dx == 0 )
			{
				dwBase = dwTime;
				return;
			}
			printf("Set timer = %02x:%02x\n", cx, dx);
		}
	}
	printf("ah=%02X al=%02X bx=%04x int %2x\n", ah, al, bx, i);
}
void _push(WORD i)
{
	stack[stacki++] = i;
}
void _pop(WORD &i)
{
	i = stack[--stacki];
}
void _push(ULONGLONG i)
{
	stack[stacki++] = i;
}
void _pop(ULONGLONG &i)
{
	i = stack[--stacki];
}
void _lahf()
{
	ah = cf;
}

void _sahf()
{
	cf = ah;
}
void _pushf() 
{
	_push(_reg.flags.f16);
}
void _popf() 
{
	_pop(_reg.flags.f16);
}

void _rcr(BYTE& arg, BYTE l)
{
	_ASSERT(l == 1);
	int ncf = arg & 1 ? 1 : 0;
	arg >>= 1;
	_ASSERT(( arg & 128) == 0 );
	if ( cf )
		arg |= 128;
	cf = ncf;
}

void _rcl(BYTE& arg, BYTE l)
{
	int ncf = arg & 128 ? 1 : 0;
	_ASSERT(l == 1);
	arg <<= 1;
	_ASSERT( (arg & 1) == 0 );
	if ( cf )
		arg |= 1;
	cf = ncf;
	//_ASSERT(0);
}
void _rcr(WORD& arg, BYTE l)
{
	_ASSERT(l == 1);
	int ncf = arg & 1 ? 1 : 0;
	arg >>= 1;
	_ASSERT(( arg & 0x8000) == 0 );
	if ( cf )
		arg |= 0x8000;
	cf = ncf;
}

int _unknown_condition()
{
	_ASSERT(0);
	return 0;
}

void _aaa()
{
	if ((al & 0x0F) > 9 || (af = 1))
	{
		al = (al + 6) & 0x0f;
		ah ++;
		af = 1;
		cf = 1;
	} else {
		cf = 0;
		af = 0;
	}
}

int nTimerState = 0;
WORD wTimerLatch = 0;
void _out(WORD port, BYTE r)
{
	return;
	//printf("out(%3x) = %2x\n", port, r);
	//if (port != 0x60 && port != 0x61 )
		procVideo();

	static int nSpkState = 0;
	static BYTE nFreqHi, nFreqLow;
	if ( port == 0x61 )
	{
//		_ASSERT( r & 1 == 1 ); 
		// bit 0:0 = manual control, spkr = r&2
		// bit 0:1 = follow PIT ch2 (r&2 == 0 disconnets, r&2==1 connects to pit)

	//	bool bSquareOutput 
		// SOUNDON = sndport & 3 
		/*
		if ( (sndport&3) && !(r&3) )
			printf("Speaker off\n");
		if ( !(sndport&3) && (r&3) )
			printf("Speaker on\n");
			*/
		sndport = r;
		return;
	}
	if ( port == 0x3d9 )
	{
		return;
	} 
	if ( port == 0x201 )
	{

		// joystick
		return;
	}
	if ( port == 0x20 )
	{
		// int finished
		return;
	}
	if ( !i8254.Out( port, r ) )
		_ASSERT(0);
}

void _in(BYTE& r, WORD port)
{
	if (port != 0x60 && port != 0x61 )
		procVideo();
	if ( port == 0x61 )
	{
		static int nTick = 0;
		nTick ^= 0x10;
		r = sndport & nTick;
		return;
	}

	if (port == 0x3da)
	{
		tick();
		if ( GetTickCount()%20 < 10 )
			r = 0;
		else
			r = 8;
		//r = 8; // retrace in progress
		//r = 0; // scanning
		return;
	}

	if ( port == 0x201 )
	{
		r = 0;
		// joystick
		//r = rand();
		return;
	}
	if ( port == 0x60 )
	{
		static char lastk = 0;
		if (lastk!=0)
		{
			r = lastk | 0x80;
			lastk = 0;
			return;
		}

		lastk = _key;
		_key = 0;
		// keyboard
		r = lastk;
		return;
	}

	if ( !i8254.In( port, r ) )
		_ASSERT(0);
}

void _lodsb() 
{
	_ASSERT(_reg.flags.bit.dir == 0);
	al = _data[ds*16+si]; 
	si++;
}

void _lodsw() 
{
	_ASSERT(_reg.flags.bit.dir == 0);
	if ( ds*16+si >= 0xb800 )
		ax = *(WORD*)&_video[ds*16+si - 0xb800]; 
	else
		ax = *(WORD*)&_data[ds*16+si]; 
	si+=2;
}
void _stosw() 
{
	_ASSERT(_reg.flags.bit.dir == 0);
	BYTE* pto = _data.raw;
	if (es == 0xb800)
	{
		pto = _video;
		es = 0;
	}
	*(WORD*)&pto[es*16+di] = ax; 
	di+=2;
	if ( pto == _video )
		es = 0xb800;
}
void _stosb() 
{
	_ASSERT(_reg.flags.bit.dir == 0);
	BYTE* pto = _data.raw;
	if (es == 0xb800)
	{
		pto = _video;
		es = 0;
	}
	pto[es*16+di] = al; 
	di++;
	if ( pto == _video )
		es = 0xb800;
}

void _repne_scasb()
{
	_ASSERT(_reg.flags.bit.dir == 0);
	zf = 0;
	while ( cx-- && zf == 0 )
	{
		zf = (al - _data[es*16+di]) == 0;
		di++;
	}
}

void _rep_stosw()
{
	_ASSERT(_reg.flags.bit.dir == 0);
	while (cx--) 
		_stosw();
}
void _rep_stosb()
{
	_ASSERT(_reg.flags.bit.dir == 0);
	while (cx--) 
		_stosb();
}

void _rep_movsw()
{
	_ASSERT(_reg.flags.bit.dir == 0);
	// [DS:SI] => [ES:DI]
	BYTE* pfrom = _data.raw;
	BYTE* pto = _data.raw;
	if (ds == 0xb800)
	{
		pfrom = _video;
		ds = 0;
	}
	if (es == 0xb800)
	{
		pto = _video;
		es = 0;
	}

	while (cx != 0) {
			pto[es*16 + di] = pfrom[ds*16 + si];
			si++;
			di++;
			pto[es*16 + di] = pfrom[ds*16 + si];
			si++;
			di++;
			cx--;
	}

	if ( pfrom == _video )
		ds = 0xb800;
	if ( pto == _video )
		es = 0xb800;
}

void _rep_movsb()
{
	int dir = _reg.flags.bit.dir == 0 ? 1 : -1;
	//_ASSERT(_reg.flags.bit.dir == 0);
	BYTE* pfrom = _data.raw;
	BYTE* pto = _data.raw;
	if (ds == 0xb800)
	{
		pfrom = _video;
		ds = 0;
	}
	if (es == 0xb800)
	{
		pto = _video;
		es = 0;
	}

	while (cx != 0) {
			pto[es*16 + di] = pfrom[ds*16 + si];
			si+=dir;
			di+=dir;
			cx--;
	}
	if ( pfrom == _video )
		ds = 0xb800;
	if ( pto == _video )
		es = 0xb800;
}

void _xchg(WORD&, WORD&)
{
	_ASSERT(0);
}
void _xchg(BYTE&a, BYTE&b)
{
	BYTE c = a;
	a = b;
	b = c;
}
void nullsub_1() {}
void nullsub_2() {}

class CFrameBuffer {
public:
	enum {
		Width = 320,
		Height = 200
	};

private:

	LPVOID m_pBuffer;
	HDC m_pDC;
	HANDLE m_Old;
	HBITMAP m_ourbitmap;

public:
	CFrameBuffer()
	{
		HDC hDC;
		BITMAPINFO bitmapinfo;
		hDC=CreateCompatibleDC(NULL);
		bitmapinfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
		bitmapinfo.bmiHeader.biWidth=Width;
		bitmapinfo.bmiHeader.biHeight=-Height; /* top-down */
		bitmapinfo.bmiHeader.biPlanes=1;
		bitmapinfo.bmiHeader.biBitCount=32;
		bitmapinfo.bmiHeader.biCompression=BI_RGB;
		bitmapinfo.bmiHeader.biSizeImage=0;
		bitmapinfo.bmiHeader.biClrUsed=256;
		bitmapinfo.bmiHeader.biClrImportant=256;
		m_pBuffer = NULL;
		m_ourbitmap=CreateDIBSection(hDC,&bitmapinfo,DIB_RGB_COLORS,&m_pBuffer,0,0);
		m_pDC=CreateCompatibleDC(NULL);
		m_Old=SelectObject(m_pDC,m_ourbitmap);
		DeleteDC(hDC);

		FillMemory(m_pBuffer, sizeof(DWORD)*Width*Height, 0xb0);
	}

	LPVOID GetBuffer()
	{
		return m_pBuffer;
	}

	void Blit(HDC hDC)
	{
		BitBlt(hDC,0,0,Width,Height,m_pDC,0,0,SRCCOPY);
	}

	~CFrameBuffer()
	{
		SelectObject(m_pDC,m_Old);
		DeleteDC(m_pDC);
		DeleteObject(m_ourbitmap);
	}
} m_Display;


long __stdcall WindowProcedure( HWND window, unsigned int msg, WPARAM wp, LPARAM lp )
{
	HDC hdc;
	PAINTSTRUCT ps;
    switch(msg)
    {
        case WM_DESTROY:
            printf( "\ndestroying window\n" );
            PostQuitMessage(0) ;
            return 0L ;
        case WM_LBUTTONDOWN:
			printf("lbutton\n");
		case WM_PAINT:
		hdc = BeginPaint(window, &ps);
		// TODO: Add any drawing code here...
		m_Display.Blit(hdc);
		EndPaint(window, &ps);
		break;

        default:
            return DefWindowProc( window, msg, wp, lp ) ;
    }
    return DefWindowProc( window, msg, wp, lp ) ;
}


HWND wnd = NULL;
void InitWindow()
{
const char* const myclass = "myclass" ;
    WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
                            0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
                            LoadCursor(0,IDC_ARROW), HBRUSH(COLOR_WINDOW+1),
                            0, myclass, LoadIcon(0,IDI_APPLICATION) } ;
	BOOL b = RegisterClassEx(&wndclass);
	_ASSERT(b);
HWND window = CreateWindowEx( 0, myclass, "title",
                   WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				   CFrameBuffer::Width+GetSystemMetrics(SM_CXFRAME)*2, CFrameBuffer::Height+ GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME)*2, 0, 0, GetModuleHandle(0), 0 ) ;
_ASSERT(window);
ShowWindow( window, SW_SHOWDEFAULT ) ;
wnd = window;
}

DWORD CgaPixel(int x, int y)
{
	if ((y&1) == 0)
	{
		y /= 2;
		BYTE pix4 = _video[y*80+x/4];
		pix4 <<= (x&3)*2;
		return pix4 >> 6;
	} else
	{
		y /= 2;
		BYTE pix4 = _video[0x2000+y*80+x/4];
		pix4 <<= (x&3)*2;
		return pix4 >> 6;
	}
	return 0;
}

void OsProc()
{
	MSG msg;
	while ( PeekMessage( &msg, wnd, 0, 0, 1 ) ) 
		DispatchMessage(&msg);
}

void procVideo()
{
	//_timer();
	if (!wnd)
		InitWindow();

	static LONG last = 0;
	LONG cur = GetTickCount();
	if (last == 0)
		last = cur;
	if ( cur - last < 100 )
		return;

	last = GetTickCount();
	InvalidateRect( wnd, NULL, FALSE );

	//DWORD colors[] = {0x000000, 0x00ffff, 0xffff00, 0xffffff};

	DWORD* pBuffer = (DWORD*)m_Display.GetBuffer();
	for (int y=0; y<200; y++)
		for (int x=0; x<320; x++)
		{
			*pBuffer++ = _cgaPalette[CgaPixel(x, y)];
		}
}

void tick()
{
	procVideo();

	MSG msg;
	BOOL bPaint = FALSE;
	while ( PeekMessage( &msg, wnd, 0, 0, 1 ) ) 
	{
		DispatchMessage(&msg);
		if ( msg.message == WM_PAINT )
		{
			if ( bPaint )
				break;
			bPaint = TRUE;
		}
	}

	if (AnyKey())
	{
		(*(WORD*)&_data[ds+0x693])++;
	}

	static LONG lTick = 0;
	LONG lCurrent = GetTickCount();
	if (lTick == 0)
		lTick = lCurrent;
	if ( lCurrent - lTick > 200 )
	{
		lTick = lCurrent;
		//printf("B:%02x 0:%02x C:%02x A:%02x 3:%02x 8:%02x 9:%02x 1:%02x 4:%02x 2:%02x\n",
		//	_data[0x55b], _data[0x550], _data[0x55c], _data[0x55a], _data[0x583], 
		//	_data[0x698], _data[0x699], _data[0x551], _data[0x584], _data[0x552]);

		//printf("8:%02x e:%02x f:%02x\n", _data[0x698], _data[0x56e], _data[0x56f]);
		//for ( int i=0x560-4; i<0x580; i++)
		 // printf("%02x ", _data[i]);
IGNORE(
		printf("x=%04x vx=%02x(%02x) y=%02d g=%02x jump=%02x, ? = %02x\n", 
			*(WORD*)&_data[0x579], _data[0x56E], _data[0x698], _data[0x5E9], _data[0x576], _data[0x699], _data[0x571]);
)

	//printf("%02x %04x %04x %04x %04x\n", byte_code_13E7, word_code_13E5, word_code_13E3, word_code_13E1, word_code_13DF );

	/*
	smer ja nastaveny 0x698 potom sa prenasa do 56E
	*/
//		printf(" - %02x%02x ", _data[0x56e], _data[0x56f]);

		//printf("8e5: %04x %02x %02x %02x\n", *(WORD*)&_data[0x579], _data[0x571], _data[0x5f1], _data[0x86f]);
//571, 576, 55a,558, [8e5] 574 5f1 56f
		//printf("\n");

	}
}

int main(int argc, char* argv[])
{/*
	char p1000[0x100];
	char p1010[0x7120+0x10];
	char p1723[0x62e0+0x0b];
	FILE* f = fopen("C:\\Data\\Work\\alley\\CAT.EXE", "rb");
	fseek(f, 0x200, SEEK_CUR);
	fread(p1000, 0x100, 1, f); 
	fread(p1010, 0x7120+0x10, 1, f); 
	fread(p1723, 0x62e0+0x0b, 1, f); 
	fclose(f);
	*/

	ds = 0;
	memset(_data.raw, 0, 0x10000);
	FILE* f = fopen("C:\\Data\\Work\\alley\\ds", "rb");
	fread(_data.raw, 0x7130, 1, f); 
	fclose(f);

	start();
	return 0;
}

