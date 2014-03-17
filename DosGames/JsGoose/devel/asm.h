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

  WORD ds;
  WORD es;
  WORD si;
  WORD di;
  WORD bp;
  WORD cs;
  WORD sp;
  int ignore;
};

extern treg _reg;
/*
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
*/

#define al 0
#define ah 1
#define bl 2
#define bh 3
#define cl 4
#define ch 5
#define dl 6
#define dh 7
#define ax 0
#define bx 1
#define cx 2
#define dx 3

#define ds _reg.ds
#define es _reg.es
#define si _reg.si
#define di _reg.di
#define bp _reg.bp
#define cs _reg.cs
#define sp _reg.sp

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
void _out(WORD, WORD);
void _in(BYTE&, WORD);
BYTE _in(WORD);
void _xchg(WORD&, WORD&);
void _xchg(BYTE&, BYTE&);
BYTE _rcr(BYTE, BYTE);
WORD _rcr(WORD, BYTE);
BYTE _rcl(BYTE, BYTE);
WORD _rcl(WORD, BYTE);
void _retn(int);

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
void _movsw();
void _cbw();
extern BYTE _video[];
//BYTE _data[]; [0x10000];

#define IGNORE(code) _reg.ignore = 1; code; _reg.ignore = 0;
class CData{
public:
	BYTE raw[0x40000];
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

extern BYTE* r8;
//extern char* r8s;
extern WORD* r16;

// js
#define _data8get(addr) _data[addr]
#define _data8set(addr, val) _data[addr] = val
WORD _data16get(int addr);
void _data16set( int addr, WORD value );
WORD _video16get(int addr);
void _video16set( int addr, WORD value );
BYTE _video8get(int addr);
void _video8set( int addr, BYTE value );
WORD _stack16get(int addr);
void _stack16set( int addr, WORD value );
BYTE _stack8get(int addr);
void _stack8set( int addr, BYTE value );
WORD get_ax();
WORD get_bx();
WORD get_cx();
WORD get_dx();
void set_ax(WORD w);
void set_bx(WORD w);
void set_cx(WORD w);
void set_dx(WORD w);
WORD _pop();

#define decrement_cx() --cx

#define seg_dseg 0
/*
unknown_command(); // var_8		= word ptr -8
  unknown_command(); // var_6		= word ptr -6
  unknown_command(); // var_4		= word ptr -4
  unknown_command(); // var_2		= word ptr -2
  unknown_command(); // arg_0		= word ptr  4
  unknown_command(); // arg_2		= word ptr  6
  */

#define var_A -10
#define var_8 -8
#define var_6 -6
#define var_4 -4
#define var_2 -2
#define arg_0 4
#define arg_2 6
#define arg_4 8
#define arg_6 10
#define arg_8 12
#define arg_A 14

int _ofs(int x);
int _seg(int x);
void _div(BYTE dby);

#define OFS(a) _ofs(a)
#define SEG(a) _seg(a)
#define function void
#define STAT(x)
#define ADR(seg,ofs) (SEG(seg) + OFS(ofs))

#define _sar16(v) (*(short*)&v)>>1

#define STAT(proc) CStat _stat(proc)

class CStat
{
	int current;
public:
	CStat(int proc);
	~CStat();
};