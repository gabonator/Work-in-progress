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
void _lodsb();
void _lodsw();
void _stosw();
void _rep_movsb();
void _rep_stosb();
void _rep_movsw();
void _rep_stosw();
void _rcr(WORD&, BYTE);
void _rcr(BYTE&, BYTE);
void _rcl(BYTE&, BYTE);
void _xchg(BYTE&, BYTE&);
void _xchg(WORD&, WORD&);

WORD _videoRead16(WORD, WORD);
void _videoWrite8(WORD, WORD, BYTE);
void Sync();
//}