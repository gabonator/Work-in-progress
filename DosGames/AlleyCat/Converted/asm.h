#pragma once
#include <stdio.h>
#include <Windows.h>
#include <crtdbg.h>

typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned long long ULONGLONG;
typedef unsigned char BYTE;
//typedef bool BOOL;
#define FLAG int
#define SEG 16

struct treg {
  struct 
  {
    union {
      WORD r16;
      struct {
        BYTE l;
        BYTE h;
      } r8;
    };
  } a, b, c, d;

  struct {
	  union {
		  struct {
			  FLAG intr:1;
			  FLAG dir:1;
			  FLAG carry:1;
			  FLAG aux:1;
			  FLAG zero:1;
		  } bit;
		  WORD f16;
	  };
  } flags;

  ULONGLONG ds;
  ULONGLONG es;
  ULONGLONG si;
  ULONGLONG di;
  ULONGLONG bp;
  ULONGLONG cs;

};

extern treg _reg;

#define ax _reg.a.r16
#define ah _reg.a.r8.h
#define al _reg.a.r8.l

#define bx _reg.b.r16
#define bh _reg.b.r8.h
#define bl _reg.b.r8.l

#define cx _reg.c.r16
#define ch _reg.c.r8.h
#define cl _reg.c.r8.l

#define dx _reg.d.r16
#define dh _reg.d.r8.h
#define dl _reg.d.r8.l

#define ds _reg.ds
#define es _reg.es
#define si _reg.si
#define di _reg.di
#define bp _reg.bp
#define cs _reg.cs

#define _cli() _reg.flags.bit.intr = 0
#define _sti() _reg.flags.bit.intr = 1
#define _cld() _reg.flags.bit.dir = 0
#define _std() _reg.flags.bit.dir = 1
#define _clc() _reg.flags.bit.carry = 0
#define _stc() _reg.flags.bit.carry = 1
#define af _reg.flags.bit.aux
#define cf _reg.flags.bit.carry
#define zf _reg.flags.bit.zero

#define unknown_condition() _unknown_condition()
#define unknown_command() _unknown_condition()
#define fix_code() _unknown_condition()

int _unknown_condition();
void _int(BYTE);
void _push(WORD);
void _pop(WORD& i);
void _push(ULONGLONG);
void _pop(ULONGLONG& i);
void _out(WORD, BYTE);
void _in(BYTE&, WORD);
void _xchg(WORD&, WORD&);
void _xchg(BYTE&, BYTE&);
void _rcr(BYTE&, BYTE);
void _rcr(WORD&, BYTE);
void _rcl(BYTE&, BYTE);
void _rcl(WORD&, BYTE);

void _lahf();
void _sahf();

void _aaa();
void _pushf();
void _popf();
void _rep_stosw();
void _rep_stosb();
void _lodsw(); 
void _stosw();
void _rep_movsw();
void _rep_movsb();
void _repne_scasb();
void _lodsb();
extern BYTE _video[];
//BYTE _data[]; [0x10000];

class CData{
public:
	BYTE raw[0x10000];
	BYTE& operator[] (ULONGLONG i);
//	{
//		_ASSERT( i >= 0 && i < 0xb000 );
//		return *(raw+i);
//	}
};

extern CData _data;
//char asc_18784[12];

void nullsub_1();
void nullsub_2();

int _wKey();
void tick();

const int seg_data = 0;