#pragma once
#include "../stdafx.h"
#include <vector>

typedef unsigned short WORD;
typedef unsigned char BYTE;

//namespace emulator
//{
const int SEG_DATA = 0;

extern BYTE memory[];

extern WORD& _ax, &_bx, &_cx, &_dx, _cs, _ds, _es;
extern BYTE& _ah, &_al, &_bh, &_bl, &_ch, &_cl, &_dh, &_dl;
extern WORD _di, _si;
extern WORD _bp, _sp;

struct TFlags
{
	bool zero, carry, direction, interrupt;
	BYTE toByte()
	{
		return zero + carry * 2;
	}

	void fromByte(int x)
	{
		zero = x & 1;
		carry = !!(x & 2);
	}
};

extern TFlags flags;

//void _ASSERT(bool condition);
void nullsub_1();
void nullsub_2();
int ofs(WORD nOffset);
int adr(WORD nSegment, WORD nOffset);
void _push(WORD);
WORD _pop();
void _interrupt(int);
void _out(WORD, BYTE);
void _in(BYTE&, WORD);
void _aaa();
void _pushf();
void _popf();

template <class SRC, class DIR> void _lodsb();
template <class SRC, class DIR> void _lodsw();
template <class DST, class DIR> void _stosw();
template <class DST, class SRC, class DIR> void _rep_movsb();
template <class DST, class DIR> void _rep_stosb();
template <class DST, class SRC, class DIR> void _rep_movsw();
template <class DST, class DIR> void _rep_stosw();

void _Sleep(int);
void _DeadLoop();
void _InfiniteLoop();

void _rcr(WORD&, BYTE);
void _rcr(BYTE&, BYTE);
void _rcl(BYTE&, BYTE);
void _xchg(BYTE&, BYTE&);
void _xchg(WORD&, WORD&);

WORD _videoRead16(WORD, WORD);
void _videoWrite8(WORD, WORD, BYTE);
void Sync();

int _esAssume(int);

	struct MemData
	{
		static void AssertSource()
		{
			_ASSERT(_ds == 0x0000);
		}
		static void AssertTarget()
		{
			_ASSERT(_es == 0x0000);
		}
		static BYTE Get8(WORD nAddr);
		static void Set8(WORD nAddr, BYTE nData);
		static WORD Get16(WORD nAddr);
		static void Set16(WORD nAddr, WORD nData);
	};

	struct MemB800
	{
		static void AssertSource()
		{
			_ASSERT(_ds == 0xb800);
		}
		static void AssertTarget()
		{
			_ASSERT(_es == 0xb800);
		}
		static BYTE Get8(WORD nAddr);
		static void Set8(WORD nAddr, BYTE nData);
		static WORD Get16(WORD nAddr);
		static void Set16(WORD nAddr, WORD nData);
	};

	struct DirForward
	{
		static void Assert()
		{
			_ASSERT(flags.direction==0);
		}
		template<class T>
		static T Move(T& i)
		{
			return i++;
		}
	};

	struct DirBackward
	{
		static void Assert()
		{
			_ASSERT(flags.direction==1);
		}
		template<class T>
		static T Move(T& i)
		{
			return i--;
		}
	};

	struct DirAuto
	{
		static void Assert()
		{
		}
		template<class T>
		static T Move(T& i)
		{
			if (flags.direction)
				return i--;
			else
				return i++;
		}
	};

	template <class DST, class SRC, class DIR> 
	void _rep_movsb()
	{
		_ASSERT(_cx);
		while (_cx--) 
			_movsb<DST, SRC, DIR>();
		_cx = 0;
	}

	template <class DST, class SRC, class DIR> 
	void _movsb()
	{
		SRC::AssertSource();
		DST::AssertTarget();
		DIR::Assert();
		DST::Set8(DIR::Move(_di), SRC::Get8(DIR::Move(_si)));
	}

	template <class DST, class SRC, class DIR> 
	void _rep_movsw()
	{
		Sync();// wtf!!
		_ASSERT(_cx);
		while (_cx--) 
			_movsw<DST, SRC, DIR>();
		_cx = 0;
	}

	template <class DST, class SRC, class DIR> 
	void _movsw()
	{
		SRC::AssertSource();
		DST::AssertTarget();
		DIR::Assert();
		DST::Set8(DIR::Move(_di), SRC::Get8(DIR::Move(_si)));
		DST::Set8(DIR::Move(_di), SRC::Get8(DIR::Move(_si)));
	}

	template <class DST, class DIR> 
	void _rep_stosb()
	{
		_ASSERT(_cx);
		while (_cx--) 
			_stosb<DST, DIR>();
		_cx = 0;
	}

	template <class DST, class DIR> 
	void _stosb()
	{
		DST::AssertTarget();
		DIR::Assert();
		DST::Set8(DIR::Move(_di), _al);
	}

	template <class DST, class DIR> 
	void _rep_stosw()
	{
		if (_cx)
		{
			while (_cx--) 
				_stosw<DST, DIR>();
		}
	}

	template <class DST, class DIR> 
	void _stosw()
	{
		DST::AssertTarget();
		DIR::Assert();
		DST::Set8(DIR::Move(_di), _al);
		DST::Set8(DIR::Move(_di), _ah);
	}
	/*
	template <class SRC, class DIR> 
	void _rep_lodsw()
	{
		_ASSERT(_cx);
		while (_cx--) 
			_lodsw<SRC, DIR>();
		_cx = 0;
	}*/

	template <class SRC, class DIR> 
	void _lodsw()
	{
		SRC::AssertSource();
		DIR::Assert();
		_al = SRC::Get8(DIR::Move(_si));
		_ah = SRC::Get8(DIR::Move(_si));
	}

	template <class SRC, class DIR> 
	void _lodsb()
	{
		SRC::AssertSource();
		DIR::Assert();
		_al = SRC::Get8(DIR::Move(_si));
	}

//}