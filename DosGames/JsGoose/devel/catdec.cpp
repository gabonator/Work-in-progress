#include <Windows.h>
#include <stdio.h>
#include <crtdbg.h>

#include "goose/goose_code.h"
#include "ega.h"
#include <vector>
#include <hash_map>
#include <algorithm>

//#include "C:\Data\Work\alley\1\cat_code.h"

CEga EGA;

WORD _stack[4096];

BYTE xx[8];
BYTE* r8 = xx;
char* r8s = (char*)xx;
WORD* r16 = (WORD*)xx;
#define al r8[0]
#define ah r8[1]
#define bl r8[2]
#define bh r8[3]
#define cl r8[4]
#define ch r8[5]
#define dl r8[6]
#define dh r8[7]
#define ax r16[0]
#define bx r16[1]
#define cx r16[2]
#define dx r16[3]
#define ds _reg.ds
#define es _reg.es

int _ofs(int x)
{
	return x & 0xffff;
}
int _seg(int x)
{
	return x*16;
}


std::vector<int> stat;
std::hash_map<int, int> scount;
std::hash_map<int, int> stime;

CStat::CStat(int proc)
{
	current = proc;
	stat.push_back(proc);
	scount[proc] = scount[proc]+1;
	stime[proc] -= GetTickCount();
}

CStat::~CStat()
{
	int last = stat.back();
	stat.pop_back();
	_ASSERT( last == current );
	stime[current] += GetTickCount();
}

bool sortnum (std::pair<int, int> a, std::pair<int, int> b) { return a.second > b.second; }
void DumpStat()
{

	std::vector<std::pair<int, int>> counts;
	std::vector<std::pair<int, int>> times;

    std::hash_map<int, int>::iterator it = scount.begin();
    for (; it != scount.end(); ++it)
		counts.push_back( std::pair<int, int>( it->first, it->second ));
    it = stime.begin();
    for (; it != stime.end(); ++it)
		if ( it->second > 0 )
			times.push_back( std::pair<int, int>( it->first, it->second ));

	std::sort (counts.begin(), counts.end(), sortnum);
	std::sort (times.begin(), times.end(), sortnum);

	// najvacsie na konci
	printf("Call counts: ");
	for ( int i=0; i<min(counts.size(), 5); i++)
		printf("(%d) proc_%0x  ", counts[i].second, counts[i].first);
	printf("\n");

	printf("Call times: ");
	for ( int i=0; i<min(times.size(), 5); i++)
		printf("(%dms) proc_%0x  ", times[i].second, times[i].first);
	printf("\n");

}

// js {{{
WORD _data16get(int addr)
{
	_ASSERT( addr >= 0 && addr <= 0xffff );
	return _data[addr] | (_data[addr+1]<<8);
}
void _data16set( int addr, WORD value )
{
	if ( addr == 37535 )
	{
		int f = 9;
	}
	_ASSERT( addr >= 0 && addr <= 0xffff );

	_ASSERT( addr >=0 && addr < 0xb700 );
  _data[addr] = value & 0xff;
  _data[addr+1] = value >> 8;
}

WORD _video16get(int addr)
{
	_ASSERT( addr/16 >= 0xa000 && addr/16 < 0xf000 );
	addr -= 0xa000*16;
	return EGA.Read(addr) | (EGA.Read(addr+1)<<8);
}
void _video16set( int addr, WORD value )
{
	_ASSERT( addr/16 >= 0xa000 & addr/16 < 0xf000 );
	addr -= 0xa000*16;
	EGA.Write(addr, value & 0xff);
	EGA.Write(addr+1, value >> 8);
}
BYTE _video8get(int addr)
{
	_ASSERT( addr/16 >= 0xa000 & addr/16 < 0xf000 );
	addr -= 0xa000*16;
	return EGA.Read(addr);
}
void _video8set( int addr, BYTE value )
{
	_ASSERT( addr/16 >= 0xa000 & addr/16 < 0xf000 );
	addr -= 0xa000*16;
	EGA.Write( addr, value );
}

WORD _stack16get(int addr)
{
	//_ASSERT( addr >=0 && addr < 0xb700 );
	_ASSERT( addr >=0 && addr < 4096 );
	return *(WORD*)&_stack[addr];
}
BYTE _stack8get(int addr)
{
	_ASSERT( addr >=0 && addr < 4096 );
	return _stack[addr];
}
void _stack16set( int addr, WORD value )
{
	_ASSERT( addr >=0 && addr < 4096 );
	//_ASSERT( addr >=0 && addr < 0xb700 );
	*(WORD*)&_stack[addr] = value;
}

WORD _pop() { WORD w; _pop(w); return w; }

// }}} js
BYTE& CData::operator[] (ULONGLONG i)
{
//	_ASSERT( i >= 0 && i <= 0xffff );
	_ASSERT( i/16 < 0xa000);
	_ASSERT( i < 0x40000);
	if ( i >= 0x1b8a && i <= 0x1b8a+9 )
	{
		int f=9;
	}

	if ( i == 0x5a5c )
	{
		int f=9;
	}

	_ASSERT( i >=0 && i < 0x70000 );
	return *(raw+i);
}

void tick();
void procVideo();
treg _reg;
//BYTE _data[0x10000];
CData _data;
BYTE _video[0x20000];
int stacki = 0;
BYTE sndport = 0;
DWORD _cgaPalette[4] = {0x000000, 0x808080, 0xb0b0b0, 0xffffff};
DWORD _cgaBackground;

void _retn(int q)
{
	sp += q;
	_ASSERT( sp >= 0 && sp < 4096);
}

int _key = 0;
int AnyKey()
{
	#define MAPKEY( k, v ) _data[0x8e8a+v] = GetAsyncKeyState(k) ? 1 : 0
	// http://www.ee.bgu.ac.il/~microlab/MicroLab/Labs/ScanCodes.htm
	MAPKEY( VK_LEFT, 75 ); 
	MAPKEY( VK_RIGHT, 77 ); 
	MAPKEY( VK_DOWN, 80 ); 
	MAPKEY( VK_UP, 72 ); 
	MAPKEY( ' ', 57 ); 
	MAPKEY( 'N', 49 ); 
	MAPKEY( 'M', 50 ); 
	MAPKEY( 'Q', 16 ); 
	MAPKEY( 'Y', 21 ); 

	/*
	MAPKEY( 'Z', 0x55 ); 
	MAPKEY( 'X', 0x56 ); 
	MAPKEY( 'P', 0x57 ); 
	//MAPKEY( 'Q', 0x58 ); 

	MAPKEY( VK_RETURN, 0x3B ); 
	MAPKEY( 'W', 0x42 ); 
	MAPKEY( 'E', 0x43 ); 
	MAPKEY( 'R', 0x44 ); 
	MAPKEY( 'T', 0x45 ); 
	MAPKEY( 'Y', 0x46 ); 
	MAPKEY( 'U', 0x47 ); 
	*/
	/*
	int keys[] = {VK_UP, VK_RIGHT, VK_LEFT, VK_DOWN, ' ', 'Z', 'X', 'Q', 'W', 0};
	for (int i=0; keys[i]; i++)
		if ( GetAsyncKeyState(keys[i]) )
			_data[0x8e8a + i] = 1;
		else
			_data[0x8e8a + i] = 0;
			*/
	return FALSE;
	/*
	BOOL bAny = FALSE;
	int keys[] = {VK_UP, VK_RIGHT, VK_LEFT, '?', '?', 'Y', 'N', 'K', 'H', 'T', 'A', 'S', 'R', VK_CONTROL, VK_DELETE, 0};
	for (int i=0; keys[i]; i++)
		if ( GetAsyncKeyState(keys[i]) )
		{
			_data[0x8e8a + i] = 1;
			//_data[0x6BC+i] = 0x00; // Y, N
			bAny = TRUE;
		}
		else
		{
			_data[0x6BC+i] = 0x80; // Y, N
			_data[0x8e8a + i] = 0;
		}
	if ( GetAsyncKeyState(' ') )
		bAny = TRUE;
	return bAny;
		*/
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

				//_ASSERT(arg==0);  // nAccess = 0 -> Latch for reading
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
//		_ASSERT(0);
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
				Beep(nSpkrFrequency*2, 100);
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
	//FILE* fa = NULL, *fb= NULL, *fc= NULL, *fd= NULL, *fe= NULL, *ff= NULL, *fg= NULL;
	//static FILE** f[8] = {&fa, &fb, &fc, &fd, &fe, &ff, &fg};
	static FILE* ff[8] = {0};
	//printf("int %02x ah=%02x al=%02x bx=%04x\n", i, ah, al, bx);
	if ( i == 0x21 && ah == 0x3d )
	{
		// DS:DX
		int j;
		for ( j=0; j<8; j++)
			if (ff[j] == 0)
				break;

		char* strName = (char*)&_data[ds*16 + dx];
		char strFull[128] = "C:\\Data\\Devel\\Github\\Work-in-progress\\AlleyCat\\Games\\goose\\";
		printf("Open file '%s'\n", strName);
		strcat(strFull, strName);
		ff[j] = fopen(strFull, "rb");
		cf = ( ff[j] != NULL && ff[j] != INVALID_HANDLE_VALUE ) ? 0 : 1;
		ax = j ^ 0xf000;
		//if ( strcmp(strName, "hiscores") == 0 )
		//	cf = 1;
		return;
	}
	if ( i == 0x21 && ah == 0x3f )
	{
		_ASSERT( (bx & 0xf000) == 0xf000);
		FILE*f = ff[bx ^ 0xf000];
		int ofs = ds*16+dx;
		int len = cx;
		BYTE* ptr = &_data.raw[ofs];
		fread(ptr, len, 1, f);
		_ASSERT( 0x5a5c < ofs || 0x5a5c > ofs+len); 
		cf = 0;
		printf("Read %x bytes into %04x:%04x\n", len, ds, dx);
		return;
	}
	if ( i == 0x21 && ah == 0x3e )
	{
		_ASSERT( (bx & 0xf000) == 0xf000);
		FILE*f = ff[bx ^ 0xf000];
		fclose(f);
		ff[bx ^ 0xf000] = NULL;
		cf = 0;
		return;
	}

	/*
	
    BX = file handle
    CX = number of bytes to read
    DS:DX -> buffer for data
*/
	if ( i == 0x12 )
	{
		// free mem ->ax
		ax = 0x1000;
		return;
	}
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
		//DWORD dwTime = (WORD)((FLOAT)GetTickCount()/5	);
		DWORD dwTime = (WORD)(GetTickCount()*18.2f/1000.0f);
		if ( ah == 0x00 )
		{
			//http://vitaly_filatov.tripod.com/ng/asm/asm_029.1.html
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
	if ( i == 0x21 )
	{
		// DOS
		if ( ah == 0x09 )
		{
			for (int i=ds*16+dx; _data[i] != '$' && _data[i] != 0; i++)
				putchar(_data[i]);
			return;
		}
	}
	if ( i == 0x33 )
	{
		if ( ah==0x00 ) //INT 33,0 - Mouse Reset/Get Mouse Installed Flag
		{	
			ax = 0xffff;
			bx = 0x2;
			return;
		}
	}
	if ( i == 0x21 )
	{
		if ( ah == 0x25 )
		{
			// set int vect
			int f = 9;
		}
	}
	printf("ah=%02X al=%02X bx=%04x int %2x\n", ah, al, bx, i);
}
void _push(WORD i)
{
	_stack16set(sp, i);
	sp -= 2;
}
void _pop(WORD &i)
{
	sp += 2;
	i = _stack16get(sp);
	//i = stack[--stacki];
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

BYTE _rcr(BYTE arg, BYTE l)
{
	_ASSERT(l == 1);
	int ncf = arg & 1 ? 1 : 0;
	arg >>= 1;
	_ASSERT(( arg & 128) == 0 );
	if ( cf )
		arg |= 128;
	cf = ncf;
	return arg;
}

BYTE _rcl(BYTE arg, BYTE l)
{
	int ncf = arg & 128 ? 1 : 0;
	_ASSERT(l == 1);
	arg <<= 1;
	_ASSERT( (arg & 1) == 0 );
	if ( cf )
		arg |= 1;
	cf = ncf;
	return arg;
	//_ASSERT(0);
}
WORD _rcr(WORD arg, BYTE l)
{
	_ASSERT(l == 1);
	int ncf = arg & 1 ? 1 : 0;
	arg >>= 1;
	_ASSERT(( arg & 0x8000) == 0 );
	if ( cf )
		arg |= 0x8000;
	cf = ncf;
	return arg;
}

void _cbw()
{
	if ( al & 0x80 )
		ah = 0xff;
	else 
		ah = 0x00;
}
int _unknown_condition()
{

	_ASSERT(0);
	return 0;
}

void _div(BYTE dby)
{
  int res = ax / dby;
  int rem = ax % dby;
  al = res;
  ah = rem;
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

void _out(WORD port, WORD data)
{
	tick();
	if ( port == 0x3c4 )
	{
		if ( (data & 0x00ff) == 0x02 )
		{
			/*
			01 = plane 0, 02 = plane 1, 04 = plane 2, 08 = plane 3
			0f = default
			*/
			//printf("Write mask = %02x\n", data>>8 );
			EGA.SetMapMask( data>>8); // 3c5.2
			return;
		}
	}	
	if ( port == 0x3d4 )
	{
		if ( (data & 0x00ff) == 0x0c )
		{
			EGA.SetAddrHi( data >>8 );
			return;
		}
		if ( (data & 0x00ff) == 0x0d )
		{
			EGA.SetAddrLo( data >> 8);
			return;
		}
	}
	if ( port == 0x3ce )
	{
		switch ( data & 0xff )
		{
		case 0x00: EGA.SetSR( data >> 8 ); return;
		case 0x01: EGA.SetEnableSR( data >> 8 ); return;
		case 0x02: EGA.SetCompare( data >> 8 ); return;
		case 0x05: EGA.SetMode( data >> 8 ); return;
		case 0x07: EGA.SetDontCare( data >> 8 ); return;
		case 0x08: EGA.SetBitMask( data >> 8 ); return;
		case 0x03: EGA.SetRotate( data >> 8 ); return;
		default:
			_ASSERT(0);
		}
	}
	if ( port == 0x3ce || port == 0x3d4 || port == 0x3c4)
	{
		printf("port[%04x] = %04x\n", port, data);
		return;
	}
	_out(port, (BYTE)(data & 0xff));
	_out(port+1, (BYTE)(data >> 8));
}
BYTE _in(WORD port )
{
	BYTE b;
	_in(b, port);
	return b;
}

void _out(WORD port, BYTE r)
{
	printf("port[%04x] = %02x\n", port, r);
	procVideo();

	static int nSpkState = 0;
	static BYTE nFreqHi, nFreqLow;
	if ( port == 0x61 )
	{
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
	_ASSERT( ds < 0xa000 );
	//al = _data[ds*16+si]; 
	al = _data.raw[ds*16+si]; 
	si++;
	_ASSERT( si < 0xfff5 );
}

void _lodsw() 
{
	_ASSERT(_reg.flags.bit.dir == 0);
	if ( ds*16+si >= 0xb800 )
		ax = *(WORD*)&_video[ds*16+si - 0xb800]; 
	else
		ax = *(WORD*)&_data[ds*16+si]; 
	si+=2;
	_ASSERT( si < 0xfff5 );
}
void _stosw() 
{
	DWORD _es = es;
	_ASSERT(_reg.flags.bit.dir == 0);
	BYTE* pto = _data.raw;
	// ega
	if (es >= 0xa000)
	{
		pto = _video;
		//es -= 0xa000;
	}
	// cga
	if (es == 0xb800)
	{
		pto = _video;
		es = 0;
	}
	_ASSERT( es < 0xb800 );
	if ( pto != _video )
		*(WORD*)&pto[es*16+di] = ax; 
	else
		_video16set(es*16+di, ax);
	di+=2;
	es = _es;
	_ASSERT( di < 0xfff5 );

}
void _stosb() 
{
	WORD _es = es;
	_ASSERT(_reg.flags.bit.dir == 0);
	BYTE* pto = _data.raw;
	if ( es == 0xa000 )
	{
		pto = _video;
	}
	if (es == 0xb800)
	{
		pto = _video;
		es = 0;
	}
	if ( pto == _video )
		_video8set( es*16+di, al );
	else
		pto[es*16+di] = al; 
	di++;
	es = _es;
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
	if ( cx == 0 )
		return;
	_ASSERT(_reg.flags.bit.dir == 0);
	while (cx--) 
		_movsw();
	cx = 0;
}

void _movsw()
{
	WORD _es = es;
	WORD _ds = ds;
	BYTE* pfrom = _data.raw;
	BYTE* pto = _data.raw;
	if (ds >= 0xa000 )
	{
		pfrom = _video;
		ds -= 0xa000;
	}
	if (es >= 0xa000 )
	{
		pto = _video;
		es -= 0xa000;
	}
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
	if ( pfrom == _video || pto == _video )
	{
		_ASSERT(0);
	} else
	{
		pto[es*16 + di] = pfrom[ds*16 + si];
		si++;
		di++;
		pto[es*16 + di] = pfrom[ds*16 + si];
		si++;
		di++;
	}

	ds = _ds;
	es = _es;
}

void _rep_movsb()
{
//	_ASSERT( _videoAddr == 0 );
	if ( cx == 0 )
		return;

	WORD _ds = ds;
	WORD _es = es;
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
	if ( ds >= 0xa000 )
	{
		//ds -= 0xa000;
		pfrom = _video;
		}
	if ( es >= 0xa000 )
	{
		//es -= 0xa000;
		pto = _video;
	}
	if ( pfrom == _video || pto == _video )
	{
		while (cx--) {
			BYTE b;
			if ( pfrom == _video )
				b = _video8get(ds*16 + si);
			else
				b = pfrom[ds*16 + si];
			if ( pto == _video )
				_video8set(es*16 + di, b);
			else
				pto[es*16 + di] = b;
			si+=dir;
			di+=dir;
		}
	} else {

		while (cx--) {
			pto[es*16 + di] = pfrom[ds*16 + si];
			si+=dir;
			di+=dir;
		}
	}
	ds = _ds;
	es = _es;
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

DWORD EgaPixel(int x, int y)
{
	const DWORD pal[] = {
	0x000000, 0x0000b0, 0x00b000, 0x00b0b0, 0xb00000, 0xb000b0, 0xb0b000, 0xb0b0b0,
	0x808080, 0x0000ff, 0x00ff00, 0x00ffff, 0xff0000, 0xff00ff, 0xffff00, 0xffffff};

	BYTE* _video = (BYTE*)EGA.memory;
	DWORD off = (LONG)y * 40L + ((LONG)x / 8L);
	DWORD mem_addr = off;
	int mask = 0x80 >> (x % 8);

	BYTE b = 0;
	/*
	if ( _video[EGA.cfgAddr*0 + off + 0x0000] & mask ) b |= 1;
	if ( _video[EGA.cfgAddr*0 + off + 0x2000] & mask ) b |= 2;
	if ( _video[EGA.cfgAddr*0 + off + 0x4000] & mask ) b |= 4;
	if ( _video[EGA.cfgAddr*0 + off + 0x6000] & mask ) b |= 8;
	*/
	//_ASSERT(EGA.cfgAddr == 0 );
	if ( _video[EGA.cfgAddr*4 + off*4 + 0] & mask ) b |= 1;
	if ( _video[EGA.cfgAddr*4 + off*4 + 1] & mask ) b |= 2;
	if ( _video[EGA.cfgAddr*4 + off*4 + 2] & mask ) b |= 4;
	if ( _video[EGA.cfgAddr*4 + off*4 + 3] & mask ) b |= 8;
	/*
	//0967 1167 1967(press any key, left right y/n) 2167 2967 3167
	b = _data[0x1967 * 0x10 + y*160 + (x>>1)] >> (4-(x&1)*4);
	b &= 0xf;
	*/
	return pal[b];
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
			*pBuffer++ = EgaPixel(x,y);///_cgaPalette[CgaPixel(x, y)];
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
		//printf("l: %04x %04x %04x\n", *(WORD*)&_data[0x9549], *(WORD*)&_data[0x9505], *(WORD*)&_data[0x9505]);
		printf("Stack: ");
		for ( int i=0; i<stat.size(); i++)
			printf("%x ", stat[i]);
		printf("\n");

		DumpStat();

		//*(WORD*)&_data[0x951A], *(WORD*)&_data[0x951B]
		//printf("B:%02x 0:%02x C:%02x A:%02x 3:%02x 8:%02x 9:%02x 1:%02x 4:%02x 2:%02x\n",
		//	_data[0x55b], _data[0x550], _data[0x55c], _data[0x55a], _data[0x583], 
		//	_data[0x698], _data[0x699], _data[0x551], _data[0x584], _data[0x552]);

		//printf("8:%02x e:%02x f:%02x\n", _data[0x698], _data[0x56e], _data[0x56f]);%
		//for ( int i=0x560-4; i<0x580; i++)
		 // printf("%02x ", _data[i]);
		/*
IGNORE(
		printf("x=%04x vx=%02x(%02x) y=%02d g=%02x jump=%02x, ? = %02x\n", 
			*(WORD*)&_data[0x579], _data[0x56E], _data[0x698], _data[0x5E9], _data[0x576], _data[0x699], _data[0x571]);
)*/
		printf(".");

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
{
	/*
	char p1000[53684-0x3c57];
	FILE* f = fopen("C:\\Data\\Devel\\Github\\Work-in-progress\\AlleyCat\\Games\\goose\\GOOSE.EXE", "rb");
	fseek(f, 0x3c57, SEEK_CUR);
	fread(p1000, sizeof(p1000), 1, f); 
	fclose(f);
	
	f = fopen("C:\\Data\\Devel\\Github\\Work-in-progress\\AlleyCat\\Games\\goose\\data", "wb");
	char b6[7] = {0};
	fwrite(b6, sizeof(b6), 1, f);
	fwrite(p1000, sizeof(p1000), 1, f);
	fclose(f);

	return 0;
	*/
	ds = 0;
	memset(_data.raw, 0, 0x20000);
	FILE* f = fopen("C:\\Data\\Devel\\Github\\Work-in-progress\\AlleyCat\\Games\\goose\\data", "rb");
	fread(_data.raw, 0x955d, 1, f); 
	fclose(f);
	///_data.raw[0x1b8a] = 0x33;

	sp = 3000;
	ds = 0x0000;
	/*
	int _pc = 0;
	while ( _pc != -1 )
	{
		_pc = start(_pc);
		tick();
	}*/
	start();
	return 0;
}

#if 0
Bitu readHandler(PhysPt start) {
	vga.latch.d=((Bit32u*)vga.mem.linear)[start];
	switch (vga.config.read_mode) {
	case 0:
		return (vga.latch.b[vga.config.read_map_select]);
	case 1:
		VGA_Latch templatch;
		templatch.d=(vga.latch.d &	FillTable[vga.config.color_dont_care]) ^ FillTable[vga.config.color_compare & vga.config.color_dont_care];
		return (Bit8u)~(templatch.b[0] | templatch.b[1] | templatch.b[2] | templatch.b[3]);
	}
	return 0;
}

INLINE static Bit32u ModeOperation(Bit8u val) {
	Bit32u full;
	switch (vga.config.write_mode) {
	case 0x00:
		// Write Mode 0: In this mode, the host data is first rotated as per the Rotate Count field, then the Enable Set/Reset mechanism selects data from this or the Set/Reset field. Then the selected Logical Operation is performed on the resulting data and the data in the latch register. Then the Bit Mask field is used to select which bits come from the resulting data and which come from the latch register. Finally, only the bit planes enabled by the Memory Plane Write Enable field are written to memory.
		val=((val >> vga.config.data_rotate) | (val << (8-vga.config.data_rotate)));
		full=ExpandTable[val];
		full=(full & vga.config.full_not_enable_set_reset) | vga.config.full_enable_and_set_reset;
		full=RasterOp(full,vga.config.full_bit_mask);
		break;
	case 0x01:
		// Write Mode 1: In this mode, data is transferred directly from the 32 bit latch register to display memory, affected only by the Memory Plane Write Enable field. The host data is not used in this mode.
		full=vga.latch.d;
		break;
	case 0x02:
		//Write Mode 2: In this mode, the bits 3-0 of the host data are replicated across all 8 bits of their respective planes. Then the selected Logical Operation is performed on the resulting data and the data in the latch register. Then the Bit Mask field is used to select which bits come from the resulting data and which come from the latch register. Finally, only the bit planes enabled by the Memory Plane Write Enable field are written to memory.
		full=RasterOp(FillTable[val&0xF],vga.config.full_bit_mask);
		break;
	case 0x03:
		// Write Mode 3: In this mode, the data in the Set/Reset field is used as if the Enable Set/Reset field were set to 1111b. Then the host data is first rotated as per the Rotate Count field, then logical ANDed with the value of the Bit Mask field. The resulting value is used on the data obtained from the Set/Reset field in the same way that the Bit Mask field would ordinarily be used. to select which bits come from the expansion of the Set/Reset field and which come from the latch register. Finally, only the bit planes enabled by the Memory Plane Write Enable field are written to memory.
		val=((val >> vga.config.data_rotate) | (val << (8-vga.config.data_rotate)));
		full=RasterOp(vga.config.full_set_reset,ExpandTable[val] & vga.config.full_bit_mask);
		break;
	default:
		LOG(LOG_VGAMISC,LOG_NORMAL)("VGA:Unsupported write mode %d",vga.config.write_mode);
		full=0;
		break;
	}
	return full;
}


void writeHandler(PhysPt start, Bit8u val) {
	Bit32u data=ModeOperation(val);
	/* Update video memory and the pixel buffer */
	VGA_Latch pixels;
	pixels.d=((Bit32u*)vga.mem.linear)[start];
	pixels.d&=vga.config.full_not_map_mask;
	pixels.d|=(data & vga.config.full_map_mask);
	((Bit32u*)vga.mem.linear)[start]=pixels.d;

	Bit8u * write_pixels=&vga.fastmem[start<<3];

	Bit32u colors0_3, colors4_7;
	VGA_Latch temp;
	temp.d=(pixels.d>>4) & 0x0f0f0f0f;
	colors0_3 =
		Expand16Table[0][temp.b[0]] |
		Expand16Table[1][temp.b[1]] |
		Expand16Table[2][temp.b[2]] |
		Expand16Table[3][temp.b[3]];
	*(Bit32u *)write_pixels=colors0_3;

	temp.d=pixels.d & 0x0f0f0f0f;
	colors4_7 =
		Expand16Table[0][temp.b[0]] |
		Expand16Table[1][temp.b[1]] |
		Expand16Table[2][temp.b[2]] |
		Expand16Table[3][temp.b[3]];
	*(Bit32u *)(write_pixels+4)=colors4_7;
}
#endif