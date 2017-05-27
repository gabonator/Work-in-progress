// asmhost1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "code/app.h"
#include <vector>
#include "ega.h"
#include "dos.h"

using namespace std;

vector<int> m_arrStack;
CDos m_dos;
shared_ptr<CVideoAdapter> m_pVideo;

#include "video.h"

CVideo videoOutput;

#include "timer.h"

CTimer8254 m_Timer;

void Sync()
{
	videoOutput.Tick(m_pVideo);
	
	//memory[4102] = rand()%3;
	BOOL bAny = FALSE;
	//0x6C3 .. 0x6C6
	int keys[] = {'?', VK_UP, VK_RIGHT, VK_DOWN, VK_LEFT, '?', '?', '?', '?', '?', 'Y', 'N', 'K', 'H', 'T', 'A', 'S', 'R', VK_CONTROL, VK_DELETE, 0};
	for (int i=0; keys[i]; i++)
		if ( GetAsyncKeyState(keys[i]) )
		{
			memory[0x6B7+i] = 0x00;
			//memory[0x6BC+i] = 0x00; // Y, N
			bAny = TRUE;
		}
		else
		{
			memory[0x6B7+i] = 0x80;
			//memory[0x6BC+i] = 0x80; // Y, N
		}

	if (bAny)
		memory[0x693]++;

	static LONG lOldTick = 0;
	LONG lTick = GetTickCount();
	if ( lOldTick == 0 )
		lOldTick = lTick;

	if ( lTick - lOldTick > 30)
	{
		// 55f, 564
		//printf("x: %d dx: %d dy: %d\n", memory[0x57C], memory[0x698], memory[0x699]);
		lOldTick = lTick;
	}

}

void StackWrite(int nOffset, WORD nData)
{
	_ASSERT(nOffset/2 >= 0 && nOffset/2 < (int)m_arrStack.size());
	_ASSERT((nOffset&1) == 0);
	m_arrStack[nOffset/2] = nData;
}

WORD StackRead(int nOffset)
{
	_ASSERT(nOffset/2 >= 0 && nOffset/2 < (int)m_arrStack.size());
	_ASSERT((nOffset&1) == 0);
	return m_arrStack[nOffset/2];
}

//namespace emulator
//{
	BYTE memory[512 * 1024];

#pragma pack(push)
#pragma pack(1)
	struct TRegisters8Helper
	{
		BYTE al, ah, bl, bh, cl, ch, dl, dh;
	};
	struct TRegisters16Helper
	{
		WORD ax, bx, cx, dx;
	};
#pragma pack(pop)

	BYTE arrRegistersBuffer[4*2];
	TRegisters8Helper* arrRegisters8 = (TRegisters8Helper*)arrRegistersBuffer;
	TRegisters16Helper* arrRegisters16 = (TRegisters16Helper*)arrRegistersBuffer;

	static_assert(sizeof(TRegisters8Helper) == sizeof(TRegisters16Helper), "error");
	static_assert(sizeof(TRegisters8Helper) == sizeof(arrRegistersBuffer), "error");

	WORD& _ax = arrRegisters16->ax;
	WORD& _bx = arrRegisters16->bx;
	WORD& _cx = arrRegisters16->cx;
	WORD& _dx = arrRegisters16->dx;
	BYTE& _ah = arrRegisters8->ah;
	BYTE& _al = arrRegisters8->al;
	BYTE& _bh = arrRegisters8->bh;
	BYTE& _bl = arrRegisters8->bl;
	BYTE& _ch = arrRegisters8->ch;
	BYTE& _cl = arrRegisters8->cl;
	BYTE& _dh = arrRegisters8->dh;
	BYTE& _dl = arrRegisters8->dl;
	WORD _di, _si, _bp, _sp, _cs, _ds, _es;

	TFlags flags;

#include "dos.cpp"

	void nullsub_1()
	{
		//_ASSERT(0);
	}

	void nullsub_2()
	{
	//	_ASSERT(0);
	}

	int ofs(WORD nOffset)
	{
		return nOffset;
	}

	int adr(WORD nSegment, WORD nOffset)
	{
		_ASSERT( nSegment < 0xa000 );
		return nSegment * 16 + nOffset;
	}

	void _push(WORD data)
	{
		StackWrite(_sp, data);
		_sp -= 2;
	}

	WORD _pop()
	{
		_sp += 2;
		return StackRead(_sp);
	}

	void _interrupt(int i)
	{
		switch (i)
		{
		case 0x11:
			// equipment detection
			_ax = 0xb91e;
			return;

		case 0x12:
			// free mem -> ax
			_ax = 0x1000;
			return;

		case 0x21:
			_ASSERT(0);
			m_dos.Interrupt();
			return;

		case 0x10:
			switch (_ah)
			{
			case 0x00:
				printf("Setting video mode 0x%02x - ", _al);
				switch (_al)
				{
				case 4: 
					printf("320x200 2bpp, CGA Adapter\n");
					m_pVideo.reset(new CCga());
					return;
				case 13: 
					printf("320x200 4bpp, EGA Adapter\n");
					m_pVideo.reset(new CEga());
					return;
				}
				_ASSERT(0);
				printf("Unknown adapter\n");
				return;
			default:
				_ASSERT( m_pVideo );
				if ( m_pVideo->Interrupt(_ah, _al, _bh, _bl ) )
					return;
			}
			break;

		case 0x1a:	
			{
				static DWORD dwTimeBase = 0;
				DWORD dwTime = (WORD)(GetTickCount()*18.2f/1000.0f);

				switch (_ah)
				{
				case 0x00:
					//http://vitaly_filatov.tripod.com/ng/asm/asm_029.1.html
					if ( dwTimeBase == 0 )
						dwTimeBase = dwTime;
					dwTime -= dwTimeBase;
					_cx = dwTime >> 16;
					_dx = dwTime & 0xffff;
					return;

				case 0x01:
					if (_cx == 0 && _dx == 0)
					{
						dwTimeBase = dwTime;
						return;
					}
					break;
				}
			break;
			}

		case 0x33:
			if ( _ah == 0 )
    		{
				_ax = 0xffff;
				_bx = 0x0002;

   				//m_reg.a.r16.ax = 0x0000; // no mouse
   				return;
    		}
		}

		_ASSERT(0);
	}

	void _out(WORD nPort, BYTE nValue)
	{
		if ( nPort >= 0x40 && nPort <= 0x43)
		{
			m_Timer.Out(nPort, nValue);
			// i8254 timer
			return;
		}

		if ( nPort == 0x3d8 || nPort == 0x3d9 )
		{
			// TODO;
			return;
		}

		if ( nPort == 0x61)
		{
			// TODO: sound
			return;
		}

		_ASSERT(0);
	}

	void _in(BYTE& nValue, WORD nPort)
	{
		if ( nPort >= 0x40 && nPort <= 0x43 )
		{
			nValue = m_Timer.In(nPort);
			return;
		}
		if ( nPort == 0x61)
		{
			// TODO: sound
			nValue = 0;
			return;
		}
		if ( nPort == 0x3da )
		{
			// TODO: wait retrace
			//return ( GetTickCount()%20 < 10 ) ? 0 : 8;
			static int counter = 0;
			counter ^= 8;
			Sync();
			nValue = counter;
			return;
		}

		_ASSERT(0);
	}

	void _aaa()
	{
		if ((_al & 0x0F) > 9 /*|| (_ah == 1)*/)
		{
			_al = (_al + 6) & 0x0f;
			_ah ++;
			//af = 1;
			flags.carry = 1;
		} else {
			flags.carry = 0;
			//cf = 0;
			//af = 0;
		}
		_al &= 0x0f;
	}

	void _pushf()
	{
		_push(flags.toByte());
	}

	void _popf()
	{
		flags.fromByte(_pop());
	}
	/*
	void _lodsb()
	{
		_ASSERT(flags.direction == false);
		_al = memory[adr(_ds, _si++)];
	}

	void _lodsw()
	{
		_ASSERT(flags.direction == false);
		_al = memory[adr(_ds, _si++)];
		_ah = memory[adr(_ds, _si++)];
	}

	void _stosw()
	{
		if ( _es >= 0xa000 )
		{
			m_pVideo->Write(_es*16 + _di++, _al);
			m_pVideo->Write(_es*16 + _di++, _ah);
			return;
		}
		
		_ASSERT( _es < 0xa000 );
		memory[adr(_es, _di++)] = _al;
		memory[adr(_es, _di++)] = _ah;
	}

	void _movsb()
	{
		if (_es >= 0xa000 && _ds >= 0xa000)
		{
			m_pVideo->Write(_es*16 + _di, m_pVideo->Read(_ds * 16 + _si));
		} else
		if (_es >= 0xa000 )
		{
			_ASSERT( _ds < 0xA000 );
			m_pVideo->Write(_es*16 + _di, memory[adr(_ds, _si)]);
		} else
		{
			_ASSERT( _es < 0xA000 );
			_ASSERT( _ds < 0xA000 );
			memory[adr(_es, _di)] = memory[adr(_ds, _si)];
		}

		if (flags.direction)
		{
			_di--;
			_si--;
		} else
		{
			_di++;
			_si++;
		}
	}

	void _rep_movsb()
	{
		_ASSERT(_cx);
		while (_cx--) 
			_movsb();
		_cx = 0;
	}

	void _stosb()
	{
		_ASSERT( _es < 0xA000 );
		memory[adr(_es, _di++)] = _al;
	}

	void _rep_stosb()
	{
		_ASSERT(_cx);
		_ASSERT(flags.direction == false);
		while (_cx--) 
			_stosb();
		_cx = 0;
	}
	
	void _movsw()
	{	
		if (_es >= 0xa000 )
		{
			_ASSERT( _ds < 0xA000 );
			m_pVideo->Write(_es*16 + _di++, memory[adr(_ds, _si++)]);
			m_pVideo->Write(_es*16 + _di++, memory[adr(_ds, _si++)]);
			return;
		}

		if (_ds >= 0xa000 )
		{
			_ASSERT( _es < 0xA000 );
			memory[adr(_es, _di++)] = m_pVideo->Read(_ds * 16 + _si++);
			memory[adr(_es, _di++)] = m_pVideo->Read(_ds * 16 + _si++);
			return;
		}

		_ASSERT( _es < 0xA000 );
		_ASSERT( _ds < 0xA000 );
		memory[adr(_es, _di++)] = memory[adr(_ds, _si++)];
		memory[adr(_es, _di++)] = memory[adr(_ds, _si++)];
	}

	void _rep_movsw()
	{
		Sync();

		if (!_cx)
			return;

		_ASSERT(flags.direction == false);
		while (_cx--) 
			_movsw();
		_cx = 0;
	}

	void _rep_stosw()
	{
		if (!_cx)
			return;

		_ASSERT(_cx);
		_ASSERT(flags.direction == false);
		while (_cx--) 
			_stosw();
		_cx = 0;		
	}
	*/

	void _Sleep(int n)
	{
		printf("sleep %d\n", n);
		int f = 9;
		_cx = 0;
	}

	BYTE MemData::Get8(WORD nAddr)
	{
		return memory[nAddr];
	}
	void MemData::Set8(WORD nAddr, BYTE nData)
	{
		memory[nAddr] = nData;
	}
	/*
	WORD MemData::Get16(WORD nAddr)
	{
		return *(WORD*)&memory[nAddr];
	}
	void MemData::Set16(WORD nAddr, WORD nData)
	{
		*(WORD*)&memory[nAddr] = nData;
	}*/

	BYTE MemB800::Get8(WORD nAddr)
	{
		return m_pVideo->Read(0xb800*16 + nAddr);
	}
	void MemB800::Set8(WORD nAddr, BYTE nData)
	{
		m_pVideo->Write(0xb800*16 + nAddr, nData);
	}
	/*
	WORD MemB800::Get16(WORD nAddr)
	{
		return 
			m_pVideo->Read(0xb800*16 + nAddr) |
			(m_pVideo->Read(0xb800*16 + nAddr+1)<<8);
	}
	void MemB800::Set16(WORD nAddr, WORD nData)
	{
		m_pVideo->Write(0xb800*16 + nAddr, nData & 0xff);
		m_pVideo->Write(0xb800*16 + nAddr+1, nData >> 8);
	}
	*/

	void _rcr(WORD& data, BYTE n)
	{
		_ASSERT( n == 1 );
		bool ncf = data & 1;
		data >>= 1;
		if ( flags.carry )
			data |= 0x8000;
		flags.carry = ncf;
	}

	void _rcr(BYTE& data, BYTE n)
	{
		_ASSERT( n == 1 );
		bool ncf = data & 1;
		data >>= 1;
		if ( flags.carry )
			data |= 0x80;
		flags.carry = ncf;
	}

	void _rcl(BYTE& data, BYTE n)
	{
		_ASSERT( n == 1 );
		bool ncf = !!(data & 128);
		data <<= 1;
		if ( flags.carry )
			data |= 1;
		flags.carry = ncf;
	}

	void _xchg(BYTE& a, BYTE& b)
	{
		BYTE t = a;
		a = b;
		b = t;
	}

	void _xchg(WORD& a, WORD& b)
	{
		WORD t = a;
		a = b;
		b = t;
	}

	WORD _videoRead16(WORD seg, WORD ofs)
	{
		WORD l = m_pVideo->Read(seg * 16 + ofs);
		WORD h = m_pVideo->Read(seg * 16 + ofs+1);
		return l | (h << 8);
	}

	void _videoWrite8(WORD seg, WORD ofs, BYTE value)
	{
		m_pVideo->Write(seg*16 + ofs, value);
	}

	void _DeadLoop()
	{
		Sleep(50);
		Sync();
	}
//}

int _tmain(int argc, _TCHAR* argv[])
{
	m_arrStack.resize(32*2, 0);

	_sp = 16*2*2;
	_bp = 0;
	
	FILE* f;
	fopen_s(&f, "C:\\Data\\Devel\\Github\\Work-in-progress\\DosGames\\AlleyCat\\Converted\\datasegment", "rb");
	fread(memory, 28976, 1, f);
	fclose(f);

	videoOutput.Init();

	start();

	return 0;
}

